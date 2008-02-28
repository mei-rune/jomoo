#ifndef PLUGIN_MANAGER_MODULE_CACHE_BASE_H
# define PLUGIN_MANAGER_MODULE_CACHE_BASE_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_PluginManager.h"
# include "IModuleReg.H"

_seal_begin

const char ModuleCacheTag[] = "cache";

class IModuleCache
{
public:
	typedef counter_ptr< IModuleCache > ptr_type;
	typedef IPluginManager::LoggerPtr LoggerPtr;

	IModuleCache(){}
	virtual ~IModuleCache() {}
	virtual const tstring& directory (void) const = 0;

	virtual void feelbackDirectory( ) = 0;

	virtual void walk( PluginInfoWalker& walker ) = 0;
	virtual void add( IModuleRegPtr ) = 0;
	virtual void remove( IModuleRegPtr ) = 0;
    virtual ModuleDescriptorPtr	cache ( IModuleDescriptorBuilder& ) const = 0;
	virtual IPluginManager& manager() = 0;
	virtual const tstring& toString( ) const = 0;

private:
	DECLARE_NO_COPY_CLASS( IModuleCache );
};

typedef IModuleCache::ptr_type IModuleCachePtr;

_seal_end

#endif // PLUGIN_MANAGER_MODULE_CACHE_BASE_H
