

#include "Hazel_IO.h"
#include <vector>

#ifdef _MEMORY_DEBUG
#undef THIS_FILE
#define new	   DEBUG_NEW  
#define malloc DEBUG_MALLOC  
static char THIS_FILE[] = __FILE__;  
#endif // _MEMORY_DEBUG

_networks_begin

Hazel_STDIO::Hazel_STDIO (void)
: handle_( HAZEL_INVALID_HANDLE_VALUE ) 
{
}

Hazel_STDIO::~Hazel_STDIO (void)
{
}

Hazel_HANDLE Hazel_STDIO::get_handle (void) const
{
  return this->handle_;
}

void Hazel_STDIO::set_handle ( Hazel_HANDLE handle )
{
  this->handle_ = handle;
}

void Hazel_STDIO::swap( Hazel_STDIO& r )
{
	std::swap( this->handle_, r.handle_ );
}

ssize_t Hazel_STDIO::recv (void *buf,
              size_t n ) const
{
	DWORD bytes_read = 0;
	DWORD short_nbyte = static_cast < DWORD>( n);
	return ::ReadFile( ( HANDLE )this->get_handle ()
		, buf
		, short_nbyte
		, &bytes_read
		, 0
		//, 0 
		) ? bytes_read : 0 ;
}
ssize_t Hazel_STDIO::recvv (FILE_SEGMENT_ELEMENT iov[],
              size_t n) const
{
	DWORD bytes_read = 0;
	DWORD short_nbyte = static_cast < DWORD>( n);
	return ::ReadFileScatter( ( HANDLE )this->get_handle ()
		, iov
		, short_nbyte
		, &bytes_read
		, 0
		//, 0 
		) ? bytes_read : 0 ;
}

bool Hazel_STDIO::recv (void *buf,
              size_t n,
              Hazel_OVERLAPPED *overlapped) const
{
	DWORD bytes_read = 0;
	DWORD short_nbyte = static_cast < DWORD>( n);
	return ::ReadFile( this->get_handle ()
		, buf
		, short_nbyte
		, &bytes_read
		, overlapped
		//, 0 
		) ? true : false ;
}
bool Hazel_STDIO::recvv (FILE_SEGMENT_ELEMENT iov[],
              size_t n,
              Hazel_OVERLAPPED *overlapped) const
{
	DWORD bytes_read = 0;
	DWORD short_nbyte = static_cast < DWORD>( n);
	return ::ReadFileScatter( this->get_handle ()
		, iov
		, short_nbyte
		, &bytes_read
		, overlapped
		//, 0 
		) ? true : false ;
}
ssize_t Hazel_STDIO::send (const void *buf,
              size_t n ) const
{
	DWORD bytes_send = 0;
	DWORD short_nbyte = static_cast < DWORD>( n);
	return ::WriteFile( ( HANDLE )this->get_handle ()
		, buf
		, short_nbyte
		, &bytes_send
		, 0
		//, 0 
		) ? bytes_send : 0 ;
}

ssize_t Hazel_STDIO::sendv (const FILE_SEGMENT_ELEMENT iov[],
               size_t n ) const
{
	DWORD bytes_send = 0;
	DWORD short_nbyte = static_cast < DWORD>( n);
	return ::WriteFileGather( ( HANDLE )this->get_handle ()
		, (FILE_SEGMENT_ELEMENT*) iov
		, short_nbyte
		, &bytes_send
		, 0
		//, 0 
		) ? bytes_send : 0 ;
}

bool Hazel_STDIO::send (const void *buf,
                size_t n,
                Hazel_OVERLAPPED *overlapped) const
{
	DWORD bytes_send = 0;
	DWORD short_nbyte = static_cast < DWORD>( n);
	return ::WriteFile( this->get_handle ()
		, buf
		, short_nbyte
		, &bytes_send
		, overlapped
		//, 0 
		) ? true : false ;
}
bool Hazel_STDIO::sendv (const FILE_SEGMENT_ELEMENT iov[],
                size_t n,
                Hazel_OVERLAPPED *overlapped) const
{
	DWORD bytes_send = 0;
	DWORD short_nbyte = static_cast < DWORD>( n);
	return ::WriteFileGather( this->get_handle ()
		, ( FILE_SEGMENT_ELEMENT* )iov
		, short_nbyte
		, &bytes_send
		, overlapped
		//, 0 
		) ? true : false ;
}
_networks_end