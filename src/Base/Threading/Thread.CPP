

#ifndef JOMOO_THREAD_CPP
#define JOMOO_THREAD_CPP


#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "config_threading.h"

#ifdef JOMOO_MT

_thread_begin

#ifndef JOMOO_INLINE_FUNCTIONS

#include "Thread.inl"

#endif // OS_HAS_INLINED

_thread_end

#endif // JOMOO_MT

#endif /* JOMOO_THREAD_CPP */
