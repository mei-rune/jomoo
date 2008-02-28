#ifndef CONFIG_PLUGIN_MANAGAER_H
# define CONFIG_PLUGIN_MANAGAER_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

#include "Hazel.Base/Logger.H"

#define _seal_begin namespace SEAL{
#define _seal_end } // SEAL

#define _seal SEAL::

#define PluginManagerLoggerPtr Hazel_Log_Impl*

#define Hazel_PLUGIN_MANAGER_VERSION "0.7.1"

#endif // CONFIG_PLUGIN_MANAGAER_H
