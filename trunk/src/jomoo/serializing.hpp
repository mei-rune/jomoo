
/**
 * -*- C++ -*-
 * -------------------------------------------------------------------------------
 * - ¤╭⌒╮ ╭⌒╮		               serialize.h,v 1.0 2005/03/29 15:41:34
 *  ╱◥██◣ ╭╭ ⌒╮
 * ︱田︱田田| ╰------
 * -------------------------------------------------------------------------------
 */


#ifndef _serializing_hpp_
#define _serializing_hpp_

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "serialize/config_serializing.h"
#include "serialize/serialize.h"
#include "serialize/serialize_macro.h"

_serializing_begin

class serialize_object
{
public:
	virtual ~serialize_object(){}
	virtual bool write( serialize_writer& stream, const tchar* name="serialize_object") = 0;
	virtual bool read( serialize_writer& stream, const tchar* name="serialize_object") = 0;
};

bool inline serialize( bool t,  & stream, const tchar* name="bool")
{
	return stream.write(t,name);
}

bool inline serialize( char t, serialize_writer& stream, const tchar* name="char")
{
	return stream.write((int)t,name);
}

bool inline serialize( short t, serialize_writer& stream, const tchar* name="short")
{
	return stream.write((int)t,name);
}

bool inline serialize( int t, serialize_writer& stream, const tchar* name="int")
{
	return stream.write(t,name);
}

bool inline serialize( long t, serialize_writer& stream, const tchar* name="long")
{
	return stream.write((int)t,name);
}

bool inline serialize( __int64 t, serialize_writer& stream, const tchar* name="__int64")
{
	return stream.write(t,name);
}

bool inline serialize( unsigned char t, serialize_writer& stream, const tchar* name="unsingedchar")
{
	return stream.write((int)t,name);
}

bool inline serialize( unsigned short t, serialize_writer& stream, const tchar* name="unsignedshort")
{
	return stream.write((int)t,name);
}

bool inline serialize( unsigned int t, serialize_writer& stream, const tchar* name="unsignedint")
{
	return stream.write((int)t,name);
}

bool inline serialize( unsigned long t, serialize_writer& stream, const tchar* name="unsignedlong")
{
	return stream.write((int)t,name);
}

bool inline serialize( unsigned __int64 t, serialize_writer& stream, const tchar* name="unsigned__int64")
{
	return stream.write((__int64)t,name);
}

bool inline serialize(const std::string& t, serialize_writer& stream, const tchar* name="string")
{
	return stream.write((int)t.size(),name) && stream.write(t.c_str(), t.size() + 1, name);
}

bool inline serialize(const std::wstring& t, serialize_writer& stream, const tchar* name="string")
{
	return stream.write((int)(t.size() * sizeof( wchar_t)),name) && stream.write(t.c_str(), (int)(t.size() * sizeof( wchar_t)) + 1, name);
}

template< typename T >
bool inline serialize(const T& s1, serialize_writer& strm, const tchar* name="serialize_object")
{
	return s1.write(strm, name);
}

//反序列化基础函数

bool inline deserialize( bool& t, serialize_reader& stream, const tchar* name="bool")
{
	return stream.read(t,name);
}

//#define DESERIALIZE_OBJECT( type1, type2, stream, name ) \
//	int val = 0;										\
//	if( stream.read( val,name) );						\
//	{													\
//		t = (type)val;									\
//		return true;									\
//	}													\
//	return false;

template< typename T,typename P>
inline bool ___deserialize_object(P& t, serialize_reader& stream, const tchar* name="char" )
{
	T value;
	if( stream.read( value, name) )
	{
		t = (P)value;
		return true;
	}
	return false;
}

bool inline deserialize( char& t, serialize_reader& stream, const tchar* name="char")
{
	return ___deserialize_object< int, char>( t, stream, name );
}

bool inline deserialize( short& t, serialize_reader& stream, const tchar* name="short")
{
	return ___deserialize_object< int, short>( t, stream, name );
}

bool inline deserialize( int& t, serialize_reader& stream, const tchar* name="int")
{
	return stream.read( t, name);
}

bool inline deserialize( long& t, serialize_reader& stream, const tchar* name="long")
{
	return ___deserialize_object< int, long>( t, stream, name );
}

bool inline deserialize( __int64& t, serialize_reader& stream, const tchar* name="__int64")
{
	return stream.read(t,name);
}

bool inline deserialize( unsigned char& t, serialize_reader& stream, const tchar* name="unsignedchar")
{
	return ___deserialize_object< int,unsigned char>( t, stream, name );
}

