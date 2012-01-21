//----------------------------------------------------------
//
//   SA:MP Multiplayer Modification For GTA:SA
//   Copyright 2004-2007 SA:MP Team
//
//----------------------------------------------------------

//	Python plugin for SAMP
//	Copyright (C) 2010-2012 Fabsch
//
//	This program is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "pythonplugin.h"
#include "constants.h"
#include "nativefunctions.h"
#include "pysamp.h"

//----------------------------------------------------------

logprintf_t logprintf;
AMX *m_AMX;
void **ppPluginData;
extern void *pAMXFunctions;
TID_TYPE m_pyMainThread = NULL;

std::deque<timer_data> m_TimerList; // TODO: deque or vector?
std::queue<invoke_data> m_InvokeQueue;

Mutex *m_MainLock;

//----------------------------------------------------------

char *_getString(AMX *amx, cell params)
{
	char *res;
	cell *addr;
	
	int len;
	amx_GetAddr(amx, params, &addr);
	amx_StrLen(addr, &len);

	res = new char[++len];
	amx_GetString(res, addr, 0, len);
	return res;
}

//----------------------------------------------------------
// The Support() function indicates what possibilities this
// plugin has. The SUPPORTS_VERSION flag is required to check
// for compatibility with the server. 

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() 
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick()
{
	static unsigned long long lasttickcount = GetTickCount();
	unsigned long long curtickcount = GetTickCount();

	// timers and function invokes
	if (curtickcount > lasttickcount) // prevent check if GetTickCount value hasn't changed
	{
		m_MainLock->Lock();
		if (!m_TimerList.empty())
		{
			for (std::deque<timer_data>::iterator i = m_TimerList.begin(); i != m_TimerList.end(); i++)
			{
				if ((i->lasttick + i->interval) <= curtickcount)
				{
					// this timer has to tick
					// we need to store this somewhere else, because timers might be set/killed in here
					timer_data tmp = (timer_data)*i;

					if (!i->repeating)
					{
						// remove it from the list
						m_TimerList.erase(i);
					}
					else
					{
						i->lasttick = curtickcount;
					}

					m_MainLock->Unlock(); // maybe this timer calls SetTimer or KillTimer, which also locks that mutex
					PyEnsureGIL;
					_pyCallObject(tmp.func, tmp.params);

					if (!tmp.repeating) // here we can free memory used by the timer
					{
						Py_DECREF(tmp.func);
						Py_XDECREF(tmp.params);
					}
					PyReleaseGIL;
					m_MainLock->Lock();
					break;
				}
			}
		}
		if (!m_InvokeQueue.empty())
		{
			invoke_data inv = m_InvokeQueue.front();
			m_InvokeQueue.pop();

			m_MainLock->Unlock();
			PyEnsureGIL;
			_pyCallObject(inv.func, inv.params);

			Py_DECREF(inv.func);
			Py_XDECREF(inv.params);
			PyReleaseGIL;
		}
		m_MainLock->Unlock();
		lasttickcount = curtickcount;
	}
}

//----------------------------------------------------------
// The Load() function gets passed on exported functions from
// the SA-MP Server, like the AMX Functions and logprintf().
// Should return true if loading the plugin has succeeded.

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];

	m_MainLock = new Mutex(); // initialize main mutex

	// workaround for missing Python symbols in Python C modules
	#ifndef WIN32
		// load the Python library (version taken from includes) with RTLD_GLOBAL
		char *libname = (char*)malloc(20);
		snprintf(libname, 20, "libpython%d.%d.so.1.0", PY_MAJOR_VERSION, PY_MINOR_VERSION);
		//void *h = dlopen("libpython" PY_MAJOR_VERSION "." PY_MINOR_VERSION ".so.1", RTLD_LAZY | RTLD_GLOBAL); // TODO: maybe find out, how to concat strings and ints
		void *h = dlopen(libname, RTLD_LAZY | RTLD_GLOBAL);
		if (!h) printf("%s\n", dlerror());
		free(libname);
	#endif

	logprintf("\tPython plugin loaded");
	return true;
}

//----------------------------------------------------------
// The Unload() function is called when the server shuts down,
// meaning this plugin gets shut down with it.

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	delete m_MainLock;

	logprintf("\tPython plugin unloaded");
}

//----------------------------------------------------------
// This is the sourcecode of the HelloWorld pawn native that we
// will be adding. "amx" is a pointer to the AMX-instance that's
// calling the function (e.g. a filterscript) and "params" is
// an array to the passed parameters. The first entry (params[0])
// is equal to  4 * PassedParameters, e.g. 16 for 4 parameters.


// Loads a specific python script
static cell AMX_NATIVE_CALL n_LoadPython(AMX* amx, cell* params)
{
	if (params[0] == 0) return 0;

	char *str = _getString(amx, params[1]);
	
	if (!m_pyInited)
	{
		_initAMX(amx);
		#if ENABLE_MULTITHREAD
			#ifdef _WIN32
				m_pyMainThread = CreateThread(NULL, 0, _pyInit, NULL, 0, NULL);
			#else
				pthread_t tid;
				m_pyMainThread = pthread_create(&tid, NULL, _pyInit, NULL);
			#endif

			// wait for the Python main thread to initialize Python
			while (!Py_IsInitialized()) sleep(1);
		#else
			_pyInit();
		#endif
	}
	// wait until the Python main thread has completely initialized
	m_MainLock->Lock();
	m_MainLock->Unlock(); // and unlock it

	PyEnsureGIL;
	cell ret = _pyLoadModule(str);
	PyReleaseGIL;
	_del(str);
	return ret;
}
// Unloads a specific python script
static cell AMX_NATIVE_CALL n_UnloadPython( AMX* amx, cell* params )
{
	PyEnsureGIL;
	// call exit functions
	_pyCallAll("OnPyExit");

	#if ENABLE_MULTITHREAD
		// set the exit_listener event in the samp module to let the Python main thread exit
		PyRun_SimpleString("import samp\nsamp.exit_listener.set()");
		PyReleaseGIL;
		// wait for Python's main thread to terminate
		#ifdef _WIN32
			WaitForSingleObject(m_pyMainThread, INFINITE);
		#else
			pthread_join(m_pyMainThread, NULL);
		#endif
	#else
		_pyExit();
	#endif
	return 0;
}

