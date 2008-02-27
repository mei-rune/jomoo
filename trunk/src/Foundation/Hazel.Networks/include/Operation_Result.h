

#ifndef Hazel_ASYNCH_OPERATION_RESULT_H
#define Hazel_ASYNCH_OPERATION_RESULT_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_Networks.h"
#include "Hazel.Base/counter_ptr.hpp"

_networks_begin

class Hazel_Operation_Result
{
public:
	
	typedef counter_ptr< Hazel_Operation_Result > ptr_type;

	virtual ~Hazel_Operation_Result(void){}
	virtual  void complete (size_t bytes_transferred,
                         int success,
                         const void *completion_key,
                         u_long error = 0) = 0;
};

typedef Hazel_Operation_Result::ptr_type Hazel_Operation_Result_Ptr;

_networks_end

#endif //Hazel_ASYNCH_OPERATION_RESULT_H