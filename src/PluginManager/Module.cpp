//<<<<<< INCLUDES                                                       >>>>>>

#include "Module.h"
#include "ModuleDescriptor.h"
#include "PluginInfoDom.h"
#include "DefaultPluginManager.h"
#include "PluginInfo.h"
#include "Hazel.Base/exception.hpp"
#include <algorithm>

_seal_begin

const char Module::s_modEntryPoint [] = "SEAL_MODULE";
const char Module::s_modVersionEntryPoint [] = "SEAL_MODULE_VERSION";


Module::Module ( PluginInfoDOM& dom , const tstring &libraryName  )
: dom_( dom ) 
, manager_( dom.manager() )
, m_libraryName (libraryName)
, m_library ()
, entry_( 0 )
, attached_( false )
{
	toString_ = "模块[";
	toString_ += m_libraryName;
	toString_ += "]";

	if ( m_libraryName.empty () )
		BT_LOG_FATAL_THROW3( getLogger()
				, IPluginFeedback::ErrorBadModule
				, ModuleTag
				, toString() <<	 BT_TEXT( "> 动态库名不能为空!")
				, PluginException );
}

Module::~Module (void)
{
	detach();
}

const tstring & Module::libraryName (void) const
{
	return m_libraryName;
}

void	Module::attach (void)
{
	return attach_i( );
}

void	Module::detach (void)
{
	return detach_i();
}

void	Module::query (void)
{
	return query_i();
}

void	Module::walk( PluginInfoWalker& walker )
{
	return walk_i( walker );
}

void	Module::add ( ModuleDescriptorPtr info )
{
	return add_i( info );
}

void	Module::remove ( ModuleDescriptorPtr info )
{
	return remove_i( info );
}


ModuleDescriptorPtr	Module::cache ( IModuleDescriptorBuilder& builder ) const
{
	return cache_i( builder );
}

IPluginManager&	Module::manager ()
{
	return manager_;
}

const	tstring& Module::toString( ) const 
{
	return toString_;
}

ModuleEntry Module::moduleEntryPoint (void)
{
	return entry_;
}

void Module::attach_i (void)
{
	if ( attached_i() )
		return ;
	BT_LOG_TRACE( getLogger(), toString() <<
			BT_TEXT("> 开始连接模块 ") << m_libraryName  << BT_TEXT(".") );

	load_i();


	IModuleDef* definition = (*entry_) ();
	if( definition == 0 )
	{
		//manager().getFeedback().feedback (IPluginFeedback::ErrorEntryFailure, ModuleTag
		//	, BT_TEXT( "取模块 '") + m_libraryName + BT_TEXT("'定义失败!") );
		BT_LOG_FATAL_THROW3( getLogger()
			, IPluginFeedback::ErrorEntryFailure
			, ModuleTag
			, toString() <<	BT_TEXT("> 取模块定义失败!")
			, PluginException );
	}

	BT_LOG_TRACE( getLogger(), toString() <<
			BT_TEXT("> 安装对象工厂 ") << m_libraryName  << BT_TEXT(".") );

	manager().getFeedback().feedback(IPluginFeedback::StatusAttaching, m_libraryName);
	definition->bind (*this);
	definition->attach ();
	
	BT_LOG_TRACE( getLogger(), toString() <<
			BT_TEXT("> 连接模块 ") << m_libraryName  << BT_TEXT("完成.") );

	attached_ = true;
}

void Module::detach_i (void)
{
	if ( !attached_i () )
		return ;

	attached_ = false;

	BT_LOG_TRACE( getLogger(),toString() <<
			BT_TEXT("> 开始卸载模块 ") << m_libraryName  << BT_TEXT(".") );

	manager().getFeedback().feedback(IPluginFeedback::StatusDetaching, m_libraryName);
	IModuleDef* definition = (*entry_) ();
	if( definition == 0 )
	{
		//manager().getFeedback().feedback (IPluginFeedback::ErrorEntryFailure, ModuleTag
		//	, BT_TEXT( "取模块 '") + m_libraryName + BT_TEXT("'定义失败!") );
		BT_LOG_FATAL_THROW3( getLogger()
			, IPluginFeedback::ErrorEntryFailure
			, ModuleTag
			, toString() <<	BT_TEXT("> 取模块定义失败!")
			, PluginException );
	}

	if (definition)
	{
		definition->detach ();
		definition->unbind (*this);
	}
	unload_i();
	BT_LOG_TRACE( getLogger(), toString() <<
			BT_TEXT("> 卸载模块 ") << m_libraryName  << BT_TEXT("完成.") );
}

