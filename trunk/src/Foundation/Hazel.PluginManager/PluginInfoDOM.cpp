
#include "PluginInfoDOM.H"
#include "ModuleCache.h"
#include "ModuleDescriptor.h"
#include "ModuleDescriptorBuilder.h"
#include "ModuleReg.h"
#include "Module.h"
#include "Hazel.Base/Exception.hpp"
#include "PluginDomConstructor.H"

_seal_begin

PluginInfoDOM::PluginInfoDOM( IPluginManager& manager )
: manager_( &manager )
{
}

PluginInfoDOM::PluginInfoDOM( )
: manager_( 0 )
{
}

void PluginInfoDOM::initDOM(  ModuleDescriptorPtr descriptor )
{
	PluginDomConstructor constructor( *this );
	constructor.constructRoot( descriptor );
}

void PluginInfoDOM::walk( PluginInfoWalker& walker )
{
	for( iterator it = cache_.begin()
		; it != cache_.end()
		; it ++ )
		(*it)->walk( walker );
}

IModuleCachePtr PluginInfoDOM::createModuleCache( const tstring &directory)
{
	return IModuleCachePtr( new ModuleCache( *this , directory ) );
}

IModuleRegPtr PluginInfoDOM::createModuleReg( const tstring &regfile, bool bad )
{
	return IModuleRegPtr( new ModuleReg( *this, regfile, bad ) );
}

IModuleRegPtr PluginInfoDOM::createModuleReg( const tstring &regfile,
	       const tstring &bad )
{
	return IModuleRegPtr( new ModuleReg( *this, regfile, bad ) );
}

IModulePtr PluginInfoDOM::createModule( const tstring &libraryName )
{
	return IModulePtr( new Module( *this, libraryName ) );
}


void PluginInfoDOM::add( IModuleCachePtr ptr )
{
	cache_.push_back( ptr );
}

void PluginInfoDOM::remove( IModuleCachePtr ptr )
{
	cache_.remove( ptr );
}

ModuleDescriptorPtr PluginInfoDOM::cache ( IModuleDescriptorBuilder& Builder ) const
{
	ModuleDescriptorPtr info = Builder.createDescriptor( PluginInfoDOMTag ) ;
	for ( const_iterator i = cache_.begin (); i != cache_.end (); ++i)
		info->addChild( (*i)->cache ( Builder ) );
	return info;
}

IPluginManager& PluginInfoDOM::manager()
{
	return *manager_;
}

void PluginInfoDOM::manager( IPluginManager& manager )
{
	manager_ = &manager;
}

_seal_end
