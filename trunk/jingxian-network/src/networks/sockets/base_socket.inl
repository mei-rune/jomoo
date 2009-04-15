

LPFN_TRANSMITFILE base_socket::__transmitfile = 0;
LPFN_ACCEPTEX base_socket::__acceptex = 0;
LPFN_TRANSMITPACKETS base_socket::__transmitpackets = 0;
LPFN_CONNECTEX base_socket::__connectex = 0;
LPFN_DISCONNECTEX base_socket::__disconnectex = 0;
LPFN_GETACCEPTEXSOCKADDRS base_socket::__getacceptexsockaddrs = 0;


JOMOO_INLINE base_socket::base_socket (void)
: handle_ (INVALID_SOCKET )
, toString_( _T("INVALID_SOCKET" ))

{
}

JOMOO_INLINE base_socket::base_socket (int protocol_family,
					int type, 
					int protocol,
                    int reuse_addr)
: handle_ (INVALID_SOCKET )
, toString_( _T("INVALID_SOCKET") )
{
  this->open (protocol_family,
				  type, 
                  protocol,
                  reuse_addr);
}

JOMOO_INLINE base_socket::base_socket (int protocol_family,
					int type, 
					int protocol,
                    WSAPROTOCOL_INFO *protocolinfo,
                    JOMOO_SOCK_GROUP g,
                    u_long flags,
                    int reuse_addr)
: handle_ (INVALID_SOCKET )
{
  this->open ( protocol_family,
				  type,
                  protocol,
                  protocolinfo,
                  g,
                  flags,
                  reuse_addr);				  
}

JOMOO_INLINE base_socket::~base_socket (void)
{
	close();
}

JOMOO_INLINE bool base_socket::is_good() const
{
	return INVALID_SOCKET != this->get_handle ();
}

JOMOO_INLINE bool base_socket::open ( int protocol_family,
				int type, 
                int protocol,
                int reuse_addr)
{
  int one = 1;

  this->set_handle (socket (protocol_family,
                                    type,
                                    protocol));

  if (this->get_handle () == INVALID_SOCKET )
    return false;
  else if (protocol_family != PF_UNIX 
           && reuse_addr 
           && !this->set_option (SOL_SOCKET,
                                SO_REUSEADDR,
                                &one,
                                sizeof one) )
    {
      this->close ();
      return false;
    }
  return true;
}

JOMOO_INLINE bool base_socket::open (int protocol_family,
				int type, 
                int protocol,
                WSAPROTOCOL_INFO *protocolinfo,
                JOMOO_SOCK_GROUP g,
                u_long flags,
                int reuse_addr)
{
  this->set_handle (::WSASocket (protocol_family,
                                    type,
                                    protocol,
                                    protocolinfo,
                                    g,
                                    flags));
  int one = 1;

  if (this->get_handle () == INVALID_SOCKET )
    return false;
  else if (reuse_addr 
           && !this->set_option (SOL_SOCKET,
                                SO_REUSEADDR,
                                &one,
                                sizeof one))
    {
      this->close ();
	  return false;
    }
  else
    return true;
}

JOMOO_INLINE SOCKET base_socket::get_handle (void) const
{
  return this->handle_;
}


JOMOO_INLINE void base_socket::set_handle (SOCKET handle)
{
  close();
  this->handle_ = handle;
}

JOMOO_INLINE void base_socket::swap( base_socket& r )
{
	std::swap( this->handle_, r.handle_ );
}

JOMOO_INLINE bool base_socket::set_option (int level, 
		      int option, 
		      void *optval, 
		      int optlen) const
{
  return ( SOCKET_ERROR == setsockopt (this->get_handle (), level, 
			     option, (char *) optval, optlen) );
}

JOMOO_INLINE bool base_socket::get_option (int level, 
		      int option, 
		      void *optval, 
		      int *optlen) const
{
  return ( SOCKET_ERROR == getsockopt (this->get_handle (), level, 
			     option, (char *) optval, optlen) );
}

JOMOO_INLINE bool base_socket::enable (int value)
{
	u_long nonblock = 1;
	return ( 0 ==::ioctlsocket (this->handle_,
		value,
		&nonblock));
}

JOMOO_INLINE bool base_socket::disable (int value)
{
    u_long nonblock = 0;
    return ( 0 == ioctlsocket (this->handle_,
                              value,
                              &nonblock));
}

JOMOO_INLINE void base_socket::close (void)
{
	if (INVALID_SOCKET == this->get_handle () )
		return;

	for( int i =0 ; i < 5; i ++ )
	{
		if( 0 == closesocket (this->get_handle ()) )
		{
			this->set_handle (INVALID_SOCKET );
			return ;
		}
	}
}