void Module::query_i (void)
{
	if ( libraryName ().empty ()) 
		return ;

	BT_LOG_TRACE( getLogger(), toString() <<
			BT_TEXT("> 开始查询模块 '") << m_libraryName  << BT_TEXT("'.") );

	load_i();


	IModuleDef* definition = (*entry_) ();
	if( definition == 0 )
	{
		BT_LOG_FATAL_THROW3( getLogger()
			, IPluginFeedback::ErrorEntryFailure
			, ModuleTag
			, toString() <<	BT_TEXT("> 取模块定义失败!")
			, PluginException );
	}

	manager().getFeedback().feedback(IPluginFeedback::StatusQuerying, m_libraryName);
	definition->bind (*this);
	definition->query ();
	definition->unbind (*this);


	//	LOG (0, trace, LFplugin_manager,
	//		"querying module " << libraryName () << '\n' << indent);

	//	while (! m_infos.empty ())
	//		delete *m_infos.begin ();

	//	// Now invoke the standard entry point.
	//	if (ModuleEntry entry = moduleEntryPoint ())
	//	{
	//		m_definition = (*entry) ();
	//		Hazel_ASSERT (m_definition);

	//		manager().feedback (PluginManager::StatusQuerying, m_libraryName);
	//		m_definition->bind (this);
	//		m_definition->query ();
	//		m_definition->release ();
	//		m_definition = 0;
	//	}


	//	if (ModuleCapEntry capEntry = capabilityEntryPoint ())
	//	{
	//		ModuleDef	*def = new ModuleDef;
	//		const char	**names = 0;
	//		int		n = -1;

	//		(*capEntry) (names, n);

	//		def->bind (this);
	//		for (int i = 0; names && names [i] && (n < 0 || i < n); ++i)
	//			PluginCapabilities::get ()->declare (def, names [i]);
	//		def->release ();
	//		delete def;
	//	}

	//	LOG (0, trace, LFplugin_manager, undent);
	//}
}


bool Module::loaded_i (void) const
{ return entry_ != 0 ; }

