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
#include "pysamp.h"

Mutex::Mutex()
{
#if !ENABLE_MULTITHREAD
	return;
#endif

	// create mutex
#ifdef _WIN32
	m_Mutex = CreateMutex(NULL, FALSE, NULL);
#else
	m_Mutex = PTHREAD_MUTEX_INITIALIZER;
#endif
}
Mutex::~Mutex()
{
#if !ENABLE_MULTITHREAD
	return;
#endif

	// close mutex
#ifdef _WIN32
	CloseHandle(m_Mutex);
#else
	pthread_mutex_destroy(&m_Mutex);
#endif
}

void Mutex::Lock()
{
#if !ENABLE_MULTITHREAD
	return;
#endif

	// lock
#ifdef _WIN32
	WaitForSingleObject(m_Mutex, INFINITE);
#else
	pthread_mutex_lock(&m_Mutex);
#endif
}
void Mutex::Unlock()
{
#if !ENABLE_MULTITHREAD
	return;
#endif

	// unlock
#ifdef _WIN32
	ReleaseMutex(m_Mutex);
#else
	pthread_mutex_unlock(&m_Mutex);
#endif
}