
/**
 * -*- C++ -*-
 * -------------------------------------------------------------------------------
 * - °Ë®q°–®r ®q°–®r		          .h,v 1.0 2005/03/14 11:36:34
 *  ®u®ê®Ä®Ä®é ®q®q °–®r
 * ¶ÚÃÔ¶ÚÃÔÃÔ| ®t------
 * -------------------------------------------------------------------------------
 */

#ifndef _Serialize_Helper_H_
#define _Serialize_Helper_H_

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include "bt_stream.h"
#include "serialize_def.h"

_bt_serialize_begin

class BIN_OUT_Source
{
public:
	BIN_OUT_Source( const char* file_name )
		: type_( file_source )
		, file_name_( file_name )
		, ostream_( 0 )
	{
	}

	BIN_OUT_Source( bt_ostream* ostream )
		: type_( stream_source )
		, file_name_( 0 )
		, ostream_( ostream )
	{
	}

	enum source_type {
		file_source
		, stream_source
		, other_source
	};
source_type type_;

const char* file_name_;

bt_ostream* ostream_;
};


class BIN_INPUT_Source
{
public:
	BIN_INPUT_Source( const char* file_name )
		: type_( file_source )
		, file_name_( file_name )
		, buf_( 0 )
		, buf_len_( 0 )
		, istream_( 0 )
	{
	}

	BIN_INPUT_Source( const void* buf, size_t len )
		: type_( mem_source )
		, file_name_( 0 )
		, buf_( buf )
		, buf_len_( len )
		, istream_( 0 )
	{
	}

	BIN_INPUT_Source( bt_istream* istream )
		: type_( stream_source )
		, file_name_( 0 )
		, buf_( 0 )
		, buf_len_( 0 )
		, istream_( istream )
	{
	}

	enum source_type {
		file_source
		, mem_source
		, stream_source
		, other_source
	};
source_type type_;

const char* file_name_;

const void * buf_;
size_t buf_len_;

bt_istream* istream_;
};

_bt_serialize_end


#endif // _Serialize_Helper_H_