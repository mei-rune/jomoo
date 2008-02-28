
#ifndef _BT_Handler_
#define _BT_Handler_

#include <iostream>
#include <set>
#include "communication/BOE_TCP_Channel.H"
#include "communication/BOE_Channel_Registry.H"
#include "communication/BOE_WINSOCK_Operation_Proactor.H"
#include "communication/BOE_Channel_Handler.H"
#include "framework/BOE_Init_BOE.H"
#include "util/get_last_error.h"

std::set< BOE_Channel* > channels;
BOE_Channel_Factory* factory = 0 ;

char  sbuf[] = "1234567890";

char ssbuf[65535] = "";


bool stop_ = false;

class BT_Handler : public BOE_Channel_Handler
{
public:

	BT_Handler( const char* buf , size_t len )
		: m_buf_( buf )
		, m_buf_len_( len )
		, m_cout_( 1 )
	{
	}
	/**
	 * channel读操作回调接口
	 * @see BOE_Channel_Read_Result
	 * @see BOE_Channel::read
	 */
	virtual void handle_read(BOE_Channel_Read_Result& result)
	{
		char* buf = ( char* )result.buffer();
		if( result.success() && result.bytes_to_transferred() > 0 )
		{
			buf[ result.bytes_to_transferred() ] = 0;
			std::cout << "server: " << buf << std::endl;

			m_cout_ ++;
			if( m_cout_ < 65535 )
			{
				ssbuf[ m_cout_ -1 ] = sbuf[ m_cout_ % 10 ];

				if( result.channel().write( *this, ssbuf,m_cout_ ) != 0 )
				{
					channels.erase( &(result.channel()) );
					BOE_Channel* ch = &(result.channel());
					delete ch;
					stop_ = true;
				}
			}
			else
			{
								channels.erase( &(result.channel()) );
				BOE_Channel* ch = &(result.channel());
				delete ch;
				stop_ = true;
			}
		}
		else
		{
			BT_LOG_INFO( result.channel().getLog(), BT_TEXT("读失败,[")<< 
			get_last_error() << BT_TEXT("]") );
			channels.erase( &(result.channel()) );
			BOE_Channel* ch = &(result.channel());
			delete ch;
			stop_ = true;
		}
		delete[] buf;
	}

	/**
	 * channel读操作回调接口
	 * @see BOE_Channel_Read_Array_Result
	 * @see BOE_Channel::read
	 */
	virtual void handle_read_array(BOE_Channel_Read_Array_Result& result )
	{
	}

	/**
	 * channel写操作回调接口
	 * @see BOE_Channel_Write_Result
	 * @see BOE_Channel::write
	 */
	virtual void handle_write(BOE_Channel_Write_Result& result)
	{
		
		if( result.success() && result.bytes_to_transferred() > 0 )
		{
			char* buf = new char[ 65545 ];
			if( result.channel().read( *this, buf, 65545 ) != 0 )
			{
				delete[] buf;
				channels.erase( &(result.channel()) );
				BOE_Channel* ch = &(result.channel());
				delete ch;
				stop_ = true;
			}
		}
		else
		{
			BT_LOG_INFO( result.channel().getLog(), BT_TEXT("写失败,[")<< 
			get_last_error() << BT_TEXT("]") );
			channels.erase( &(result.channel()) );
			BOE_Channel* ch = &(result.channel());
			delete ch;
			stop_ = true;
		}
	}

	/**
	 * channel写操作回调接口
	 * @see BOE_Channel_Transmit_Result
	 * @see BOE_Channel::transmit
	 */
	virtual void handle_transmit(BOE_Channel_Transmit_Result& result )
	{
	}

	/**
	 * channel建立连接操作回调接口
	 * @see BOE_Channel_Connect_Result
	 * @see BOE_Channel::connect
	 */
	virtual void handle_connect(BOE_Channel_Connect_Result& result )
	{
		if( result.success() )
		{
			ssbuf[ m_cout_ -1 ] = sbuf[ m_cout_ % 10 ];

			if( result.channel().write( *this, ssbuf,m_cout_ ) != 0 )
			//if( result.channel().write( *this, m_buf_,m_buf_len_ ) != 0 )
			{
				channels.erase( &(result.channel()) );
				BOE_Channel* ch = &(result.channel());
				delete ch;
				stop_ = true;
			}
		}
		else
		{
			BT_LOG_INFO( result.channel().getLog(), BT_TEXT("连接失败,[")<< 
			get_last_error() << BT_TEXT("]") );
			channels.erase( &(result.channel()) );
			BOE_Channel* ch = &(result.channel());
			delete ch;
			stop_ = true;
		}
	}

	/**
	 * channel连接轮询操作回调接口
	 * @see BOE_Channel_Accept_Result
	 * @see BOE_Channel::accept
	 */
	virtual void handle_accept(BOE_Channel_Accept_Result& result)
	{

		if( result.success() )
		{
			BOE_Channel& channel = result.new_channel();

			char* buffer = new char[ 1024 ];
			if( channel.read( *this, buffer, 1024 ) != 0 )
			{
				delete [] buffer;
				channels.erase( &(result.new_channel()));
				std::cout << "启动读失败!" << std::endl;
				BOE_Channel* ch = &(result.new_channel());
				delete ch;
			}
			else
			{
				
			}
		}
		else
		{
			channels.erase( &(result.new_channel()));
			BOE_Channel* ch = &(result.new_channel());
			delete ch;
		}

		BOE_Channel* new_channel = factory->createChannel( "channel1" );
		if( new_channel == 0 )
		{
			std::cout << "生成通信通道实例失败" << std::endl;
			return ;
		}
		if( result.channel().accept( *this, *new_channel ) != 0 )
		{
			std::cout << "启动接收通道失败" << std::endl;
			delete new_channel;
			BOE_Channel* ch = &(result.channel());
			delete ch;
		}
		else
		{
			channels.insert( new_channel );
		}
	}
private:

		const char* m_buf_;
		size_t m_buf_len_;
		size_t m_cout_ ;
};


#endif // _BT_Handler_