

#ifndef JOMOO_SYNCH_TRAITS_H
#define JOMOO_SYNCH_TRAITS_H

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#ifdef JOMOO_MT

#include "thread_mutex.h"
#include "thread_semaphore.h"
#include "thread.h"
#include "thread_manager.h"

_jomoo_begin

typedef thread_mutex mutex;
typedef thread_semaphore semaphore;

_jomoo_end

#else

#include "null_mutex.h"
#include "null_semaphore.h"

_jomoo_begin

typedef null_mutex mutex;
typedef null_semaphore semaphore;

_jomoo_end

#endif //JOMOO_MT

#endif //SYNCH_TRAITS_H