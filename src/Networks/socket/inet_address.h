
#ifndef inet_address_H
#define inet_address_H

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_Networks.h"
# include "Platform/os_networks.H"
# include "Base/string.hpp"

_networks_begin

class inet_address
{
public:

	inet_address (void);

	inet_address (const inet_address & );

	inet_address (const sockaddr_in *, int len);

	inet_address (const void*, int len);

	inet_address (u_long ip, u_short port_number);

	inet_address (const char* name, u_short number);

	inet_address (const char* name, const char* number);

	explicit inet_address (const char* address);

	~inet_address (void);

	bool operator < (const inet_address &rhs) const;

	bool operator > (const inet_address &rhs) const;

	bool operator == (const inet_address &SAP) const;

	bool operator != (const inet_address &SAP) const;

	inet_address& operator=( const inet_address& r);

	void port(u_short number , bool encode = true );
	void port( const char* number);
	u_short port() const;

	void ip( u_long addr, bool encode = false);
	void ip( const char* addr);
	u_long ip() const;
	const tstring& ip_string() const;

	size_t size (void) const;
	void size (size_t size);

	const void *addr (void) const ;
	void *addr (void);
	void addr (const void *, size_t len);
	void addr(const sockaddr_in *, int len);

	bool parse( const char* txt);

	void reset (void);

	const tstring& toString( ) const;
private:

	sockaddr m_addr_;

	mutable tstring to_string_;
	mutable tstring ip_string_;
};

#if !defined (JOMOO_LACKS_INLINE_FUNCTIONS)
#include "inet_address.inl"
#endif

_networks_end

#endif /* inet_address_H */
