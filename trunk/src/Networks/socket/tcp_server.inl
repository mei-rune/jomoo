

JOMOO_INLINE tcp_server::tcp_server (void)
: socket_(AF_INET , SOCK_STREAM, IPPROTO_TCP )
{
	toString_ = "tcp_server - " + socket_.toString();
}

JOMOO_INLINE tcp_server::~tcp_server (void)
{
}

JOMOO_INLINE base_socket& tcp_server::socket()
{
	return socket_;
}

JOMOO_INLINE  const base_socket& tcp_server::socket() const
{
	return socket_;
}

JOMOO_INLINE  const inet_address& tcp_server::bind_addr() const
{
	return bind_addr_;
}

JOMOO_INLINE bool tcp_server::is_good() const
{
	return socket_.is_good();
}

JOMOO_INLINE bool tcp_server::bind( const inet_address& addr)
{
	if ( SOCKET_ERROR != ::bind( socket_.get_handle(), addr.addr(), addr.size() ) )
	{
		bind_addr_ = addr;
		toString_ = "tcp_server " + socket_.toString() + " °ó¶¨ÔÚ " + bind_addr_.toString();
		return true;
	}
	return false;
}

JOMOO_INLINE bool tcp_server::listen( int backlog )
{
	if( SOCKET_ERROR != ::listen( socket_.get_handle(), backlog ) )
	{
		toString_ = "tcp_server " + socket_.toString() + " ¼àÌýÔÚ " + bind_addr_.toString();
		return true;
	}
	return false;
}

JOMOO_INLINE bool tcp_server::accept( tcp_client& accepted)
{
	int len = accepted.remote_addr().size();
	accepted.socket().set_handle( ::accept( socket_.get_handle(),( sockaddr* ) accepted.remote_addr().addr(),&len ) );
	return accepted.is_good();
}

JOMOO_INLINE bool tcp_server::accept(tcp_client& accepted
						, void* data_buffer
						, size_t data_len
						, size_t local_addr_len
						, size_t remote_addr_len
						, JOMOO_OVERLAPPED& overlapped )
{
	DWORD bytesReceived = 0;
	return ( TRUE == base_socket::__acceptex( socket_.get_handle(), accepted.socket().get_handle(),data_buffer, data_len, local_addr_len, remote_addr_len, &bytesReceived, &overlapped ));
}

JOMOO_INLINE void tcp_server::swap( tcp_server& r)
{
	bind_addr_.swap( r.bind_addr_ );
	socket_.swap( r.socket_ );
	toString_.swap( r.toString_ );
}

JOMOO_INLINE const tstring& tcp_server::toString( ) const
{
	return toString_;
}