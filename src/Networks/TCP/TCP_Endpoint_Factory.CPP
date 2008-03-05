
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
, toString_( BT_TEXT("TCP端点工厂") )
{
}

JOMOO_Endpoint* TCP_Endpoint_Factory::create( Instance_Networks& instance, const JOMOO_Url_Base& url )
{
	Instance_TCP* tcpinstance =  dynamicCast< Instance_TCP , _micro_kernel Component>( &(instance.findComponent( url ) ) ) ;
	if( tcpinstance == 0 )
		ThrowException1( CastException , BT_TEXT("找到的关于 '") + url.toString() + BT_TEXT("'组件不是 TCP 实例组件 ") );

	return tcpinstance->getEndpiontFactory().create( tcpinstance, &url );
}

void TCP_Endpoint_Factory::release( JOMOO_Endpoint* endpoint )
{
	TcpEndpoint* tcpendpoint = dynamicCast< TcpEndpoint, JOMOO_Endpoint >( endpoint );
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
