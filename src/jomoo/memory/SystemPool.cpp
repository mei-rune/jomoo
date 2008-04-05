
#include "SystemPool.h"


_jomoo_memory_begin


class mem_block
{
	mem_block* next;
	mem_block* prov;
	const char* name;
	size_t line;
};

const size_t mem_head_length = sizeof( mem_block );

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
	return ::malloc ( nbytes + mem_head_length );
}

void SystemPool::free (void *chunk)
{
	return ::free( chunk );
}

void SystemPool::dump( tostream& Target ) const
{
}

const tstring& SystemPool::toString() const
{
	return toString_;
}


_jomoo_memory_end