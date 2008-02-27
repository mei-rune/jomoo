#ifndef PLUGIN_MANAGER_CACHE_PARSE_H
# define PLUGIN_MANAGER_CACHE_PARSE_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
#include "config_PluginManager.h"
#include "ModuleDescriptor.h"
#include "PluginInfoDOM.H"

_seal_begin

class PluginDomConstructor
{
public:
	PluginDomConstructor( PluginInfoDOM& dom );
	~PluginDomConstructor( );
	void constructRoot(ModuleDescriptorPtr info);
	void constructCache(ModuleDescriptorPtr info);
	void constructReg(ModuleDescriptorPtr info, IModuleCache& cache );
	void constructModule (ModuleDescriptorPtr info,IModuleReg& reg );
	void constructPlugin (ModuleDescriptorPtr info,IModule& reg );
	void construct (ModuleDescriptorPtr info);
private:
	PluginInfoDOM& dom_;
};

_seal_end

#endif // PLUGIN_MANAGER_MODULE_CACHE_H
