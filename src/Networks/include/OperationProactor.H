

#ifndef Hazel_Operation_Proactor_H
#define Hazel_Operation_Proactor_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_Networks.h"
#include "Platform/OS.H"
#include "Hazel_Operation_Result.H"

_networks_begin

class Hazel_Operation_Proactor
{
public:
	virtual ~Hazel_Operation_Proactor(){}

	virtual int open ( size_t number_of_threads = 0 ) = 0;
	virtual void close (void) = 0;
	virtual int handle_events ( u_long milli_seconds ) = 0;
	virtual int post_completion ( Hazel_Operation_Result_Ptr result) = 0;
};

_networks_end

#endif // Hazel_Operation_Proactor_H