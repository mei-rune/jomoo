
#ifndef tcp_socket_h
#define tcp_socket_h

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_Networks.h"
#include "base_socket.h"
#include "inet_address.h"

_networks_begin

class tcp_socket : public base_socket
{
public:

  tcp_socket (void);

  ~tcp_socket (void);

  ssize_t recv (void *buf,
                size_t n,
                int flags );

  ssize_t recv (void *buf,
                size_t n );

  ssize_t recvv (iovec iov[],
                size_t n);

  ssize_t recv (size_t n,
                ...);

  bool recv (void *buf,
                size_t n,
                JOMOO_OVERLAPPED& overlapped);
   
  bool recvv (iovec iov[],
                size_t n,
                JOMOO_OVERLAPPED& overlapped);

  ssize_t send (const void *buf,
                size_t n,
                int flags );

  ssize_t send (const void *buf,
                size_t n );
  
  ssize_t send_n( const char* buf,ssize_t length);

  ssize_t sendv (const iovec* iov,
                 size_t n );

  bool sendv_n( const iovec* wsaBuf, ssize_t size);

  ssize_t send (size_t n,
                ...);

  bool send (const void *buf,
                size_t n,
                JOMOO_OVERLAPPED& overlapped);

  bool sendv (const iovec* iov,
                 size_t n,
                 JOMOO_OVERLAPPED& overlapped);

  bool transmit (const iopack* iov,
                 size_t n,
                 JOMOO_OVERLAPPED& overlapped);

  bool recv_n( char* buf,ssize_t length);
  bool recv_n( iovec* wsaBuf, ssize_t size);

};


#if !defined (JOMOO_LACKS_INLINE_FUNCTIONS)
#include "tcp_socket.inl"
#endif

_networks_end

#endif /* tcp_socket_h */
