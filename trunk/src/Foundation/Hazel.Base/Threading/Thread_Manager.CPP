
#ifndef Hazel_THREAD_MANAGER_CPP
#define Hazel_THREAD_MANAGER_CPP

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

#include "config_threading.h"

#ifdef Hazel_MT

_thread_begin

#ifndef OS_HAS_INLINED

#include "Hazel_Thread_Manager.inl"

#endif // OS_HAS_INLINED

_thread_end

#endif // Hazel_MT

#endif // Hazel_THREAD_MANAGER_CPP