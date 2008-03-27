

#ifndef _binary_writer_h_
#define _binary_writer_h_

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
#include "platform/os.H"

_jomoo_begin

template<typename STREAM>
class binary_writer
{
public:

	binary_writer( STREAM& stream)
		: _stream( &stream )
	{
	}

	bool write(const int& v )
	{
		return _stream->write( &v, sizeof(v) );
	}

	bool write(const __int64& v )
	{
		return _stream->write( &v, sizeof(v) );
	}

	bool write(const void* blob, size_t len )
	{
		return _stream->write( &v, sizeof(v) );
	}
private:

	DECLARE_NO_COPY_CLASS( binary_writer );

	STREAM* _stream;

};

_jomoo_end

#endif // _binary_writer_h_