
#include "Instance_Networks.h"
#include "TCP/TCP_Endpoint_Factory.H"

#ifdef _MEMORY_DEBUG
#undef THIS_FILE
#define new	   DEBUG_NEW  
#define malloc DEBUG_MALLOC  
static char THIS_FILE[] = __FILE__;  
#endif // _MEMORY_DEBUG

_networks_begin

InstanceNetworks::InstanceNetworks(void)
: Logger_( 0 )
, toString_( 0 )
{
}

InstanceNetworks::~InstanceNetworks(void)
{
	close();
}

int InstanceNetworks::open( _util ConfigurationSettings& config )
{
	config_ = config;

	if( m_proactor_.open( config.get< int32_t >( "Hazel.Networks.Proactor.Threads", 0 ) ) != 0 )
		return -403;

	return 0;
}

void InstanceNetworks::close( )
{
	m_proactor_.close();
}

bool InstanceNetworks::isStop()
{
	return false;
}

proactor& InstanceNetworks::getNativeProactor()
{
	return m_proactor_;
}

JOMOO_Operation_Proactor& InstanceNetworks::getProactor()
{
	return m_proactor_;
}

int InstanceNetworks::run( u_long milli_seconds )
{
	return m_proactor_.handle_events( milli_seconds );
}

InstanceNetworks::LoggerPtr InstanceNetworks::getLogger()
{
	return Logger_;
}

void InstanceNetworks::setLogger( LoggerPtr ptr )
{
	Logger_ = ptr;
}

const _util ConfigurationSettings& InstanceNetworks::conf() const
{
	return config_;
}

JOMOO_Endpoint_Ptr InstanceNetworks::create(const std::string& endpoint )
{
	JOMOO_Url url( endpoint );
	return JOMOO_Endpoint_Ptr( JOMOO_Endpoint_Factory::get().create( url.protocol() ,*this, url ) );
}

_micro_kernel Component& InstanceNetworks::findComponent( const JOMOO_Url_Base& url )
{
	return kernel().component( url.protocol() );
}

_micro_kernel IKernel& InstanceNetworks::kernel( )
{
	return *( _micro_kernel IKernel*)0;
}


const tstring& InstanceNetworks::toString() const
{
	return toString_;
}

_networks_end