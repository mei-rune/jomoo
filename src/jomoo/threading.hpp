

#ifndef _threading_hpp_
#define _threading_hpp_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#ifdef JOMOO_MT

#include "threading/thread.h"
#include "threading/thread_manager.h"
#include "threading/thread_mutex.h"
#include "threading/thread_semaphore.h"
#include "threading/event.h"

_thread_begin

typedef thread_mutex mutex;
typedef thread_semaphore semaphore;

_thread_end

#else

#include "null_mutex.h"
#include "null_semaphore.h"

_thread_begin

typedef null_mutex mutex;
typedef null_semaphore semaphore;

_thread_end

#endif //JOMOO_MT

#endif //_threading_hpp_