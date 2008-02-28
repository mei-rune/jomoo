
#ifndef _BT_Service_Handler_
#define _BT_Service_Handler_


#include "BOE\IO\IO.h"
#include "BOE/StdLogger.H"
#include "BOE/get_last_error.h"
#define MAX_SIZE 10
#define MEMSEG 1

class Service_Handler : public _io BOE_Transport_Handler
{
public:

	Service_Handler()
	{
		for( int i =0; i < 10; i ++ )
		{
			iobuf[ i ].buf = ( char* ) malloc( MEMSEG + 1 );
			iobuf[ i ].len = MEMSEG;
		}
	}

	~Service_Handler()
	{
		for( int i =0; i < 10; i ++ )
		{
			free( iobuf[ i ].buf );
		}
	}

	void open( _io BOE_Transport_Ptr connect )
	{
		connect_ = connect;
		if( ! connect->read( *this, buf, MAX_SIZE , 0 ) )
			close();

		//if( ! connect->read( *this, iobuf, 10, 0 ) )
		//	close();
	}

	void close( )
	{
		connect_.reset( ( _io BOE_Transport*) 0 ) ;
		delete this;
	}

	
	/**
	 * channel读操作回调接口
	 * @see BOE_Read_Result
	 * @see BOE_Transport::read
	 */
	virtual void onRead( _io BOE_Read_Result& result)
	{
		if( !result.success() || result.bytes_to_transferred() == 0 )
		{
			if( result.error() == ERROR_OPERATION_ABORTED )
			{
				BT_LOG_ERROR( result.transport().getLogger()
				, result.transport().toString() << "> 用户中断" );
			}
			else
			{
				BT_LOG_ERROR( result.transport().getLogger()
				, result.transport().toString() << "> " << get_last_error() );
			}
			return close();
		}

		if( ! result.transport().write( *this, buf, result.bytes_to_transferred(), 0 ) )
			close();
	}

	/**
	 * channel读操作回调接口
	 * @see BOE_Read_Array_Result
	 * @see BOE_Transport::read
	 */
	virtual void onReadArray( _io BOE_Read_Array_Result& result )
	{
		if( !result.success() || result.bytes_to_transferred() == 0 )
			return close();
		size_t bytes = result.bytes_to_transferred();
		for( size_t i = 0; i < 10; i ++ )
		{
			if( bytes > result.data()[i].len  )
			{
				bytes -= result.data()[i].len;
				continue;
			}
			result.data()[i].len = bytes;
			bytes = 0;
			break;
		}
		i ++;

		if( ! result.transport().transmit( *this, result.data(), i, 0 ) )
			close();
	}

	/**
	 * channel写操作回调接口
	 * @see BOE_Write_Result
	 * @see BOE_Transport::write
	 */
	virtual void onWrite( _io BOE_Write_Result& result)
	{
		if( !result.success() || result.bytes_to_transferred() == 0 )
			return close();
		if( ! result.transport().read( *this, buf, MAX_SIZE, 0 ) )
			close();
		 //result.transport().cancel();
	}

	/**
	 * channel写操作回调接口
	 * @see BOE_Transmit_Result
	 * @see BOE_Transport::transmit
	 */
	virtual void onWriteArray(BOE_Write_Array_Result& result )
	{
		//if( !result.success() || result.bytes_to_transferred() == 0 )
		//	return close();

		//for( size_t i = 0; i < 10; i ++ )
		//{
		//	(( iovec* )result.data())[i].len = MEMSEG;
		//}

		//if( ! result.transport().read( *this, result.data(), 10, 0 ) )
		//	close();
	}

	virtual void onTransmit(BOE_Transmit_Result& result )
	{
	}

	const tstring& toString() const
	{
		return toString_;
	}
private:
	tstring toString_;

	BOE_Transport_Ptr connect_;

	char buf[ MAX_SIZE ];

	iopack iobuf[ 10 ];
};

class Accept_Handler : public BOE_Accept_Handler
{
public:

	Accept_Handler()
	{
		toString_ = "Accept";
	}

	virtual void onAccept(BOE_Accept_Result& result)
	{
		BOE_Transport_Ptr channel = result.new_channel();
		
		Service_Handler* peer_handler = new Service_Handler;
		peer_handler->open( channel );

		result.acceptor().accept( *this, 0 ) ;
	}

	const tstring& toString() const
	{
		return toString_;
	}
private:
	tstring toString_;
};


#endif // _BT_Service_Handler_