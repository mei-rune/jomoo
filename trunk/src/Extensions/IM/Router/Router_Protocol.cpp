#include "StdAfx.h"
#include "Router_Protocol.h"

_im_begin

Router_Session::Router_Session( Router_Server& server )
: server_( server )
, running_( false )
{
	toString_ = BT_TEXT("��·�ɴ�����");
}



Router_Handler::LoggerPtr Router_Session::getLogger()
{
	return server_.getLogger();
}

const tstring& Router_Session::toString() const
{
	return toString_;
}

void Router_Accept_Handler::onAccept( Msg_Accept_Result& result )
{
	if( ! result.success() )
		return ;

	Router_Handler_Ptr handler = server_.createHandler( );
	if( isNone( handler ) )
		BT_LOG_ERROR( server_.getLogger(), toString() << BT_TEXT( "> ����ͨ����ʧ��") );
	BOE_INET_Addr addr;
	handler->getOption( "remoteaddr" , addr.get_addr() ,addr.get_size() );
	if( handler->open( addr.toString(),result.connection() ) != 0 )
		BT_LOG_ERROR( server_.getLogger(), toString() << BT_TEXT( "> ��ʼ��ͨ����ʧ��") );

	if( ! result.acceptor().accept( *this, result.act() ) )
		BT_LOG_ERROR( server_.getLogger(), toString() << BT_TEXT( "> ����ʧ��") );
}

_im_end
