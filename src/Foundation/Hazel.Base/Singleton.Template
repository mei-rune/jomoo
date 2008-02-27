/**
* -*- C++ -*-
* -------------------------------------------------------------------------------
* - °Ë®q°–®r ®q°–®r		               BT_Singleton.CPP,v 1.0 2004/09/23 13:04:54
*  ®u®ê®Ä®Ä®é ®q®q °–®r
* ¶ÚÃÔ¶ÚÃÔÃÔ| ®t------
* -------------------------------------------------------------------------------
*/

#ifndef _Hazel_Singleton_CPP_
#define _Hazel_Singleton_CPP_


#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

#include "Singleton.H"

_hazel_begin

template <Hazel_Singleton_ST_1> Hazel_INLINE
Hazel_Singleton<Hazel_Singleton_ST_2>::Hazel_Singleton ( )
: instance_( 0 )
{
}

template <Hazel_Singleton_ST_1> void
Hazel_Singleton<Hazel_Singleton_ST_2>::dump (void)
{
}

template <Hazel_Singleton_ST_1> typename Hazel_Singleton<Hazel_Singleton_ST_2>::value_type* &
Hazel_Singleton<Hazel_Singleton_ST_2>::instance_i (void)
{
	return Hazel_Singleton<Hazel_Singleton_ST_2>::singleton_.instance_;
}

template <Hazel_Singleton_ST_1> typename Hazel_Singleton<Hazel_Singleton_ST_2>::lock_type &
Hazel_Singleton<Hazel_Singleton_ST_2>::lock_i (void)
{
	return Hazel_Singleton<Hazel_Singleton_ST_2>::singleton_.lock_; 
}

template <Hazel_Singleton_ST_1> typename Hazel_Singleton<Hazel_Singleton_ST_2>::value_type &
Hazel_Singleton<Hazel_Singleton_ST_2>::get (  )
{
	value_type* &instance =
		Hazel_Singleton<Hazel_Singleton_ST_2>::instance_i ();

	if (instance != 0)
		return *instance;

	Hazel_Guard guard( Hazel_Singleton<Hazel_Singleton_ST_2>::lock_i() );

	if (instance != 0)
		return *instance;

	instance = new value_type();
	return *instance;
}

template <Hazel_Singleton_ST_1> void
Hazel_Singleton<Hazel_Singleton_ST_2>::close_singleton( )
{
	value_type* &instance =
		Hazel_Singleton<Hazel_Singleton_ST_2>::instance_i ();

	if (instance == 0)
		return ;

	Hazel_Guard guard( Hazel_Singleton<Hazel_Singleton_ST_2>::lock_i() );

	if (instance == 0)
		return ;

	delete instance;
	instance = 0;
}

template <Hazel_Singleton_ST_1> void
Hazel_Singleton<Hazel_Singleton_ST_2>::cleanup ( )
{
	close_singleton( );
}

template <Hazel_Singleton_ST_1> Hazel_Singleton<Hazel_Singleton_ST_2>
Hazel_Singleton<Hazel_Singleton_ST_2>::singleton_;


_hazel_end

#endif // _Hazel_Singleton_CPP_
