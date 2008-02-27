

#ifndef hazel_sap_H
#define hazel_sap_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
#include "config_Networks.h"
#include "Hazel_INET_Addr.H"
#include "Hazel.Base/Exception.hpp"


_networks_begin

class hazel_sap
{
public:

   MakeException( NetworkException, NetworkError );

  ~hazel_sap (void);

  int enable (int value) const;

  int disable (int value) const;

  void swap( hazel_sap& r );

  hazel_sap_HANDLE get_handle (void) const;

  void set_handle (hazel_sap_HANDLE handle);

  int set_option (int level,
                  int option,
                  void *optval,
                  int optlen) const;

  int get_option (int level,
                  int option,
                  void *optval,
                  int *optlen) const;

  int close (void);

  int get_local_addr (Hazel_INET_Addr &) const;

  int get_remote_addr (Hazel_INET_Addr &) const;

  int open (int type = SOCK_STREAM,
            int protocol_family = AF_INET,
            int protocol = IPPROTO_TCP,
            int reuse_addr = 0 );

  int open (int type,
            int protocol_family,
            int protocol,
            WSAPROTOCOL_INFO *protocolinfo,
            hazel_sap_GROUP g,
            u_long flags,
            int reuse_addr);


  static int initsocket();

  static void shutdownsock();

protected:

  hazel_sap (void);

  hazel_sap (int type,
            int protocol_family,
            int protocol = 0,
            int reuse_addr = 0);

  hazel_sap (int type,
            int protocol_family,
            int protocol,
            WSAPROTOCOL_INFO *protocolinfo,
            hazel_sap_GROUP g,
             u_long flags,
            int reuse_addr);

private:

  DECLARE_NO_COPY_CLASS( hazel_sap );

  hazel_sap_HANDLE handle_;
};

#if !defined (Hazel_LACKS_INLINE_FUNCTIONS)
#include "hazel_sap.inl"
#endif /* Hazel_LACKS_INLINE_FUNCTIONS */

_networks_end

#endif /* hazel_sap_H */
