
/**
* -*- C++ -*-
* -------------------------------------------------------------------------------
* - °Ë®q°–®r ®q°–®r		                 BT_Singleton.h,v 1.0 2004/09/23 13:04:54
*  ®u®ê®Ä®Ä®é ®q®q °–®r
* ¶ÚÃÔ¶ÚÃÔÃÔ| ®t------
* -------------------------------------------------------------------------------
*/
#ifndef _JOMOO_Singleton_H_
#define _JOMOO_Singleton_H_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "Cleanup.h"

_jomoo_begin

#define JOMOO_Singleton_ST_1 class TYPE,  class JOMOO_LOCK
#define JOMOO_Singleton_ST_2 TYPE, JOMOO_LOCK

template < JOMOO_Singleton_ST_1 >
class JOMOO_Singleton : public JOMOO_Cleanup
{
public:
	typedef TYPE value_type;
	typedef JOMOO_LOCK lock_type;

	class JOMOO_Guard
	{
	public:
		JOMOO_Guard( lock_type& lock )
			: lock_( 0 )
		{
			if( lock.acquire() )
				lock_ = &lock;
		}

		~JOMOO_Guard( )
		{
			if( lock_ != 0 )
				lock_->release();
		}
	private:
		lock_type* lock_;
	};


	static value_type& get ( );
	static void close_singleton( );
	static void dump (void);

	void cleanup ( );


protected:
	JOMOO_Singleton ( );

	TYPE* instance_;
	lock_type lock_;

	static JOMOO_Singleton<JOMOO_Singleton_ST_2> singleton_;

	static value_type* &instance_i ( );
	static lock_type &lock_i ( );
};

_jomoo_end


#if defined (JOMOO_TEMPLATES_REQUIRE_SOURCE)
#include "Singleton.T"
#endif /* JOMOO_TEMPLATES_REQUIRE_SOURCE */

#if defined (JOMOO_TEMPLATES_REQUIRE_PRAGMA)
#pragma implementation ("Singleton.Template")
#endif /* JOMOO_TEMPLATES_REQUIRE_PRAGMA */

#endif // _JOMOO_Singleton_H_
