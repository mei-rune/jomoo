

/**
* -*- C++ -*-
* -------------------------------------------------------------------------------
* - ¤╭⌒╮ ╭⌒╮						   Hazel_Buffer.H,v 1.0 2005/10/10 16:45:54
*  ╱◥██◣ ╭╭ ⌒╮
* ︱田︱田田| ╰------
* -------------------------------------------------------------------------------
*/

#ifndef _Hazel_Buffer_H_
#define _Hazel_Buffer_H_

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

#include "tstring.h"
#include "counter_ptr.hpp"
#include "Hazel_Export.h"
#include "Hazel.Base/exception.hpp"

_hazel_begin

class Hazel_Read_Buffer
{
public:
	virtual ~Hazel_Read_Buffer() {}
	virtual bool read( void* blob, size_t t ) = 0;
	virtual const tstring& toString() const = 0;
};

class Hazel_Read_Stream
{
public:

	Hazel_Read_Stream( Hazel_Read_Buffer* buf )
		: buf_( buf )
	{
		if( buf_ == 0 )
			ThrowException1( InvalidPointerException, ",读流buf不能为空" );
	}

	virtual ~Hazel_Read_Stream() {}

	bool read( Byte& b )
	{
		return read( &b, sizeof( Byte ) );
	}

	bool read( Int16& i )
	{
		return read( &i, sizeof( Int16 ) );
	}

	bool read( Int32& i )
	{
		return read( &i, sizeof( Int32 ) );
	}

	bool read( Int64& i )
	{
		return read( &i, sizeof( Int64 ) );
	}

	bool read( Float& f )
	{
		return read( &f, sizeof( Float ) );
	}

	bool read( Double& d )
	{
		return read( &d, sizeof( Double ) );
	}

	bool read( void* blob, size_t t )
	{
		return buf_->read( blob, t );
	}

	const tstring& toString() const
	{
		return buf_->toString();
	}

	Hazel_Read_Buffer* rd_buf()
	{
		return buf_;
	}
private:

	DECLARE_NO_COPY_CLASS( Hazel_Read_Stream );

	Hazel_Read_Buffer* buf_;
};

class Hazel_Write_Buffer
{
public:
	virtual ~Hazel_Write_Buffer() {}
	virtual bool write( const void* blob, size_t t ) = 0;
	virtual const tstring& toString() const = 0;
};

class Hazel_Write_Stream
{
public:

	Hazel_Write_Stream( Hazel_Write_Buffer* buf )
		: buf_( buf )
	{
		if( buf_ == 0 )
			ThrowException1( InvalidPointerException, ",写流buf不能为空" );
	}

	virtual ~Hazel_Write_Stream() {}

	bool write( Byte b)
	{
		return buf_->write( &b, sizeof( Byte ) );
	}

	bool write( Int16 i )
	{
		return buf_->write( &i, sizeof( Int16 ) );
	}

	bool write( Int32 i ) 
	{
		return buf_->write( &i, sizeof( Int32 ) );
	}

	bool write( Int64 i )
	{
		return buf_->write( &i, sizeof( Int64 ) );
	}

	bool write( Float f )
	{
		return buf_->write( &f, sizeof( Float ) );
	}

	bool write( Double d )
	{
		return buf_->write( &d, sizeof( Double ) );
	}

	bool write( const void* blob, size_t t )
	{
		return buf_->write( blob, t );
	}

	const tstring& toString() const
	{
		return buf_->toString();
	}
		
	Hazel_Write_Buffer* wd_buf()
	{
		return buf_;
	}
private:

	DECLARE_NO_COPY_CLASS( Hazel_Write_Stream );
	Hazel_Write_Buffer* buf_;
};

class Hazel_Buffer : public Hazel_Read_Buffer
	, public Hazel_Write_Buffer
{
public :
	virtual ~Hazel_Buffer(){}
	virtual const tstring& toString() const = 0;
};

_hazel_end

#endif // _Hazel_Buffer_H_
