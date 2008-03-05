
#include "TCPAsynchResult.h"
#include "TcpTransport.h"
#include "Base/lastError.h"
#include "Instance_TCP.H"

#ifdef _MEMORY_DEBUG
#undef THIS_FILE
#define new	   DEBUG_NEW  
#define malloc DEBUG_MALLOC  
static char THIS_FILE[] = __FILE__;  
#endif // _MEMORY_DEBUG

_networks_begin

TCP_Asynch_Result::TCP_Asynch_Result(  )
: instance_( 0 )
, m_act_( 0 )
, m_bytes_transferred_( 0 )
, m_success_( -1 )
, m_error_( 0 )
{
	this->setHandler( *this );
}

TCP_Asynch_Result::~TCP_Asynch_Result()
{
}

void TCP_Asynch_Result::init( Instance_TCP* instance , JOMOO_HANDLE handle , void* act )
{
	if( instance == 0 )
		ThrowException1( NullException, BT_TEXT("instance") );

	getOverlapped().init( & instance->getInstanceNetwork().getNativeProactor(), handle );
	instance_ = instance;
	m_act_ = act;
	m_bytes_transferred_ = 0;
	m_success_ = -1;
	m_error_ = 0;
}

void TCP_Asynch_Result::fini( )
{
	getOverlapped().fini();
	instance_ = 0;
	m_act_ = 0;

	//m_bytes_transferred_ = 0;
	//m_success_ = -1;
	//m_error_ = 0;
}
size_t TCP_Asynch_Result::bytes_to_transferred() const
{
	return m_bytes_transferred_;
}

void* TCP_Asynch_Result::act()
{
	return m_act_;
}


bool TCP_Asynch_Result::success() const
{
	return ( m_success_ == 0 );
}


int TCP_Asynch_Result::error() const
{
	return m_error_;
}

WIN32OperationOverlapped& TCP_Asynch_Result::getOverlapped()
{
	return *this;
}

_networks_end
