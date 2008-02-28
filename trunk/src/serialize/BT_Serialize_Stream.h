
/**
 * -*- C++ -*-
 * -------------------------------------------------------------------------------
 * - ¤╭⌒╮ ╭⌒╮		        BT_Serialize_Stream.h,v 1.0 2005/03/11 16:56:34
 *  ╱◥██◣ ╭╭ ⌒╮
 * ︱田︱田田| ╰------
 * -------------------------------------------------------------------------------
 */

#ifndef _BT_Serialize_Stream_H_
#define _BT_Serialize_Stream_H_

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include "serializer_factory.h"

_bt_begin

template< typename T >
bool serilaize_typename_T( const T& t ,_bt serialize_ostream_base& sr )
{
	return serialize( t,sr );
}

template< typename T >
bool serilaize_typename_T( const T& t ,_bt serialize_ostream_base& sr ,const tchar* name )
{
	return serialize( t,sr ,name );
}


template< typename T >
bool deserilaize_typename_T( T& t ,_bt serialize_istream_base& dsr )
{
	return deserialize( t,dsr );
}

template< typename T >
bool deserilaize_typename_T( T& t , serialize_istream_base& dsr ,const tchar* name )
{
	return deserialize( t,dsr ,name );
}

_bt_end

_bt_serialize_begin



/**
 * @Brief 序列化流类
 * 本类用提供一个统一的序列应用接口
 */
class BT_Out_Stream
{
public:
	/**
	 * BT_Out_Stream constructor
	 * 将序列化的内容保存到一个文件中
	 * @param[ in ] file_name 文件名
	 * @param[ in ] type 序列的格式( 如 bin xml ini )
	 * @remarks 注意它可能会扔出异常
	 */
	BT_Out_Stream( const char* file_name ,int type = dom_stream )
		: delete_( true )
	{
		if( file_name == 0 )
			throw( std::runtime_error( "文件名不可以为空" ) );
		 BIN_OUT_Source out( file_name );
		sr.reset( _bt_serialize BTOUTSerializeFactory_Singleton::instance()->CreateObject( type ,&out )  );
		if( sr.get() == 0 )
			throw( std::runtime_error( "创建流失败" ) ) ;
	}

	/**
	 * BT_Out_Stream constructor
	 * 将序列化的内容保存到一个输出流中
	 * @param[ in ] ostream 输出流引用
	 * @param[ in ] type 序列的格式( 如 bin xml ini )
	 * @remarks 注意它可能会扔出异常
	 */
	BT_Out_Stream( bt_ostream& ostream ,int type = dom_stream )
		: delete_( true )
	{
		_bt_serialize BIN_OUT_Source out( &ostream );
		sr.reset( _bt_serialize BTOUTSerializeFactory_Singleton::instance()->CreateObject( type ,&out )  );
		if( sr.get() == 0 )
			throw( std::runtime_error( "创建流失败" ) ) ;
	}

	/**
	 * BT_Out_Stream constructor
	 * 将序列化的内容保存到一个输出源中
	 * @param[ in ] bos 输出源
	 * @param[ in ] type 序列的格式( 如 bin xml ini )
	 * @remarks 注意它可能会扔出异常
	 */
	BT_Out_Stream( BIN_OUT_Source bos ,int type = dom_stream )
		: delete_( true )
	{
		_bt_serialize BIN_OUT_Source out( bos );
		sr.reset( _bt_serialize BTOUTSerializeFactory_Singleton::instance()->CreateObject( type ,&out )  );
		if( sr.get() == 0 )
			throw( std::runtime_error( "创建流失败" ) ) ;
	}

	/**
	 * BT_Out_Stream constructor
	 * 将序列化的内容保存到一个序列化接口中
	 * @param[ in ] stream 序列化接口指针
	 * @param[ in ] del 指示序列化接口在本类析构时，是否自动删除( true,删除 false 不删除)
	 * @remarks 注意它可能会扔出异常
	 */
	BT_Out_Stream( serialize_ostream_base* stream , bool del = false )
		: sr( stream )
		, delete_( del )
	{
		if( sr.get() == 0 )
			throw( std::runtime_error( "创建流失败" ) ) ;
	}

	/**
	 * BT_Out_Stream destructor
	 */
	~BT_Out_Stream(  )
	{
		if( !delete_ )
			sr.release();

	}

	/**
	 * 序列化模板函数，用于序列化一个指定的对象
	 * @param[ in ] t 指定的对象
	 * @param[ in ] name 对象的名称
	 * @return 成功返回true，否则返回false
	 */
	template< typename	T >
		bool serialize( const T& t, tchar* name )
	{
		return serilaize_typename_T( t, *sr,name );
	}

	/**
	 * 序列化模板函数，用于序列化一个指定的对象
	 * @param[ in ] t 指定的对象
	 * @return 成功返回true，否则返回false
	 */
		template< typename	T >
		bool serialize( const T& t )
	{
		return serilaize_typename_T( t, *sr );
	}
private:
	std::auto_ptr< serialize_ostream_base > sr;
	bool delete_;
};

