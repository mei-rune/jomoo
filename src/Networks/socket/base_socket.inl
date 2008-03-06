
inline base_socket::base_socket (void)
: handle_ (INVALID_SOCKET )
, blocking_( true )
{
}

inline base_socket::base_socket (int type, 
                    int protocol_family, 
                    int protocol,
                    int reuse_addr)
: handle_ (INVALID_SOCKET )
, blocking_( true )
{
  this->open (type,
                  protocol_family, 
                  protocol,
                  reuse_addr);
}

inline base_socket::base_socket (int type, 
                    int protocol_family, 
                    int protocol,
                    WSAPROTOCOL_INFO *protocolinfo,
                    JOMOO_SOCK_GROUP g,
                    u_long flags,
                    int reuse_addr)
: handle_ (INVALID_SOCKET )
, blocking_( true )
{
  this->open (type,
                  protocol_family,
                  protocol,
                  protocolinfo,
                  g,
                  flags,
                  reuse_addr);				  
}

inline base_socket::~base_socket (void)
{
	close();
}

inline bool base_socket::is_good() const
{
	return INVALID_SOCKET != this->get_handle ();
}

inline int base_socket::open (int type, 
                int protocol_family, 
                int protocol,
                int reuse_addr)
{
int one = 1;

  this->set_handle (socket (protocol_family,
                                    type,
                                    protocol));

  if (this->get_handle () == INVALID_SOCKET )
    return -1;
  else if (protocol_family != PF_UNIX 
           && reuse_addr 
           && this->set_option (SOL_SOCKET,
                                SO_REUSEADDR,
                                &one,
                                sizeof one) == -1)
    {
      this->close ();
      return -1;
    }
  return 0;
}

inline int base_socket::open (int type, 
                int protocol_family, 
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
    return -1;
  else if (reuse_addr 
           && this->set_option (SOL_SOCKET,
                                SO_REUSEADDR,
                                &one,
                                sizeof one) == -1)
    {
      this->close ();
	return -1;
    }
  else
    return 0;
}

inline SOCKET base_socket::get_handle (void) const
{
  return this->handle_;
}


inline void base_socket::set_handle (SOCKET handle)
{
  this->handle_ = handle;
}

inline void base_socket::swap( base_socket& r )
{
	std::swap( this->handle_, r.handle_ );
	std::swap( this->blocking_, r.blocking_ );
	this->local_addr_.swap( r.local_addr_ );
	this->remote_addr_.swap( r.remote_addr_ );
}

inline int base_socket::set_option (int level, 
		      int option, 
		      void *optval, 
		      int optlen) const
{
  return setsockopt (this->get_handle (), level, 
			     option, (char *) optval, optlen);
}

inline int base_socket::get_option (int level, 
		      int option, 
		      void *optval, 
		      int *optlen) const
{
  return getsockopt (this->get_handle (), level, 
			     option, (char *) optval, optlen);
}

inline bool base_socket::enable (int value)
{
	u_long nonblock = 1;
	return ( 0 ==::ioctlsocket (this->handle_,
		value,
		&nonblock));
}

inline bool base_socket::disable (int value)
{
    u_long nonblock = 0;
    return ( 0 == ioctlsocket (this->handle_,
                              value,
                              &nonblock));
}


inline const inet_address& base_socket::remote_addr () const
{
	return remote_addr_;
}

inline const inet_address& base_socket::local_addr () const
{
  return local_addr_;
}

inline void base_socket::close (void)
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

inline bool base_socket::poll( const TIMEVAL& time_val, int mode)
{
	fd_set socket_set;
	FD_ZERO( &socket_set );
	FD_SET(get_handle(), &socket_set );

	return ( 1 == ::select( 0, (mode == select_mode::select_read)?&socket_set:NULL
		, (mode == select_mode::select_write)?&socket_set:NULL
		, (mode == select_mode::select_error)?&socket_set:NULL
		, &time_val ) );
}

inline bool base_socket::readable()
{
	TIMEVAL time_val;
	time_val.tv_sec = 0;
	time_val.tv_usec = 0;
	return poll( time_val, select_mode::select_read );
}

inline bool base_socket::writable()
{
	TIMEVAL time_val;
	time_val.tv_sec = 0;
	time_val.tv_usec = 0;
	return poll( time_val, select_mode::select_write );
}

inline void base_socket::blocking(bool val)
{
	if( val )
	{
		enable( FIONBIO );
		blocking_ = false;
	}
	else
	{
		disable( FIONBIO );
		blocking_ = true;
	}
}

inline bool base_socket::blocking() const
{
	return blocking_;
}

inline bool  base_socket::initsocket()
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
		&_connectex,
		sizeof(_connectex),
		&dwBytes,
		NULL,
		NULL))
	{
		_connectex = NULL;
	}

	
	dwBytes = 0;
	if( SOCKET_ERROR == WSAIoctl(cliSock,
		SIO_GET_EXTENSION_FUNCTION_POINTER,
		&GuidDisconnectEx,
		sizeof(GuidDisconnectEx),
		&_disconnectex,
		sizeof(_disconnectex),
		&dwBytes,
		NULL,
		NULL))
	{
		_disconnectex = NULL;
	}

	dwBytes = 0;
	if( SOCKET_ERROR == WSAIoctl(cliSock,
		SIO_GET_EXTENSION_FUNCTION_POINTER,
		&GuidTransmitFile,
		sizeof(GuidTransmitFile),
		&_transmitfile,
		sizeof(_transmitfile),
		&dwBytes,
		NULL,
		NULL))
	{
		_transmitfile = NULL;
	}
	
	dwBytes = 0;
	if( SOCKET_ERROR == WSAIoctl(cliSock,
		SIO_GET_EXTENSION_FUNCTION_POINTER,
		&GuidAcceptEx,
		sizeof(GuidAcceptEx),
		&_acceptex,
		sizeof(_acceptex),
		&dwBytes,
		NULL,
		NULL))
	{
		_acceptex = NULL;
	}

	dwBytes = 0;
	if( SOCKET_ERROR == WSAIoctl(cliSock,
		SIO_GET_EXTENSION_FUNCTION_POINTER,
		&GuidTransmitPackets,
		sizeof(GuidTransmitPackets),
		&_transmitpackets,
		sizeof(_transmitpackets),
		&dwBytes,
		NULL,
		NULL))
	{
		_transmitpackets = NULL;
	}

	dwBytes = 0;
	if( SOCKET_ERROR == WSAIoctl(cliSock,
		SIO_GET_EXTENSION_FUNCTION_POINTER,
		&GuidGetAcceptExSockAddrs,
		sizeof(GuidGetAcceptExSockAddrs),
		&_getacceptexsockaddrs,
		sizeof(_getacceptexsockaddrs),
		&dwBytes,
		NULL,
		NULL))
	{
		_getacceptexsockaddrs = NULL;
	}

	closesocket(  cliSock );

	return true;
}

inline void base_socket::shutdownsock()
{
	WSACleanup( );
}