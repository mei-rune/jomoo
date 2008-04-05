

#ifndef _config_Threading_H
#define _config_Threading_H


#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#define _thread_begin _jomoo_begin
#define _thread_end _jomoo_end
#define _jomoo_thread _jomoo

#ifdef JOMOO_MT
#define JOMOO_MUTEX_MUTABLE( x ) mutable mutex x
#define JOMOO_MUTEX( x ) mutex x
#define JOMOO_MUTEX_STATIC( x ) static mutex x
#define JOMOO_GUARD(  g, l )	mutex::spcode_lock g( l )
#define JOMOO_GUARD_THROW(  g, l , t )	mutex::spcode_lock g( l , false , true ) ; if( !g.locked() ) ThrowException1( RuntimeException, t )
#define JOMOO_GUARD_RETURN(  g, l , r) mutex::spcode_lock g( l, false ); if( !g.locked() ) return r
#define JOMOO_GUARD_RETURN_VOID( g, l ) mutex::spcode_lock g( l, false ); if( !g.locked() ) return
#else
#define JOMOO_MUTEX_MUTABLE( x )
#define JOMOO_MUTEX( x ) 
#define JOMOO_MUTEX_STATIC( x )
#define JOMOO_GUARD(  g, l )	
#define JOMOO_GUARD_THROW(  g, l , t )	
#define JOMOO_GUARD_RETURN( g, l , r) 
#define JOMOO_GUARD_RETURN_VOID( g, l ) 
#endif

#endif // 