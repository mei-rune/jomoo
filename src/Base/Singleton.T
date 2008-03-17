/**
* -*- C++ -*-
* -------------------------------------------------------------------------------
* - °Ë®q°–®r ®q°–®r		               BT_Singleton.CPP,v 1.0 2004/09/23 13:04:54
*  ®u®ê®Ä®Ä®é ®q®q °–®r
* ¶ÚÃÔ¶ÚÃÔÃÔ| ®t------
* -------------------------------------------------------------------------------
*/

#ifndef _JOMOO_Singleton_CPP_
#define _JOMOO_Singleton_CPP_


#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "Singleton.H"

_jomoo_begin

template <JOMOO_Singleton_ST_1> inline
JOMOO_Singleton<JOMOO_Singleton_ST_2>::JOMOO_Singleton ( )
: instance_( 0 )
{
}

template <JOMOO_Singleton_ST_1> void
JOMOO_Singleton<JOMOO_Singleton_ST_2>::dump (void)
{
}

template <JOMOO_Singleton_ST_1> typename JOMOO_Singleton<JOMOO_Singleton_ST_2>::value_type* &
JOMOO_Singleton<JOMOO_Singleton_ST_2>::instance_i (void)
{
	return JOMOO_Singleton<JOMOO_Singleton_ST_2>::singleton_.instance_;
}

template <JOMOO_Singleton_ST_1> typename JOMOO_Singleton<JOMOO_Singleton_ST_2>::lock_type &
JOMOO_Singleton<JOMOO_Singleton_ST_2>::lock_i (void)
{
	return JOMOO_Singleton<JOMOO_Singleton_ST_2>::singleton_.lock_; 
}

template <JOMOO_Singleton_ST_1> typename JOMOO_Singleton<JOMOO_Singleton_ST_2>::value_type &
JOMOO_Singleton<JOMOO_Singleton_ST_2>::get (  )
{
	value_type* &instance =
		JOMOO_Singleton<JOMOO_Singleton_ST_2>::instance_i ();

	if (instance != 0)
		return *instance;

	JOMOO_Guard guard( JOMOO_Singleton<JOMOO_Singleton_ST_2>::lock_i() );

	if (instance != 0)
		return *instance;

	instance = new value_type();
	return *instance;
}

template <JOMOO_Singleton_ST_1> void
JOMOO_Singleton<JOMOO_Singleton_ST_2>::close_singleton( )
{
	value_type* &instance =
		JOMOO_Singleton<JOMOO_Singleton_ST_2>::instance_i ();

	if (instance == 0)
		return ;

	JOMOO_Guard guard( JOMOO_Singleton<JOMOO_Singleton_ST_2>::lock_i() );

	if (instance == 0)
		return ;

	delete instance;
	instance = 0;
}

template <JOMOO_Singleton_ST_1> void
JOMOO_Singleton<JOMOO_Singleton_ST_2>::cleanup ( )
{
	close_singleton( );
}

template <JOMOO_Singleton_ST_1> JOMOO_Singleton<JOMOO_Singleton_ST_2>
JOMOO_Singleton<JOMOO_Singleton_ST_2>::singleton_;


_jomoo_end

#endif // _JOMOO_Singleton_CPP_
