#include "StdAfx.h"
#include "Router_Server.h"

_im_begin

Router_Server::Router_Server( _io Instance_IO& instance )
: instance_( instance )
{
	toString_ = BT_TEXT("·�ɷ�����");
	handler_.reset( new Router_Accept_Handler( *this ) );
}

int Router_Server::open( _util PropertiesPtr config )
{
	if( !isNone( acceptor_ ) )
		BT_LOG_ERROR_RETURN( instance_.getLogger(),toString() << BT_TEXT("> ��������ʧ�ܣ��Ѿ���������!") , -1 );
	if( config.get() == 0 )
		BT_LOG_ERROR_RETURN( instance_.getLogger(),toString() << BT_TEXT("> ��������ʧ�ܣ�����Ϊ��!") , -1 );
	tstring addr = config->getPropertyWithDefault( "ServerAddress", "" );
	if( addr.empty() )
		BT_LOG_ERROR_RETURN( instance_.getLogger(), toString() << BT_TEXT("> ��������ʧ�ܣ�û�з�������ַ!") , -1 );
	toString_ = BT_TEXT("·�ɷ�����[");
	toString_ += config->getPropertyWithDefault( "ServerName", addr );
	toString_ += BT_TEXT("]");
	instance_type::endpoint_ptr endpoint = instance_.createEndpoint( addr );
	if( isNone( endpoint ) )
		BT_LOG_ERROR_RETURN( instance_.getLogger(), toString() << 
		BT_TEXT("��������ʧ�ܣ�����ͨ�Ŷ˽ڵ�ʧ��!") , -1 );
	acceptor_ = endpoint->acceptor();
	if( isNone( acceptor_ ) )
		BT_LOG_ERROR_RETURN( instance_.getLogger(), toString() << 
		BT_TEXT("��������ʧ�ܣ�����������ʧ��!") , -1 );
	return acceptor_->accept( *handler_ , 0 );
}

void Router_Server::close( )
{
	if( isNone( acceptor_ ) )
		BT_LOG_ERROR( instance_.getLogger(), toString() << 
		BT_TEXT("ֹͣ����ʧ�ܣ�������Ϊ��!") );
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