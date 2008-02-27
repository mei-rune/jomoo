#ifndef DEFAULT_HANDLER_H
# define DEFAULT_HANDLER_H

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

// Include files
# include "config_MicroKernel.h"
# include "IHandler.h"
# include "IKernel.h"
# include "BOE.Base/Memory/Memory.h"
# include "ReferenceGuard.H"
# include "BOE.Base/Builder.H"

_micro_kernel_begin


class DefaultHandler : public IHandler
{
public:
	DefaultHandler( );
	virtual ~DefaultHandler();
	void init( IComponentModel* );
	void fini( );

	virtual Component* Resolve();
	virtual void Release( Component* );
	virtual IComponentModel& model();
private:

	DECLARE_NO_COPY_CLASS( DefaultHandler );

	IKernel* kernel_;
	ReferenceGuard< IComponentModel , IComponentModelBuilder > model_;
};
//
//class HandlerOP
//{
//public:
//	static void init( DefaultHandler* handler,IComponentModel* model )
//	{
//		handler->init( model );
//	}
//	static void fini( DefaultHandler* handler )
//	{
//		handler->fini();
//	}
//};

class DefaultHandlerBuilder : public _boe Builder< IHandler, DefaultHandler, IHandlerBuilder >
{
public:
	typedef _boe Builder< IHandler, DefaultHandler, IHandlerBuilder > base_type;
	typedef base_type::pool_type pool_type;
	
	DefaultHandlerBuilder( IKernel& kernel , pool_type::pool_ptr_type _pool );
	virtual ~DefaultHandlerBuilder();
    //virtual IHandler * create(IComponentModel*);
	//virtual void release( IHandler * ); 
private:
	
	DECLARE_NO_COPY_CLASS( DefaultHandlerBuilder );

	IKernel& kernel_;
};

_micro_kernel_end

#endif // DEFAULT_HANDLER_H
