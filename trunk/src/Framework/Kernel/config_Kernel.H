

#ifndef ___CONFIG_KERNAL_H___
#define ___CONFIG_KERNAL_H___


#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include "BOE/Logger.H"

#define _kernel_begin
#define _kernel_end
#define _kernel

#ifndef KernelLoggerPtr
#define KernelLoggerPtr BOE_Log_Impl*
#endif 


_kernel_begin

_kernel_end

#endif // ___CONFIG_KERNAL_H___