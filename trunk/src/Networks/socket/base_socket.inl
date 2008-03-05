
JOMOO_INLINE
base_socket::base_socket (void)
: handle_ (INVALID_SOCKET )
{
}

JOMOO_INLINE
base_socket::base_socket (int type, 
                    int protocol_family, 
                    int protocol,
                    int reuse_addr)
					  : handle_ (INVALID_SOCKET )
{
  this->open (type,
                  protocol_family, 
                  protocol,
                  reuse_addr);
}

JOMOO_INLINE
base_socket::base_socket (int type, 
                    int protocol_family, 
                    int protocol,
                    WSAPROTOCOL_INFO *protocolinfo,
                    JOMOO_SOCK_GROUP g,
                    u_long flags,
                    int reuse_addr)
					  : handle_ (INVALID_SOCKET )
{
  this->open (type,
                  protocol_family,
                  protocol,
                  protocolinfo,
                  g,
                  flags,
                  reuse_addr);				  
}

JOMOO_INLINE
base_socket::~base_socket (void)
{
	close();
}

JOMOO_INLINE bool base_socket::is_good() const
{
	return INVALID_SOCKET != this->get_handle ();
}

JOMOO_INLINE int base_socket::open (int type, 
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

JOMOO_INLINE int base_socket::open (int type, 
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

JOMOO_INLINE SOCKET
base_socket::get_handle (void) const
{
  return this->handle_;
}


JOMOO_INLINE void
base_socket::set_handle (SOCKET handle)
{
  this->handle_ = handle;
}

JOMOO_INLINE void
base_socket::swap( base_socket& r )
{
	std::swap( this->handle_, r.handle_ );
}

//JOMOO_INLINE int 
//base_socket::control (int cmd, void *arg) const
//{
//  return ::ioctlsocket (this->handle_, cmd, arg);
//}

JOMOO_INLINE int 
base_socket::set_option (int level, 
		      int option, 
		      void *optval, 
		      int optlen) const
{
  return setsockopt (this->get_handle (), level, 
			     option, (char *) optval, optlen);
}

JOMOO_INLINE int 
base_socket::get_option (int level, 
		      int option, 
		      void *optval, 
		      int *optlen) const
{
  return getsockopt (this->get_handle (), level, 
			     option, (char *) optval, optlen);
}

JOMOO_INLINE int base_socket::enable (int value) const
{
  switch (value)
    {
    case JOMOO_NONBLOCK:
      {
        u_long nonblock = 1;
		return ::ioctlsocket (this->handle_,
                              FIONBIO,
                              &nonblock);
      }
    default:
      return (-1);
    }
}

JOMOO_INLINE int base_socket::disable (int value) const
{
  switch (value)
    {
    case JOMOO_NONBLOCK:
      {
        u_long nonblock = 0;
        return ioctlsocket (this->handle_,
                              FIONBIO,
                              &nonblock);
      }
    default:
       return (-1);
    }
}


JOMOO_INLINE int base_socket::get_remote_addr (JOMOO_INET_Addr &sa) const
{
  int len = sa.get_size ();
  sockaddr *addr = reinterpret_cast< sockaddr * >( sa.get_addr ());

  if ( getpeername (this->get_handle (),
                           addr,
                           &len) == -1)
    return -1;
  
  sa.set_size (len);
  return 0;
}

JOMOO_INLINE int base_socket::get_local_addr (JOMOO_INET_Addr &sa) const
{
  int len = sa.get_size ();
  sockaddr *addr = reinterpret_cast< sockaddr * >( sa.get_addr ());

  if ( getsockname (this->get_handle (),
                           addr,
                           &len) == -1)
    return -1;

  sa.set_size (len);
  return 0;
}

// Close down a base_socket.

JOMOO_INLINE int base_socket::close (void)
{
  int result = 0;
  if (INVALID_SOCKET != this->get_handle () )
    {
      result = closesocket (this->get_handle ());
      this->set_handle (INVALID_SOCKET );
    }
  return result;
}

JOMOO_INLINE int  base_socket::initsocket()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD( 2, 2 );

	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) {
		/* Tell the user that we could not find a usable */
		/* WinSock DLL.                                  */
		return -1;
	}

	/* Confirm that the WinSock DLL supports 2.2.*/
	/* Note that if the DLL supports versions greater    */
	/* than 2.2 in addition to 2.2, it will still return */
	/* 2.2 in wVersion since that is the version we      */
	/* requested.                                        */

	if ( LOBYTE( wsaData.wVersion ) != 2 ||
		HIBYTE( wsaData.wVersion ) != 2 ) {
			/* Tell the user that we could not find a usable */
			/* WinSock DLL.                                  */
			WSACleanup( );
			return -1; 
		}
		return 0;
}
JOMOO_INLINE void base_socket::shutdownsock()
{
	WSACleanup( );
}