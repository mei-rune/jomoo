
#ifndef JOMOO_STDIO_H
#define JOMOO_STDIO_H

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_IO.h"
# include "Platform/os.H"
_networks_begin

class JOMOO_STDIO
{
public:

  JOMOO_STDIO (void);

  ~JOMOO_STDIO (void);

  JOMOO_HANDLE get_handle (void) const;

  void set_handle ( JOMOO_HANDLE handle );

  void swap( JOMOO_STDIO& r );

  ssize_t recv (void *buf,
                size_t n ) const;

  ssize_t recvv (FILE_SEGMENT_ELEMENT iov[],
                size_t n) const;

  bool recv (void *buf,
                size_t n,
                JOMOO_OVERLAPPED *overlapped) const;

  bool recvv (FILE_SEGMENT_ELEMENT iov[],
                size_t n,
                JOMOO_OVERLAPPED *overlapped) const;

  ssize_t send (const void *buf,
                size_t n ) const;

  ssize_t sendv (const FILE_SEGMENT_ELEMENT iov[],
                 size_t n ) const;

  bool send (const void *buf,
                size_t n,
                JOMOO_OVERLAPPED *overlapped) const;

  bool sendv (const FILE_SEGMENT_ELEMENT iov[],
                 size_t n,
                 JOMOO_OVERLAPPED *overlapped) const;

private:

	DECLARE_NO_COPY_CLASS( JOMOO_STDIO );

	JOMOO_HANDLE handle_;
};

_networks_end

#endif /* JOMOO_STDIO_H */
