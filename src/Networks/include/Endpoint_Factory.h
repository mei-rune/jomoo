

#ifndef ICE_ENDPOINT_FACTORY_MANAGER_H
#define ICE_ENDPOINT_FACTORY_MANAGER_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "../config_Networks.h"
# include "Hazel.Base/Exception.HPP"
# include "Hazel.Base/Threading/Threading.H"
# include "Hazel.Base/Singleton.H"
# include "Hazel.PluginManager/PluginManager.H"
# include "Hazel_Endpoint.H"
# include "Hazel_Communicator.H"
# include "../Hazel_Url.H"

_networks_begin



class Hazel_Endpoint_Factory : public _seal PluginFactory< Hazel_Endpoint* ( Instance_Networks& , const Hazel_Url_Base& ) >
{
public:
	
	typedef _seal PluginFactory< Hazel_Endpoint* ( Instance_Networks& , const Hazel_Url_Base& ) > base_type;

	static Hazel_Endpoint_Factory& get (void)
	{
		return Hazel_Singleton< Hazel_Endpoint_Factory , Threading::MUTEX >::get();
	}

private:

	friend class Hazel_Singleton< Hazel_Endpoint_Factory , Threading::MUTEX >;

	Hazel_Endpoint_Factory ( ) : base_type( _seal getPluginManager(), BT_TEXT("Hazel.Networks.Endpoint"), BT_TEXT("1.0") )
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
//    void add(const Hazel_Endpoint_Factory_Ptr& );
//    Hazel_Endpoint_Factory_Ptr get( int ) const;
//    Hazel_Endpoint_Ptr create(const std::string&) const;
//
//private:
//
//	friend class InstanceNetworks;
//
//    EndpointFactoryManager( Instance_Networks& instance );
//
//	Instance_Networks& instance_;
//
//    std::vector<Hazel_Endpoint_Factory_Ptr> _factories;
//};

_networks_end

#endif
