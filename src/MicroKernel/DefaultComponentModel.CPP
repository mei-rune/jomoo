

// Include files
#include "DefaultComponentModel.h"

_micro_kernel_begin

DefaultComponentModel::DefaultComponentModel(  )
: kernel_( 0 )
, conf_( 0 )
{
}

DefaultComponentModel::~DefaultComponentModel()
{
}

IKernel& DefaultComponentModel::kernel()
{
	if( NULL == kernel_ )
		ThrowException1( NullException , BT_TEXT("kernel_") );
	return (*kernel_);
}

_util ConfigurationSettings& DefaultComponentModel::conf( )
{
	if( NULL == conf_)
		ThrowException1( NullException , BT_TEXT("conf_") );
	return *conf_;
}

void DefaultComponentModel::init( IKernel& kernel, _util ConfigurationSettings& conf )
{
	kernel_ = &kernel;
	conf_ = &conf;
}

void DefaultComponentModel::fini( )
{
	conf_ = 0;
	kernel_ = 0;
}

DefaultComponentModelBuilder::DefaultComponentModelBuilder( IKernel& kernel , pool_type::pool_ptr_type _pool )
: base_type( _pool , BT_TEXT("DefaultComponentModelBuilder") )
, kernel_( kernel )
{
}

DefaultComponentModelBuilder:: ~DefaultComponentModelBuilder()
{
}
_micro_kernel_end
