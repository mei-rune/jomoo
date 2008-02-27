

#ifndef _Config_Proxy_H
#define _Config_Proxy_H


#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include "BOE/os.H"

#ifndef ProxyLoggerPtr
#define ProxyLoggerPtr BOE_Log_Impl*
#endif 

#define _proxy_begin
#define _proxy_end
#define _proxy

#endif // _Config_Proxy_H