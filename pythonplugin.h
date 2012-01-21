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

#ifndef __pythonplugin_h_
#define __pythonplugin_h_

#include <deque>
#include <queue>

// include Python header; prevent it from using its debug library
#ifdef _DEBUG
	#undef _DEBUG
	#include "Python.h"
	#define _DEBUG
#else
	#include "Python.h"
#endif


#include "./SDK/amx/amx.h"
#include "./SDK/plugincommon.h"

#ifdef _WIN32
	#include <Windows.h>
#else
	#include <sys/time.h>
	#include <pthread.h>
#endif

#include "mutex.h"


typedef void (*logprintf_t)(char* format, ...);
extern logprintf_t logprintf;

typedef int (*amx_function_t)(AMX *amx, cell *params);

extern AMX *m_AMX;

struct invoke_data
{
	PyObject *func;
	PyObject *params;
};
struct timer_data
{
	long id;
	PyObject *func;
	PyObject *params;
	int interval;
	bool repeating;
	unsigned long long lasttick;
};

extern std::deque<timer_data> m_TimerList;
extern std::queue<invoke_data> m_InvokeQueue;
extern Mutex *m_MainLock;

#ifdef _WIN32
	#define GetTickCount		GetTickCount64
	#define sleep				Sleep
	
	#define THREAD_RETURN		DWORD WINAPI
	#define TID_TYPE			HANDLE
#else
	unsigned long long GetTickCount();

	#define THREAD_RETURN		void *
	#define TID_TYPE			int
#endif

#endif