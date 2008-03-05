
#include "include/Endpoint_Factory.H"
#include "Tcp/Instance_Tcp.H"

#ifdef _MEMORY_DEBUG
#undef THIS_FILE
#define new	   DEBUG_NEW  
#define malloc DEBUG_MALLOC  
static char THIS_FILE[] = __FILE__;  
#endif // _MEMORY_DEBUG

_networks_begin

_networks_end

DEFINE_SEAL_MODULE ();
//DEFINE_SEAL_PLUGIN_FACTORY_DEFAULT_NAME ( _networks JOMOO_Endpoint_Factory, _networks TCP_Endpoint_Factory );
//DEFINE_SEAL_PLUGIN_FACTORY_DEFAULT_NAME ( ComponentFactory , _networks Instance_TCP );
