
#include "TCPScan.H"
#include "BOE_SOCK_IO.h"
#include <list>
#include "BOE_INET_Addr.h"
#include "WIN32OperationResult.H"
#include "BOE_WIN_Select_Reactor.H"
#include <iostream>
#include "BOE.Base/get_last_error.h"
#include "BOE_Communicator.H"


BT_Export_C int init_TCPack( )
{
#ifndef _WINXP_
	return BOE_SOCK_IO::initsocket();
#endif
}
BT_Export_C void shutdown_TCPack( )
{
#ifndef _WINXP_
	BOE_SOCK_IO::shutdownsock();
#endif
}


class TCPConnector;
struct TCPack
{
	TCPack( )
	{
		handler_ = 0;
	}
	std::list< TCPConnector* > cache_;
	std::list< TCPConnector* > connecting_;
	TCPConnectedHandler handler_;

#ifdef _WINXP_
	typedef BOE_Communicator proactor_type;
	typedef BOE_Communicator_Ptr proactor_ptr;
#else
	typedef BOE_WIN_Select_Reactor proactor_type;
	typedef std::auto_ptr< proactor_type > proactor_ptr;
#endif 
	proactor_ptr proactor_;
};


//typedef struct TCPack* TCPackPtr;


class BOE_TCPConnect_Result
#ifdef _WINXP_
	: public WIN32OperationResult
#else
	: public BOE_WIN32_Select_Operation_Result
#endif // _WINXP_
{
public:

	BOE_TCPConnect_Result( TCPackPtr tcpack , TCPConnector& connector, BOE_SOCK_HANDLE handle , void * act );

	TCPackPtr* getTCPack()
	{
		return &tcpack_;
	}

	void complete (size_t bytes_transferred,
                         int success,
                         const void *completion_key,
                         u_long error = 0);

private:

	TCPackPtr tcpack_;
	TCPConnector* connector_;
};


class TCPConnector
{
public:
	TCPConnector( TCPackPtr tcpack, const char* ipstr, u_short port )
		: m_remoteaddr_( port,ipstr )
		, tcpack_( tcpack )
		, result_( 0 )
	{
#ifdef _WINXP_
		if( m_handle_.open() != 0 )
			throw std::runtime_error( "²Ù×÷Ê§°Ü" ); 
#endif // _WINXP_
	}

	TCPConnector( TCPackPtr tcpack, u_long ip , u_short port )
		: m_remoteaddr_(  port,ip )
		, tcpack_( tcpack )
	{
#ifdef _WINXP_
		if( m_handle_.open() != 0 )
			throw std::runtime_error( "²Ù×÷Ê§°Ü" ); 
#endif // _WINXP_
	}

	~TCPConnector()
	{
		close();
	}

	int connect( );

	int cancel();

	BOE_INET_Addr& getRemoteAddr( )
	{
		return m_remoteaddr_;
	}

	int close( )
	{
		return m_handle_.close();
	}
	void reset( )
	{
		cancel();
		close();
	}
private:

	int init( );

	BOE_INET_Addr m_remoteaddr_;
	TCPackPtr tcpack_;
	BOE_SOCK_IO m_handle_;
	std::auto_ptr< BOE_TCPConnect_Result > result_;
};


BOE_TCPConnect_Result::BOE_TCPConnect_Result( TCPackPtr tcpack , TCPConnector& connector, BOE_SOCK_HANDLE handle , void * act )
: 
#ifdef _WINXP_
WIN32OperationResult( tcpack->proactor_->getI ,handle , act )
#else
BOE_WIN32_Select_Operation_Result( *tcpack->proactor_ ,handle , act )
#endif //
, tcpack_( tcpack )
, connector_( &connector )
{
}

void BOE_TCPConnect_Result::complete (size_t bytes_transferred,
									  int success,
									  const void *completion_key,
									  u_long error)
{
	if( tcpack_ != 0 )
	{
		(*tcpack_->handler_)( ( success == 0 ) ? Tcp_success : Tcp_error ,connector_->getRemoteAddr().get_ip_address()
		, connector_->getRemoteAddr().get_port_number() );
		
#ifndef _WINXP_
		connector_->reset();
#endif
		tcpack_->cache_ .push_back( connector_ );
		tcpack_->connecting_.remove( connector_ );
	}
}

int TCPConnector::connect( )
{

#ifdef _WINXP_
	if( result_.get() == 0 )
		result_.reset( new BOE_TCPConnect_Result( tcpack_, *this,m_handle_.get_handle(), 0 ) );
	if( result->open( ) != 0 )
		return -1;
	if( ::ConnectEx( m_handle_.get_handle()
		, (const struct sockaddr*)addr.get_addr()
		, (int)addr.get_size()
		, 0
		, 0
		, 0
		, result.get() ) != TRUE )
	{
		if ( GetLastError() != ERROR_IO_PENDING )
			return -1;
	}
	return 0;
#else
	if( m_handle_.open() != 0 )
		return -1;

	if( m_handle_.enable( BOE_NONBLOCK ) != 0 )
		return -1;

	if( result_.get() == 0 )
		result_.reset( new BOE_TCPConnect_Result( tcpack_, *this,m_handle_.get_handle(), 0 ) );
	else
		result_->setHandle( m_handle_.get_handle() );

	if( ::connect( m_handle_.get_handle(), ( const sockaddr *)m_remoteaddr_.get_addr(),m_remoteaddr_.get_size() ) == SOCKET_ERROR ) 
	{
		if( WSAGetLastError() != WSAEWOULDBLOCK)
		{
			std::cout << "error : " << get_last_error() << std::endl;
			m_handle_.close();
			return -1;
		}
	}

	if( tcpack_-> proactor_ ->register_handle( result_.get() ) != 0 )
	{
		m_handle_.close();
		return -1;
	}
	return 0;
#endif // _WINXP_
}

