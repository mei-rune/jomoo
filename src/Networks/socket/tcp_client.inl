

JOMOO_INLINE tcp_client::tcp_client (void)
: socket_(AF_INET , SOCK_STREAM, IPPROTO_TCP )   
, blocking_( true )
{
}

JOMOO_INLINE tcp_client::~tcp_client (void)
{
}

JOMOO_INLINE bool tcp_client::readable()
{
	TIMEVAL time_val;
	time_val.tv_sec = 0;
	time_val.tv_usec = 0;
	return socket_.poll( time_val, select_mode::select_read );
}

JOMOO_INLINE bool tcp_client::writable()
{
	TIMEVAL time_val;
	time_val.tv_sec = 0;
	time_val.tv_usec = 0;
	return socket_.poll( time_val, select_mode::select_write );
}

JOMOO_INLINE void tcp_client::blocking(bool val)
{
	if( val )
	{
		socket_.enable( FIONBIO );
		blocking_ = false;
	}
	else
	{
		socket_.disable( FIONBIO );
		blocking_ = true;
	}
}

JOMOO_INLINE bool tcp_client::blocking() const
{
	return blocking_;
}

JOMOO_INLINE const inet_address& tcp_client::remote_addr () const
{
	return remote_addr_;
}

JOMOO_INLINE const inet_address& tcp_client::local_addr () const
{
  return local_addr_;
}

JOMOO_INLINE base_socket& tcp_client::socket()
{
	return socket_;
}
	
JOMOO_INLINE const base_socket& tcp_client::socket() const
{
	return socket_;
}

JOMOO_INLINE bool tcp_client::is_good() const
{
	return socket_.is_good();
}

JOMOO_INLINE ssize_t tcp_client::recv (void *buf,
                   size_t len,
                   int flags )
{

	return ::recv ( socket_.get_handle (),
                    ( char* )buf,
                    ( int )len,
                    flags );
}

JOMOO_INLINE ssize_t tcp_client::send (const void *buf,
                   size_t len,
                   int flags )
{

    return ::send (socket_.get_handle(), (const char *) buf, ( int )len, flags);
}

JOMOO_INLINE ssize_t tcp_client::recvv (iovec* iov, size_t n)
{
	DWORD bytes_recvd = 0;
	DWORD Flags = 0;
	int r = WSARecv( socket_.get_handle()
		, iov
		, ( DWORD ) n
		, &bytes_recvd
		, &Flags
		, 0
		, 0 );
	if( SOCKET_ERROR != r )
		return  bytes_recvd;
	return r;
}

JOMOO_INLINE ssize_t tcp_client::sendv ( const iovec* iov,
                    size_t n )
{
	DWORD bytes_sent = 0;
	int r = ::WSASend ( socket_.get_handle(),
		(WSABUF *) iov,
		( DWORD )n,
		&bytes_sent,
		0,
		0,
		0);
	if( SOCKET_ERROR != r )
		return bytes_sent;
	return r;
}

JOMOO_INLINE bool tcp_client::send_n( const char* buf, size_t length)
{
	do
	{
		int n = ::send( socket_.get_handle(), buf, length, 0 ); 

		if( 0 >= n)
			return false;

		length -= n;
		buf += n;
	}while( 0 < length );

	return true;
}

JOMOO_INLINE bool tcp_client::recv_n( char* buf, size_t length)
{
	do
	{
		int n = ::recv( socket_.get_handle(), buf, length, 0 ); 

		if( 0 >= n)
			return false;

		length -= n;
		buf += n;
	}while( 0 < length );

	return true;
}

JOMOO_INLINE bool tcp_client::sendv_n( const iovec* wsaBuf, size_t size)
{
	std::vector<iovec> buf( wsaBuf, wsaBuf + size );
	iovec* p = &buf[0];

	do
	{
		DWORD numberOfBytesSent =0;
		if( SOCKET_ERROR == ::WSASend( socket_.get_handle(), p, size, &numberOfBytesSent,0,0 , 0 ) )
			return false;

		do
		{
			if( numberOfBytesSent < p->len)
			{
				p->len -= numberOfBytesSent;
				p->buf = p->buf + numberOfBytesSent;
				break;
			}
			numberOfBytesSent -= p->len;
			++ p;
			-- size;
		}
		while( 0 < numberOfBytesSent );
	}
	while( 0 < size );

	return true;
}

