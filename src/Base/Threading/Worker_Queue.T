#ifndef Hazel_WORKER_QUEUE_TEMPL
#define Hazel_WORKER_QUEUE_TEMPL


#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

#ifdef Hazel_MT

#include "Hazel_Thread.h"
#include "Hazel.Base/Exception.hpp"
#include "Hazel.Base/get_last_error.h"

#ifdef _MEMORY_DEBUG
#undef THIS_FILE
#define new	   DEBUG_NEW  
#define malloc DEBUG_MALLOC  
static char THIS_FILE[] = __FILE__;  
#endif // _MEMORY_DEBUG

_thread_begin

_thread_end


#endif // Hazel_MT

#endif // Hazel_WORKER_QUEUE_TEMPL