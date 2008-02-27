#include "StdAfx.h"
#include "MessageServer.h"


_im_begin

MessageServer::MessageServer( _io Instance_IO& instance )
: instance_( instance )
{
	toString_ = "MessageServer";
}

int MessageServer::open( _util PropertiesPtr config )
{
		if( !isNone( acceptor_ ) )
			BT_LOG_ERROR_RETURN( getLogger(), toString() << "> 已经启动了" , -1 );

		toString_ = config->getProperty( "ServerName" );
		if( toString_.empty() )
			toString_ = "MessageServer";

		ServerAddr_ = config->getProperty( "ServerAddress" );
		if( ServerAddr_.empty() )
			BT_LOG_ERROR_RETURN( getLogger(), toString() << "> 配置不正确，没有服务器地址。" , -1);

		acceptor_ = instance_.createAcceptor( ServerAddr_ );
		if( isNone( acceptor_ ) )
			BT_LOG_ERROR_RETURN( getLogger(), toString() 
			<< BT_TEXT("> 创建接受器") 
			<< ServerAddr_ 
			<< BT_TEXT("失败。" ), -1);
		
        if( acceptor_->open( ) != 0 )
			BT_LOG_ERROR_RETURN( getLogger(), toString() 
			<< BT_TEXT("> 接受连接失败。" ), -1);

		instance_.setConcurrencyBridge( concurrency_ );

		return 0;
}

void MessageServer::close( )
{
	if( isNone( acceptor_ ) )
			BT_LOG_ERROR_RETURN( getLogger(), toString() << "> 没有启动" , -1 );
	acceptor_->close();
	return instance_.close();
}

MessageServer::LoggerPtr MessageServer::getLogger()
{
	return instance_.getLogger();
}

const tstring& MessageServer::toString() const
{
	return toString_;
}

_im_end