
#include "SystemPool.h"


_jomoo_memory_begin

SystemPool& SystemPool::get()
{
	static SystemPool system_pool_;
	return system_pool_;
}

SystemPool::SystemPool()
: toString_( _T("System") )
{
}

void* SystemPool::malloc (size_t nbytes , const char* file, size_t line )
{
	return ::malloc( nbytes );
}

void SystemPool::free (void *chunk)
{
	return ::free( chunk );
}

void SystemPool::dump( std::ostream& Target ) const
{
}

const tstring& SystemPool::toString() const
{
	return toString_;
}


_jomoo_memory_end