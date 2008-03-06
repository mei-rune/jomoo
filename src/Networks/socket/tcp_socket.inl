

inline
tcp_socket::tcp_socket (void)
: base_socket(AF_INET , SOCK_STREAM, IPPROTO_TCP )   
{
}

inline
tcp_socket::~tcp_socket (void)
{
}

inline ssize_t
tcp_socket::recv (void *buf,
                   size_t len,
                   int flags )
{

	return ::recv ( this->get_handle (),
                    ( char* )buf,
                    ( int )len,
                    flags );
}

inline ssize_t
tcp_socket::recv (void *buf,
                   size_t len )
{

	return recv (  buf,
                    len,
                    0);
}
inline ssize_t
tcp_socket::recvv (iovec iov[],
                   size_t n)
{

	DWORD NumberOfBytesRecvd = 0;
	DWORD Flags = 0;
	int r = WSARecv( get_handle()
		, iov
		, ( DWORD ) n
		, &NumberOfBytesRecvd
		, &Flags
		, 0
		, 0 );
	if( r == 0 )
		return  NumberOfBytesRecvd;
	return r;
}

inline bool
tcp_socket::recvv (iovec iov[],
					size_t n,
					JOMOO_OVERLAPPED& overlapped)
{
	DWORD NumberOfBytesRecvd = 0;
	DWORD Flags = 0;
	return (WSARecv( get_handle()
		, iov
		, ( DWORD ) n
		, &NumberOfBytesRecvd
		, &Flags
		, &overlapped
		, 0 ) == 0 ) ? true : false;
}

inline bool
tcp_socket::recv (void *buf,
				   size_t n,
				   JOMOO_OVERLAPPED& overlapped)
{
	DWORD bytes_read = 0;
	DWORD short_nbyte = static_cast < DWORD>( n);
	return ::ReadFile( ( HANDLE )this->get_handle ()
		, buf
		, short_nbyte
		, &bytes_read
		, &overlapped
		//, 0 
		) ? true : false ;
	//return r;
}

inline ssize_t
tcp_socket::send (const void *buf,
                   size_t len,
                   int flags )
{

    return ::send (get_handle(), (const char *) buf, ( int )len, flags);
}

inline ssize_t
tcp_socket::send (const void *buf,
                   size_t len )
{

    return ::send (get_handle(), (const char *) buf, ( int )len, 0);
}


inline bool 
tcp_socket::send (const void *buf,
				   size_t n,
				   JOMOO_OVERLAPPED& overlapped)
{
	DWORD bytes_written;
	DWORD short_nbyte = static_cast< DWORD >( n);
	return ::WriteFile ( ( HANDLE ) get_handle(), buf, short_nbyte, &bytes_written, &overlapped) ? true : false;
}


inline ssize_t
tcp_socket::sendv ( const iovec iov[],
                    size_t n )
{
	DWORD bytes_sent = 0;
	int r = ::WSASend ( get_handle(),
		(WSABUF *) iov,
		( DWORD )n,
		&bytes_sent,
		0,
		0,
		0);
	if( r == 0 )
		return bytes_sent;
	return r;
}

inline   bool 
tcp_socket::sendv (const iovec iov[],
					size_t n,
					JOMOO_OVERLAPPED& overlapped)
{
	DWORD bytes_sent = 0;
	return (::WSASend ( get_handle(),
		(WSABUF *) iov,
		( DWORD )n,
		&bytes_sent,
		0,
		&overlapped,
		0) == 0 ) ? true : false;
}

inline   bool 
tcp_socket::transmit (const iopack iov[],
                 size_t n,
                 JOMOO_OVERLAPPED& overlapped)
{
#ifdef _WINXP_
	return ::TransmitPackets ( get_handle(),
		( iopack* )iov,
		( DWORD )n,
		0,
		&overlapped,
		0) ? true : false;
#else
	return sendv( iov, n ,overlapped );
#endif // _WINXP_
}


inline ssize_t
tcp_socket::send (size_t n, ...)
{
  va_list argp;
  int total_tuples = static_cast< int >( n) / 2;
  std::vector< iovec > iovp( total_tuples );

  va_start (argp, n);

  for (int i = 0; i < total_tuples; i++)
    {
      iovp[i].buf = va_arg (argp, char *);
      iovp[i].len = va_arg (argp, int);
    }

  ssize_t result = sendv ( &iovp[0],
                                  total_tuples);
  va_end (argp);
  return result;
}


inline ssize_t
tcp_socket::recv (size_t n, ...)
{
	va_list argp;
	int total_tuples = static_cast< int >(n / 2);
	std::vector< iovec > iovp( total_tuples );
	va_start (argp, n);

	for (int i = 0; i < total_tuples; i++)
	{
		iovp[i].buf = va_arg (argp, char *);
		iovp[i].len = va_arg (argp, int);
	}

	ssize_t result = recvv ( &iovp[ 0 ],
		total_tuples);
	va_end (argp);
	return result;
}


inline bool tcp_socket::connect( const inet_address& addr )
{
	if( 0 != ::connect( this->get_handle(), addr.addr(), addr.size() ) )
		return false;
	
	this->remote_addr_ = addr;
	::getsockname( this->get_handle(), this->local_addr_.addr(), this->local_addr_.size() );
	return true;
}

inline bool tcp_socket::connect( const char* ip, int port )
{
	inet_address addr( port, ip );
	return connect( addr );
}

inline bool tcp_socket::connect( const inet_address& addr
 ,JOMOO_OVERLAPPED& overlapped )
{
 DWORD sendbytes = 0;
 return (TRUE == _connectex( get_handle(), addr.get_addr(), addr.get_size(), NULL, 0, &sendbytes, &overlapped));
}

inline bool tcp_socket::connect( const inet_address& addr
	 , const void* send_buffer
	 , size_t send_data_len
	 , JOMOO_OVERLAPPED& overlapped )
{
	 DWORD sendbytes = 0;
	 return (TRUE == _connectex( get_handle(), addr.get_addr(), addr.get_size(), sendBuffer, sendBufferLen, &sendbytes, &overlapped));
}

inline bool tcp_socket::accept( tcp_socket& accepted)
{
	accepted.set_handle( ::accept( get_handle(), accepted.addr(), accepted.size() ) );
	return accepted.is_good();
}

inline bool tcp_socket::accept(SOCKET accepted
						, void* data_buffer
						, size_t data_len
						, size_t local_addr_len
						, size_t remote_addr_len
						, JOMOO_OVERLAPPED& overlapped )
{
	DWORD bytesReceived = 0;
	return ( TRUE == _acceptex( get_handle(), accepted,data_buffer, data_len, local_addr_len, remote_addr_len, &bytesReceived, &overlapped ));
}
