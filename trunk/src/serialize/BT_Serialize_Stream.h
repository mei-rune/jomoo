
/**
 * -*- C++ -*-
 * -------------------------------------------------------------------------------
 * - ��q�Шr �q�Шr		        BT_Serialize_Stream.h,v 1.0 2005/03/11 16:56:34
 *  �u�������� �q�q �Шr
 * ���������| �t------
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
 * @Brief ���л�����
 * �������ṩһ��ͳһ������Ӧ�ýӿ�
 */
class BT_Out_Stream
{
public:
	/**
	 * BT_Out_Stream constructor
	 * �����л������ݱ��浽һ���ļ���
	 * @param[ in ] file_name �ļ���
	 * @param[ in ] type ���еĸ�ʽ( �� bin xml ini )
	 * @remarks ע�������ܻ��ӳ��쳣
	 */
	BT_Out_Stream( const char* file_name ,int type = dom_stream )
		: delete_( true )
	{
		if( file_name == 0 )
			throw( std::runtime_error( "�ļ���������Ϊ��" ) );
		 BIN_OUT_Source out( file_name );
		sr.reset( _bt_serialize BTOUTSerializeFactory_Singleton::instance()->CreateObject( type ,&out )  );
		if( sr.get() == 0 )
			throw( std::runtime_error( "������ʧ��" ) ) ;
	}

	/**
	 * BT_Out_Stream constructor
	 * �����л������ݱ��浽һ���������
	 * @param[ in ] ostream ���������
	 * @param[ in ] type ���еĸ�ʽ( �� bin xml ini )
	 * @remarks ע�������ܻ��ӳ��쳣
	 */
	BT_Out_Stream( bt_ostream& ostream ,int type = dom_stream )
		: delete_( true )
	{
		_bt_serialize BIN_OUT_Source out( &ostream );
		sr.reset( _bt_serialize BTOUTSerializeFactory_Singleton::instance()->CreateObject( type ,&out )  );
		if( sr.get() == 0 )
			throw( std::runtime_error( "������ʧ��" ) ) ;
	}

	/**
	 * BT_Out_Stream constructor
	 * �����л������ݱ��浽һ�����Դ��
	 * @param[ in ] bos ���Դ
	 * @param[ in ] type ���еĸ�ʽ( �� bin xml ini )
	 * @remarks ע�������ܻ��ӳ��쳣
	 */
	BT_Out_Stream( BIN_OUT_Source bos ,int type = dom_stream )
		: delete_( true )
	{
		_bt_serialize BIN_OUT_Source out( bos );
		sr.reset( _bt_serialize BTOUTSerializeFactory_Singleton::instance()->CreateObject( type ,&out )  );
		if( sr.get() == 0 )
			throw( std::runtime_error( "������ʧ��" ) ) ;
	}