void Module::load_i (void)
{
	if ( loaded_i() )
		return ;

	try
	{
		BT_LOG_TRACE( getLogger(), toString() <<
			BT_TEXT("> 载入dll [") << m_libraryName  << BT_TEXT("].") );

		manager().getFeedback().feedback( IPluginFeedback::StatusLoading, m_libraryName);
		if( m_library.open( m_libraryName) != 0 )
			BT_LOG_FATAL_THROW3( getLogger()
				, IPluginFeedback::ErrorLoadFailure
				, ModuleTag
				, toString() <<	 BT_TEXT( "> 载入 '") << m_libraryName << BT_TEXT("'时，发生错误，") << m_library.error()
				, PluginException );

			//throw std::runtime_error(	m_library.error() );
	}
	catch ( PluginException &e)
	{
		//manager().getFeedback().feedback( e.code(), e.scope() , e);
		e.rethrow();
		//ThrowException1( RuntimeException , BT_TEXT( ",载入dll时，发生错误，") + tstring( e.what() ) );
	}
	catch( ... )
	{
		//manager().getFeedback().feedback(IPluginFeedback::ErrorLoadFailure, ModuleTag
		//	, BT_TEXT( "> 载入 '") + m_libraryName + BT_TEXT("'时，发生未知错误!") );

		BT_LOG_FATAL_THROW3( getLogger()
				, IPluginFeedback::ErrorLoadFailure
				, ModuleTag
				, toString() <<	 BT_TEXT( "> 载入 '") << m_libraryName << BT_TEXT("'时，发生未知错误!")
				, PluginException );

		//ThrowException1( RuntimeException , BT_TEXT( ",载入dll时，发生未知错误") );
	}
	manager().getFeedback().feedback (IPluginFeedback::StatusEntries, m_libraryName);
	try
	{
		MODULE_VERSION_ENTRY version_entry = ( MODULE_VERSION_ENTRY )
			m_library.symbol (s_modVersionEntryPoint);

		if ( version_entry == 0 )
			BT_LOG_FATAL_THROW3( getLogger()
				, IPluginFeedback::ErrorLoadFailure
				, ModuleTag
				, toString() <<	 BT_TEXT( "> 取模块 '") << m_libraryName << BT_TEXT("'版本信息入口时，发生错误，") << m_library.error()
				, PluginException );

		const char* version =  (*version_entry)();
		if( strcmp( version , Hazel_PLUGIN_MANAGER_VERSION ) != 0 )
			BT_LOG_FATAL_THROW3( getLogger()
				, IPluginFeedback::ErrorVersionFailure
				, ModuleTag
				, toString() <<	 BT_TEXT( "> 模块 '") << m_libraryName << BT_TEXT("'的版本 '")<< version << BT_TEXT("' 与要求 '") << Hazel_PLUGIN_MANAGER_VERSION << BT_TEXT("' 不符")
				, PluginException );


		entry_ = ( ModuleEntry ) m_library.symbol (s_modEntryPoint);
		if ( entry_ == 0 )
			BT_LOG_FATAL_THROW3( getLogger()
				, IPluginFeedback::ErrorLoadFailure
				, ModuleTag
				, toString() <<	 BT_TEXT( "> 取模块 '") << m_libraryName << BT_TEXT("'入口时，发生错误，") << m_library.error()
				, PluginException );

			//throw std::runtime_error(	m_library.error() );
	}
	catch ( PluginException &e )
	{
		//manager().getFeedback().feedback( e.code(), e.scope() , e);
		e.rethrow();

		//manager().getFeedback().feedback (IPluginFeedback::ErrorEntryFailure, m_libraryName, e);
		//ThrowException1( RuntimeException , BT_TEXT( ",取模块入口发生错误,") + tstring( e.what() ) );
	}
	catch( ... )
	{
			//manager().getFeedback().feedback (IPluginFeedback::ErrorEntryFailure , ModuleTag
			//	, BT_TEXT( "> 载入 '") + m_libraryName + BT_TEXT("'时，发生未知错误!") );
			BT_LOG_FATAL_THROW3( getLogger()
				, IPluginFeedback::ErrorEntryFailure
				, ModuleTag
				, toString() <<	 BT_TEXT( "> 载入 '") << m_libraryName << BT_TEXT("'时，发生未知错误!")
				, PluginException );

		//ThrowException1( RuntimeException , BT_TEXT( ",取模块入口，发生未知错误") );
	}
}

void Module::unload_i (void)
{
	BT_LOG_TRACE( getLogger(), toString() <<
			BT_TEXT("> 卸载模块") << m_libraryName  << BT_TEXT(".") );

	if ( getenv ("SEAL_KEEP_MODULES") != NULL )
	{
		manager().getFeedback().feedback (IPluginFeedback::StatusUnloading, ModuleTag
			, BT_TEXT( "> 卸载模块 '") + m_libraryName + BT_TEXT("'!") );
		m_library.close();
	}
	entry_ = 0;
}



bool Module::attached_i (void)
{
	return attached_;
}

void	Module::walk_i( PluginInfoWalker& walker )
{
	walker.onModule( *this );
	for( DescriptorList::iterator it = descriptors_.begin()
		; it != descriptors_.end()
		; it ++  )
		walker.onPlugInfo( *( *it ) );
}

void	Module::add_i ( ModuleDescriptorPtr info )
{
	descriptors_.push_back( info );
}

void	Module::remove_i ( ModuleDescriptorPtr info )
{
	descriptors_.remove( info );
}

ModuleDescriptorPtr	Module::cache_i ( IModuleDescriptorBuilder& Builder ) const
{
	ModuleDescriptorPtr info = Builder.createDescriptor( ModuleTag, libraryName() );
	for( DescriptorList::const_iterator it = descriptors_.begin()
		; it != descriptors_.end()
		; it ++ )
		info->addChild( Builder.dup( *it ) );
	return info;
}

Module::LoggerPtr Module::getLogger()
{
	return manager().getLogger();
}

_seal_end

