

#ifndef _binary_reader_h_
#define _binary_reader_h_

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
#include "platform/os.H"

_jomoo_begin

class binary_reader
{
public:
	binary_reader( char* pointer
	, size_t capability
	, size_t offest = 0 )
	: pointer_( pointer)
	, capability_( capability )
	, position_( offest )
	{
	}

	bool read( int& v )
	{
		if( capability_ >= position_ + sizeof(int) )
			return false;
		v = *(int*)( pointer_ + position_ );
		position_ += sizeof(int);
		return true;
	}

	bool read( __int64& v )
	{
		if( capability_ >= position_ + sizeof(__int64) )
			return false;
		v = *(__int64*)( pointer_ + position_ );
		position_ += sizeof(__int64);
		return true;
	}

	bool read( void* blob, size_t len )
	{
		if( capability_ >= position_ + len )
			return false;
		memcpy( blob, pointer_ + position_, len );
		position_ += len;
		return true;
	}

private:
	char* pointer_;
	size_t capability_;
	size_t position_;
};

_jomoo_end

#endif // _binary_reader_h_