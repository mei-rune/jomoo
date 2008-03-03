
/**
* -*- C++ -*-
* -------------------------------------------------------------------------------
* - °Ë®q°–®r ®q°–®r		                 BT_Singleton.h,v 1.0 2004/09/23 13:04:54
*  ®u®ê®Ä®Ä®é ®q®q °–®r
* ¶ÚÃÔ¶ÚÃÔÃÔ| ®t------
* -------------------------------------------------------------------------------
*/
#ifndef _Hazel_Singleton_H_
#define _Hazel_Singleton_H_

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

#include "Cleanup.h"

_hazel_begin

#define Hazel_Singleton_ST_1 class TYPE,  class Hazel_LOCK
#define Hazel_Singleton_ST_2 TYPE, Hazel_LOCK

template < Hazel_Singleton_ST_1 >
class Hazel_Singleton : public Hazel_Cleanup
{
public:
	typedef TYPE value_type;
	typedef Hazel_LOCK lock_type;

	class Hazel_Guard
	{
	public:
		Hazel_Guard( lock_type& lock )
			: lock_( 0 )
		{
			if( lock.acquire() )
				lock_ = &lock;
		}

		~Hazel_Guard( )
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
	Hazel_Singleton ( );

	TYPE* instance_;
	lock_type lock_;

	static Hazel_Singleton<Hazel_Singleton_ST_2> singleton_;

	static value_type* &instance_i ( );
	static lock_type &lock_i ( );
};

_hazel_end


#if defined (Hazel_TEMPLATES_REQUIRE_SOURCE)
#include "Singleton.T"
#endif /* Hazel_TEMPLATES_REQUIRE_SOURCE */

#if defined (Hazel_TEMPLATES_REQUIRE_PRAGMA)
#pragma implementation ("Singleton.Template")
#endif /* Hazel_TEMPLATES_REQUIRE_PRAGMA */

#endif // _Hazel_Singleton_H_
