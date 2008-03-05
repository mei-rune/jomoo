// Communication


#ifndef __JOMOO_TCP_ENDPOINT__
#define __JOMOO_TCP_ENDPOINT__

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_Networks.h"
#include "../include/JOMOO_Endpoint.h"
#include "TcpAcceptor.h"
#include "TcpConnector.h"

_networks_begin

class TcpEndpoint :
	public JOMOO_Endpoint
{
public:
	//TcpEndpoint( Instance_TCP& instance, const tstring& ipstr, const tstring& port );
	
	//TcpEndpoint( Instance_TCP& instance, const tstring& url );

	TcpEndpoint();

	~TcpEndpoint(void);

	const tstring& toString() const;

    int type() const;

	const tstring& protocol() const;

    JOMOO_Connector& connector() const;

    JOMOO_Acceptor& acceptor( ) const;

	void release();

	void init( Instance_TCP* instance, const JOMOO_Url_Base* url );

	void fini( );

private:

	DECLARE_NO_COPY_CLASS( TcpEndpoint );

	Instance_TCP* instance_;
	JOMOO_INET_Addr addr_;

	mutable std::auto_ptr< TcpConnector > connector_;
	mutable std::auto_ptr< TcpAcceptor > acceptor_;

	//mutable Connector_T< TcpConnector, JOMOO_Connector > connector_;
	//mutable Acceptor_T< TcpAcceptor, JOMOO_Acceptor > acceptor_;
	
	tstring toString_;
	static tstring protocol_;
};


_networks_end

#endif // __JOMOO_TCP_ENDPOINT__