bool inline deserialize( unsigned short& t, serialize_reader& stream, const tchar* name="unsignedshort")
{
	return ___deserialize_object< int,unsigned short>( t, stream, name );
}

bool inline deserialize( unsigned int& t, serialize_reader& stream, const tchar* name="unsignedint")
{
	return ___deserialize_object< int,unsigned int>( t, stream, name );
}

bool inline deserialize( unsigned long& t, serialize_reader& stream, const tchar* name="unsignedlong")
{
	return ___deserialize_object< int,unsigned long>( t, stream, name );
}

bool inline deserialize( unsigned __int64& t, serialize_reader& stream, const tchar* name="unsigned__int64")
{
	return ___deserialize_object< __int64,unsigned __int64>( t, stream, name );
}


bool inline serialize( std::string& t, serialize_writer& stream, const tchar* name="string")
{
	int value;
	if( !stream.read( value, name) )
		return false;
	t.resize( value );
	size_t len = 0;
	if( !stream.read( (void*)t.c_str(),len, name) )
		return false;

	t.resize( len-1 );
	return true;
}

bool inline serialize( std::wstring& t, serialize_writer& stream, const tchar* name="string")
{
	int value;
	if( !stream.read( value, name) )
		return false;
	t.resize( value );
	size_t len = 0;
	if( !stream.read( (void*)t.c_str(),len, name) )
		return false;

	t.resize( len-1 );
	return true;
}

bool inline deserialize( tstring& t, serialize_reader& stream, const tchar* name="string")
{
	string_helper2 sh(t);
	return stream.read(sh,name);
}

template< typename T >
bool inline deserialize(T& s1, serialize_writer& strm, const tchar* name="serialize_object")
{
	return s1.read(strm, name);
}

template< typename T>
bool inline serialize( const std::auto_ptr<T>& ptr_, serialize_writer& stream, const tchar* name = "auto_ptr")
{
	return serialize( *ptr_, stream,name);
}

template< typename T1, typename T2>
bool inline serialize( const std::pair<T1,T2>& pair_, serialize_writer& stream, const tchar* name = "pair")
{
	return serialize( pair_.second, stream,name );
}
template< typename _Init>
bool inline serialize( _Init _F, _Init _E, serialize_writer& stream, const size_t& size = -1, const tchar* name = "array")
{
	size_t sz = size;
	if ( -1 == sz )
		sz  = std::distance( _F, _E );

	if ( !stream.open(name, sz) )
		return false;

	bool ret = false;
		for(;_F!=_E && (ret=serialize( *_F, stream ));_F++);			
		if ( ret ) ret = stream.close(name);
	
	return ret;
}


template< typename T1, typename T2 >
bool inline serialize( const std::list< T1,T2 >& list_ , serialize_writer& stream, const tchar* name = "list" )
{
	return serialize(list_.begin(), list_.end(), stream, list_.size(),  name);
}
template< typename T1, typename T2 >
bool inline serialize( const std::vector< T1,T2 >& vector_ , serialize_writer& stream, const tchar* name ="vector" )
{
	return serialize(vector_.begin(), vector_.end(), stream, vector_.size(), name );
}
template< typename T1, typename T2, typename T3 >
bool inline serialize( const std::set< T1, T2, T3 >& set_ , serialize_writer& stream, const tchar* name ="set" )
{
	return serialize(set_.begin(), set_.end(), stream, set_.size(), name );
}

template< typename T1, typename T2, typename T3, typename T4 >
bool inline serialize( const std::map< T1, T2, T3, T4 >& map_ , serialize_writer& stream, const tchar* name ="map" )
{
	return serialize(map_.begin(), map_.end(), stream, map_.size(), name );
}
template< typename T1, typename T2, typename T3, typename T4 >
bool inline serialize( const std::multimap< T1, T2, T3, T4 >& map_ , serialize_writer& stream, const tchar* name ="map" )
{
	return serialize(map_.begin(), map_.end(), stream, map_.size(), name );
}

template< typename T>
bool inline deserialize( std::auto_ptr<T>& ptr_, serialize_reader& stream, const tchar* name = "auto_ptr")
{
	if( ptr.get() == 0 )
		ptr_.reset( new T() );
	return deserialize( *ptr_, stream,name);
}

