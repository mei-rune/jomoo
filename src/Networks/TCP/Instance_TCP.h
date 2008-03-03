

#ifndef Instance_TCP_H
#define Instance_TCP_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "../config_Networks.h"
# include "../Instance_Networks.H"
# include "Base/Builder.H"
# include "Base/EmptyType.H"
# include "Hazel.MicroKernel/MicroKernel.H"
# include "../include/Hazel_Transport.H"
# include "TCPTransport.H"
# include "TCPConnector.H"
# include "TCPAcceptor.H"
# include "TCPEndpoint.H"

/**
*/
_networks_begin


class Instance_TCP : _micro_kernel Component
{
	DECLARE_SEAL_COMPONENT( Instance_TCP );
public:

	typedef _memory pool pool_type;

	Instance_TCP( _micro_kernel IKernel& kernel, const _micro_kernel IKernel::key_type& key );

	~Instance_TCP(void);

    _micro_kernel IKernel&		kernel (void);

	const _micro_kernel IKernel::key_type&		contextKey (void) const;

	int open( _util ConfigurationSettings& conf );

	void close( );

	InstanceNetworks& getInstanceNetwork();

	typedef _hazel Builder< TcpEndpoint , TcpEndpoint , EmptyType , pool_type > EndpiontFactory;
	EndpiontFactory& getEndpiontFactory();
	
	typedef _hazel Builder< TcpTransport , TcpTransport , EmptyType , pool_type > TransportFactory;
	TransportFactory& getTransportFactory();

	typedef _hazel Builder< TCP_Transmit_Result , TCP_Transmit_Result , EmptyType , pool_type > TransmitResultFactory;
	TransmitResultFactory& getTransmitResultFactory();

	typedef _hazel Builder< TCP_Write_Result , TCP_Write_Result , EmptyType , pool_type > WriteResultFactory;
	WriteResultFactory& getWriteResultFactory();

	typedef _hazel Builder< TCP_Write_Array_Result , TCP_Write_Array_Result , EmptyType , pool_type > WriteArrayResultFactory;
	WriteArrayResultFactory& getWriteArrayResultFactory();

	typedef _hazel Builder< TCP_Read_Result , TCP_Read_Result , EmptyType , pool_type > ReadResultFactory;
	ReadResultFactory& getReadResultFactory();

	typedef _hazel Builder< TCP_Read_Array_Result , TCP_Read_Array_Result , EmptyType , pool_type > ReadArrayResultFactory;
	ReadArrayResultFactory& getReadArrayResultFactory();

	typedef _hazel Builder< TCP_Accept_Result , TCP_Accept_Result , EmptyType , pool_type > AcceptResultFactory;
	AcceptResultFactory& getAcceptResultFactory();

	typedef _hazel Builder< TCP_Connect_Result , TCP_Connect_Result , EmptyType , pool_type > ConnectResultFactory;
	ConnectResultFactory& getConnectResultFactory();

	const tstring& toString() const;

private:

	DECLARE_NO_COPY_CLASS( Instance_TCP );


	_micro_kernel IKernel& kernel_;
	_micro_kernel IKernel::key_type key_type_;
	InstanceNetworks* instance_;

	std:: auto_ptr< EndpiontFactory				> EndpiontFactory_			;
	std:: auto_ptr< TransportFactory			> getTransportFactory_		;
	std:: auto_ptr< TransmitResultFactory		> TransmitResultFactory_	;
	std:: auto_ptr< WriteResultFactory			> WriteResultFactory_		;
	std:: auto_ptr< WriteArrayResultFactory		> WriteArrayResultFactory_	;
	std:: auto_ptr< ReadResultFactory			> ReadResultFactory_		;
	std:: auto_ptr< ReadArrayResultFactory		> ReadArrayResultFactory_	;
	std:: auto_ptr< AcceptResultFactory			> AcceptResultFactory_		;
	std:: auto_ptr< ConnectResultFactory		> ConnectResultFactory_		;

	tstring toString_;
};

_networks_end

#endif // Instance_TCP_H