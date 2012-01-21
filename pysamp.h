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

#define ENABLE_MULTITHREAD	1

#if ENABLE_MULTITHREAD
	#define PyEnsureGIL			PyGILState_STATE gstate = PyGILState_Ensure()
	#define PyReleaseGIL		PyGILState_Release(gstate)
#else
	#define PyEnsureGIL
	#define PyReleaseGIL
#endif

extern PyMethodDef _pySampMethods[];
extern bool m_pyInited;

PyObject *_pyCallObject(PyObject *func, PyObject *params);
PyObject *_pyCallFunc(PyObject *module, const char *funcname, PyObject *args=NULL);
cell _pyCallAll(const char *funcname, PyObject *args=NULL, int nondefval=0, int defval=1);

#if ENABLE_MULTITHREAD
	THREAD_RETURN _pyInit(void *prm);
#else
	void _pyInit();
#endif

int _pyLoadModule(char *pyscript);
void _pyExit();
void _pyInitMacros(PyObject *module);

void clearTimerData(std::deque<timer_data>::iterator x);
short firstFreeTimerID();