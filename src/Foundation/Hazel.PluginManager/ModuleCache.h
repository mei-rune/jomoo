#ifndef PLUGIN_MANAGER_MODULE_CACHE_H
# define PLUGIN_MANAGER_MODULE_CACHE_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_PluginManager.h"
# include "IModuleCache.H"
# include "PluginInfoDOM.H"

_seal_begin

class ModuleCache : public IModuleCache
{
public:

	ModuleCache( PluginInfoDOM& dom , const tstring& directory );

	const tstring& directory (void) const;

	void feelbackDirectory( );

	void walk( PluginInfoWalker& walker );

	void add( IModuleRegPtr );
	void remove( IModuleRegPtr );
    ModuleDescriptorPtr	cache ( IModuleDescriptorBuilder& ) const ;
	IPluginManager& manager() ;
	const	tstring& toString( ) const ;

	LoggerPtr getLogger()
	{
		return manager().getLogger();
	}

private:
	PluginInfoDOM& dom_;
    IPluginManager&	manager_;
	tstring toString_;

	typedef std::list< IModuleRegPtr >::const_iterator const_iterator;
	typedef std::list< IModuleRegPtr >::iterator iterator;
	std::list< IModuleRegPtr > reg_;
	tstring directory_;

	static const char	s_cacheFile [];
};

typedef ModuleCache::ptr_type IModuleCachePtr;

_seal_end

#endif // PLUGIN_MANAGER_MODULE_CACHE_H
