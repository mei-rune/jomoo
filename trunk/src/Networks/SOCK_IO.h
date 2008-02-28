
#ifndef HAZEL_SOCKET_H
#define HAZEL_SOCKET_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
#include "config_Networks.h"
#include "hazel_sap.h"

_networks_begin

class hazel_socket : public hazel_sap
{
public:

  hazel_socket (void);

  ~hazel_socket (void);

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
                Hazel_OVERLAPPED& overlapped) const;
   
  bool recvv (iovec iov[],
                size_t n,
                Hazel_OVERLAPPED& overlapped) const;

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
                Hazel_OVERLAPPED& overlapped) const;

  bool sendv (const iovec iov[],
                 size_t n,
                 Hazel_OVERLAPPED& overlapped) const;

  bool transmit (const iopack iov[],
                 size_t n,
                 Hazel_OVERLAPPED& overlapped) const;
};


#if !defined (Hazel_LACKS_INLINE_FUNCTIONS)
#include "hazel_socket.inl"
#endif

_networks_end

#endif /* HAZEL_SOCKET_H */
