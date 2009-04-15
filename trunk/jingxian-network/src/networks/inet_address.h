
#ifndef _INET_ADDRESS_H_
#define _INET_ADDRESS_H_

#include "config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
# include "os_networks.H"
# include "string.hpp"

_jingxian_begin

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
	
	void swap( inet_address& r);

	void port(u_short number , bool encode = true );
	void port( const char* number);
	u_short port() const;

	void ip( u_long addr, bool encode = false);
	void ip( const char* addr);
	u_long ip() const;
	const tstring& ip_string() const;

	size_t size (void) const;
	void size (size_t size);

	const sockaddr *addr (void) const ;
	sockaddr *addr (void);
	void addr (const void *, size_t len);

	bool parse( const char* txt);

	void reset (void);

	const tstring& toString( ) const;
private:

	sockaddr m_addr_;

	mutable tstring to_string_;
	mutable tstring ip_string_;
};

inline tostream& operator<<( tostream& target, const inet_address& addr )
{
	target << addr.toString();
	return target;
}

#if defined (JOMOO_HAS_INLINED)
#include "inet_address.inl"
#endif

_jingxian_end

#endif /* _INET_ADDRESS_H_ */
