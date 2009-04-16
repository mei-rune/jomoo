
# include "pro_config.h"
# include <vector>
# include "inet_address.h"

_jingxian_begin

 inet_address::inet_address (void)
{
	this->reset ();
}

 inet_address::inet_address (const inet_address &sa)
{
	this->reset ();
	*this = sa;
}

 inet_address::inet_address (const sockaddr_in *addr, int len)
{
	this->reset ();
	this->addr(addr, len);
}

 inet_address::inet_address (const void* addr, int len)
{
	this->reset ();
	this->addr(addr, len);
}

 inet_address::inet_address ( u_long ip,u_short number )
{
	this->reset ();
	this->ip( ip );
	this->port( number );
}

 inet_address::inet_address ( const char* ipstr,u_short number)
{
	this->reset ();
	this->ip( ipstr );
	this->port( number );
}

 inet_address::inet_address ( const char* ipstr, const char* number)
{
	this->reset ();
	this->ip( ipstr );
	this->port( number );
}

 inet_address::inet_address (const char* address)
{
	this->reset ();
	this->parse( address );
}

 inet_address::~inet_address (void)
{
}

 bool inet_address::operator != (const inet_address &sap) const
{
	return !((*this) == sap);
}

bool inet_address::operator == (const inet_address &sap) const
{
	return (::memcmp (&this->m_addr_,
		&sap.m_addr_,
		this->size ()) == 0);
}

bool inet_address::operator < (const inet_address &rhs) const
{
  return (::memcmp (&this->m_addr_,
		&rhs.m_addr_,
		this->size ()) < 0 );
}

bool inet_address::operator > (const inet_address &rhs) const
{
  return (::memcmp (&this->m_addr_,
		&rhs.m_addr_,
		this->size ()) > 0 );
}

inet_address& inet_address::operator=( const inet_address& sa)
{
	if( this != &sa)
		::memcpy( &this->m_addr_, &sa.m_addr_, sa.size () );

	return *this;
}


void inet_address::swap( inet_address& r)
{
	sockaddr address;
	memcpy( &address, &this->m_addr_, sizeof( sockaddr ) );
	memcpy( &this->m_addr_, &r.m_addr_, sizeof( sockaddr ) );
	memcpy( &r.m_addr_, &address, sizeof( sockaddr ) );
}

void inet_address::reset (void)
{
  memset (&this->m_addr_ , 0, sizeof (this->m_addr_ ));
  this->m_addr_.sa_family = AF_INET;
}

void inet_address::port(u_short number,
							   bool encode )
{
	((sockaddr_in*) &m_addr_)->sin_port = encode?htons (number):number;
}

void inet_address::port( const char* number )
{
	((sockaddr_in*) &m_addr_)->sin_port = htons( ::atoi( number ) );
}

u_short inet_address::port( void ) const 
{
	return htons( ((sockaddr_in*) &m_addr_)->sin_port );
}

void inet_address::ip( u_long ip , bool encode )
{
	((sockaddr_in*) &m_addr_)->sin_addr.s_addr = encode? htonl ( ip ) : ip;
}

void inet_address::ip( const char* ipstr )
{
	((sockaddr_in*) &m_addr_)->sin_addr.s_addr = ::inet_addr( ipstr );
}

u_long inet_address::ip ( void ) const
{
	return (((sockaddr_in*) &m_addr_)->sin_addr .s_addr);
}

const tstring& inet_address::ip_string ( ) const
{
	ip_string_ = toTstring( ::inet_ntoa(((sockaddr_in*) &m_addr_)->sin_addr ) );
	return ip_string_;
}

size_t inet_address::size (void) const
{
	return sizeof( this->m_addr_ );
}

void inet_address::size (size_t size)
{
}

const sockaddr* inet_address::addr (void) const
{
	return &(this->m_addr_);
}

sockaddr* inet_address::addr (void)
{
	return &(this->m_addr_);
}

void inet_address::addr ( const void * address, size_t len)
{
	if( len > size() )
		memcpy( addr(), address, size() );
	else
		memcpy( addr(), address, len );
}

bool inet_address::parse (const char* address)
{
	if( string_traits<char>::strnicmp( address, "TCP://", 6 ) == 0 )
		address += 6;
	else if( string_traits<char>::strstr( address, "://" ) != 0 )
		return false;

	std::vector< char > ip_addr( strlen( address ) + 10 , 0 );
	string_traits<char>::strcpy( &ip_addr[ 0 ], ip_addr.size(), address );
	char *port_p = string_traits<char>::strrchr (&ip_addr[0], ':');

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

const tstring& inet_address::toString( ) const
{
	char* ipstr = inet_ntoa( ((sockaddr_in*) &m_addr_)->sin_addr );
	if( ipstr == 0 )
	{
		to_string_.clear();
		return to_string_;
	}

	to_string_ = toTstring(ipstr);

	tchar tmp[ 100 ] = _T("");
	string_traits<tstring::value_type>::itoa( port(), tmp, 100, 10);

	to_string_ +=_T( ':');
	to_string_ += tmp;
	return to_string_;
}

_jingxian_end