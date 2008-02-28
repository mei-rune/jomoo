
/**
* -*- C++ -*-
* -------------------------------------------------------------------------------
* - °Ë®q°–®r ®q°–®r		                 BT_Singleton.h,v 1.0 2004/09/23 13:04:54
*  ®u®ê®Ä®Ä®é ®q®q °–®r
* ¶ÚÃÔ¶ÚÃÔÃÔ| ®t------
* -------------------------------------------------------------------------------
*/
#ifndef _BOE_Singleton_H_
#define _BOE_Singleton_H_

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include "Cleanup.h"
#include "synch/synch_traits.h"

#define BT_Singleton_ST_1 class TYPE, class PARAMETER, class BOE_LOCK
#define BT_Singleton_ST_2 TYPE, PARAMETER, BOE_LOCK

_bt_begin

template < BT_Singleton_ST_1 >
class BT_Singleton : public BOE_Cleanup
{
public:
  /// Global access point to the Singleton.
  static TYPE *instance ( PARAMETER parameter = 0 );

  /// Cleanup method, used by <ace_cleanup_destroyer> to destroy the
  /// ACE_Singleton.
  virtual void cleanup (void *param = 0);

  /// Dump the state of the object.
  static void dump (void);

protected:
  /// Default constructor.
  BT_Singleton ( PARAMETER parameter );

  /// Contained instance.
  TYPE instance_;

#if !defined (BOE_LACKS_STATIC_DATA_MEMBER_TEMPLATES)
  /// Pointer to the Singleton (BOE_Cleanup) instance.
  static BT_Singleton<BT_Singleton_ST_2> *singleton_;
   static BOERegisterCleanup cleanup_;
#endif /* BOE_LACKS_STATIC_DATA_MEMBER_TEMPLATES */

  /// Get pointer to the Singleton instance.
  static BT_Singleton<BT_Singleton_ST_2> *&instance_i ( );
};

#define BOE_Singleton_ST_1 class TYPE,  class BOE_LOCK
#define BOE_Singleton_ST_2 TYPE, BOE_LOCK

template < BOE_Singleton_ST_1 >
class BOE_Singleton : public BOE_Cleanup
{
public:
  /// Global access point to the Singleton.
  static TYPE *instance ( );

  /// Cleanup method, used by <ace_cleanup_destroyer> to destroy the
  /// ACE_Singleton.
  virtual void cleanup (void *param = 0);

  /// Dump the state of the object.
  static void dump (void);

protected:
  /// Default constructor.
  BOE_Singleton ( );

  /// Contained instance.
  TYPE instance_;

#if !defined (BOE_LACKS_STATIC_DATA_MEMBER_TEMPLATES)
  /// Pointer to the Singleton (BOE_Cleanup) instance.
  static BOE_Singleton<BOE_Singleton_ST_2> *singleton_;

  static BOERegisterCleanup cleanup_;

#endif /* BOE_LACKS_STATIC_DATA_MEMBER_TEMPLATES */

  /// Get pointer to the Singleton instance.
  static BOE_Singleton<BOE_Singleton_ST_2> *&instance_i ( );
};

_bt_end


#if defined (BOE_TEMPLATES_REQUIRE_SOURCE)
#include "Singleton.cpp"
#endif /* BOE_TEMPLATES_REQUIRE_SOURCE */

#if defined (BOE_TEMPLATES_REQUIRE_PRAGMA)
#pragma implementation ("Singleton.cpp")
#endif /* BOE_TEMPLATES_REQUIRE_PRAGMA */

#endif // _BOE_Singleton_H_
