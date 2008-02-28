/**
* -*- C++ -*-
* -------------------------------------------------------------------------------
* - °Ë®q°–®r ®q°–®r		               BT_Singleton.CPP,v 1.0 2004/09/23 13:04:54
*  ®u®ê®Ä®Ä®é ®q®q °–®r
* ¶ÚÃÔ¶ÚÃÔÃÔ| ®t------
* -------------------------------------------------------------------------------
*/

#ifndef _BOE_Singleton_CPP_
#define _BOE_Singleton_CPP_


#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include "Singleton.H"

_bt_begin

template <BT_Singleton_ST_1> BOE_INLINE
BT_Singleton<BT_Singleton_ST_2>::BT_Singleton ( PARAMETER parameter )
: instance_( parameter )
{
}

template <BT_Singleton_ST_1> void
BT_Singleton<BT_Singleton_ST_2>::dump (void)
{
}

template <BT_Singleton_ST_1> BT_Singleton<BT_Singleton_ST_2> *&
BT_Singleton<BT_Singleton_ST_2>::instance_i (void)
{
#if defined (BOE_LACKS_STATIC_DATA_MEMBER_TEMPLATES)
  // Pointer to the Singleton instance.  This works around a bug with
  // G++ and it's (mis-)handling of templates and statics...
  static BT_Singleton<BT_Singleton_ST_2> *singleton_ = 0;

  return singleton_;
#else
  return BT_Singleton<BT_Singleton_ST_2>::singleton_;
#endif /* BOE_LACKS_STATIC_DATA_MEMBER_TEMPLATES */
}

template <BT_Singleton_ST_1> TYPE *
BT_Singleton<BT_Singleton_ST_2>::instance ( PARAMETER parameter )
{

  BT_Singleton<BT_Singleton_ST_2> *&singleton =
    BT_Singleton<BT_Singleton_ST_2>::instance_i ();

  // Perform the Double-Check pattern...
  if (singleton == 0)
  {
	  std::auto_ptr< BOE_Mutex::spcode_lock > ptr;
	  BOE_Mutex * mutex = BOERegisterCleanup_Implementation::get()->get_singleton_lock();
	  if( mutex != 0 )
		  ptr.reset( new BOE_Mutex::spcode_lock( *mutex ) );

	  if (singleton == 0)
	  {
		  singleton = new BT_Singleton<BT_Singleton_ST_2>( parameter );
		  cleanup_.registerCleanup(  singleton );
	  }
  }

  return &singleton->instance_;
}

template <BT_Singleton_ST_1> void
BT_Singleton<BT_Singleton_ST_2>::cleanup (void *)
{
  delete this;
  BT_Singleton<BT_Singleton_ST_2>::instance_i () = 0;
}

#if !defined (BOE_LACKS_STATIC_DATA_MEMBER_TEMPLATES)
// Pointer to the Singleton instance.
template <BT_Singleton_ST_1> BT_Singleton<BT_Singleton_ST_2> *
BT_Singleton<BT_Singleton_ST_2>::singleton_ = 0;
 static BOERegisterCleanup cleanup_;
#endif /* !defined (BOE_LACKS_STATIC_DATA_MEMBER_TEMPLATES) */




template <BOE_Singleton_ST_1> BOE_INLINE
BOE_Singleton<BOE_Singleton_ST_2>::BOE_Singleton ( )
: instance_( )
{
}

template <BOE_Singleton_ST_1> void
BOE_Singleton<BOE_Singleton_ST_2>::dump (void)
{
}

template <BOE_Singleton_ST_1> BOE_Singleton<BOE_Singleton_ST_2> *&
BOE_Singleton<BOE_Singleton_ST_2>::instance_i (void)
{
#if defined (BOE_LACKS_STATIC_DATA_MEMBER_TEMPLATES)
  // Pointer to the Singleton instance.  This works around a bug with
  // G++ and it's (mis-)handling of templates and statics...
  static BOE_Singleton<BOE_Singleton_ST_2> *singleton_ = 0;

  return singleton_;
#else
  return BOE_Singleton<BOE_Singleton_ST_2>::singleton_;
#endif /* BOE_LACKS_STATIC_DATA_MEMBER_TEMPLATES */
}

template <BOE_Singleton_ST_1> TYPE *
BOE_Singleton<BOE_Singleton_ST_2>::instance (  )
{

  BOE_Singleton<BOE_Singleton_ST_2> *&singleton =
    BOE_Singleton<BOE_Singleton_ST_2>::instance_i ();

  // Perform the Double-Check pattern...
  if (singleton == 0)
    {
		std::auto_ptr< BOE_Mutex::spcode_lock > ptr;
		BOE_Mutex * mutex = BOERegisterCleanup_Implementation::get()->get_singleton_lock();
		if( mutex != 0 )
			ptr.reset( new BOE_Mutex::spcode_lock( *mutex ) );
		  if (singleton == 0)
		  {
			singleton = new BOE_Singleton<BOE_Singleton_ST_2>();
			cleanup_.registerCleanup(  singleton );
		  }

    }

  return &singleton->instance_;
}

template <BOE_Singleton_ST_1> void
BOE_Singleton<BOE_Singleton_ST_2>::cleanup (void *)
{
  delete this;
  BOE_Singleton<BOE_Singleton_ST_2>::instance_i () = 0;
}

#if !defined (BOE_LACKS_STATIC_DATA_MEMBER_TEMPLATES)
// Pointer to the Singleton instance.
template <BOE_Singleton_ST_1> BOE_Singleton<BOE_Singleton_ST_2> *
BOE_Singleton<BOE_Singleton_ST_2>::singleton_ = 0;

template <BOE_Singleton_ST_1> 
BOERegisterCleanup BOE_Singleton<BOE_Singleton_ST_2>::cleanup_;

#endif /* !defined (BOE_LACKS_STATIC_DATA_MEMBER_TEMPLATES) */

_bt_end

#endif // _BOE_Singleton_CPP_
