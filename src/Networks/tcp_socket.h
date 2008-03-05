
#ifndef JOMOO_SOCKET_H
#define JOMOO_SOCKET_H

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
#include "config_Networks.h"
#include "base_socket.h"

_networks_begin

class tcp_socket : public base_socket
{
public:

  tcp_socket (void);

  ~tcp_socket (void);

  ssize_t recv (void *buf,
                size_t n,
                int flags ) const;

  ssize_t recv (void *buf,
                size_t n ) const;

  ssize_t recvv (iovec iov[],
                size_t n) const;

  ssize_t recv (size_t n,
                ...) const;

  bool recv (void *buf,
                size_t n,
                JOMOO_OVERLAPPED& overlapped) const;
   
  bool recvv (iovec iov[],
                size_t n,
                JOMOO_OVERLAPPED& overlapped) const;

  ssize_t send (const void *buf,
                size_t n,
                int flags ) const;

  ssize_t send (const void *buf,
                size_t n ) const;

  ssize_t sendv (const iovec iov[],
                 size_t n ) const;

  ssize_t send (size_t n,
                ...) const;

  bool send (const void *buf,
                size_t n,
                JOMOO_OVERLAPPED& overlapped) const;

  bool sendv (const iovec iov[],
                 size_t n,
                 JOMOO_OVERLAPPED& overlapped) const;

  bool transmit (const iopack iov[],
                 size_t n,
                 JOMOO_OVERLAPPED& overlapped) const;
};


#if !defined (JOMOO_LACKS_INLINE_FUNCTIONS)
#include "tcp_socket.inl"
#endif

_networks_end

#endif /* JOMOO_SOCKET_H */
