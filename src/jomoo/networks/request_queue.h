

#ifndef _request_queue_h_
#define _request_queue_h_

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
#include "config_Networks.h"
#include "io_request.h"

_networks_begin

class request_queue
{
public:
	io_request* createRequest()
	{
	}

private:

};

_networks_end

#endif // _request_queue_h_