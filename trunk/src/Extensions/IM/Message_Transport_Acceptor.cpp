#include "StdAfx.h"
#include "Message_Transport_Acceptor.h"

_im_begin

Message_Transport_Acceptor::Message_Transport_Acceptor( Instance_IM& instance , const tstring& addr )
: instance_( instance )
, addr_( addr )
{
	toString_ = "ͨ�Ž�����[";
	toString_ += addr;
	toString_ += "]";
}

Message_Transport_Acceptor::~Message_Transport_Acceptor(void)
{
}

int Message_Transport_Acceptor::open(  )
{
	BOE_Endpoint_Ptr endpoint = instance_.getIOInstance().create( addr_ );
	if( isNone( endpoint ) )
		BT_LOG_ERROR_RETURN( instance_.getLogger(), toString() << BT_TEXT("> �����˽ڵ�ʧ��") , -1 );
	acceptor_ = endpoint->acceptor();
	if( isNone( acceptor_ ) )
		BT_LOG_ERROR_RETURN( instance_.getLogger(), toString() << BT_TEXT("> ����������ʧ��") , -1 );

	if( acceptor_->accept( *this , 0 ) != 0 )
		BT_LOG_ERROR_RETURN( instance_.getLogger(), toString() << BT_TEXT("> ������������ʧ��") , -1 );

	return 0;
}

void Message_Transport_Acceptor::close( )
{
	if( isNone( acceptor_ ) )
	{
		BT_LOG_ERROR( instance_.getLogger(),
		toString() << BT_TEXT( "> ȡ������ʧ�ܣ�û�м�����") );
		return ;
	}
	acceptor_->cancel();
}


const tstring& Message_Transport_Acceptor::toString() const
{
	return toString_;
}

void Message_Transport_Acceptor::onAccept(BOE_Accept_Result& result)
{
	Message_Transport_Handler_Ptr ptr = instance_.createConnection( result.new_channel(), 0 );
	if( isNone( ptr ) )
		return ;
	ptr->open( );
	if( acceptor_->accept( *this ,0 ) != 0 )
		BT_LOG_ERROR( instance_.getLogger(), toString() << BT_TEXT("> ������������ʧ��") );
}