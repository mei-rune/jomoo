

#ifndef Proxy_Statistics_H
#define Proxy_Statistics_H

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

// Include files
#include "config_Proxy.h"


struct Proxy_Statistics {
  unsigned long int V5Total_Connect,V4Total_Connect;
  unsigned long int V5Normal_Connect,V4Normal_Connect;
  unsigned long int V5Failed_Connect,V4Failed_Connect;

  unsigned long int V5Current_Connect,V4Current_Connect;

  unsigned long int V5Total_Bind,V4Total_Bind;
  unsigned long int V5Normal_Bind,V4Normal_Bind;
  unsigned long int V5Failed_Bind,V4Failed_Bind;

  unsigned long int V5Current_Bind,V4Current_Bind;

  unsigned long int V5Total_Udp;
  unsigned long int V5Normal_Udp;
  unsigned long int V5Failed_Udp;

  unsigned long int V5Current_Udp;

  unsigned long int Total_Auth_File;
  unsigned long int Total_Auth_EAP;
  unsigned long int Total_Auth_PAM;
  unsigned long int Normal_Auth_File;
  unsigned long int Normal_Auth_EAP;
  unsigned long int Normal_Auth_PAM;
  unsigned long int Failed_Auth_File;
  unsigned long int Failed_Auth_EAP;
  unsigned long int Failed_Auth_PAM;

  unsigned long int Current_Auth_File;
  unsigned long int Current_Auth_EAP;
  unsigned long int Current_Auth_PAM;

  unsigned long int Total_Author_File;
  unsigned long int Total_Author_Ldap;
  unsigned long int Normal_Author_File;
  unsigned long int Normal_Author_Ldap;
  unsigned long int Failed_Author_File;
  unsigned long int Failed_Author_Ldap;

  unsigned long int Current_Author_File;
  unsigned long int Current_Author_Ldap;

};



#endif // Proxy_Statistics_H