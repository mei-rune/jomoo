
#include "PluginDomConstructor.h"
#include "ModuleDescriptor.h"

_seal_begin

PluginDomConstructor::PluginDomConstructor( PluginInfoDOM& dom )
: dom_( dom )
{
}

PluginDomConstructor::~PluginDomConstructor()
{
}

void PluginDomConstructor::constructRoot(ModuleDescriptorPtr info)
{
	if ( is_null( info ) || ! info->tokens ())
		throw std::runtime_error ("empty descriptor");
	if( info->token( 0 ) != PluginInfoDOMTag )
		throw std::runtime_error( "不是期望的节点!" );
	if (info->tokens () != 1)
		throw std::runtime_error ("`root' 必须没有参数");
	//if (info->parent ())
	//	throw std::runtime_error (  "`root' 必须是根"));
	for (unsigned i = 0; i < info->children (); ++i)
		constructCache (info->child (i));
}

void PluginDomConstructor::constructCache(ModuleDescriptorPtr info)
{
	if ( is_null( info ) || ! info->tokens ())
		throw std::runtime_error ("empty descriptor");
	if( info->token( 0 ) != ModuleCacheTag )
		throw std::runtime_error( "不是期望的节点!" );
	if (info->tokens () != 2)
		throw std::runtime_error ("`cache' 必须一个参数");
	//if (! info->parent () || info->parent ()->token (0) != PluginInfoDOMTag )
	//	throw std::runtime_error ("`cache' 必须在 `root' 下面");
	IModuleCachePtr cache = dom_.createModuleCache( info->token (1) );
	if( is_null( cache ) )
		throw std::runtime_error( "创建cache节点失败" );
	for (unsigned i = 0; i < info->children (); ++i)
		constructReg (info->child (i),*cache );
	dom_.add( cache );
}

void PluginDomConstructor::constructReg(ModuleDescriptorPtr info, IModuleCache& cache )
{
	if ( is_null( info ) || ! info->tokens ())
		throw std::runtime_error ("empty descriptor");
	if( info->token( 0 ) != ModuleRegTag )
		throw std::runtime_error( "不是期望的节点!" );
	if (info->tokens () != 3)
		throw std::runtime_error ("`file' 必须有二个参数" );
	//if (! info->parent () || info->parent ()->token (0) != ModuleCacheTag )
	//	throw std::runtime_error ("`file' 必须在 `cache' 下面");
	if (info->token (2) != "1" && info->token (2) != "0")
		throw std::runtime_error("`file' 最后一个参数是 1 或 0");
	IModuleRegPtr file = dom_.createModuleReg(info->token (1),
		info->token (2) );
	if( is_null( file ) )
		throw std::runtime_error( "创建reg节点失败" );

	for (unsigned i = 0; i < info->children (); ++i)
		constructModule(info->child (i),*file );
	cache.add ( file );
}

void PluginDomConstructor::constructModule (ModuleDescriptorPtr info,IModuleReg& reg )
{
	if ( is_null( info ) || ! info->tokens ())
		throw std::runtime_error ("empty descriptor");
	if( info->token( 0 ) != ModuleTag )
		throw std::runtime_error( "不是期望的节点!" );
	if (info->tokens () != 2)
		throw std::runtime_error("`module' 必须有一个参数");
	IModulePtr module = dom_.createModule ( info->token (1) );
	if( is_null( module ) )
		throw std::runtime_error( "创建module节点失败" );

	for (unsigned i = 0; i < info->children (); ++i)
		constructPlugin (info->child (i),*module );
	reg.add ( module );
}

void PluginDomConstructor::constructPlugin (ModuleDescriptorPtr info,IModule& module )
{
	if ( is_null( info ) || ! info->tokens ())
		throw std::runtime_error ("empty descriptor");
	module.add( info );
}

void PluginDomConstructor::construct (ModuleDescriptorPtr info)
{
	constructRoot( info );
}

_seal_end
