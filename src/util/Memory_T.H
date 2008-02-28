


/**
* -*- C++ -*-
* -------------------------------------------------------------------------------
* - ¡è¨q¡Ð¨r ¨q¡Ð¨r					         Memory_T.H,v 1.0 2005/03/25 10:52:54
*  ¨u¨¨€¨€¨Ž ¨q¨q ¡Ð¨r
* ¦òÌï¦òÌïÌï| ¨t------
* -------------------------------------------------------------------------------
*/

#ifndef __Memory_T_H_
#define __Memory_T_H_


#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include "BT_SPL.H"


#define NEW_T_DEFINE( mem ) 	if( memory == 0 )									\
		memory = g_Server_Core->get_Memory_Manager();								\
																					\
	Memory_Guard mem( memory, memory->malloc( sizeof( T ) ) , file , line );		\
	if( mem.empty() )																\
		return 0;

template< typename T >
T* New_T( BT_Memory_Base* memory = 0 , const char* file=NULL, int line=-1 )
{
	NEW_T_DEFINE( mem );
	T* ptr = new mem.get() T( );
	mem.release();
	return ptr;
}

template< typename T >
void Free_T( T* t,BT_Memory_Base* memory = 0 )
{
	if ( t != 0 )
	{
		if( memory == 0 )
			memory = g_Server_Core->get_Memory_Manager();

		( t )->~T();
		memory->free( t );
	}
}

template< typename T ,typename P >
T* New_T( P p , BT_Memory_Base* memory = 0 , const char* file=NULL, int line=-1 )
{
	NEW_T_DEFINE( mem );
	T* ptr = new ( mem.get() ) T( p );
	mem.release();
	return ptr;
}

template< typename T ,typename P1,typename P >
T* New_T( P1 p1,P p,BT_Memory_Base* memory = 0 , const char* file=NULL, int line=-1 )
{
	NEW_T_DEFINE( mem );
	T* ptr = new ( mem.get() ) T( p1,p );
	mem.release();
	return ptr;
}

template< typename T ,typename P1,typename P2,typename P >
T* New_T( P1 p1,P2 p2,P p,BT_Memory_Base* memory = 0 , const char* file=NULL, int line=-1 )
{
	NEW_T_DEFINE( mem );
	T* ptr = new ( mem.get() ) T( p1,p2,p );
	mem.release();
	return ptr;
}

template< typename T ,typename P1,typename P2,typename P3,typename P >
T* New_T( P1 p1,P2 p2,P3 p3,P p,BT_Memory_Base* memory = 0 , const char* file=NULL, int line=-1 )
{
	NEW_T_DEFINE( mem );
	T* ptr = new ( mem.get() ) T( p1,p2,p3,p );
	mem.release();
	return ptr;
}

template< typename T ,typename P1,typename P2,typename P3,typename P4,typename P >
T* New_T( P1 p1,P2 p2,P3 p3,P4 p4,P p,BT_Memory_Base* memory = 0 , const char* file=NULL, int line=-1 )
{
	NEW_T_DEFINE( mem );
	T* ptr = new ( mem.get() ) T( p1,p2,p3,p4,p );
	mem.release();
	return ptr;
}

template< typename T ,typename P1,typename P2,typename P3,typename P4,typename P5,typename P >
T* New_T( P1 p1,P2 p2,P3 p3,P4 p4,P5 p5,P p,BT_Memory_Base* memory = 0 , const char* file=NULL, int line=-1 )
{
	NEW_T_DEFINE( mem );
	T* ptr = new ( mem.get() ) T( p1,p2,p3,p4,p5,p );
	mem.release();
	return ptr;
}

template< typename T ,typename P1,typename P2,typename P3,typename P4,typename P5,typename P6,typename P >
T* New_T( P1 p1,P2 p2,P3 p3,P4 p4,P5 p5,P6 p6,P p, BT_Memory_Base* memory = 0 , const char* file=NULL, int line=-1 )
{
	NEW_T_DEFINE( mem );
	T* ptr = new ( mem.get() ) T( p1,p2,p3,p4,p5,p6,p );
	mem.release();
	return ptr;
}

template< typename T ,typename P1,typename P2,typename P3,typename P4,typename P5,typename P6,typename P7,typename P >
T* New_T( P1 p1,P2 p2,P3 p3,P4 p4,P5 p5,P6 p6,P7 p7,P p, BT_Memory_Base* memory = 0 , const char* file=NULL, int line=-1 )
{
	NEW_T_DEFINE( mem );
	T* ptr = new ( mem.get() ) T( p1,p2,p3,p4,p5,p6,p7,p );
	mem.release();
	return ptr;
}

template< typename T ,typename P1,typename P2,typename P3,typename P4,typename P5,typename P6,typename P7,typename P8,typename P >
T* New_T( P1 p1,P2 p2,P3 p3,P4 p4,P5 p5,P6 p6,P7 p7,P8 p8,P p, BT_Memory_Base* memory = 0 , const char* file=NULL, int line=-1 )
{
	NEW_T_DEFINE( mem );
	T* ptr = new ( mem.get() ) T( p1,p2,p3,p4,p5,p6,p7,p8,p );
	mem.release();
	return ptr;
}

template< typename T ,typename P1,typename P2,typename P3,typename P4,typename P5,typename P6,typename P7,typename P8,typename P9,typename P >
T* New_T( P1 p1,P2 p2,P3 p3,P4 p4,P5 p5,P6 p6,P7 p7,P8 p8,P9 p9,P p, BT_Memory_Base* memory = 0 , const char* file=NULL, int line=-1 )
{
	NEW_T_DEFINE( mem );
	T* ptr = new ( mem.get() ) T( p1,p2,p3,p4,p5,p6,p7,p8,p9,p );
	mem.release();
	return ptr;
}

template< typename T ,typename P1,typename P2,typename P3,typename P4,typename P5,typename P6,typename P7,typename P8,typename P9,typename P10,typename P >
T* New_T( P1 p1,P2 p2,P3 p3,P4 p4,P5 p5,P6 p6,P7 p7,P8 p8,P9 p9,P10 p10,P p ,BT_Memory_Base* memory = 0 , const char* file=NULL, int line=-1 )
{
	NEW_T_DEFINE( mem );
	T* ptr = new ( mem.get() ) T( p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p );
	mem.release();
	return ptr;
}

#endif // __Memory_T_H_