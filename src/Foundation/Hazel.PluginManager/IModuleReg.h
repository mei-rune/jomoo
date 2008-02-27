#ifndef PLUGIN_MANAGER_MODULE_REG_BASE_H
# define PLUGIN_MANAGER_MODULE_REG_BASE_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_PluginManager.h"
# include "IModule.H"

_seal_begin

const char ModuleRegTag[] = "file";

/// 每一个IModuleReg对应一个reg文件
class IModuleReg
{
public:
	
	typedef counter_ptr< IModuleReg > ptr_type;
	typedef IPluginManager::LoggerPtr LoggerPtr;
	
	IModuleReg(){}
	virtual ~IModuleReg (void){};

    virtual const tstring&		file ( void ) const = 0;
    virtual bool		bad ( void ) const = 0;
    virtual void		bad ( bool value ) = 0;

	virtual void walk( PluginInfoWalker& walker ) = 0;
	virtual void add( IModulePtr ) = 0;
	virtual void remove( IModulePtr ) = 0;
    virtual ModuleDescriptorPtr	cache ( IModuleDescriptorBuilder& ) const = 0;
	virtual IPluginManager& manager() = 0;
	virtual const tstring& toString( ) const = 0;
private:
	DECLARE_NO_COPY_CLASS( IModuleReg );
};

typedef IModuleReg::ptr_type IModuleRegPtr;

_seal_end

#endif // PLUGIN_MANAGER_MODULE_REG_BASE_H
