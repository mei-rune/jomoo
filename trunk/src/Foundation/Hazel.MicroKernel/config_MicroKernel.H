

#ifndef _Config_Seal_H
#define _Config_Seal_H


#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

# include "Hazel.Base/Logger.H"
# include "Hazel.Base/Exception.HPP"

#define _micro_kernel_begin namespace MicroKernel {
#define _micro_kernel_end }

#define _micro_kernel_xml_begin _micro_kernel_begin namespace xml {
#define _micro_kernel_xml_end _micro_kernel_end }

#define _micro_kernel MicroKernel::
#define _micro_kernel_xml  _micro_kernel xml::

#ifndef SealLoggerPtr
#define SealLoggerPtr _hazel Hazel_Log_Impl*
#endif 


_micro_kernel_begin

_micro_kernel_end

#endif // _Config_Seal_H