template< typename T >
BT_Out_Stream& operator<<( BT_Out_Stream& sm, const T& t )
{
	if( !sm.serialize( t ) )
		throw( std::runtime_error( "序列化对象失败" ) );
	return sm;
}



/**
 * @Brief 反序列化流类
 * 本类用提供一个统一的反序列应用接口
 */
class BT_Input_Stream
{
public:
	/**
	 * BT_Input_Stream constructor
	 * 将从一个文件中反序列化出指定的对象
	 * @param[ in ] file_name 文件名
	 * @param[ in ] type 序列的格式( 如 bin xml ini )
	 * @remarks 注意它可能会扔出异常
	 */
	BT_Input_Stream( const char* file_name ,int type = dom_stream )
		: delete_( true )
	{
		if( file_name == 0 )
			throw( std::runtime_error( "文件名不可以为空" ) );
		_bt_serialize BIN_INPUT_Source in( file_name );
		dsr.reset( _bt_serialize BTINPUTSerializeFactory_Singleton::instance()->CreateObject( type ,&in  ) );
		if( dsr.get() == 0 )
			throw( std::runtime_error( "创建流失败" ) ) ;
	}

	/**
	 * BT_Input_Stream constructor
	 * 将从一个内存块中反序列化出指定的对象
	 * @param[ in ] buf 内存指针
	 * @param[ in ] lenght 内存大小
	 * @param[ in ] type 序列的格式( 如 bin xml ini )
	 * @remarks 注意它可能会扔出异常
	 */
	BT_Input_Stream( const void * buf, size_t lenght ,int type = dom_stream )
		: delete_( true )
	{
		if( buf == 0 )
			throw( std::runtime_error( "内存不可以为空" ) );
		_bt_serialize BIN_INPUT_Source in( buf,lenght );
		dsr.reset( _bt_serialize BTINPUTSerializeFactory_Singleton::instance()->CreateObject( type ,&in  ) );
		if( dsr.get() == 0 )
			throw( std::runtime_error( "创建流失败" ) ) ;
	}

	/**
	 * BT_Input_Stream constructor
	 * 将从一个输入流中反序列化出指定的对象
	 * @param[ in ] istream 输入流
	 * @param[ in ] type 序列的格式( 如 bin xml ini )
	 * @remarks 注意它可能会扔出异常
	 */
	BT_Input_Stream( bt_istream& istream ,int type = dom_stream )
		: delete_( true )
	{
		_bt_serialize BIN_INPUT_Source in( &istream );
		dsr.reset( _bt_serialize BTINPUTSerializeFactory_Singleton::instance()->CreateObject( type ,&in  ) );
		if( dsr.get() == 0 )
			throw( std::runtime_error( "创建流失败" ) ) ;
	}

	/**
	 * BT_Input_Stream constructor
	 * 将从一个输入源中反序列化出指定的对象
	 * @param[ in ] bis 输入源
	 * @param[ in ] type 序列的格式( 如 bin xml ini )
	 * @remarks 注意它可能会扔出异常
	 */
	BT_Input_Stream( BIN_INPUT_Source bis ,int type = dom_stream )
		: delete_( true )
	{
		_bt_serialize BIN_INPUT_Source in( bis );
		dsr.reset( _bt_serialize BTINPUTSerializeFactory_Singleton::instance()->CreateObject( _bt_serialize dom_stream ,&in  ) );
		if( dsr.get() == 0 )
			throw( std::runtime_error( "创建流失败" ) ) ;
	}

	/**
	 * BT_Input_Stream constructor
	 * 将从一个反序列化接口中反序列化出指定的对象
	 * @param[ in ] stream 反序列化接口
	 * @param[ in ] del 指示序列化接口在本类析构时，是否自动删除( true,删除 false 不删除)
	 * @remarks 注意它可能会扔出异常
	 */
	BT_Input_Stream( serialize_istream_base* stream , bool del = false )
	: dsr( stream )
	, delete_( del )
	{
		if( dsr.get() == 0 )
			throw( std::runtime_error( "创建流失败" ) ) ;
	}

	/**
	 * BT_Input_Stream destructor
	 */
	~BT_Input_Stream( )
	{
		if( !delete_ )
			dsr.release();
	}

	/**
	 * 反序列化模板函数，用于反序列化一个指定的对象
	 * @param[ in ] t 指定的对象
	 * @param[ in ] name 对象的名称
	 * @return 成功返回true，否则返回false
	 */
	template< typename	T >
		bool deserialize( T& t, const tchar* name )
	{
		return deserilaize_typename_T( t, *dsr,name );
	}

	/**
	 * 反序列化模板函数，用于反序列化一个指定的对象
	 * @param[ in ] t 指定的对象
	 * @return 成功返回true，否则返回false
	 */
	template< typename	T >
		bool deserialize( T& t )
	{
		return deserilaize_typename_T( t, *dsr );
	}
private:
	std::auto_ptr< serialize_istream_base > dsr;
	bool delete_;
};

template< typename T >
BT_Input_Stream& operator>>( BT_Input_Stream& sm, T& t )
{
	if( !sm.deserialize( t ) )
		throw( std::runtime_error( "反序列化对象失败" ) );
	return sm;
}

_bt_serialize_end

#endif // _BT_Serialize_Stream_H_
