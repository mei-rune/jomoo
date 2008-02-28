
#ifndef MODULE_BASE_H
#define MODULE_BASE_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_PluginManager.h"
# include "PluginInfoBase.h"

_seal_begin

const char ModuleTag[] = "module";

class IModule
{
public:

	typedef counter_ptr< IModule > ptr_type;
	typedef IPluginManager::LoggerPtr LoggerPtr;

	IModule(){}
	virtual ~IModule(void){};


	//// PlugInfo接口
	//virtual void	attachInfo( PluginInfoBase* ) = 0;
	//virtual void	detachInfo( PluginInfoBase* ) = 0;

	/// 用户接口
	virtual const tstring&	libraryName (void) const = 0;

	//virtual void	load (void) = 0;
	//virtual void	unload (void) = 0;
	//virtual bool	loaded (void) = 0;

	virtual void	attach (void) = 0;
    virtual void	detach (void) = 0;
    virtual void	query (void) = 0;
	//virtual bool	attached (void) = 0;

	virtual void	walk( PluginInfoWalker& walker ) = 0;
    virtual void	add ( ModuleDescriptorPtr info ) = 0;
    virtual void	remove ( ModuleDescriptorPtr info ) = 0;
    virtual ModuleDescriptorPtr	cache ( IModuleDescriptorBuilder& ) const = 0;
	virtual IPluginManager& manager() = 0;
	virtual const	tstring& toString( ) const = 0;
private:
	DECLARE_NO_COPY_CLASS( IModule );
};

typedef IModule::ptr_type IModulePtr;

_seal_end

#endif // MODULE_BASE_H
