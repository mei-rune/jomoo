

#ifndef Instance_Proxy_H
#define Instance_Proxy_H

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

// Include files
#include "config_Proxy.h"
#include "BOE/Logger.H"
#include "BOE/IO/Instance_IO.h"
#include "BOE/Kernel/Kernel.H"
#include "BOE/counter_ptr.hpp"


_proxy_begin

#define THREADED()	( instance_.getDefaultsAndOverrides().IsThreaded      )
#define NOTTHREADED()	( !SS5SocksOpt.IsThreaded     )

#define SYSLOG()	( instance_.getDefaultsAndOverrides().Syslog        )
#define VERBOSE()	( instance_.getDefaultsAndOverrides().Verbose       )
#define DEBUG()		( instance_.getDefaultsAndOverrides().Debug         )
#define BALANCE()	( instance_.getDefaultsAndOverrides().IsBalance )
#define DUMP()		( instance_.getDefaultsAndOverrides().IsDump )
#define ROUTE()		( instance_.getDefaultsAndOverrides().IsRoute )
#define UPSTREAM()	( instance_.getDefaultsAndOverrides().IsUpstream   )
#define AUTHENFILE()      ( instance_.getDefaultsAndOverrides().Authentication == FILE_AUTHENTICATION )
#define AUTHENEAP()       ( instance_.getDefaultsAndOverrides().Authentication == EAP_AUTHENTICATION  )
#define AUTHENPAM()       ( instance_.getDefaultsAndOverrides().Authentication == PAM_AUTHENTICATION )
#define AUTHORFILE()      ( instance_.getDefaultsAndOverrides().Profiling == FILE_PROFILING )
#define AUTHORDIRECTORY() ( instance_.getDefaultsAndOverrides().Profiling == LDAP_PROFILING )
#define LDAPBASE() 		  ( instance_.getDefaultsAndOverrides().LdapCriteria == LDAP_BASE   )
#define LDAPFILTER() 	  ( instance_.getDefaultsAndOverrides().LdapCriteria == LDAP_FILTER )
#define NOTMUTE()		  ( instance_.getDefaultsAndOverrides().Mute == ERR      


#define SS5_VERSION        "BOE_Proxy Version 3.2 - Release 5"
#define SS5_CONFIG_FILE    "ss5.conf"
#define SS5_PASSWORD_FILE  "ss5.passwd"
#define SS5_DEFAULT_ADDR   "0.0.0.0"
#define SS5_DEFAULT_PORT   "1080"
#define SS5_DEFAULT_USER   "nobody"


#define SOCKS4_VERSION 	4
#define SOCKS5_VERSION 	5

#define NOAUTH 		0
#define GSSAPI 		1
#define USRPWD 		2
#define FAKEPWD 	254 
#define NOMETHOD 	255

#define CONNECT         1
#define BIND            2
#define UDP_ASSOCIATE   3
#define IPV4   		1
#define DOMAIN 		3
#define IPV6   		4


#define CONTINUE                0
#define EXIT                    1
#define THREAD_EXIT             0

#define LOAD_CONFIG             2
#define RELOAD_CONFIG           1
#define PARSE_CONFIG            0

#define SOCKS5_PORT             1080    /* Default socks port */
#define DATABUF                 1460    /* MTU - (header IP + header TCP) */
#define MAXIF                   30      /* Max number of network interfaces */ 


class Instance_Proxy
{
public:
	typedef ProxyLoggerPtr LoggerPtr;

	struct DefaultsAndOverrides
	{
		DefaultsAndOverrides()
		{
		}
		unsigned int DnsOrder;           
		unsigned int Verbose;            
		unsigned int Mute;               
		unsigned int SessionTimeout;     
		unsigned int Profiling;          
		unsigned int AuthCacheAge;       
		unsigned int AuthoCacheAge;      
		unsigned int StickyAge;          
		unsigned int Sticky;             
		unsigned int Authentication;     
		unsigned int AcceptTimeout;      
		unsigned int IsThreaded;         
		unsigned int IsBalance;          
		unsigned int IsUpstream;         
		unsigned int IsRoute;            
		unsigned int IsDump;             
	};

	Instance_Proxy( _io Instance_IO& instance );
	
	~Instance_Proxy(void);

	int open( _util PropertiesPtr config );

	void close( );

	bool isStop();

	_io Instance_IO& getIOInstance();

	const DefaultsAndOverrides& getDefaultsAndOverrides()const;

	void setConcurrencyBridge( _kernel BOE_Concurrency_Impl& concurrency );
	_kernel BOE_Concurrency_Impl& getConcurrencyBridge();

	LoggerPtr getLogger();

	void setLogger( LoggerPtr );

	const tstring& toString();
	void setToString( const tstring& s );

private:

	DECLARE_NO_COPY_CLASS( Instance_Proxy );

	_io Instance_IO& ioinstance_;

	_kernel BOE_Concurrency_Impl* concurrency_;

	DefaultsAndOverrides overrides_;

	tstring toString_;

};


_proxy_end

#endif // Instance_Proxy_H