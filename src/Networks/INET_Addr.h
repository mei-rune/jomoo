
#ifndef Hazel_INET_ADDR_H
#define Hazel_INET_ADDR_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_Networks.h"
# include "Platform/os_networks.H"
# include "Base/string.hpp"

_networks_begin

class Hazel_INET_Addr
{
public:

	Hazel_INET_Addr (void);

	Hazel_INET_Addr (const Hazel_INET_Addr & );

	Hazel_INET_Addr (const sockaddr_in *, int len);

	Hazel_INET_Addr (u_short port_number,
		u_long ip_addr = INADDR_ANY );

	Hazel_INET_Addr (u_short port_number,
		const char* host_name );

	Hazel_INET_Addr (const char* port_number,
		const char* ip_addr );

	explicit Hazel_INET_Addr (const char* address);

	~Hazel_INET_Addr (void);


	bool operator < (const Hazel_INET_Addr &rhs) const;

	bool operator > (const Hazel_INET_Addr &rhs) const;

	bool operator == (const Hazel_INET_Addr &SAP) const;

	bool operator != (const Hazel_INET_Addr &SAP) const;

	void set_port_number (u_short port_number , bool encode = true );

	void set_ip_address ( u_long ip_address , bool encode = false );
    
	u_long get_ip_address ( void ) const;

	u_short get_port_number( void ) const ;

	int set (const Hazel_INET_Addr &);

	int set (const char* addr );

	int set (u_short port_number,
		u_long ip_addr = INADDR_ANY);

	int set (const char port_name[],
		const char host_name[] );

	int set (const char port_name[],
		u_long ip_addr );

	int set (u_short port_number,
		const char host_name[] );

	int set (const sockaddr_in *,
		int len);

	size_t get_size (void) const;

	void set_size (size_t size);

	const void *get_addr (void) const ;

	void *get_addr (void);

	void set_addr (const void *, size_t len);

	const tstring& toString( ) const;

	int addr_to_string (char* s,
							   size_t size ) const;

   int string_to_addr ( const char* addres );

private:

	void reset (void);

	sockaddr m_addr_;

	mutable tstring to_string_;
};

#if !defined (Hazel_LACKS_INLINE_FUNCTIONS)
#include "INET_Addr.inl"
#endif

_networks_end

#endif /* Hazel_INET_ADDR_H */
