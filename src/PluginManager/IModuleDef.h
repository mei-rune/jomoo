#ifndef PLUGIN_MANAGER_MODULE_DEF_BASE_H
# define PLUGIN_MANAGER_MODULE_DEF_BASE_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_PluginManager.h"
# include "IModule.h"

_seal_begin

class IModuleDef
{
public:
	virtual ~IModuleDef (void) {};

    virtual void	query (void) = 0;
    virtual void	attach (void) = 0;
    virtual void	detach (void) = 0;

    virtual void		bind ( IModule& module ) = 0;
	virtual    void		unbind ( IModule& module ) = 0;
    virtual IModule*		module (void) = 0;
};

_seal_end

#endif // PLUGIN_MANAGER_MODULE_DEF_BASE_H
