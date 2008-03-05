

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


_JOMOO_begin

typedef JOMOO_Thread_Mutex JOMOO_Mutex;
typedef JOMOO_Thread_Semaphore JOMOO_Semaphore;
_JOMOO_end

#define JOMOO_MUTEX_MUTABLE( x ) mutable JOMOO_Mutex x

#define JOMOO_MUTEX( x ) JOMOO_Mutex x

#define JOMOO_MUTEX_STATIC( x ) static JOMOO_Mutex x

#define JOMOO_GUARD(  g, l )	JOMOO_Mutex::spcode_lock g( l )

#define JOMOO_GUARD_THROW(  g, l , t )	JOMOO_Mutex::spcode_lock g( l , false , true ) ; if( !g.locked() ) ThrowException1( RuntimeException, t )

#define JOMOO_GUARD_RETURN(  g, l , r) JOMOO_Mutex::spcode_lock g( l, false ); if( !g.locked() ) return r

#define JOMOO_GUARD_RETURN_VOID( g, l ) JOMOO_Mutex::spcode_lock g( l, false ); if( !g.locked() ) return

#else

_JOMOO_begin

typedef JOMOO_Null_Mutex JOMOO_Mutex;
typedef JOMOO_Null_Semaphore JOMOO_Semaphore;

_JOMOO_end

#define JOMOO_MUTEX_MUTABLE( x )

#define JOMOO_MUTEX( x ) 

#define JOMOO_MUTEX_STATIC( x )

#define JOMOO_GUARD(  g, l )	

#define JOMOO_GUARD_THROW(  g, l , t )	

#define JOMOO_GUARD_RETURN( g, l , r) 

#define JOMOO_GUARD_RETURN_VOID( g, l ) 

#endif //JOMOO_MT

namespace Threading
{
	typedef _hazel JOMOO_Mutex MUTEX;
	typedef _hazel JOMOO_Semaphore SEMAPHORE;
}

#endif //SYNCH_TRAITS_H