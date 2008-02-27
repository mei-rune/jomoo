#ifndef PLUGIN_INFO_BASE_H
# define PLUGIN_INFO_BASE_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_PluginManager.h"
# include "Hazel.Base/string.hpp"
# include "IPluginManager.H"

_seal_begin

//class PluginInfoWalker;
//
//class PluginInfoBase
//{
//public:
//
//	typedef counter_ptr< PluginInfoBase > ptr_type;
//
//    virtual ~PluginInfoBase (void);
//    virtual const tstring&	name (void) const = 0;
//    virtual const tstring&	category (void) const = 0;
//
//    virtual void	detach (void) = 0;
//
//	virtual const tstring& toString() const = 0;
//
//private:
//	DECLARE_NO_COPY_CLASS( PluginInfoBase );
//};

//typedef PluginInfoBase::ptr_type PluginInfoBasePtr;


_seal_end

#endif // PLUGIN_INFO_BASE_H
