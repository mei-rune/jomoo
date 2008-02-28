
/**
* -*- C++ -*-
* -------------------------------------------------------------------------------
* - °Ë®q°–®r ®q°–®r							Singleton.h,v 1.0 2006/02/16 22:26:54
*  ®u®ê®Ä®Ä®é ®q®q °–®r
* ¶ÚÃÔ¶ÚÃÔÃÔ| ®t------
* -------------------------------------------------------------------------------
*/
#ifndef _PLUGIN_MANAGER_RESULT_TRAITS_H_
#define _PLUGIN_MANAGER_RESULT_TRAITS_H_

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
#include "config_PluginManager.h"
#include "boost/type_traits/remove_all_extents.hpp"
#include "boost/type_traits/remove_volatile.hpp"
#include "boost/type_traits/remove_cv.hpp"
#include "boost/type_traits/remove_reference.hpp"
#include "boost/type_traits/remove_pointer.hpp"

_seal_begin

template< typename T >
class result_traits
{
public:
	typedef typename  boost::remove_all_extents< typename boost::remove_cv< T >::type >::type no_extents_type;
	typedef typename  boost::remove_cv< no_extents_type >::type no_cv_type;
	typedef typename  boost::remove_reference< no_cv_type >::type no_reference_type;
	typedef typename  boost::remove_cv< no_reference_type >::type no_reference_cv_type;
	typedef typename  boost::remove_pointer< no_reference_cv_type >::type no_pointer_type;
	typedef typename  boost::remove_cv< no_pointer_type >::type value_type;
	typedef value_type* pointer_type;
	typedef const value_type* const_pointer_type;
	typedef value_type& reference_type;
	typedef const value_type& const_reference_type;
};

_seal_end



#endif // _PLUGIN_MANAGER_RESULT_TRAITS_H_
