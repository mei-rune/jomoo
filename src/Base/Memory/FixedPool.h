

#ifndef FIXED_POOL_H
#define FIXED_POOL_H

# include "config.h"

# if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
# endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_Memory.H"
# include "Memory_Pool.h"
# include "../Collections/ThreadSafePtrQueue.HPP"

_memory_begin

class FixedPool : public  fixed_pool
{
public:

	struct CHUNK LIST_INTERFACE( CHUNK )
	{
		//enum
		//{
		//	CHUNK_LENGTH = JOMOO_LCD_DEF( sizeof( CHUNK ) , sizeof( void* ) );
		//}

		CHUNK()
		: pointee_( 0 )
		, magic_( pool_magic_v )
		{
		}
		int32_t magic_;
		LIST_DEFINE( CHUNK );
		void* pointee_;
	};

	enum
	{
		CHUNK_HEAD_SIZE = JOMOO_LCD_DEF( sizeof( CHUNK ) , JOMOO_TM )
	};

	FixedPool( const tstring& name ,size_t number, size_t size );
	~FixedPool();

	void* malloc ( const char* file=0, size_t line=-1 );

	void free (void *);

	size_t chunk_size() const;

	void dump( std::ostream& Target ) const;

	const tstring& toString() const;

private:

	DECLARE_NO_COPY_CLASS( FixedPool );

	ThreadSafePtrQueue< CHUNK > queue_;
	void* lpvAddr_;
	size_t chunk_size_;
	size_t used_;
	size_t number_;
	tstring toString_;

	//size_t CHUNK_HEAD_SIZE;
};

_memory_end

#endif //FIXED_POOL_H
