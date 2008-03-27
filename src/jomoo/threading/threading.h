

#ifndef JOMOO_SYNCH_TRAITS_H
#define JOMOO_SYNCH_TRAITS_H

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "Null_Mutex.h"
#include "Null_Semaphore.h"

#ifdef JOMOO_MT

#include "Thread_Mutex.h"
#include "Thread_Semaphore.h"
#include "Base_Thread.H"
#include "Base_Thread_Manager.H"


_jomoo_begin

typedef thread_mutex mutex;
typedef thread_semaphore semaphore;

_jomoo_end

#define JOMOO_MUTEX_MUTABLE( x ) mutable mutex x

#define JOMOO_MUTEX( x ) JOMOO_Mutex x

#define JOMOO_MUTEX_STATIC( x ) static mutex x

#define JOMOO_GUARD(  g, l )	mutex::spcode_lock g( l )

#define JOMOO_GUARD_THROW(  g, l , t )	mutex::spcode_lock g( l , false , true ) ; if( !g.locked() ) ThrowException1( RuntimeException, t )

#define JOMOO_GUARD_RETURN(  g, l , r) mutex::spcode_lock g( l, false ); if( !g.locked() ) return r

#define JOMOO_GUARD_RETURN_VOID( g, l ) mutex::spcode_lock g( l, false ); if( !g.locked() ) return

#else

_jomoo_begin

typedef null_mutex mutex;
typedef null_semaphore semaphore;

_jomoo_end

#define JOMOO_MUTEX_MUTABLE( x )

#define JOMOO_MUTEX( x ) 

#define JOMOO_MUTEX_STATIC( x )

#define JOMOO_GUARD(  g, l )	

#define JOMOO_GUARD_THROW(  g, l , t )	

#define JOMOO_GUARD_RETURN( g, l , r) 

#define JOMOO_GUARD_RETURN_VOID( g, l ) 

#endif //JOMOO_MT

#endif //SYNCH_TRAITS_H