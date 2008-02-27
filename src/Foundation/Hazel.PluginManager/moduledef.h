#ifndef PLUGIN_MANAGER_MODULE_DEF_H
# define PLUGIN_MANAGER_MODULE_DEF_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_PluginManager.h"
# include "IModuleDef.H"
# include "PluginDef.H"
# include <list>
# include "Hazel.Base/macro/macro_define.hpp"


#  ifdef _WIN32
#   define Hazel_PLUGIN_API __declspec(dllexport)
#  else
#   define Hazel_PLUGIN_API
#  endif


# define DEFINE_SEAL_MODULE()											\
	namespace { _seal SimpleModuleDef SEAL_THIS_MODULE; }				\
	extern "C" Hazel_PLUGIN_API _seal IModuleDef *SEAL_MODULE (void)	\
	{ return &SEAL_THIS_MODULE; }										\
	extern "C" Hazel_PLUGIN_API const char *SEAL_MODULE_VERSION (void)	\
	{ return  Hazel_PLUGIN_MANAGER_VERSION ; }


# define DEFINE_SEAL_PLUGIN(factory,type,name)			\
	SEAL_MODULE_ACTION									\
	( ( new _seal PluginDef<factory, type>( name ) ) );

# define DEFINE_SEAL_PLUGIN_FACTORY(factory,name,autofactory )			\
	SEAL_MODULE_ACTION									\
	( ( new _seal PluginDefAsFactory<factory, autofactory>( name ) ) );

# define DEFINE_SEAL_PLUGIN_DEFAULT_NAME(factory,type)		\
	SEAL_MODULE_ACTION					\
	( ( new _seal PluginDef<factory, type>( ) ) );

# define DEFINE_SEAL_PLUGIN_FACTORY_DEFAULT_NAME( factory, autofactory )		\
	SEAL_MODULE_ACTION					\
	( ( new _seal PluginDef<factory, PluginDefAsFactory >( ) ) );

#  define SEAL_MODULE_ACTION(cbargs)				\
	static bool Hazel_APPEND (moduleInitAction, __LINE__) =	\
	(SEAL_THIS_MODULE.add( _seal SimpleModuleDef::Action cbargs ), true)



_seal_begin


class SimpleModuleDef : public IModuleDef
{
public:
	typedef counter_ptr< PluginDefBase > Action;

	SimpleModuleDef(): module_( 0 )
	{
	}

	void		bind ( IModule& module ){
		module_ = & module;
	}
	void		unbind ( IModule& module )
	{
		ASSERT( module_ != 0 );
		ASSERT( module_ == &module );
		module_ = 0;
	}
	IModule*		module (void) 
	{
		return module_;
	}


	bool add( Action action )
	{
		onAction.push_back( action );
		return true;
	}

	virtual void	query (void)
	{
		ASSERT( module_ != 0 );
		for( std::list< Action >::iterator it = onAction.begin()
			; it != onAction.end()
			; it ++ )
			(*it)->query( *this );
	}
	virtual void	attach (void)
	{
		ASSERT( module_ != 0 );
		for( std::list< Action >::iterator it = onAction.begin()
			; it != onAction.end()
			; it ++ )
			(*it)->attach( *this );
	}
	virtual void	detach (void)
	{
		ASSERT( module_ != 0 );
		for( std::list< Action >::iterator it = onAction.begin()
			; it != onAction.end()
			; it ++ )
			(*it)->detach( *this );
	}


private:
	std::list< Action > onAction;
	IModule* module_;
};

_seal_end

#endif // PLUGIN_MANAGER_MODULE_DEF_H
