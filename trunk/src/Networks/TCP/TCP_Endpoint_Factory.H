// Communication


#ifndef __TCP_ENDPOINT_FACTORY__
#define __TCP_ENDPOINT_FACTORY__

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_Networks.h"
#include "../include/JOMOO_Endpoint_Factory.h"
#include "../Instance_Networks.H"
#include "Instance_TCP.H"

_networks_begin

class TCP_Endpoint_Factory : public JOMOO_Endpoint_Factory::base_type::AbstractFactory
{
public:
	TCP_Endpoint_Factory( );

	JOMOO_Endpoint* create( Instance_Networks& , const JOMOO_Url_Base& );
	
	void release( JOMOO_Endpoint* );

	const tstring& toString() const;

	const tstring& name() const;

private:

	tstring protocol_;
	tstring toString_;
};
_networks_end

#endif // __TCP_ENDPOINT_FACTORY__
