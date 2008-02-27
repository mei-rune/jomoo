
#ifndef Hazel_STDIO_H
#define Hazel_STDIO_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_IO.h"
# include "Hazel.Platform/os.H"
_networks_begin

class Hazel_STDIO
{
public:

  Hazel_STDIO (void);

  ~Hazel_STDIO (void);

  Hazel_HANDLE get_handle (void) const;

  void set_handle ( Hazel_HANDLE handle );

  void swap( Hazel_STDIO& r );

  ssize_t recv (void *buf,
                size_t n ) const;

  ssize_t recvv (FILE_SEGMENT_ELEMENT iov[],
                size_t n) const;

  bool recv (void *buf,
                size_t n,
                Hazel_OVERLAPPED *overlapped) const;

  bool recvv (FILE_SEGMENT_ELEMENT iov[],
                size_t n,
                Hazel_OVERLAPPED *overlapped) const;

  ssize_t send (const void *buf,
                size_t n ) const;

  ssize_t sendv (const FILE_SEGMENT_ELEMENT iov[],
                 size_t n ) const;

  bool send (const void *buf,
                size_t n,
                Hazel_OVERLAPPED *overlapped) const;

  bool sendv (const FILE_SEGMENT_ELEMENT iov[],
                 size_t n,
                 Hazel_OVERLAPPED *overlapped) const;

private:

	DECLARE_NO_COPY_CLASS( Hazel_STDIO );

	Hazel_HANDLE handle_;
};

_networks_end

#endif /* Hazel_STDIO_H */
