#include "StdAfx.h"
#include "Router_Server.h"

_im_begin

Router_Server::Router_Server( _io Instance_IO& instance )
: instance_( instance )
{
	toString_ = BT_TEXT("路由服务器");
	handler_.reset( new Router_Accept_Handler( *this ) );
}

int Router_Server::open( _util PropertiesPtr config )
{
	if( !isNone( acceptor_ ) )
		BT_LOG_ERROR_RETURN( instance_.getLogger(),toString() << BT_TEXT("> 启动服务失败，已经启动过了!") , -1 );
	if( config.get() == 0 )
		BT_LOG_ERROR_RETURN( instance_.getLogger(),toString() << BT_TEXT("> 启动服务失败，配置为空!") , -1 );
	tstring addr = config->getPropertyWithDefault( "ServerAddress", "" );
	if( addr.empty() )
		BT_LOG_ERROR_RETURN( instance_.getLogger(), toString() << BT_TEXT("> 启动服务失败，没有服务器地址!") , -1 );
	toString_ = BT_TEXT("路由服务器[");
	toString_ += config->getPropertyWithDefault( "ServerName", addr );
	toString_ += BT_TEXT("]");
	instance_type::endpoint_ptr endpoint = instance_.createEndpoint( addr );
	if( isNone( endpoint ) )
		BT_LOG_ERROR_RETURN( instance_.getLogger(), toString() << 
		BT_TEXT("启动服务失败，创建通信端节点失败!") , -1 );
	acceptor_ = endpoint->acceptor();
	if( isNone( acceptor_ ) )
		BT_LOG_ERROR_RETURN( instance_.getLogger(), toString() << 
		BT_TEXT("启动服务失败，创建监听器失败!") , -1 );
	return acceptor_->accept( *handler_ , 0 );
}

void Router_Server::close( )
{
	if( isNone( acceptor_ ) )
		BT_LOG_ERROR( instance_.getLogger(), toString() << 
		BT_TEXT("停止服务失败，监听器为空!") );
	acceptor_->cancel( );
}

ConnectionManager< Router_Handler >& Router_Server::manager()
{
	return manager_;
}

Router_Server::instance_type::acceptor_ptr Router_Server::acceptor()
{
	return acceptor_;
}

const tstring& Router_Server::toString() const
{
	return toString_;
}


Router_Handler_Ptr Router_Server::createHandler( )
{
	return Router_Handler_Ptr( new Router_Handler( *this ) );
}

_im_end

BOE_Export_C _io BOE_Server* MODUE_POINT( _io Instance_IO& instance )
{
	return new Router_Server( instance );
}