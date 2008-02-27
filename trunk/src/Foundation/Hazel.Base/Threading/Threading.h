

#ifndef Hazel_SYNCH_TRAITS_H
#define Hazel_SYNCH_TRAITS_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

#include "Null_Mutex.h"
#include "Null_Semaphore.h"

#ifdef Hazel_MT

#include "Thread_Mutex.h"
#include "Thread_Semaphore.h"
#include "Base_Thread.H"
#include "Base_Thread_Manager.H"


_hazel_begin

typedef Hazel_Thread_Mutex Hazel_Mutex;
typedef Hazel_Thread_Semaphore Hazel_Semaphore;
_hazel_end

#define Hazel_MUTEX_MUTABLE( x ) mutable Hazel_Mutex x

#define Hazel_MUTEX( x ) Hazel_Mutex x

#define Hazel_MUTEX_STATIC( x ) static Hazel_Mutex x

#define Hazel_GUARD(  g, l )	Hazel_Mutex::spcode_lock g( l )

#define Hazel_GUARD_THROW(  g, l , t )	Hazel_Mutex::spcode_lock g( l , false , true ) ; if( !g.locked() ) ThrowException1( RuntimeException, t )

#define Hazel_GUARD_RETURN(  g, l , r) Hazel_Mutex::spcode_lock g( l, false ); if( !g.locked() ) return r

#define Hazel_GUARD_RETURN_VOID( g, l ) Hazel_Mutex::spcode_lock g( l, false ); if( !g.locked() ) return

#else

_hazel_begin

typedef Hazel_Null_Mutex Hazel_Mutex;
typedef Hazel_Null_Semaphore Hazel_Semaphore;

_hazel_end

#define Hazel_MUTEX_MUTABLE( x )

#define Hazel_MUTEX( x ) 

#define Hazel_MUTEX_STATIC( x )

#define Hazel_GUARD(  g, l )	

#define Hazel_GUARD_THROW(  g, l , t )	

#define Hazel_GUARD_RETURN( g, l , r) 

#define Hazel_GUARD_RETURN_VOID( g, l ) 

#endif //Hazel_MT

namespace Threading
{
	typedef _hazel Hazel_Mutex MUTEX;
	typedef _hazel Hazel_Semaphore SEMAPHORE;
}

#endif //SYNCH_TRAITS_H