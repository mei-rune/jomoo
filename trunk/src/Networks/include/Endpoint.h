
#ifndef Hazel_ENDPOINT_H
#define Hazel_ENDPOINT_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_Networks.h"
#include "Hazel_Connector.H"
#include "Hazel_Acceptor.H"

_networks_begin


enum TransportType
{
	 nTcpTransport
	,nUdpTransport
};

class Hazel_Endpoint
{
public:

	typedef counter_ptr< Hazel_Endpoint > ptr_type;

	virtual ~Hazel_Endpoint() {}

    virtual const std::string& toString() const = 0;

    virtual int type() const = 0;

	virtual const tstring& protocol() const = 0;

    virtual Hazel_Connector& connector() const = 0;

    virtual Hazel_Acceptor& acceptor( ) const = 0;
};

typedef Hazel_Endpoint::ptr_type Hazel_Endpoint_Ptr;

//class Hazel_Endpoint_Factory
//{
//public:
//
//	virtual ~Hazel_Endpoint_Factory(){}
//
//	virtual Hazel_Endpoint_Ptr create( const std::string& ) = 0;
//
//	virtual int type() = 0;
//
//	virtual const tstring& protocol() const = 0;
//
//	virtual const tstring& toString() const = 0;
//};
//
//typedef counter_ptr< Hazel_Endpoint_Factory > Hazel_Endpoint_Factory_Ptr;

_networks_end

#endif
