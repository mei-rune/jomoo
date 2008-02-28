
/**
 * -*- C++ -*-
 * -------------------------------------------------------------------------------
 * - ¤╭⌒╮ ╭⌒╮		             DB_serializer.h,v 1.0 2005/04/07 11:33:34
 *  ╱◥██◣ ╭╭ ⌒╮
 * ︱田︱田田| ╰------
 * -------------------------------------------------------------------------------
 */

#ifndef _DB_serializer_H_
#define _DB_serializer_H_

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */


#include "serialize/serialize2.h"
#include "serialize/serialize_def.h"
#include "framework/BT_Ptr.h"
#include "util/tstring.h"
#include <stack>
#include <iostream>
#include "db/dbmanager.h"

_bt_serialize_begin

/**
 * @brief Db_serializer xml序列化类
 * 本类继承序列化接口下来的，它将一个可序列化的类序列化到一个dom模型中。
 */
class Db_serializer : public serialize_ostream_base
{
public:

	Db_serializer( DbExecute* executer )
		: executer_( executer )
	{
		init( executer );
	}

	virtual ~Db_serializer(void)
	{
	}

	virtual bool open(const tchar* ClassName)
	{
		if( executer_ == 0 )
			return false;
		return executer_->prepare( ClassName );
	}

	virtual bool open(const tchar* ClassName, const size_t& size)
	{
		if( executer_ == 0 )
			return false;
		return true;
	}

	bool close(const tchar* ClassName)
	{
		if( executer_ == 0 )
			return false;
		return executer_->exec( );
	}

	template< typename T >
		bool write_( const T& t, const tchar* fieldname  )
	{
		if( executer_ == 0 )
			return false;
		return executer_->bind( fieldname, -1, t );
	}
	template< typename T >
		bool write_str( const T& t, const tchar* fieldname  )
	{
		if( executer_ == 0 )
			return false;
		return executer_->bind( fieldname, -1, t.c_str(), t.size() );
	}
	bool write(const bool& t, const tchar* fieldname = "bool")
	{
		return write_( t, fieldname );
	}

	bool write(const char& t, const tchar* fieldname = "char")
	{
		return write_( t, fieldname );
	}
	bool write(const short& t, const tchar* fieldname = "short")
	{
		return write_( t, fieldname );
	}
	bool write(const int& t, const tchar* fieldname = "int")
	{
		return write_( t, fieldname );
	}
	bool write(const long& t, const tchar* fieldname = "long")
	{
		return write_( t, fieldname );
	}

	bool write(const __int64& t, const tchar* fieldname = "__int64")
	{
		return write_( t, fieldname );
	}
	bool write(const unsigned char& t, const tchar* fieldname = "unsignedchar")
	{
		return write_( t, fieldname );
	}
	bool write(const unsigned short& t, const tchar* fieldname = "unsingedshort")
	{
		return write_( t, fieldname );
	}

	bool write(const unsigned int& t, const tchar* fieldname = "unsignedint")
	{
		return write_( ( __int64 )t, fieldname );
	}
	bool write(const unsigned long& t, const tchar* fieldname = "unsignedlong")
	{
		return write_( ( __int64 )t, fieldname );
	}

	bool write(const unsigned __int64& t, const tchar* fieldname = "unsigned__int64")
	{
		return write_( ( double )t, fieldname );
	}

	bool write(const  double& t, const tchar* fieldname = "double")
	{
		return write_( t, fieldname );
	}
	bool write(const float& t, const tchar* fieldname = "float")
	{
		return write_( t, fieldname );
	}
	bool write(const tstring& t, const tchar* fieldname = "string")
	{
		return write_str( t, fieldname );
	}

protected:

	Db_serializer( )
		: executer_( 0 )
	{
	}

	void init( DbExecute* executer )
	{
		if( executer == 0 )
			throw std::runtime_error( "初始化Db_serialize失败，DbExecute不能为空" );
		executer_ = executer;
	}
private:

	DbExecute* executer_;
};



/**
 * @brief Db_deserializer xml反序列化类
 * 本类继承反序列化接口下来的，它将一个可序列化的类从一个dom模型中读从来。
 */
class Db_deserializer : public serialize_istream_base
{
public:
	Db_deserializer( DbQuery* query )
		: query_( query )
		, state_( 0 )
		, col_( 0 )
	{
		init( query );
	}

	~Db_deserializer(void)
	{
	}
	


