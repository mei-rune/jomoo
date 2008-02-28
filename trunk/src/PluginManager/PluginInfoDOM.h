#ifndef PLUGIN_INFO_DOM_H
# define PLUGIN_INFO_DOM_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_PluginManager.h"
# include "IModuleCache.H"
# include "IPluginManager.H"
# include "ModuleDescriptor.H"
# include "IModuleDescriptorBuilder.H"
# include <list>

_seal_begin

const char PluginInfoDOMTag[] = "root";

class PluginInfoDOM //: public PluginNode
{
public:
	PluginInfoDOM( );
	PluginInfoDOM( IPluginManager& manager );
	void initDOM(  ModuleDescriptorPtr descriptor );

	void walk( PluginInfoWalker& walker );
	void add( IModuleCachePtr );
	void remove( IModuleCachePtr );
    ModuleDescriptorPtr cache (  IModuleDescriptorBuilder& Builder ) const;
    static const char *	tag (void);

	IModuleCachePtr createModuleCache( const tstring &directory );
	IModuleRegPtr createModuleReg( const tstring &regfile, bool bad );
	IModuleRegPtr createModuleReg( const tstring &regfile,
	       const tstring &bad );
	IModulePtr createModule(const tstring &libraryName);

	IPluginManager& manager();
	void manager( IPluginManager& );

private:
	IPluginManager* manager_;

	typedef std::list< IModuleCachePtr >::iterator iterator;
	typedef std::list< IModuleCachePtr >::const_iterator const_iterator;

	std::list< IModuleCachePtr > cache_;
};

_seal_end

#endif // PLUGIN_INFO_DOM_H
