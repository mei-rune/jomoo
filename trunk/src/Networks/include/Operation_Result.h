

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

class JOMOO_Operation_Result
{
public:
	
	typedef counter_ptr< JOMOO_Operation_Result > ptr_type;

	virtual ~JOMOO_Operation_Result(void){}
	virtual  void complete (size_t bytes_transferred,
                         int success,
                         const void *completion_key,
                         u_long error = 0) = 0;
};

typedef JOMOO_Operation_Result::ptr_type JOMOO_Operation_Result_Ptr;

_networks_end

#endif //JOMOO_ASYNCH_OPERATION_RESULT_H