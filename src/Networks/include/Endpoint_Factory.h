

#ifndef ICE_ENDPOINT_FACTORY_MANAGER_H
#define ICE_ENDPOINT_FACTORY_MANAGER_H

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "../config_Networks.h"
# include "Base/Exception.HPP"
# include "Base/Threading/Threading.H"
# include "Base/Singleton.H"
# include "PluginManager/PluginManager.H"
# include "Endpoint.H"
# include "Communicator.H"
# include "../Url.H"

_networks_begin



class JOMOO_Endpoint_Factory : public _seal PluginFactory< JOMOO_Endpoint* ( Instance_Networks& , const JOMOO_Url_Base& ) >
{
public:
	
	typedef _seal PluginFactory< JOMOO_Endpoint* ( Instance_Networks& , const JOMOO_Url_Base& ) > base_type;

	static JOMOO_Endpoint_Factory& get (void)
	{
		return JOMOO_Singleton< JOMOO_Endpoint_Factory , Threading::MUTEX >::get();
	}

private:

	friend class JOMOO_Singleton< JOMOO_Endpoint_Factory , Threading::MUTEX >;

	JOMOO_Endpoint_Factory ( ) : base_type( _seal getPluginManager(), BT_TEXT("Hazel.Networks.Endpoint"), BT_TEXT("1.0") )
	{
	}

};

//class Instance_Networks;

//class EndpointFactoryManager
//{
//public:
//
//	MakeException( EndpointParseException, "Endpoint·ÖÎö³ö´í" );
//
//    void add(const JOMOO_Endpoint_Factory_Ptr& );
//    JOMOO_Endpoint_Factory_Ptr get( int ) const;
//    JOMOO_Endpoint_Ptr create(const std::string&) const;
//
//private:
//
//	friend class InstanceNetworks;
//
//    EndpointFactoryManager( Instance_Networks& instance );
//
//	Instance_Networks& instance_;
//
//    std::vector<JOMOO_Endpoint_Factory_Ptr> _factories;
//};

_networks_end

#endif
