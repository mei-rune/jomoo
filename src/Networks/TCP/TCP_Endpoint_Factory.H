// Communication


#ifndef __TCP_ENDPOINT_FACTORY__
#define __TCP_ENDPOINT_FACTORY__

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_Networks.h"
#include "../include/Hazel_Endpoint_Factory.h"
#include "../Instance_Networks.H"
#include "Instance_TCP.H"

_networks_begin

class TCP_Endpoint_Factory : public Hazel_Endpoint_Factory::base_type::AbstractFactory
{
public:
	TCP_Endpoint_Factory( );

	Hazel_Endpoint* create( Instance_Networks& , const Hazel_Url_Base& );
	
	void release( Hazel_Endpoint* );

	const tstring& toString() const;

	const tstring& name() const;

private:

	tstring protocol_;
	tstring toString_;
};
_networks_end

#endif // __TCP_ENDPOINT_FACTORY__