	virtual bool open(const tchar* ClassName)
	{
		if( query_ == 0 )
			return false;
		switch( state_ )
		{
		case 0:
			col_ = 0;
			return query_ ->exec( ClassName, -1 );
			break;
		case 1:
			state_ ++;
			col_ = 0;
			return query_->nextRow();
		}
		return true;
	}

	virtual bool open(const tchar* ClassName, size_t& size)
	{
		if( query_ == 0 )
			return false;
		if( state_ != 0 )
			return true;
		col_ = 0;
		if( !query_ ->exec( ClassName, -1 ) )
			return false;
		state_ = 1;
		return true;
	}

	bool close(const tchar* ClassName)
	{
		switch( state_ )
		{
		case 0:
			break;
		case 1:
		case 2:
			state_ --;
		}
		return true;
	}

	template< typename T >
	bool read_( T& t, const tchar* fieldname )
	{
		if( query_ == 0 )
			return false;
		return getQueryCol( *query_, col_,t );
	}

		template< typename T >
	bool read_str( T& t, const tchar* fieldname )
	{
		if( query_ == 0 )
			return false;
		return getQueryCol( *query_, col_,t );
	}
	bool read( bool& t, const tchar* fieldname = "bool")
	{
		return read_( t, fieldname );
	}
	
	bool read( char& t, const tchar* fieldname = "char")
	{
		int i = 0;
		if( !read_( i, fieldname ) )
			return false;
		t = ( char )i;
		return true;
	}

	bool read( short& t, const tchar* fieldname = "short")
	{
		int i = 0;
		if( !read_( i, fieldname ) )
			return false;
		t = ( short )i;
		return true;
	}

	bool read( int& t, const tchar* fieldname = "int")
	{
		return read_( t, fieldname );
	}
	bool read( long& t, const tchar* fieldname = "long")
	{
		int i = 0;
		if( !read_( i, fieldname ) )
			return false;
		t = ( long )i;
		return true;
	}
	bool read( __int64& t, const tchar* fieldname = "__int64")
	{
		return read_( t, fieldname );
	}
	bool read( unsigned char& t, const tchar* fieldname = "unsignedchar")
	{
		int i = 0;
		if( !read_( i, fieldname ) )
			return false;
		t = ( unsigned char ) i;
		return true;
	
	}
	bool read( unsigned short& t, const tchar* fieldname = "unsingedshort")
	{
		int i = 0;
		if( !read_( i, fieldname ) )
			return false;
		t = i;
		return true;
	}
	bool read( unsigned int& t, const tchar* fieldname = "unsignedint")
	{
		__int64 i = 0;
		if( !read_( i, fieldname ) )
			return false;
		t =( unsigned int ) i;
		return true;
	}

	bool read( unsigned long& t, const tchar* fieldname = "unsignedlong")
	{
		__int64 i = 0;
		if( !read_( i, fieldname ) )
			return false;
		t =( unsigned long ) i;
		return true;
	}
	bool read( unsigned __int64& t, const tchar* fieldname = "unsigned__int64")
	{
		double i = 0;
		if( !read_( i, fieldname ) )
			return false;
		t =( unsigned __int64 ) i;
		return true;
	}

	bool read( double& t, const tchar* fieldname = "double")
	{
		return read_( t, fieldname );
	}

	bool read( float& t, const tchar* fieldname = "float")
	{
		double i = 0;
		if( !read_( i, fieldname ) )
			return false;
		t =( float ) i;
		return true;
	}

	bool read( tstring& t, const tchar* fieldname = "string")
	{
		return read_( t, fieldname );
	}

	bool read( string_helper_base2& t, const tchar* fieldname = "string")
	{
		if( query_ == 0 )
			return false;
		t.clear();
		t = query_->getString( col_ );
		return true;
	}

protected:

	Db_deserializer( )
		: query_( 0 )
		, state_( 0 )
		, col_( 0 )
	{
	}

	void init( DbQuery* query )
	{
		if( query == 0 )
			throw std::runtime_error( "初始化Db_deserializer失败，DbQuery不能为空" );
		query_ = query;
		state_ = 0;
		col_ = 0;
	}

private:

	DbQuery* query_;
	
	/// state_ > 0 表示已经open,open == 1时表示，用open( name, size )过
	int state_;

	int col_;
};

_bt_serialize_end

#endif // _XML_serializer_H_