template< typename T1, typename T2 >
bool inline deserialize( std::list< T1,T2 >& list_ , serialize_reader& stream, const tchar* name = "list" )
{
	bool ret = false;
	size_t size = -1;


	if ( ret=stream.open(name, size) )
	{
		list_.clear();

		while( ret && (size==-1|| list_.size()<size) )
		{
			std::list< T1,T2 >::value_type val;//std::list< T1,T2 >::iterator it = list_.insert(list.end(), std::list< T1,T2 >::value_type());
			if ( ret=deserialize(val, stream) )
				list_.push_back(val);	

		};

		//可能某些流如xml等不支持size,
		//如果 支持size：必须读取相应size个且能close,才为成功
		//如果不支持size：必须要能close为成功

		ret = (  size==-1 || list_.size()==size  ) && stream.close(name)  ;
	}
	return ret;
}
template< typename T1, typename T2 >
bool inline deserialize( std::vector< T1,T2 >& vector_ , serialize_reader& stream, const tchar* name ="vector" )
{
	bool ret = false;
	size_t size = -1;
	if ( ret=stream.open(name, size) )
	{
		vector_.clear();
		if ( size != -1 ) vector_.reserve( size );
		while( ret && (size==-1|| vector_.size()<size) )
		{
			std::vector< T1,T2 >::value_type val;//std::vector< T1,T2 >::iterator it = vector_.insert(vector_.end(), std::vector< T1,T2 >::value_type());
			if ( ret=deserialize(val, stream) )
				vector_.push_back(val);	
		};

		//可能某些流如xml等不支持size,
		//如果 支持size：必须读取相应size个且能close,才为成功
		//如果不支持size：必须要能close为成功

		ret = (  size==-1 || vector_.size()==size  ) && stream.close(name)  ;		

	}
	return ret;
}
template< typename T1, typename T2, typename T3 >
bool inline deserialize( std::set< T1, T2, T3 >& set_ , serialize_reader& stream, const tchar* name ="set" )
{
	bool ret = false;
	size_t size = -1;
	if ( ret=stream.open(name, size) )
	{
		set_.clear();
		while(ret && (size==-1|| set_.size()<size) )
		{
			std::set< T1, T2, T3 >::value_type val;
			if ( ret=deserialize(val, stream) )
				set_.insert(val);	
		};
		

		//可能某些流如xml等不支持size,
		//如果 支持size：必须读取相应size个且能close,才为成功
		//如果不支持size：必须要能close为成功

		ret = (  size==-1 || set_.size()==size  ) && stream.close(name)  ;
	}
	return ret;	
	//return serialize(set_.begin(), set_.end(), stream, set_.size(), name );
}

template< typename T1, typename T2, typename T3, typename T4 >
bool inline deserialize( std::map< T1, T2, T3, T4 >& map_ , serialize_reader& stream, const tchar* name ="map" )
{
	bool ret = false;
	size_t size = -1;
	if ( ret=stream.open(name, size) )
	{
		map_.clear();
		while( ret &&(size==-1|| map_.size()<size) )
		{
			std::map< T1, T2, T3, T4 >::key_type  key;
			std::map< T1, T2, T3, T4 >::referent_type  val;
			if ( ret=(deserialize(val, stream) && deserialize_getkey( key, (const std::map< T1, T2, T3, T4 >::referent_type)val )) )
				map_.insert( std::map< T1, T2, T3, T4 >::value_type(key, val));	
		};

		//可能某些流如xml等不支持size,
		//如果 支持size：必须读取相应size个且能close,才为成功
		//如果不支持size：必须要能close为成功

		ret = (  size==-1 || map_.size()==size  ) && stream.close(name)  ;
	}
	return ret;	
	//return serialize(map_.begin(), map_.end(), stream, map_.size(), name );
}
template< typename T1, typename T2, typename T3, typename T4 >
bool inline deserialize( std::multimap< T1, T2, T3, T4 >& map_ , serialize_reader& stream, const tchar* name ="map" )
{
	bool ret = false;
	size_t size = -1;
	if ( ret=stream.open(name, size) )
	{
		map_.clear();
		while( ret && (size==-1|| map_.size()<size) )
		{
			std::multimap< T1, T2, T3, T4 >::key_type  key;
			std::multimap< T1, T2, T3, T4 >::referent_type  val;
			if ( ret=(deserialize(val, stream) && deserialize_getkey( key, (const std::multimap< T1, T2, T3, T4 >::referent_type)val )) )
				map_.insert( std::map< T1, T2, T3, T4 >::value_type(key, val));	

			//std::multimap< T1, T2, T3, T4 >::value_type  val;
			//if ( ret=deserialize(val, stream) )
			//	map_.insert(val);	
		};

		//可能某些流如xml等不支持size,
		//如果 支持size：必须读取相应size个且能close,才为成功
		//如果不支持size：必须要能close为成功

		ret = (  size==-1 || map_.size()==size  ) && stream.close(name)  ;
	}
	return ret;	
}

_serializing_begin

#endif // _serialize2_H_
