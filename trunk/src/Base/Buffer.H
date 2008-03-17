

/**
* -*- C++ -*-
* -------------------------------------------------------------------------------
* - ¤╭⌒╮ ╭⌒╮						   JOMOO_Buffer.H,v 1.0 2005/10/10 16:45:54
*  ╱◥██◣ ╭╭ ⌒╮
* ︱田︱田田| ╰------
* -------------------------------------------------------------------------------
*/

#ifndef _JOMOO_Buffer_H_
#define _JOMOO_Buffer_H_

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "tstring.h"
#include "counter_ptr.hpp"
#include "jomoo_export.h"
#include "Base/exception.hpp"

_jomoo_begin

class JOMOO_Read_Buffer
{
public:
	virtual ~JOMOO_Read_Buffer() {}
	virtual bool read( void* blob, size_t t ) = 0;
	virtual const tstring& toString() const = 0;
};

class JOMOO_Read_Stream
{
public:

	JOMOO_Read_Stream( JOMOO_Read_Buffer* buf )
		: buf_( buf )
	{
		if( buf_ == 0 )
			ThrowException1( InvalidPointerException, ",读流buf不能为空" );
	}

	virtual ~JOMOO_Read_Stream() {}

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

	JOMOO_Read_Buffer* rd_buf()
	{
		return buf_;
	}
private:

	DECLARE_NO_COPY_CLASS( JOMOO_Read_Stream );

	JOMOO_Read_Buffer* buf_;
};

class JOMOO_Write_Buffer
{
public:
	virtual ~JOMOO_Write_Buffer() {}
	virtual bool write( const void* blob, size_t t ) = 0;
	virtual const tstring& toString() const = 0;
};

class JOMOO_Write_Stream
{
public:

	JOMOO_Write_Stream( JOMOO_Write_Buffer* buf )
		: buf_( buf )
	{
		if( buf_ == 0 )
			ThrowException1( InvalidPointerException, ",写流buf不能为空" );
	}

	virtual ~JOMOO_Write_Stream() {}

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
		
	JOMOO_Write_Buffer* wd_buf()
	{
		return buf_;
	}
private:

	DECLARE_NO_COPY_CLASS( JOMOO_Write_Stream );
	JOMOO_Write_Buffer* buf_;
};

class JOMOO_Buffer : public JOMOO_Read_Buffer
	, public JOMOO_Write_Buffer
{
public :
	virtual ~JOMOO_Buffer(){}
	virtual const tstring& toString() const = 0;
};

_jomoo_end

#endif // _JOMOO_Buffer_H_
