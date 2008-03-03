
#include "Instance_TCP.h"
#include "Base/ToString.H"

_networks_begin

DEFINE_SEAL_COMPONENT( Instance_TCP , "Instance_TCP" )

Instance_TCP::Instance_TCP( _micro_kernel IKernel& kernel, const _micro_kernel IKernel::key_type& key )
: kernel_( kernel )
, key_type_( key )
, instance_( 0 )
//, EnpiontFactory_( _pool, BT_TEXT("EnpiontFactory_") )
//, TransmitResultFactory_( _pool, BT_TEXT("TransmitResultFactory_") )
//, WriteResultFactory_( _pool, BT_TEXT("WriteResultFactory_") )
//, WriteArrayResultFactory_( _pool, BT_TEXT("WriteArrayResultFactory_") )
//, ReadResultFactory_( _pool, BT_TEXT("ReadResultFactory_") )
//, ReadArrayResultFactory_( _pool, BT_TEXT("ReadArrayResultFactory_") )
//, AcceptResultFactory_( _pool, BT_TEXT("AcceptResultFactory_") )
//, ConnectResultFactory_( _pool, BT_TEXT("ConnectResultFactory_") )
, toString_( BT_TEXT("Instance_TCP[") )
{
	toString_ +=  key ;
	toString_ += BT_TEXT("]");
}

Instance_TCP::~Instance_TCP(void)
{
}

_micro_kernel IKernel&		Instance_TCP::kernel (void)
{
	return getInstanceNetwork().kernel();
}

const _micro_kernel IKernel::key_type&		Instance_TCP::contextKey (void) const
{
	return key_type_;
}

const tstring&		Instance_TCP::toString (void) const
{
	return toString_;
}

int Instance_TCP::open( _util ConfigurationSettings& config )
{
	return 0;
}

void Instance_TCP::close( )
{
}

InstanceNetworks& Instance_TCP::getInstanceNetwork()
{
	return *instance_;
}


Instance_TCP::EndpiontFactory& Instance_TCP::getEndpiontFactory()
{
	return *EndpiontFactory_;
}

Instance_TCP::TransportFactory& Instance_TCP::getTransportFactory()
{
	return *getTransportFactory_;
}

Instance_TCP::TransmitResultFactory& Instance_TCP::getTransmitResultFactory()
{
	return *TransmitResultFactory_;
}

Instance_TCP::WriteResultFactory& Instance_TCP::getWriteResultFactory()
{
	return *WriteResultFactory_;
}

Instance_TCP::WriteArrayResultFactory& Instance_TCP::getWriteArrayResultFactory()
{
	return *WriteArrayResultFactory_;
}

Instance_TCP::ReadResultFactory& Instance_TCP::getReadResultFactory()
{
	return *ReadResultFactory_;
}

Instance_TCP::ReadArrayResultFactory& Instance_TCP::getReadArrayResultFactory()
{
	return *ReadArrayResultFactory_;
}

Instance_TCP::AcceptResultFactory& Instance_TCP::getAcceptResultFactory()
{
	return *AcceptResultFactory_;
}

Instance_TCP::ConnectResultFactory& Instance_TCP::getConnectResultFactory()
{
	return *ConnectResultFactory_;
}


//TcpEndpoint_Ptr Instance_TCP::createEndpoint( const std::string& url )
//{
//	return TcpEndpoint_Ptr( new TcpEndpoint( *this, url ) );
//}
//
//TCP_Transmit_Result* Instance_TCP::createTransmitResult( TcpTransport& transport,
//	TCP_Transport_Handler& handle,
//	const iopack* data,
//	size_t size,
//	void* act )
//{
//	return new TCP_Transmit_Result( *this, transport, handle, data, size, act );
//}
//
//TCP_Write_Result* Instance_TCP::createWriteResult( TcpTransport& transport,
//	TCP_Transport_Handler& handle,
//	const void* buffer,
//	size_t length,
//	void* act )
//{
//	return new TCP_Write_Result( *this, transport, handle, buffer, length, act );
//}
//
//TCP_Write_Array_Result* Instance_TCP::createWriteResult( TcpTransport& transport,
//	TCP_Transport_Handler& handle,
//	const iovec* data,
//	size_t size,
//	void* act )
//{
//	return new TCP_Write_Array_Result( *this, transport, handle, data, size, act );
//}
//
//TCP_Read_Result* Instance_TCP::createReadResult( TcpTransport& transport,
//	TCP_Transport_Handler& handle,
//	void* buffer,
//	size_t length,
//	void* act )
//{
//	return new TCP_Read_Result( *this, transport, handle, buffer, length, act );
//}
//
//TCP_Read_Array_Result* Instance_TCP::createReadResult( TcpTransport& transport,
//	TCP_Transport_Handler& handle,
//	iovec* data,
//	size_t size,
//	void* act )
//{
//	return new TCP_Read_Array_Result( *this, transport, handle, data, size, act );
//}
//
//TCP_Accept_Result* Instance_TCP::createAcceptResult( TcpAcceptor& channel
//	,TCP_Accept_Handler& handle
//	,int recv_size
//	,void * act )
//{
//	return new TCP_Accept_Result( *this, channel, TcpTransportPtr( new TcpTransport( *this, 0 ) ),handle, recv_size, act );
//}
//
//TCP_Connect_Result* Instance_TCP::createConnectResult( TcpConnector& channel
//	,TCP_Connect_Handler& handle
//	,void * act )
//{
//	return new TCP_Connect_Result( *this, channel,TcpTransportPtr( new TcpTransport( *this, 0 ) ),handle,  act );
//}

_networks_end