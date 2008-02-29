
#include "TCP_Endpoint_Factory.h"
#include "TcpEndpoint.H"

#ifdef _MEMORY_DEBUG
#undef THIS_FILE
#define new	   DEBUG_NEW  
#define malloc DEBUG_MALLOC  
static char THIS_FILE[] = __FILE__;  
#endif // _MEMORY_DEBUG

_networks_begin

TCP_Endpoint_Factory::TCP_Endpoint_Factory( )
: protocol_( BT_TEXT("tcp") )
, toString_( BT_TEXT("TCP�˵㹤��") )
{
}

Hazel_Endpoint* TCP_Endpoint_Factory::create( Instance_Networks& instance, const Hazel_Url_Base& url )
{
	Instance_TCP* tcpinstance =  dynamicCast< Instance_TCP , _micro_kernel Component>( &(instance.findComponent( url ) ) ) ;
	if( tcpinstance == 0 )
		ThrowException1( CastException , BT_TEXT("�ҵ��Ĺ��� '") + url.toString() + BT_TEXT("'������� TCP ʵ����� ") );

	return tcpinstance->getEndpiontFactory().create( tcpinstance, &url );
}

void TCP_Endpoint_Factory::release( Hazel_Endpoint* endpoint )
{
	TcpEndpoint* tcpendpoint = dynamicCast< TcpEndpoint, Hazel_Endpoint >( endpoint );
	if( tcpendpoint != 0 )
		tcpendpoint ->release();
}

const tstring& TCP_Endpoint_Factory::name() const
{
	return protocol_;
}

const tstring& TCP_Endpoint_Factory::toString() const
{
	return toString_;
}

_networks_end