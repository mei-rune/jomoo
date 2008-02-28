
# ifndef SEAL_KERNEL_COMPONENT_FACTORY_H
# define SEAL_KERNEL_COMPONENT_FACTORY_H

# include "config.h"

# if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
# endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_MicroKernel.h"
# include "Hazel.PlugInManager/PluginFactory.h"
# include "Hazel.Base/Singleton.H"
# include "IComponent.H"

_micro_kernel_begin

class ComponentFactory : public _seal PluginFactory< IComponent* ( IKernel& ) >
{
public:
	typedef _seal PluginFactory< IComponent* ( IKernel& ) > base_type;
    static ComponentFactory& get (void);
private:
	friend class _hazel Hazel_Singleton< ComponentFactory , Threading::MUTEX >;
	ComponentFactory();
};

_micro_kernel_end

# endif // SEAL_KERNEL_COMPONENT_FACTORY_H
