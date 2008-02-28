#ifndef DefaultComponentModel_H
# define DefaultComponentModel_H

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

// Include files
# include "config_MicroKernel.h"
# include "IKernel.h"
# include "IComponentModel.h"
# include "BOE.Base/Builder.h"
# include "BOE.Base/util/Configuration.h"

_micro_kernel_begin

class DefaultComponentModel : public IComponentModel
{
public:
	DefaultComponentModel( );
	virtual ~DefaultComponentModel();
	virtual IKernel& kernel();
	virtual _util ConfigurationSettings& conf();

	void init( IKernel& kernel , _util ConfigurationSettings& conf );
	void fini( );

private:
	
	DECLARE_NO_COPY_CLASS( DefaultComponentModel );

	IKernel* kernel_;
	_util ConfigurationSettings* conf_;
};

//class ComponentModelOP
//{
//public:
//	static void init( DefaultComponentModel* model,IKernel& kernel , _util ConfigurationSettings& conf )
//	{
//		model->InitComponentModel( kernel, conf );
//	}
//	static void fini( DefaultComponentModel* model )
//	{
//		model->FiniComponentModel();
//	}
//};

class DefaultComponentModelBuilder : public _boe Builder< IComponentModel, DefaultComponentModel, IComponentModelBuilder >
{
public :
	typedef _boe Builder< IComponentModel, DefaultComponentModel, IComponentModelBuilder > base_type;
	typedef base_type::pool_type pool_type;
	DefaultComponentModelBuilder( IKernel& kernel , pool_type::pool_ptr_type _pool );
	virtual ~DefaultComponentModelBuilder();
private:
	
	DECLARE_NO_COPY_CLASS( DefaultComponentModelBuilder );

	IKernel& kernel_;
};

_micro_kernel_end

#endif // DefaultComponentModel_H
