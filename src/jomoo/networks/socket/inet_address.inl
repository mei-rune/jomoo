

inline inet_address::inet_address (void)
{
	this->reset ();
}

inline inet_address::inet_address (const inet_address &sa)
{
	this->reset ();
	*this = sa;
}

inline inet_address::inet_address (const sockaddr_in *addr, int len)
{
	this->reset ();
	this->addr(addr, len);
}

inline inet_address::inet_address (const void* addr, int len)
{
	this->reset ();
	this->addr(addr, len);
}

inline inet_address::inet_address ( u_long ip,u_short number )
{
	this->reset ();
	this->ip( ip );
	this->port( number );
}

inline inet_address::inet_address ( const char* ipstr,u_short number)
{
	this->reset ();
	this->ip( ipstr );
	this->port( number );
}

inline inet_address::inet_address ( const char* ipstr, const char* number)
{
	this->reset ();
	this->ip( ipstr );
	this->port( number );
}

inline inet_address::inet_address (const char* address)
{
	this->reset ();
	this->parse( address );
}

inline inet_address::~inet_address (void)
{
}

inline bool inet_address::operator != (const inet_address &sap) const
{
	return !((*this) == sap);
}

inline bool inet_address::operator == (const inet_address &sap) const
{
	return (::memcmp (&this->m_addr_,
		&sap.m_addr_,
		this->size ()) == 0);
}

inline bool inet_address::operator < (const inet_address &rhs) const
{
  return (::memcmp (&this->m_addr_,
		&rhs.m_addr_,
		this->size ()) < 0 );
}

inline bool inet_address::operator > (const inet_address &rhs) const
{
  return (::memcmp (&this->m_addr_,
		&rhs.m_addr_,
		this->size ()) > 0 );
}

inline inet_address& inet_address::operator=( const inet_address& sa)
{
	if( this != &sa)
		::memcpy( &this->m_addr_, &sa.m_addr_, sa.size () );

	return *this;
}


inline void inet_address::swap( inet_address& r)
{
	sockaddr address;
	memcpy( &address, &this->m_addr_, sizeof( sockaddr ) );
	memcpy( &this->m_addr_, &r.m_addr_, sizeof( sockaddr ) );
	memcpy( &r.m_addr_, &address, sizeof( sockaddr ) );
}

inline void inet_address::reset (void)
{
  memset (&this->m_addr_ , 0, sizeof (this->m_addr_ ));
  this->m_addr_.sa_family = AF_INET;
}

inline void inet_address::port(u_short number,
							   bool encode )
{
	((sockaddr_in*) &m_addr_)->sin_port = encode?htons (number):number;
}

inline void inet_address::port( const char* number )
{
	((sockaddr_in*) &m_addr_)->sin_port = htons( ::atoi( number ) );
}

inline u_short inet_address::port( void ) const 
{
	return htons( ((sockaddr_in*) &m_addr_)->sin_port );
}

inline void inet_address::ip( u_long ip , bool encode )
{
	((sockaddr_in*) &m_addr_)->sin_addr.s_addr = encode? htonl ( ip ) : ip;
}

inline void inet_address::ip( const char* ipstr )
{
	((sockaddr_in*) &m_addr_)->sin_addr.s_addr = ::inet_addr( ipstr );
}

inline u_long inet_address::ip ( void ) const
{
	return (((sockaddr_in*) &m_addr_)->sin_addr .s_addr);
}

inline const tstring& inet_address::ip_string ( ) const
{
	ip_string_ = ::inet_ntoa(((sockaddr_in*) &m_addr_)->sin_addr );
	return ip_string_;
}

inline size_t inet_address::size (void) const
{
	return sizeof( this->m_addr_ );
}

inline void inet_address::size (size_t size)
{
}

inline const sockaddr* inet_address::addr (void) const
{
	return &(this->m_addr_);
}

inline sockaddr* inet_address::addr (void)
{
	return &(this->m_addr_);
}

inline void inet_address::addr ( const void * address, size_t len)
{
	if( len > size() )
		memcpy( addr(), address, size() );
	else
		memcpy( addr(), address, len );
}

inline bool inet_address::parse (const char* address)
{
	if( strnicmp( address, "TCP://", 6 ) == 0 )
		address += 6;
	else if( strstr( address, "://" ) != 0 )
		return false;

	std::vector< char > ip_addr( strlen( address ) + 10 , 0 );
	string_traits<char>::strcpy( &ip_addr[ 0 ], ip_addr.size(), address );
	char *port_p = ::strrchr (&ip_addr[0], ':');

	if (port_p == 0) 
	{
		u_long ip = inet_addr( &ip_addr[0] );
		if( ip == INADDR_NONE )
			return false;
		this->ip( ip );
		return true;
	}
	else
	{
		*port_p = '\0'; ++port_p;
		u_long ip = inet_addr( &ip_addr[0] );
		if( ip == INADDR_NONE )
			return false;
		this->ip( ip );
		this->port( port_p );
		return true;
	}
}

inline const tstring& inet_address::toString( ) const
{
	char* ipstr = inet_ntoa( ((sockaddr_in*) &m_addr_)->sin_addr );
	if( ipstr == 0 )
	{
		to_string_.clear();
		return to_string_;
	}

	to_string_ = ipstr;

	char tmp[ 100 ] = "";
	_itoa_s( port(), tmp, 100, 10);

	to_string_ += ':';
	to_string_ += tmp;
	return to_string_;
}