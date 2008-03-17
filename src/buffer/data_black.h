

#ifndef _data_black_h_
#define _data_black_h_

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
#include "counter_ptr.hpp"
#include "counter_ptr.hpp"

_networks_begin

class data_black
{
public:

	size_t capability() const;

    void incRef();
    void decRef();
private:
	counter counter_
	char* pointer_;
	size_t capability_;
};

_networks_end

#endif // _proactor_h_