
#ifndef JOMOO_ENDPOINT_H
#define JOMOO_ENDPOINT_H

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_Networks.h"
#include "JOMOO_Connector.H"
#include "JOMOO_Acceptor.H"

_networks_begin


enum TransportType
{
	 nTcpTransport
	,nUdpTransport
};

class JOMOO_Endpoint
{
public:

	typedef counter_ptr< JOMOO_Endpoint > ptr_type;

	virtual ~JOMOO_Endpoint() {}

    virtual const std::string& toString() const = 0;

    virtual int type() const = 0;

	virtual const tstring& protocol() const = 0;

    virtual JOMOO_Connector& connector() const = 0;

    virtual JOMOO_Acceptor& acceptor( ) const = 0;
};

typedef JOMOO_Endpoint::ptr_type JOMOO_Endpoint_Ptr;

//class JOMOO_Endpoint_Factory
//{
//public:
//
//	virtual ~JOMOO_Endpoint_Factory(){}
//
//	virtual JOMOO_Endpoint_Ptr create( const std::string& ) = 0;
//
//	virtual int type() = 0;
//
//	virtual const tstring& protocol() const = 0;
//
//	virtual const tstring& toString() const = 0;
//};
//
//typedef counter_ptr< JOMOO_Endpoint_Factory > JOMOO_Endpoint_Factory_Ptr;

_networks_end

#endif
