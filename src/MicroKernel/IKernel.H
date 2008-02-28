
#ifndef _IKernel_H_
#define _IKernel_H_

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
#include "config_MicroKernel.h"
#include "INamingSubSystem.H"
#include "IComponentModel.H"
#include "IComponentContext.H"

/**
 */
_micro_kernel_begin

class IKernel : public IComponentContext
{
public:

	virtual ~IKernel(){}

	/**
	 * 取得容器
	 */
	virtual INamingSubSystem& NamingSubSystem() = 0;
	virtual const INamingSubSystem& NamingSubSystem() const = 0;

	/**
	 * 取得组件模型工厂
	 */
	virtual IComponentModelFactory& ComponentModelFactory() = 0;

	/**
	 * 取得组件句柄工厂
	 */
	virtual IHandlerFactory& HandlerFactory() = 0;
};

_micro_kernel_end

#endif // _IKernel_H_