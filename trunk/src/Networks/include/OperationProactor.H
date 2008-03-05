

#ifndef JOMOO_Operation_Proactor_H
#define JOMOO_Operation_Proactor_H

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_Networks.h"
#include "Platform/OS.H"
#include "Operation_Result.H"

_networks_begin

class JOMOO_Operation_Proactor
{
public:
	virtual ~JOMOO_Operation_Proactor(){}

	virtual int open ( size_t number_of_threads = 0 ) = 0;
	virtual void close (void) = 0;
	virtual int handle_events ( u_long milli_seconds ) = 0;
	virtual int post_completion ( JOMOO_Operation_Result_Ptr result) = 0;
};

_networks_end

#endif // JOMOO_Operation_Proactor_H