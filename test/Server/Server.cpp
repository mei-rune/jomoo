// Server.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../BT_Server_Handler.H"
int _tmain(int argc, _TCHAR* argv[])
{

	if( BOE_Init_BOE::init() != 0 )
		return -1;

	factory = BOE_Channel_Registry::get()->getChannelImplementation( "tcp" );
	if( factory == 0 )
	{
		std::cout << "取得tcp通道工厂失败，请确认它是否存在" << std::endl;
		BOE_Init_BOE::fini();
		return -1;
	}
	{
		BOE_Channel_Factory* f = BOE_Channel_Registry::get()->getChannelImplementation( "jabber" );
		if( f == 0 )
		{
			std::cout << "取得jabber通道工厂失败，请确认它是否存在" << std::endl;
			BOE_Init_BOE::fini();
			return -1;
		}
		std::auto_ptr< BOE_Channel > new_channel( f->createChannel( "jabber" ) );
	}
	{
		std::auto_ptr< BOE_Channel > new_channel( factory->createChannel( "accept" ) );
	}


	std::auto_ptr< BOE_Channel > accept_channel( factory->createChannel( "accept" ));
	if( accept_channel.get() == 0 )
	{
		std::cout << "生成接收通道实例失败" << std::endl;
		BOE_Init_BOE::fini();
		return -1;
	}

	if( accept_channel->setOption( "server_address", "0.0.0.0:5222", strlen( "0.0.0.0:5222" ) ) != 0 )
	{
		std::cout << "设置接收通道服务地址失败" << std::endl;
		
		BOE_Init_BOE::fini();
		return -1;
	}

	BT_Handler handle;

	std::auto_ptr< BOE_Channel > new_channel( factory->createChannel( "channel"));
	if( new_channel.get() == 0 )
	{
		std::cout << "生成通信通道实例失败" << std::endl;
		BOE_Init_BOE::fini();
		return -1;
	}

	
	if( accept_channel->accept( handle, *new_channel ) != 0 )
	{
		std::cout << "启动接收通道失败" << get_last_error() << std::endl;
		BOE_Init_BOE::fini();
		return -1;
	}
	channels.insert( accept_channel.get() );
	channels.insert( new_channel.get() );

	//new_channel = factory->createChannel( "channel2");
	//if( new_channel == 0 )
	//{
	//	std::cout << "生成通信通道实例失败" << std::endl;
	//	BOE_Init_BOE::fini();
	//	return -1;
	//}

	//channels.insert( new_channel );
	//if( accept_channel->accept( handle, *new_channel ) != 0 )
	//{
	//	std::cout << "启动接收通道失败" << get_last_error() << std::endl;
	//	BOE_Init_BOE::fini();
	//	return -1;
	//}

	while( true )
		BOE_WINSOCK_Operation_Proactor::get()->handle_events( 1000 );

	BOE_Init_BOE::fini();
	
	channels.erase( accept_channel.get() );
	channels.erase( new_channel.get() );

	return 0;
}

