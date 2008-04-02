

#ifndef JOMOO_WORKER_QUEUE_H
#define JOMOO_WORKER_QUEUE_H


#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "config_threading.h"

#ifdef JOMOO_MT


_thread_begin

_thread_end

#endif // JOMOO_MT

#endif /* JOMOO_WORKER_QUEUE_H */
