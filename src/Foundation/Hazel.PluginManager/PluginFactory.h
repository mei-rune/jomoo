#ifndef PLUGIN_MANAGER_PLUGIN_DB_VIEW_H
# define PLUGIN_MANAGER_PLUGIN_DB_VIEW_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_PluginManager.h"
# include "PluginFactoryImpl.H"
# include "MapUniqueIterator.h"
# include <map>

_seal_begin

template < typename I>
class PluginFactory
{
public:
};

template <>
class PluginFactory<void>
{
public:
	PluginFactory (const tstring &name)
	{
	}
};

_seal_end

#include "PluginFactory0.H"
#include "PluginFactory1.H"
#include "PluginFactory2.H"
#include "PluginFactory3.H"
#include "PluginFactory4.H"
#include "PluginFactory5.H"
#include "PluginFactory6.H"
#include "PluginFactory7.H"
#include "PluginFactory8.H"
#include "PluginFactory9.H"
#include "PluginFactory10.H"
#include "PluginFactory11.H"
#include "PluginFactory12.H"
#include "PluginFactory13.H"
#include "PluginFactory14.H"
#include "PluginFactory15.H"
#include "PluginFactory16.H"




#endif // PLUGIN_MANAGER_PLUGIN_DB_VIEW_H
