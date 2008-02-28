#ifndef IHANDLER_H
# define IHANDLER_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_MicroKernel.h"
# include "IComponent.h"

_micro_kernel_begin

class IHandler
{
public:
	typedef IComponent::key_type key_type;

	virtual ~IHandler(){}
	virtual ComponentPtr Resolve() = 0;
	virtual ComponentConstPtr Resolve() const = 0;
	virtual void Release( ComponentPtr ) = 0;

	///**
	// * 注意它只是含有对IComponentModel的引用而已，它自已被IComponentModel管理
	// */
	//virtual IComponentModel& model() = 0;
};

_micro_kernel_end

#endif // IHANDLER_H
