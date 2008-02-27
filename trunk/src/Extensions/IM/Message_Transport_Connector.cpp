#include "StdAfx.h"
#include "Message_Transport_Connector.h"

_im_begin

Message_Transport_Connector::Message_Transport_Connector( Instance_IM& instance , const tstring& addr )
: instance_( instance )
, addr_( addr )
{
	toString_ = "ͨ��������[";
	toString_ += addr;
	toString_ += "]";
}

Message_Transport_Connector::~Message_Transport_Connector(void)
{
}

int Message_Transport_Connector::open(  )
{
	BOE_Endpoint_Ptr endpoint = instance_.getIOInstance().create( addr_ );
	if( isNone( endpoint ) )
		BT_LOG_ERROR_RETURN( instance_.getLogger(), toString() << BT_TEXT("> �����˽ڵ�ʧ��") , -1 );
	connector_ = endpoint->connector();
	if( isNone( connector_ ) )
		BT_LOG_ERROR_RETURN( instance_.getLogger(), toString() << BT_TEXT("> ����������ʧ��") , -1 );
	if( connector_->connect( *this ,0 ) != 0 )
		BT_LOG_ERROR_RETURN( instance_.getLogger(), toString() << BT_TEXT("> ��������������ʧ��") , -1 );

	return 0;
}


void Message_Transport_Connector::onConnect(BOE_Connect_Result& result)
{
	Message_Transport_Handler_Ptr ptr = instance_.createConnection( result.new_channel(), 0 );
	if( isNone( ptr ) )
		return ;
	ptr->open( );
	if( connector_->connect( *this ,0) != 0 )
		BT_LOG_ERROR( instance_.getLogger(), toString() << BT_TEXT("> ������������ʧ��") );
}

void Message_Transport_Connector::close( )
{
	if( isNone( connector_ ) )
	{
		BT_LOG_ERROR( instance_.getLogger(),
		toString() << BT_TEXT( "> ȡ������ʧ�ܣ�û��������") );
		return ;
	}
	connector_->cancel();
}

const tstring& Message_Transport_Connector::toString() const
{
	return toString_;
}
_im_end