JOMOO_INLINE bool tcp_client::recvv_n( iovec* wsaBuf, size_t size)
{
	iovec* p = wsaBuf;

	do
	{
		DWORD numberOfBytesRecvd =0;
		if( SOCKET_ERROR == ::WSARecv( socket_.get_handle(), p, size, &numberOfBytesRecvd,0,0 , 0 ) )
			return false;

		do
		{
			if( numberOfBytesRecvd < p->len)
			{
				p->len -= numberOfBytesRecvd;
				p->buf = p->buf + numberOfBytesRecvd;
				break;
			}
			numberOfBytesRecvd -= p->len;
			++ p;
			-- size;
		}
		while( 0 < numberOfBytesRecvd );
	}
	while( 0 < size );

	return true;
}

JOMOO_INLINE bool tcp_client::send (const void *buf, size_t n,
				   JOMOO_OVERLAPPED& overlapped)
{
	DWORD bytes_written;
	DWORD short_nbyte = static_cast< DWORD >( n);
	return ::WriteFile ( ( HANDLE ) socket_.get_handle(), buf, short_nbyte, &bytes_written, &overlapped) ? true : false;
}

JOMOO_INLINE bool tcp_client::recvv (iovec* iov, size_t n,
					JOMOO_OVERLAPPED& overlapped)
{
	DWORD NumberOfBytesRecvd = 0;
	DWORD Flags = 0;
	return (WSARecv( socket_.get_handle()
		, iov
		, ( DWORD ) n
		, &NumberOfBytesRecvd
		, &Flags
		, &overlapped
		, 0 ));
}

JOMOO_INLINE bool tcp_client::recv (void *buf, size_t n,
				   JOMOO_OVERLAPPED& overlapped)
{
	DWORD bytes_read = 0;
	return ::ReadFile( ( HANDLE )socket_.get_handle ()
		, buf
		, static_cast < DWORD>( n)
		, &bytes_read
		, &overlapped );
}

JOMOO_INLINE   bool tcp_client::transmit (const iopack* iov, size_t n )
{
	return ( TRUE == base_socket::__transmitpackets( socket_.get_handle(),
		( iopack* )iov,
		( DWORD )n,
		0,
		0,
		0) );
}

JOMOO_INLINE   bool tcp_client::transmit (const iopack* iov, size_t n,
                 JOMOO_OVERLAPPED& overlapped)
{
	return ( TRUE == base_socket::__transmitpackets( socket_.get_handle(),
		( iopack* )iov,
		( DWORD )n,
		0,
		&overlapped,
		0) );
}

JOMOO_INLINE bool tcp_client::transmit ( HANDLE hFile
				, size_t nNumberOfBytesToWrite
				, size_t nNumberOfBytesPerSend
				, io_file_buf* transmitBuffers )
{
	return (base_socket::__transmitfile( socket_.get_handle(),
		hFile,
        (DWORD) nNumberOfBytesToWrite,
        (DWORD) nNumberOfBytesPerSend,
        0,
		transmitBuffers,
        0 ) );
}

JOMOO_INLINE bool tcp_client::transmit ( HANDLE hFile
				, size_t nNumberOfBytesToWrite
				, size_t nNumberOfBytesPerSend
				, io_file_buf* transmitBuffers
                , JOMOO_OVERLAPPED& overlapped)
{
	return ( base_socket::__transmitfile( socket_.get_handle(),
		hFile,
        (DWORD) nNumberOfBytesToWrite,
        (DWORD) nNumberOfBytesPerSend,
        &overlapped,
		transmitBuffers,
        0 ) );
}

JOMOO_INLINE bool tcp_client::connect( const inet_address& addr )
{
	if( 0 != ::connect( this->socket_.get_handle(), addr.addr(), addr.size() ) )
		return false;
	
	this->remote_addr_ = addr;
	int len = this->local_addr_.size();
	::getsockname( this->socket_.get_handle(), this->local_addr_.addr(), &len );
	return true;
}

JOMOO_INLINE bool tcp_client::connect( const inet_address& addr
									  ,JOMOO_OVERLAPPED& overlapped )
{
 DWORD sendbytes = 0;
 return (TRUE == base_socket::__connectex( socket_.get_handle(), addr.addr(), addr.size(), NULL, 0, &sendbytes, &overlapped));
}

JOMOO_INLINE bool tcp_client::connect( const inet_address& addr
									  , const void* send_buffer
									  , size_t send_data_len
									  , JOMOO_OVERLAPPED& overlapped )
{
	 DWORD sendbytes = 0;
	 return (TRUE == base_socket::__connectex( socket_.get_handle(), addr.addr(), addr.size(), (void*)send_buffer, send_data_len, &sendbytes, &overlapped));
}
