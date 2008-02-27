#include "StdAfx.h"
#include "Message_Transport_Handler.H"
#include "Message_Transport_State.H"

#ifdef _MEMORY_DEBUG
#undef THIS_FILE
#define new	   DEBUG_NEW  
#define malloc DEBUG_MALLOC  
static char THIS_FILE[] = __FILE__;  
#endif // _MEMORY_DEBUG

_im_begin

DEFINE_SHARED( Message_Transport_Handler );

Message_Transport_Handler::Message_Transport_Handler( 
	  Instance_IM& instance 
	, im_transport_ptr transport
	, stateTable* pJumpTable
	, bool delete_table )
: instance_( instance )
, state_( Transport_Read_State::get() )
, Messaging_( instance.createMessaging() )
, transport_( transport )
, counter_( 0 )
, pJumpTable_( pJumpTable )
{
	toString_ = BT_TEXT("消息处理器");
	if( isNone( transport_ ) )
		BT_LOG_ERROR_THROW( getLogger(), 
		toString() << BT_TEXT( "> 传输器不能为空") 
		, InvalidPointerException );

	toString_ += BT_TEXT("[");
	toString_ += transport_->toString();
	toString_ += BT_TEXT( "]" );

	if( isNone( Messaging_ ) )
		BT_LOG_ERROR_THROW( getLogger(), 
		toString() << BT_TEXT( "> 消息分析器不能为空") 
		, InvalidPointerException );

	if( delete_table )
		selfTable_.reset( pJumpTable );
	if( pJumpTable_ == 0 )
	{
		selfTable_.reset( new stateTable );
		pJumpTable_ = selfTable_.get();
	}
}

int Message_Transport_Handler::open( )
{
	if( getMessaging().open() != 0 )
		BT_LOG_ERROR_RETURN( getLogger(), 
		toString() << BT_TEXT( "> 初始化消息分析器失败")
		, -1 );
	return instance_.getConcurrencyBridge().putq( BOE_Protocol_Handler_Ptr( this ) );
}

void Message_Transport_Handler::close( )
{
	getMessaging().close();
	getTransport().cancel();
}

bool Message_Transport_Handler::isStop()
{
	return instance_.isStop();
}

void Message_Transport_Handler::finalize()
{
	getMessaging().finalize();
}

int Message_Transport_Handler::service()
{
	if( state_ == 0 )
		BT_LOG_ERROR_RETURN( getLogger(), toString() << BT_TEXT("> 状态为null") , -1 );
	int r = state_->service( this );
	if( r != 0 )
		state_ = 0;
	return r;
}

void Message_Transport_Handler::onRead( im_transport_handler_type::read_result_type& result)
{
	if( state_ == 0 )
		ThrowException1( InvalidPointerException , "，state_为null" );

	state_ = state_->transition( this, result , 0 );
	if( state_ == 0 )
	{
		BT_LOG_TRACE( getLogger(), toString() << BT_TEXT("> 写数据状态结束!")  );
	}
	instance_.getConcurrencyBridge().putq( BOE_Protocol_Handler_Ptr( this ) );
}

void Message_Transport_Handler::onReadArray(im_transport_handler_type::read_array_result_type& result )
{
	if( state_ == 0 )
		ThrowException1( InvalidPointerException , "，state_为null" );
	state_ = state_->transition( this, result , 0 );
	if( state_ == 0 )
	{
		BT_LOG_TRACE( getLogger(), toString() << BT_TEXT("> 写数据状态结束!")  );
	}
	instance_.getConcurrencyBridge().putq( BOE_Protocol_Handler_Ptr( this ) );

}

void Message_Transport_Handler::onWrite(  im_transport_handler_type::write_result_type& result)
{
	if( state_ == 0 )
		ThrowException1( InvalidPointerException , "，state_为null" );
	state_ = state_->transition( this, result , 0 );
		if( state_ == 0 )
	{
		BT_LOG_TRACE( getLogger(), toString() << BT_TEXT("> 写数据状态结束!")  );
	}
	instance_.getConcurrencyBridge().putq( BOE_Protocol_Handler_Ptr( this ) );
}

void Message_Transport_Handler::onWriteArray(  im_transport_handler_type::write_array_result_type& result)
{
	if( state_ == 0 )
		ThrowException1( InvalidPointerException , "，state_为null" );
	state_ = state_->transition( this, result , 0 );
		if( state_ == 0 )
	{
		BT_LOG_TRACE( getLogger(), toString() << BT_TEXT("> 写数据状态结束!")  );
	}
	instance_.getConcurrencyBridge().putq( BOE_Protocol_Handler_Ptr( this ) );
}

void Message_Transport_Handler::onTransmit(  im_transport_handler_type::transmit_result_type& result )
{
	if( state_ == 0 )
		ThrowException1( InvalidPointerException , "，state_为null" );
	state_ = state_->transition( this, result , 0 );
		if( state_ == 0 )
	{
		BT_LOG_TRACE( getLogger(), toString() << BT_TEXT("> 写数据状态结束!")  );
	}
	instance_.getConcurrencyBridge().putq( BOE_Protocol_Handler_Ptr( this ) );
}

const tstring& Message_Transport_Handler::toString() const
{

	return toString_;
}

Message_Transport_Handler::LoggerPtr Message_Transport_Handler::getLogger()
{
	return instance_.getLogger();
}

BOE_Pluggable_Messaging& Message_Transport_Handler::getMessaging()
{
	return (*Messaging_);
}

im_transport_type& Message_Transport_Handler::getTransport()
{
	return (*transport_);
}

stateTable& Message_Transport_Handler::getJumpTable()
{
	return *pJumpTable_;
}

void Message_Transport_Handler::nextState( Transport_Protocol_State* next )
{
	state_ = next;
}

_im_end