// And an array containing the native function-names and the functions
// specified with them, e.g. HelloWorld -> n_HelloWorld in this example.
AMX_NATIVE_INFO HelloWorldNatives[ ] =
{
	{ "LoadPython",			n_LoadPython },
	{ "UnloadPython",		n_UnloadPython },
	// Callbacks
	//{ "pyOnTimerTick", n_OnTimerTick },
	{ "pyOnDialogResponse",	n_OnDialogResponse },
	{ "pyOnEnterExitModShop", n_OnEnterExitModShop },
	{ "pyOnObjectMoved", n_OnObjectMoved },
	{ "pyOnPlayerClickPlayer", n_OnPlayerClickPlayer },
	{ "pyOnPlayerCommandText", n_OnPlayerCommandText },
	{ "pyOnPlayerConnect", n_OnPlayerConnect },
	{ "pyOnPlayerDeath", n_OnPlayerDeath },
	{ "pyOnPlayerDisconnect", n_OnPlayerDisconnect },
	{ "pyOnPlayerEnterCheckpoint", n_OnPlayerEnterCheckpoint },
	{ "pyOnPlayerEnterRCheckpoint", n_OnPlayerEnterRaceCheckpoint },
	{ "pyOnPlayerEnterVehicle", n_OnPlayerEnterVehicle },
	{ "pyOnPlayerExitedMenu", n_OnPlayerExitedMenu },
	{ "pyOnPlayerExitVehicle", n_OnPlayerExitVehicle },
	{ "pyOnPlayerInteriorChange", n_OnPlayerInteriorChange },
	{ "pyOnPlayerKeyStateChange", n_OnPlayerKeyStateChange },
	{ "pyOnPlayerLeaveCheckpoint", n_OnPlayerLeaveCheckpoint },
	{ "pyOnPlayerLeaveRCheckpoint", n_OnPlayerLeaveRaceCheckpoint },
	{ "pyOnPlayerObjectMoved", n_OnPlayerObjectMoved },
	{ "pyOnPlayerPickUpPickup", n_OnPlayerPickUpPickup },
	{ "pyOnPlayerRequestClass", n_OnPlayerRequestClass },
	{ "pyOnPlayerRequestSpawn", n_OnPlayerRequestSpawn },
	{ "pyOnPlayerSelectedMenuRow", n_OnPlayerSelectedMenuRow },
	{ "pyOnPlayerSpawn", n_OnPlayerSpawn },
	{ "pyOnPlayerStateChange", n_OnPlayerStateChange },
	{ "pyOnPlayerStreamIn", n_OnPlayerStreamIn },
	{ "pyOnPlayerStreamOut", n_OnPlayerStreamOut },
	{ "pyOnPlayerText", n_OnPlayerText },
	{ "pyOnPlayerUpdate", n_OnPlayerUpdate },
	{ "pyOnRconCommand", n_OnRconCommand },
	{ "pyOnRconLoginAttempt", n_OnRconLoginAttempt },
	{ "pyOnVehicleDamageStatusUpdate", n_OnVehicleDamageStatusUpdate },
	{ "pyOnVehicleDeath", n_OnVehicleDeath },
	{ "pyOnVehicleMod", n_OnVehicleMod },
	{ "pyOnVehiclePaintjob", n_OnVehiclePaintjob },
	{ "pyOnVehicleRespray", n_OnVehicleRespray },
	{ "pyOnVehicleSpawn", n_OnVehicleSpawn },
	{ "pyOnVehicleStreamIn", n_OnVehicleStreamIn },
	{ "pyOnVehicleStreamOut", n_OnVehicleStreamOut },
	{ "pyOnUnoccupiedVehicleUpdate", n_OnUnoccupiedVehicleUpdate },
	{ "pyOnPlayerTakeDamage", n_OnPlayerTakeDamage },
	{ "pyOnPlayerGiveDamage", n_OnPlayerGiveDamage },
	{ "pyOnPlayerClickMap", n_OnPlayerClickMap },
	{ 0,					0 }
};

//----------------------------------------------------------
// The AmxLoad() function gets called when a new gamemode or
// filterscript gets loaded with the server. In here we register
// the native functions we like to add to the scripts.

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad( AMX *amx ) 
{
	// DONE: move to LoadPython function, as it would also load in filterscripts here
	//_initAMX(amx);

	return amx_Register( amx, HelloWorldNatives, -1 );
}

//----------------------------------------------------------
// When a gamemode is over or a filterscript gets unloaded, this
// function gets called. No special actions needed in here.

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload( AMX *amx ) 
{
	return AMX_ERR_NONE;
}



#ifndef _WIN32
	unsigned long long GetTickCount()
	{
		struct timeval tv;
		if(gettimeofday(&tv, NULL) != 0) return 0;

		return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	}
#endif