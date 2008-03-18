

#ifndef _data_black_h_
#define _data_black_h_

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
#include "platform/os.H"

_jomoo_begin

class data_black
{
public:
	data_black(memory_destructor* allocator, void* pointer, size_t capability )
		: pointer_( ((char*)pointer) + _offest_pointer)
	{
		*(long*)(pointer_ - _offest_ref_count) = 1;
		*(memory_destructor**)(pointer_ - _offest_destructor) = allocator;
		*(size_t*)(pointer_ - _offest_capability) = capability;
	}

	data_black( data_black& data)
	{
		data.increment();
		pointer_ = data.pointer_;
	}

	data_black& operator=(data_black& data)
	{
		data.increment();
		pointer_ = data.pointer_;
	}

	void* pointer()
	{
		return _pointer;
	}

	size_t capability() const
	{
		return (int*)(_pointer - _offest_capability );
	}
private:

	const int _offest_destructor = sizeof( memory_destructor* );
	const int _offest_ref_count = sizeof( long ) + sizeof( memory_destructor* );
	const int _offest_pointer = sizeof( size_t ) + sizeof( long ) + sizeof( memory_destructor* );
	const int _offest_capability = sizeof( size_t ) + sizeof( long ) + sizeof( memory_destructor* );

	long increment( )
	{
		return OS::InterlockedIncrement( *(long*)(pointer_ - _offest_ref_count) );
	}
	
	long decrement( )
	{
		int i = OS::InterlockedDecrement( *(long*)(pointer_ - _offest_ref_count) );
		if( 0 >= i )
		{
			(*(memory_destructor**)(pointer_ - _offest_destructor))->free( pointer_ - _offest_pointer);
		}
	}

	char* pointer_;
};

_jomoo_end

#endif // _proactor_h_