

#include "ComponentFactory.h"

_micro_kernel_begin

ComponentFactory::ComponentFactory (void)
  : base_type ( _seal getPluginManager(), BT_TEXT("Loadable Component"), BT_TEXT("1.0") )
{
}

ComponentFactory&
ComponentFactory::get (void)
{
 return Hazel_Singleton< ComponentFactory , Threading::MUTEX >::get();
}

_micro_kernel_end
