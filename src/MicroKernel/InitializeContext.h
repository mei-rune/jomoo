// Hazel


#ifndef __Seal_InitializeContext_H__
#define __Seal_InitializeContext_H__

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_MicroKernel.h"
# include "IKernel.H"
# include "DebugAids.H"

_micro_kernel_begin

class InitializeContext
{
public:
	virtual ~InitializeContext(){}
	virtual IHandler& handler() = 0;
	virtual IKernel& kernel() = 0;
	virtual IComponentModel& component_model() = 0;
	virtual const tstring& toString() const = 0;
};

_micro_kernel_end

#endif // __Seal_InitializeContext_H__