int TCPConnector::cancel()
{
#ifdef _WINXP_
	return ( CancelIo( ( BOE_HANDLE )m_handle_.get_handle() ) == 0 ) ? -1 : 0 ;
#else
	if( tcpack_-> proactor_ ->unregister_handle( result_.get() ) != 0 )
		return -1;
	return 0;
#endif //
}

TCPackPtr createTCPack()
{
	std::auto_ptr< TCPack > ptr( new TCPack() );
	ptr->proactor_.reset( initializeCommunicator( 0, 0 ) ) );
	if( ptr->proactor_->open( 0 ) != 0 )
		return 0;
	return ptr.release();
}

BT_Export_C void freeTCPack( TCPackPtr ptr )
{
	if( ptr == 0 )
		return ;

	std::list< TCPConnector* > cache_;
	for( std::list< TCPConnector* >::iterator it = ptr-> connecting_.begin()
		; it != ptr->connecting_.end()
		; it ++ )
		(*it)->cancel();
	ptr->proactor_->close();

	for( std::list< TCPConnector* >::iterator it = ptr-> connecting_.begin()
		; it != ptr->connecting_.end()
		; it ++ )
	{
		delete (*it );
	}
	ptr-> connecting_.clear();

	for( std::list< TCPConnector* >::iterator it = ptr-> cache_.begin()
		; it != ptr->cache_.end()
		; it ++ )
	{
		delete (*it );
	}
	ptr-> cache_.clear();

	delete ptr;
}


BT_Export_C int setTCPConnectedHandler( TCPackPtr ptr ,TCPConnectedHandler handler )
{
	if( ptr == 0 )
		return -1;

	ptr->handler_ = handler;
	return 0;
}
BT_Export_C int sendTCPConnectPack_str( TCPackPtr ptr , const char* ipstr, u_short port )
{
	//	unsigned long arg = 1;
	//ioctlsocket(fd, FIONBIO, &arg);

	if( ptr == 0 )
		return -1;
	TCPConnector* connector = 0;

	if( ptr->cache_.empty() )
	{
		connector = new TCPConnector( ptr, ipstr , port );
	}
	else
	{
		std::list< TCPConnector* >::iterator it = ptr-> cache_.begin();
		connector = *it;
		connector->getRemoteAddr().set( port, ipstr );
		ptr->cache_.erase( it );
	}

	if( connector->connect( ) == 0 )
	{
		ptr->connecting_.push_back( connector );
		return 0;
	}
	
	ptr->cache_.push_back( connector );
	return -1;
}

BT_Export_C int sendTCPConnectPack( TCPackPtr ptr , long ip, u_short port )
{
	if( ptr == 0 )
		return -1;
	TCPConnector* connector = 0;

	if( ptr->cache_.empty() )
	{
		connector = new TCPConnector( ptr, ip, port );
	}
	else
	{
		std::list< TCPConnector* >::iterator it = ptr-> cache_.begin();
		connector = *it;
		connector->getRemoteAddr().set( port, ip );
		ptr->cache_.erase( it );
	}

	if( connector->connect( ) == 0 )
	{
		ptr->connecting_.push_back( connector );
		return 0;
	}
	
	ptr->cache_.push_back( connector );
	return -1;

}

void fireTCPConnectHander( TCPackPtr ptr, int value )
{
	if( ptr == 0 )
		return ;

	for( std::list< TCPConnector* >::iterator it = ptr-> connecting_.begin()
		; it != ptr->connecting_.end()
		; it ++ )
	{
		(*ptr->handler_)( value ,(*it)->getRemoteAddr().get_ip_address()
			, (*it)->getRemoteAddr().get_port_number() );
		ptr->cache_ .push_back( (*it) );
		(*it)->reset();

	}
	ptr-> connecting_.clear();


}

BT_Export_C int getTCPConnectStatus( TCPackPtr ptr , u_long milli_seconds )
{
	if( ptr == 0 )
		return -1;
	int count = 0;
repeat:
	int ret = ptr->proactor_->handle_events( milli_seconds );
	switch( ret )
	{
	case 1:
		{
#ifndef _WINXP_
			fireTCPConnectHander( ptr, Tcp_timeout );
#endif // _WINXP_
			break;
		}
	case 0:
		break;
	default:
		{
			count ++;
			if( count <= 5 )
			{
				goto repeat;
			}
			fireTCPConnectHander( ptr, Tcp_other );
		}
	}
	return ret;
}
