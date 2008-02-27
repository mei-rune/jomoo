

#ifndef _Config_IM_H
#define _Config_IM_H


#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include "BOE/Logger.H"

#define _im_begin
#define _im_end
#define _im

#ifndef IMLoggerPtr
#define IMLoggerPtr BOE_Log_Impl*
#endif 


_im_begin

_im_end

#endif // _Config_Networks_H