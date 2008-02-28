#ifndef PLUGIN_MANAGER_PLUGIN_DEF_H
# define PLUGIN_MANAGER_PLUGIN_DEF_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
#include "config_PluginManager.h"
# include <string>
# include "IModuleDef.H"

_seal_begin


class PluginDefBase
{
public:
	virtual ~PluginDefBase( ){}
    virtual void	query ( IModuleDef& def ) = 0;
	virtual void	attach ( IModuleDef& def ) = 0;
    virtual void	detach ( IModuleDef& def ) = 0;
};

template <class Factory, class Type >
class PluginDef : public PluginDefBase
{
public:
	typedef typename Factory::Types::template AutoFactory<Type> AutoFactory;
	typedef typename Factory::Types::Factory AbstractFactory;

	PluginDef( const tstring& name )
		: name_( name )
		, Factory_( new AutoFactory() )
	{
	}

	PluginDef( const tstring& name ,AbstractFactory* factory )
		: name_( name )
		, Factory_( factory )
	{
	}

	PluginDef( )
		: name_( Type::classContextKey () )
		, Factory_( new AutoFactory() )
	{
	}


    void	query ( IModuleDef& def )
	{
		IModuleDescriptorBuilderPtr builder = createModuleDescriptorBuilder( def.module()->manager() );
		def.module()->add( builder->createDescriptor( Factory::get ().category() , name_ ) );
	}
	
	void	attach ( IModuleDef& def )
	{
		//typedef typename Factory::Types::template AutoFactory<Type> AutoFactory;
		Factory::get ().installFactory ( def, name_ , get_ptr( Factory_ ) );
	}

    void	detach ( IModuleDef& def )
	{
		Factory::get ().uninstallFactory ( def, name_ );
	}


private:

	std::auto_ptr< AutoFactory > Factory_;
	tstring name_;

};




template <class Factory, class AbstractFactory >
class PluginDefAsFactory : public PluginDefBase
{
public:

	PluginDefAsFactory( const tstring& name )
		: Factory_()
		, name_( name )
	{
	}

	PluginDefAsFactory( )
		: Factory_()
	{
		name_ = Factory_.name();
	}

    void	query ( IModuleDef& def )
	{
		IModuleDescriptorBuilderPtr builder = createModuleDescriptorBuilder( def.module()->manager() );
		def.module()->add( builder->createDescriptor( Factory::get ().category() , name_ ) );
	}
	
	void	attach ( IModuleDef& def )
	{
		Factory::get ().installFactory ( def, name_ , &Factory_ );
	}

    void	detach ( IModuleDef& def )
	{
		Factory::get ().uninstallFactory ( def, name_ );
	}

private:

	AbstractFactory Factory_;
	tstring name_;
};

_seal_end

#endif // PLUGIN_MANAGER_PLUGIN_DEF_H
