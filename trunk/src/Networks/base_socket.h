

#ifndef JOMOO_sap_H
#define JOMOO_sap_H

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
#include "config_Networks.h"
#include "INET_Addr.H"
#include "Base/Exception.hpp"


_networks_begin

class base_socket
{
public:

  ~base_socket (void);

  int enable (int value) const;

  int disable (int value) const;

  void swap( JOMOO_sap& r );

  HANDLE get_handle (void) const;

  void set_handle (HANDLE handle);

  int set_option (int level,
                  int option,
                  void *optval,
                  int optlen) const;

  int get_option (int level,
                  int option,
                  void *optval,
                  int *optlen) const;

  int close (void);

  int get_local_addr (JOMOO_INET_Addr &) const;

  int get_remote_addr (JOMOO_INET_Addr &) const;

  int open (int type = SOCK_STREAM,
            int protocol_family = AF_INET,
            int protocol = IPPROTO_TCP,
            int reuse_addr = 0 );

  int open (int type,
            int protocol_family,
            int protocol,
            WSAPROTOCOL_INFO *protocolinfo,
            JOMOO_sap_GROUP g,
            u_long flags,
            int reuse_addr);


  static int initsocket();

  static void shutdownsock();

protected:

  base_socket (void);

  base_socket (int type,
            int protocol_family,
            int protocol = 0,
            int reuse_addr = 0);

  base_socket (int type,
            int protocol_family,
            int protocol,
            WSAPROTOCOL_INFO *protocolinfo,
            JOMOO_sap_GROUP g,
             u_long flags,
            int reuse_addr);

private:

  DECLARE_NO_COPY_CLASS( base_socket );

  HANDLE handle_;
};

#if !defined (JOMOO_LACKS_INLINE_FUNCTIONS)
#include "base_socket.inl"
#endif /* JOMOO_LACKS_INLINE_FUNCTIONS */

_networks_end

#endif /* JOMOO_sap_H */
