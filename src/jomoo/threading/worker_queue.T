#ifndef JOMOO_WORKER_QUEUE_TEMPL
#define JOMOO_WORKER_QUEUE_TEMPL


#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#ifdef JOMOO_MT

#include "JOMOO_Thread.h"
#include "Base/Exception.hpp"
#include "Base/get_last_error.h"

#ifdef _MEMORY_DEBUG
#undef THIS_FILE
#define new	   DEBUG_NEW  
#define malloc DEBUG_MALLOC  
static char THIS_FILE[] = __FILE__;  
#endif // _MEMORY_DEBUG

_thread_begin

_thread_end


#endif // JOMOO_MT

#endif // JOMOO_WORKER_QUEUE_TEMPL