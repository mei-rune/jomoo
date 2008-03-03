
#include "mmap.h"
#include "Base/exception.hpp"
#include "Base/lastError.h"

#ifdef _MEMORY_DEBUG
#undef THIS_FILE
#define new	   DEBUG_NEW  
#define malloc DEBUG_MALLOC  
static char THIS_FILE[] = __FILE__;  
#endif // _MEMORY_DEBUG

_networks_begin

Hazel_Mem_MAP::Hazel_Mem_MAP (void)
: base_addr_ ( 0 ),
length_ (0),
handle_ (HAZEL_INVALID_HANDLE),
file_mapping_ (HAZEL_INVALID_HANDLE)
{
}

Hazel_Mem_MAP::Hazel_Mem_MAP (const tchar *file_name,
						  int len,
						  int prot,
						  int share,
						  void *addr,
						  off_t offset,
						  LPSECURITY_ATTRIBUTES sa)
						  : base_addr_ ( 0 ),
						  length_ (0),
						  handle_ (HAZEL_INVALID_HANDLE),
						  file_mapping_ (HAZEL_INVALID_HANDLE)
{
	if (this->map (file_name,
		len,
		prot,
		share,
		addr,
		offset,
		sa) < 0)
		ThrowException1( RuntimeException , lastError() );

}

Hazel_Mem_MAP::Hazel_Mem_MAP (Hazel_HANDLE handle,
						  int len,
						  int prot,
						  int share,
						  void *addr,
						  off_t offset,
						  LPSECURITY_ATTRIBUTES sa)
						  : base_addr_ ( 0 ),
						  length_ (0),
						  handle_ (HAZEL_INVALID_HANDLE),
						  file_mapping_ (HAZEL_INVALID_HANDLE)
{
	if (this->map (handle,
		len,
		prot,
		share,
		addr,
		offset,
		sa) < 0)
		ThrowException1( RuntimeException , lastError() );
}

Hazel_Mem_MAP::~Hazel_Mem_MAP (void)
{
	this->close ();
}

int Hazel_Mem_MAP::close (void)
{
	this->unmap ();
	return this->close_handle ();
}


int Hazel_Mem_MAP::map_it (Hazel_HANDLE handle,
						 int length_request,
						 int prot,
						 int share,
						 void *addr,
						 off_t offset,
						 LPSECURITY_ATTRIBUTES sa)
{
	this->base_addr_ = OS::mmap ( addr,
		length_request,
		prot,
		share,
		handle,
		offset,
		this->file_mapping_,
		sa);

	this->length_ = length_request;
	return this->base_addr_ == 0 ? -1 : 0;
}


int Hazel_Mem_MAP::map (const tchar *file_name,
					  int len,
					  int prot,
					  int share,
					  void *addr,
					  off_t offset,
					  LPSECURITY_ATTRIBUTES sa)
{
	if( file_name == 0 )
		return -1;

	filename_ = file_name;
	this->base_addr_ = OS::mmap( this->base_addr_,
		this->length_,
		prot,
		share,
		HAZEL_INVALID_HANDLE_VALUE,
		offset,
		this->file_mapping_,
		sa
		,file_name );

	return this->base_addr_ == 0 ? -1 : 0;
}


int Hazel_Mem_MAP::map (Hazel_HANDLE handle,
					  int len,
					  int prot,
					  int share,
					  void *addr,
					  off_t offset,
					  LPSECURITY_ATTRIBUTES sa)
{
	this->handle_ = handle;
	return this->map_it (handle, len, prot, share, addr, offset, sa);
}

int Hazel_Mem_MAP::map (int len,
					  int prot,
					  int share,
					  void *addr,
					  off_t offset,
					  LPSECURITY_ATTRIBUTES sa)
{
	if (addr == 0 && this->base_addr_ != 0 )
	{
		share |= MAP_FIXED;
		addr = this->base_addr_;
	}
	return this->map_it (this->handle_, len, prot,
		share, addr, offset, sa);
}

int
Hazel_Mem_MAP::remove (void)
{
	this->close ();
	return 0;
}

const tstring& Hazel_Mem_MAP::filename (void) const
{
	return this->filename_;
}

void* Hazel_Mem_MAP::addr (void) const
{
	return this->base_addr_;
}

size_t Hazel_Mem_MAP::size (void) const
{
	return this->length_;
}

int Hazel_Mem_MAP::close_filemapping_handle (void)
{
	int result = 0;

	if (this->file_mapping_ != this->handle_
		&& this->file_mapping_ != HAZEL_INVALID_HANDLE)
	{
		result = OS::close_handle (this->file_mapping_) ? 0 : -1;
		this->file_mapping_ = HAZEL_INVALID_HANDLE;
	}

	return result;
}

int Hazel_Mem_MAP::unmap ( )
{

	this->close_filemapping_handle ();

	if (this->base_addr_ != 0 )
	{
		int result = OS::munmap (this->base_addr_,this->length_ );
		this->base_addr_ = 0;
		this->length_ = 0;
		return result;
	}
	return 0;
}

int Hazel_Mem_MAP::sync (int flags)
{
	return OS::msync (this->base_addr_,
		this->length_,
		flags);
}

int Hazel_Mem_MAP::protect ( int prot )
{
	return OS::mprotect (this->base_addr_, this->length_, prot);
}

int Hazel_Mem_MAP::advise (int behavior )
{
	return OS::madvise ( this->base_addr_,
		this->length_ ,
		behavior);
}

int Hazel_Mem_MAP::close_handle (void)
{
	int result = 0;
	if( this->handle_ != HAZEL_INVALID_HANDLE )
	{
		result = OS::close_handle (this->handle_) ? 0 : -1;
		this->handle_ = HAZEL_INVALID_HANDLE;
	}
	return result;
}

_networks_end
