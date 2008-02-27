
#ifndef SEAL_KERNEL_ICOMPONENT_LOADER_H
# define SEAL_KERNEL_ICOMPONENT_LOADER_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
#include "config_MicroKernel.h"
#include "IKernel.h"
#include "Hazel.Base/Exception.hpp"

_micro_kernel_begin

class IComponentLoader : public IComponent
{
    DECLARE_SEAL_COMPONENT( IComponentLoader, "SEAL/Kernel/Component/ComponentLoader" );
public:
	virtual ~IComponentLoader( ){}

	/**
	 * 载入指定的组件到指定的容器
	 * @param[ in ] into 组件容器
	 * @param[ in ] componentKey 组件的名称
	 * @param[ in ] key 组件的key
	 * @return 成功载入组件返回true， 否则返回false
	 */
    virtual bool load ( IKernel& into, const tstring &componentKey, int key = 0 ) = 0;

	/**
	 * 载入指定类别下所有的组件到指定的容器
	 * @param[ in ] into 组件容器
	 * @param[ in ] componentKey 组件的类别
	 * @return 成功载入组件返回true， 否则返回false
	 */
	virtual bool loadAll (IKernel& into, const tstring &componentKey ) = 0;

	/**
	 * 载入指定的组件到本组件所在的容器
	 * @param[ in ] componentKey 组件的类别
	 * @param[ in ] key 组件的key
	 * @return 成功载入组件返回true， 否则返回false
	 */
	virtual bool load ( const tstring &componentKey, int key ) = 0;

	/**
	 * 载入指定类别下所有的组件到本组件所在的容器
	 * @param[ in ] componentKey 组件的类别
	 * @return 成功载入组件返回true， 否则返回false
	 */
	virtual bool loadAll ( const tstring &componentKey ) = 0;
};

_micro_kernel_end

#endif // SEAL_KERNEL_ICOMPONENT_LOADER_H