JOMOO_INLINE bool base_socket::poll( const TIMEVAL& time_val, int mode)
{
	fd_set socket_set;
	FD_ZERO( &socket_set );
	FD_SET(get_handle(), &socket_set );

	return ( 1 == ::select( 0, (mode == select_read)?&socket_set:NULL
		, (mode == select_write)?&socket_set:NULL
		, (mode == select_error)?&socket_set:NULL
		, &time_val ) );
}

JOMOO_INLINE const string& base_socket::toString() const
{
  if( INVALID_SOCKET == handle_)
  {
	  toString_ = _T("INVALID_SOCKET" );
  }
  else
  {
	  string::value_type tmp[1024];
 #pragma warning(disable: 4244)
	  string_traits< string::value_type >::itoa( handle_, tmp, 1024, 10 );
 #pragma warning(default: 4244)

	  toString_ = tmp;
  }
  return toString_;
}

JOMOO_INLINE bool  base_socket::initsocket()
{
	WSADATA wsaData;
	if ( 0 != WSAStartup( MAKEWORD( 2, 2 ), &wsaData ) )
		return false;
	
	if ( LOBYTE( wsaData.wVersion ) != 2 ||
		HIBYTE( wsaData.wVersion ) != 2 )
	{
			WSACleanup( );
			return false; 
	}

	SOCKET cliSock = ::socket( AF_INET , SOCK_STREAM, IPPROTO_TCP);

	GUID GuidConnectEx = WSAID_CONNECTEX;
	GUID GuidDisconnectEx = WSAID_DISCONNECTEX;
	GUID GuidGetAcceptExSockAddrs = WSAID_GETACCEPTEXSOCKADDRS;
	GUID GuidAcceptEx = WSAID_ACCEPTEX;
	GUID GuidTransmitFile = WSAID_TRANSMITFILE;
	GUID GuidTransmitPackets = WSAID_TRANSMITPACKETS;

	DWORD dwBytes = 0;
	if( SOCKET_ERROR == WSAIoctl(cliSock,
		SIO_GET_EXTENSION_FUNCTION_POINTER,
		&GuidConnectEx,
		sizeof(GuidConnectEx),
		&__connectex,
		sizeof(__connectex),
		&dwBytes,
		NULL,
		NULL))
	{
		__connectex = NULL;
	}

	
	dwBytes = 0;
	if( SOCKET_ERROR == WSAIoctl(cliSock,
		SIO_GET_EXTENSION_FUNCTION_POINTER,
		&GuidDisconnectEx,
		sizeof(GuidDisconnectEx),
		&__disconnectex,
		sizeof(__disconnectex),
		&dwBytes,
		NULL,
		NULL))
	{
		__disconnectex = NULL;
	}

	dwBytes = 0;
	if( SOCKET_ERROR == WSAIoctl(cliSock,
		SIO_GET_EXTENSION_FUNCTION_POINTER,
		&GuidTransmitFile,
		sizeof(GuidTransmitFile),
		&__transmitfile,
		sizeof(__transmitfile),
		&dwBytes,
		NULL,
		NULL))
	{
		__transmitfile = NULL;
	}
	
	dwBytes = 0;
	if( SOCKET_ERROR == WSAIoctl(cliSock,
		SIO_GET_EXTENSION_FUNCTION_POINTER,
		&GuidAcceptEx,
		sizeof(GuidAcceptEx),
		&__acceptex,
		sizeof(__acceptex),
		&dwBytes,
		NULL,
		NULL))
	{
		__acceptex = NULL;
	}

	dwBytes = 0;
	if( SOCKET_ERROR == WSAIoctl(cliSock,
		SIO_GET_EXTENSION_FUNCTION_POINTER,
		&GuidTransmitPackets,
		sizeof(GuidTransmitPackets),
		&__transmitpackets,
		sizeof(__transmitpackets),
		&dwBytes,
		NULL,
		NULL))
	{
		__transmitpackets = NULL;
	}

	dwBytes = 0;
	if( SOCKET_ERROR == WSAIoctl(cliSock,
		SIO_GET_EXTENSION_FUNCTION_POINTER,
		&GuidGetAcceptExSockAddrs,
		sizeof(GuidGetAcceptExSockAddrs),
		&__getacceptexsockaddrs,
		sizeof(__getacceptexsockaddrs),
		&dwBytes,
		NULL,
		NULL))
	{
		__getacceptexsockaddrs = NULL;
	}

	closesocket(  cliSock );

	return true;
}

JOMOO_INLINE void base_socket::shutdownsock()
{
	WSACleanup( );
}