

// Include files
#include "DefaultHandler.h"

_micro_kernel_begin

DefaultHandler::DefaultHandler( )
: kernel_( 0 )
{
}

DefaultHandler::~DefaultHandler()
{
}

Component* DefaultHandler::Resolve()
{
	return 0;
}

void DefaultHandler::Release( Component* component )
{
}

IComponentModel& DefaultHandler::model()
{
	if( is_null( model_ ) )
		ThrowException1( NullException , BT_TEXT("model_") );
	return (* model_);
}

void DefaultHandler::init( IComponentModel* model )
{
	kernel_ = &(model->kernel());
	model_.reset( model, model->kernel().ComponentModelBuilder() );
}

void DefaultHandler::fini( )
{
	model_.reset( 0 );
}

DefaultHandlerBuilder::DefaultHandlerBuilder( IKernel& kernel , pool_type::pool_ptr_type _pool )
: base_type( _pool , BT_TEXT("DefaultHandlerBuilder") )
, kernel_( kernel )
{
}

DefaultHandlerBuilder:: ~DefaultHandlerBuilder()
{
}

//IHandler * DefaultHandlerBuilder::create( IComponentModel* model )
//{
//	_memory auto_ptr< DefaultHandler, pool_type > h( pool_.malloc() , pool_ );
//	h->InitHandler( model );
//	return h.release();
//}
//
// void DefaultHandlerBuilder::release( IHandler * h )
// {
//	 if( h == 0 )
//		 return ;
//	 _memory auto_ptr< DefaultHandler, pool_type > handler( dynamicCast< DefaultHanlder, IHandler >( h ), pool_  );
//	 if( !is_null( handler ) )
//		handler->FiniHandler();
// }

_micro_kernel_end
