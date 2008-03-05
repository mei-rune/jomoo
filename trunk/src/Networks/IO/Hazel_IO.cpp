

#include "JOMOO_IO.h"
#include <vector>

#ifdef _MEMORY_DEBUG
#undef THIS_FILE
#define new	   DEBUG_NEW  
#define malloc DEBUG_MALLOC  
static char THIS_FILE[] = __FILE__;  
#endif // _MEMORY_DEBUG

_networks_begin

JOMOO_STDIO::JOMOO_STDIO (void)
: handle_( JOMOO_INVALID_HANDLE_VALUE ) 
{
}

JOMOO_STDIO::~JOMOO_STDIO (void)
{
}

JOMOO_HANDLE JOMOO_STDIO::get_handle (void) const
{
  return this->handle_;
}

void JOMOO_STDIO::set_handle ( JOMOO_HANDLE handle )
{
  this->handle_ = handle;
}

void JOMOO_STDIO::swap( JOMOO_STDIO& r )
{
	std::swap( this->handle_, r.handle_ );
}

ssize_t JOMOO_STDIO::recv (void *buf,
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
ssize_t JOMOO_STDIO::recvv (FILE_SEGMENT_ELEMENT iov[],
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

bool JOMOO_STDIO::recv (void *buf,
              size_t n,
              JOMOO_OVERLAPPED *overlapped) const
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
bool JOMOO_STDIO::recvv (FILE_SEGMENT_ELEMENT iov[],
              size_t n,
              JOMOO_OVERLAPPED *overlapped) const
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
ssize_t JOMOO_STDIO::send (const void *buf,
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

ssize_t JOMOO_STDIO::sendv (const FILE_SEGMENT_ELEMENT iov[],
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

bool JOMOO_STDIO::send (const void *buf,
                size_t n,
                JOMOO_OVERLAPPED *overlapped) const
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
bool JOMOO_STDIO::sendv (const FILE_SEGMENT_ELEMENT iov[],
                size_t n,
                JOMOO_OVERLAPPED *overlapped) const
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