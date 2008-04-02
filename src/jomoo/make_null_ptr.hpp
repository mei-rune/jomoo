
#ifndef _make_null_ptr_hpp_
#define _make_null_ptr_hpp_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

template <typename T>
inline T* make_null_ptr()
{
	return (T*)0;
}


#endif /* _make_null_ptr_hpp_ */
