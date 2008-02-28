#ifndef MODULE_DESCRIPTOR_BUILDER_BASE_H
# define MODULE_DESCRIPTOR_BUILDER_BASE_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_PluginManager.h"
# include "Hazel.Base/counter_ptr.hpp"
# include <vector>
# include "IPluginManager.H"

_seal_begin

class ModuleDescriptor;
typedef counter_ptr< ModuleDescriptor > ModuleDescriptorPtr;
//class IPluginManager;

class IModuleDescriptorBuilder
{
public:

	typedef counter_ptr< IModuleDescriptorBuilder > ptr_type;

	~IModuleDescriptorBuilder(){}
	virtual ModuleDescriptorPtr parse( const tstring &file ) = 0;

	virtual ModuleDescriptorPtr createDescriptor (
		const tstring &t1 ,
		const tstring &t2 = "",
		const tstring &t3 = "",
		const tstring &t4 = "",
		const tstring &t5 = "",
		const tstring &t6 = "",
		const tstring &t7 = "",
		const tstring &t8 = "") = 0;

	virtual ModuleDescriptorPtr createDescriptor(
		const std::vector<tstring> &tokens) = 0;

	virtual ModuleDescriptorPtr dup ( ModuleDescriptorPtr to ) = 0;
	virtual IPluginManager& manager() = 0;

	virtual const tstring& toString() const = 0;

};

typedef IModuleDescriptorBuilder::ptr_type IModuleDescriptorBuilderPtr;

_seal_end

Hazel_Export_C _seal IModuleDescriptorBuilder* ___createModuleDescriptorBuilder();

Hazel_Export_C _seal IModuleDescriptorBuilder* ___createModuleDescriptorBuilderWithManager( _seal IPluginManager& manager );

Hazel_Export_C void ___freeModuleDescriptorBuilder( _seal IModuleDescriptorBuilder* builder );

_seal_begin

inline IModuleDescriptorBuilderPtr createModuleDescriptorBuilder()
{
	return IModuleDescriptorBuilderPtr( ___createModuleDescriptorBuilder() , ___freeModuleDescriptorBuilder );
}

inline IModuleDescriptorBuilderPtr createModuleDescriptorBuilder( IPluginManager& manager )
{
	return IModuleDescriptorBuilderPtr( ___createModuleDescriptorBuilderWithManager( manager ) , ___freeModuleDescriptorBuilder );
}

_seal_end

#endif // MODULE_DESCRIPTOR_BUILDER_BASE_H
