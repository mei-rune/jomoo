

#ifndef JOMOO_ASYNCH_OPERATION_RESULT_H
#define JOMOO_ASYNCH_OPERATION_RESULT_H

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_Networks.h"
#include "Base/counter_ptr.hpp"

_networks_begin

class jomoo_callable<typename T>
{
public:
	
	typedef counter_ptr< JOMOO_Operation_Result > ptr_type;

	virtual ~jomoo_callable(void){}
	virtual  T call () = 0;
	
    virtual void incRef() = 0;
    virtual void decRef() = 0;
};

typedef jomoo_call::ptr_type jomoo_call_ptr;

_networks_end

#endif //JOMOO_ASYNCH_OPERATION_RESULT_H