// Communication


#ifndef __Hazel_TCP_ENDPOINT__
#define __Hazel_TCP_ENDPOINT__

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_Networks.h"
#include "../include/Hazel_Endpoint.h"
#include "TcpAcceptor.h"
#include "TcpConnector.h"

_networks_begin

class TcpEndpoint :
	public Hazel_Endpoint
{
public:
	//TcpEndpoint( Instance_TCP& instance, const tstring& ipstr, const tstring& port );
	
	//TcpEndpoint( Instance_TCP& instance, const tstring& url );

	TcpEndpoint();

	~TcpEndpoint(void);

	const tstring& toString() const;

    int type() const;

	const tstring& protocol() const;

    Hazel_Connector& connector() const;

    Hazel_Acceptor& acceptor( ) const;

	void release();

	void init( Instance_TCP* instance, const Hazel_Url_Base* url );

	void fini( );

private:

	DECLARE_NO_COPY_CLASS( TcpEndpoint );

	Instance_TCP* instance_;
	Hazel_INET_Addr addr_;

	mutable std::auto_ptr< TcpConnector > connector_;
	mutable std::auto_ptr< TcpAcceptor > acceptor_;

	//mutable Connector_T< TcpConnector, Hazel_Connector > connector_;
	//mutable Acceptor_T< TcpAcceptor, Hazel_Acceptor > acceptor_;
	
	tstring toString_;
	static tstring protocol_;
};


_networks_end

#endif // __Hazel_TCP_ENDPOINT__