	/**
	 * BT_Out_Stream constructor
	 * �����л������ݱ��浽һ�����л��ӿ���
	 * @param[ in ] stream ���л��ӿ�ָ��
	 * @param[ in ] del ָʾ���л��ӿ��ڱ�������ʱ���Ƿ��Զ�ɾ��( true,ɾ�� false ��ɾ��)
	 * @remarks ע�������ܻ��ӳ��쳣
	 */
	BT_Out_Stream( serialize_ostream_base* stream , bool del = false )
		: sr( stream )
		, delete_( del )
	{
		if( sr.get() == 0 )
			throw( std::runtime_error( "������ʧ��" ) ) ;
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
	 * ���л�ģ�庯�����������л�һ��ָ���Ķ���
	 * @param[ in ] t ָ���Ķ���
	 * @param[ in ] name ���������
	 * @return �ɹ�����true�����򷵻�false
	 */
	template< typename	T >
		bool serialize( const T& t, tchar* name )
	{
		return serilaize_typename_T( t, *sr,name );
	}

	/**
	 * ���л�ģ�庯�����������л�һ��ָ���Ķ���
	 * @param[ in ] t ָ���Ķ���
	 * @return �ɹ�����true�����򷵻�false
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
		throw( std::runtime_error( "���л�����ʧ��" ) );
	return sm;
}



/**
 * @Brief �����л�����
 * �������ṩһ��ͳһ�ķ�����Ӧ�ýӿ�
 */
class BT_Input_Stream
{
public:
	/**
	 * BT_Input_Stream constructor
	 * ����һ���ļ��з����л���ָ���Ķ���
	 * @param[ in ] file_name �ļ���
	 * @param[ in ] type ���еĸ�ʽ( �� bin xml ini )
	 * @remarks ע�������ܻ��ӳ��쳣
	 */
	BT_Input_Stream( const char* file_name ,int type = dom_stream )
		: delete_( true )
	{
		if( file_name == 0 )
			throw( std::runtime_error( "�ļ���������Ϊ��" ) );
		_bt_serialize BIN_INPUT_Source in( file_name );
		dsr.reset( _bt_serialize BTINPUTSerializeFactory_Singleton::instance()->CreateObject( type ,&in  ) );
		if( dsr.get() == 0 )
			throw( std::runtime_error( "������ʧ��" ) ) ;
	}

	/**
	 * BT_Input_Stream constructor
	 * ����һ���ڴ���з����л���ָ���Ķ���
	 * @param[ in ] buf �ڴ�ָ��
	 * @param[ in ] lenght �ڴ��С
	 * @param[ in ] type ���еĸ�ʽ( �� bin xml ini )
	 * @remarks ע�������ܻ��ӳ��쳣
	 */
	BT_Input_Stream( const void * buf, size_t lenght ,int type = dom_stream )
		: delete_( true )
	{
		if( buf == 0 )
			throw( std::runtime_error( "�ڴ治����Ϊ��" ) );
		_bt_serialize BIN_INPUT_Source in( buf,lenght );
		dsr.reset( _bt_serialize BTINPUTSerializeFactory_Singleton::instance()->CreateObject( type ,&in  ) );
		if( dsr.get() == 0 )
			throw( std::runtime_error( "������ʧ��" ) ) ;
	}

	/**
	 * BT_Input_Stream constructor
	 * ����һ���������з����л���ָ���Ķ���
	 * @param[ in ] istream ������
	 * @param[ in ] type ���еĸ�ʽ( �� bin xml ini )
	 * @remarks ע�������ܻ��ӳ��쳣
	 */
	BT_Input_Stream( bt_istream& istream ,int type = dom_stream )
		: delete_( true )
	{
		_bt_serialize BIN_INPUT_Source in( &istream );
		dsr.reset( _bt_serialize BTINPUTSerializeFactory_Singleton::instance()->CreateObject( type ,&in  ) );
		if( dsr.get() == 0 )
			throw( std::runtime_error( "������ʧ��" ) ) ;
	}

	/**
	 * BT_Input_Stream constructor
	 * ����һ������Դ�з����л���ָ���Ķ���
	 * @param[ in ] bis ����Դ
	 * @param[ in ] type ���еĸ�ʽ( �� bin xml ini )
	 * @remarks ע�������ܻ��ӳ��쳣
	 */
	BT_Input_Stream( BIN_INPUT_Source bis ,int type = dom_stream )
		: delete_( true )
	{
		_bt_serialize BIN_INPUT_Source in( bis );
		dsr.reset( _bt_serialize BTINPUTSerializeFactory_Singleton::instance()->CreateObject( _bt_serialize dom_stream ,&in  ) );
		if( dsr.get() == 0 )
			throw( std::runtime_error( "������ʧ��" ) ) ;
	}

	/**
	 * BT_Input_Stream constructor
	 * ����һ�������л��ӿ��з����л���ָ���Ķ���
	 * @param[ in ] stream �����л��ӿ�
	 * @param[ in ] del ָʾ���л��ӿ��ڱ�������ʱ���Ƿ��Զ�ɾ��( true,ɾ�� false ��ɾ��)
	 * @remarks ע�������ܻ��ӳ��쳣
	 */
	BT_Input_Stream( serialize_istream_base* stream , bool del = false )
	: dsr( stream )
	, delete_( del )
	{
		if( dsr.get() == 0 )
			throw( std::runtime_error( "������ʧ��" ) ) ;
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
	 * �����л�ģ�庯�������ڷ����л�һ��ָ���Ķ���
	 * @param[ in ] t ָ���Ķ���
	 * @param[ in ] name ���������
	 * @return �ɹ�����true�����򷵻�false
	 */
	template< typename	T >
		bool deserialize( T& t, const tchar* name )
	{
		return deserilaize_typename_T( t, *dsr,name );
	}

	/**
	 * �����л�ģ�庯�������ڷ����л�һ��ָ���Ķ���
	 * @param[ in ] t ָ���Ķ���
	 * @return �ɹ�����true�����򷵻�false
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
		throw( std::runtime_error( "�����л�����ʧ��" ) );
	return sm;
}

_bt_serialize_end

#endif // _BT_Serialize_Stream_H_
