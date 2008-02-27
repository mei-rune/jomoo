
#include "ModuleCache.h"
#include "ModuleDescriptor.h"
#include "ModuleReg.h"
#include "Module.h"
#include "PluginManager.h"
#include "ModuleDescriptorBuilder.H"
#include "PluginInfoDOM.H"
#include "PluginDomConstructor.H"
#include "Hazel.Base/Exception.hpp"
#include "codes.h"
#include "Hazel.Base/Directory.H"

_seal_begin

const char		ModuleCache::s_cacheFile [] = ".cache";



ModuleCache::ModuleCache( PluginInfoDOM& dom , const tstring& directory )
: dom_( dom ) 
, manager_( dom.manager() )
, directory_( directory )
{
	toString_ = ModuleCacheTag;
	toString_ += BT_TEXT( "[" );
	toString_ += directory;
	toString_ += BT_TEXT( "]" );
}

void ModuleCache::feelbackDirectory( )
{
	StringSeq files = readDirectory( directory() );
	for( StringSeq::const_iterator it = files.begin()
		; it != files.end()
		; it ++ )
	{
		try
		{
			tstring r = _hazel simplify(directory() + BT_TEXT("/") + *it);
			if( isDirectory( r ) )
				continue;
			if( getExtension( *it ) != "reg" )
				continue;
			ModuleDescriptorBuilder builder( manager() );
			ModuleDescriptorPtr descriptor = builder.parse( r );
			if( is_null( descriptor ) )
				continue;
			PluginInfoDOM dom( manager() );
			PluginDomConstructor constructor( dom );
			constructor.constructReg( descriptor , *this );
		}
		catch( PluginException& e )
		{
			manager().getFeedback().feedback( e.code(),e.scope(),e );
		}
		catch( _hazel Exception& e )
		{
			manager().getFeedback().feedback( IPluginFeedback::Other ,"unknown",e );
		}
		catch( std::exception& e )
		{
			manager().getFeedback().feedback( IPluginFeedback::Other ,"unknown",e.what() );
		}
		catch( ... )
		{
			manager().getFeedback().feedback( IPluginFeedback::Other ,"unknown" );
		}
	}

}

void ModuleCache::walk( PluginInfoWalker& walker )
{
	walker.onModuleCache( *this );
	for( iterator it = reg_.begin()
		; it != reg_.end()
		; it ++ )
		(*it)->walk( walker );
}

void ModuleCache::add( IModuleRegPtr ptr )
{
	reg_.push_back( ptr );
}

void ModuleCache::remove( IModuleRegPtr ptr )
{
	reg_.remove( ptr );
}

ModuleDescriptorPtr ModuleCache::cache ( IModuleDescriptorBuilder& Builder )  const
{
	ModuleDescriptorPtr info = Builder.createDescriptor ( ModuleCacheTag, directory() );
	for (const_iterator i = reg_.begin (); i != reg_.end (); ++i)
		info->addChild( (*i)->cache ( Builder ) );
	return info;
}

IPluginManager& ModuleCache::manager()
{
	return manager_;
}

const	tstring& ModuleCache::toString( ) const
{
	return toString_;
}

const tstring& ModuleCache::directory (void) const
{ return directory_; }

//ModuleCache::ModuleCache (PluginManager *manager, const tstring &directory)
//: m_manager (manager),
//m_directory ( directory )
//{
//	SEAL_ASSERT (! m_directory.empty ());
//
//	m_state.status = CACHE_MISSING;
//	m_state.added  = m_state.removed
//		= m_state.changed
//		= m_state.skipped
//		= false;
//
//	refresh ();
//}
//
//ModuleCache::~ModuleCache (void)
//{
//	SEAL_ASSERT (! m_directory.empty ());
//	ModuleList::iterator module = m_modules.begin ();
//	for (; module != m_modules.end (); ++module)
//		delete *module;
//}
//
//tstring ModuleCache::directory (void) const
//{ return m_directory; }
//
//ModuleCache::Iterator ModuleCache::begin (void) const
//{ return m_modules.begin (); }
//
//ModuleCache::Iterator ModuleCache::end (void) const
//{ return m_modules.end (); }
//
//void ModuleCache::refresh (void)
//{
//	load ();
//	rebuild ();
//	notify ();
//	update ();
//}
//
//bool ModuleCache::parse (const tstring &file )
//{
//	struct stat		statbuf;
//	tstring		filename = simplify( m_directory + "/" + file );
//
//	bool		errors = false;
//	if (::stat (filename, &statbuf) == -1)
//		return true;
//
//	SEAL_TRACING( "plugin_manager", "开始分析文件 '" << file << "'.");
//
//	try {
//		CacheParser parser;
//		std::auto_ptr< ModuleDescriptor > regdata( parser.parse( filename ) );
//		constructor.clear();
//		constructor.construct (regdata.get() );
//
//	} catch ( const std::exception &e) {
//		m_manager->feedback (PluginManager::ErrorBadCacheFile, file, &e);
//		SEAL_ERRORING ( "plugin_manager","文件 "<<  file <<  " 发生错误，" << e.what() << ".");
//		errors = true;
//	} catch (...) {
//		m_manager->feedback (PluginManager::Other, file);
//		SEAL_ERRORING ( "plugin_manager","文件 "<<  file <<  " 发生未知错误.");
//		errors = true;
//	}
//
//	return !errors;
//}
//
//void ModuleCache::load (void)
//{
//	SEAL_TRACING ( "plugin_manager", "开始载入 cache "
//		<< m_directory << "." << s_cacheFile) << ".");
//
//	m_state.status = CACHE_MISSING;
//	m_state.added  = m_state.removed
//		= m_state.changed
//		= m_state.skipped
//		= false;
//
//	if ( parse (s_cacheFile) )
//	{
//		m_state.status = CACHE_OLD;
//		for (RegIterator r = m_cache.begin (); r != m_cache.end (); ++r)
//			delete *r;
//		m_cache.clear ();
//		m_cache.splice (m_cache.end (), m_parse.result);
//	}
//
//	SEAL_TRACING ( "plugin_manager", "载入 cache "
//		<< m_directory << "." << s_cacheFile) << "完毕.")
//}
//
//ModuleDescriptor * ModuleCache::makeBad (const tstring &file, const tstring &time)
//{
//	PluginManager::get ()->feedback (PluginManager::ErrorBadCacheFile, file);
//	ModuleDescriptor *top = new ModuleDescriptor (0, s_cacheTag);
//	new ModuleDescriptor (top, ModuleReg::tag (), file, time, "0");
//	return top;
//}
//
//ModuleCache::CacheStatus  ModuleCache::scanModules (RegList &cache)
//{
//	SEAL_TRACING ( "plugin_manager","开始搜索目录 `" << m_directory << "'" );
//	SEAL_ASSERT (cache.empty ());
//
//	CacheStatus	result = CACHE_MISSING;
//	StringSeq files = readDirectory (m_directory);
//	for (StringSeq::iterator file = files.begin(); file != files.end(); ++file)
//	{
//		if (*file == s_cacheFile)
//			continue;
//
//		struct stat	statbuf;
//		tstring	filename simplify(m_directory + "/" + *file);
//		int		status = stat (filename, &statbuf);
//		if (status == -1)
//		{
//			SEAL_ERRORING ( "plugin_manager", "stat() 发生错误 " << errno << ", 忽略 `"
//				<< *file << "'");
//			m_state.skipped = true;
//			continue;
//		}
//
//		RegIterator match
//			= std::find_if (m_cache.begin(), m_cache.end(), FileByName (*file));
//
//		if (match == m_cache.end ())
//		{
//			SEAL_TRACING( "plugin_manager","==> 新模块 `" << *file << "'");
//			m_state.added = true;
//		}
//		else if ((*match)->time () != (unsigned long) statbuf.st_mtime)
//		{
//			SEAL_TRACING( "plugin_manager,
//				"==> 模块 `" << *file << "' (实际是 "
//				<< statbuf.st_mtime << ", cached 是 " << (*match)->time ()
//				<< ")");
//			m_state.changed = true;
//		}
//		else
//		{
//			SEAL_TRACING( "plugin_manager","==> 模块 `" << *file << "'没有更改");
//			cache.splice (cache.end (), m_cache, match);
//			continue;
//		}
//		
//		tstring time = toString(statbuf.st_mtime);
//
//		std::auto_ptr< ModuleDescriptor > top( new ModuleDescriptor (0, s_cacheTag) );
//		new ModuleDescriptor (top, ModuleReg::tag (), *file, time, "1");
//		CacheParser parser;
//		if (! parser.parse (*file, *top) || m_parse.result.empty ())
//		{
//			constructor.clear();
//			constructor.construct (makeBad (*file, time));
//			m_state.skipped = true;
//		}
//
//		SEAL_ASSERT (m_parse.result.size () <= 1);
//		for (RegIterator r = m_parse.result.begin () ; r != m_parse.result.end (); ++r)
//			for (ModuleReg::Iterator m = (*r)->begin (); m != (*r)->end (); ++m)
//			try
//			{
//				(*m)->load (); // checks for entry points
//				(*m)->query ();
//				(*m)->unload ();
//			}
//			catch (const std::exception &e)
//			{
//				m_manager->feedback (PluginManager::ErrorBadModule,
//					(*m)->libraryName (), e);
//
//				SEAL_TRACING( "plugin_manager","==> 坏模块 `" << *file << "'被忽略," << e.what() );
//				m_state.skipped = true;
//				(*r)->bad (true);
//				break;
//			}
//		cache.splice (cache.end (), m_parse.result);
//	}
//
//	for (RegIterator r = m_cache.begin (); r != m_cache.end (); ++r)
//		if (std::find_if (cache.begin (), cache.end (),
//			FileByName ((*r)->file ())) == cache.end ())
//		{
//			SEAL_TRACING( "plugin_manager",
//				"==> 删除模块 `" << (*r)->file () << "'");
//			m_state.removed = true;
//		}
//
//		result = (m_state.added || m_state.removed || m_state.changed
//			|| m_state.skipped) ? CACHE_OLD : CACHE_VALID;
//
//		SEAL_TRACING( "plugin_manager", "完成 (" << (int) result << ")");
//		return result;
//}
//
//void ModuleCache::rebuild (void)
//{
//	SEAL_TRACING( "plugin_manager", "开始重建 cache.");
//
//	RegList cache;
//	m_state.status = scanModules (cache);
//	m_cache.swap (cache);
//	for (RegIterator r = cache.begin (); r != cache.end (); ++r)
//		for (ModuleReg::Iterator p = (*r)->begin (); p != (*r)->end (); ++p)
//			delete *p;
//
//	SEAL_TRACING( "plugin_manager","开始重建 cache 完成(" << (int) m_state.status
//		<< ", added = " << m_state.added
//		<< ", removed = " << m_state.removed
//		<< ", changed = " << m_state.changed
//		<< ", skipped = " << m_state.skipped
//		<< ")" );
//}
//
//void  ModuleCache::notify (void)
//{
//	SEAL_TRACING( "plugin_manager", "开始收集模块." );
//	for (RegIterator r = m_cache.begin (); r != m_cache.end (); ++r)
//		if (! (*r)->bad ())
//			for (ModuleReg::Iterator p = (*r)->begin (); p != (*r)->end (); ++p)
//				m_modules.push_back (*p);
//	 SEAL_TRACING( "plugin_manager", "收集模块完成." );
//}
//
//void ModuleCache::write (std::ostream &s, ModuleDescriptor *doc, int level/*=0*/)
//{
//	s << tstring (level, ' ') << encode (doc->token (0));
//	for (unsigned i = 1; i < doc->tokens (); ++i)
//		s << ' ' << encode (doc->token (i));
//	s << std::endl;
//
//	for (unsigned i = 0; i < doc->children (); ++i)
//		write (s, doc->child (i), level+1);
//}
//
//void ModuleCache::update (void)
//{
//	if (m_state.status == CACHE_VALID)
//		return;
//
//	SEAL_TRACING ( "plugin_manager", "开始更新 cache." );
//
//	ModuleDescriptor *all = new ModuleDescriptor (0, s_cacheTag);
//	for (RegIterator r = m_cache.begin (); r != m_cache.end (); ++r)
//		(*r)->cache (all);
//
//	
//	tstring		filename = simplify( m_directory + "/" + file );
//
//	tstring tmpfilename = filename;
//	tmpfilename += ".tmp";
//	std::ofstream file( tmpfilename );
//	if (! file)
//	{
//		SEAL_ERRORING ( "plugin_manager","不能打开文件 '"
//			<< tmpfilename 
//			<< "' " 
//			<< strerror( NULL )
//			<< " -- cache 不能被更新" );
//		return;
//	}
//	write (file, all);
//	m_state.status = CACHE_VALID;
//	::remove( filename.c_str() );
//	if( ::rename( tmpfilename.c_str(), filename.c_str() ) != 0 )
//		SEAL_TRACING ( "plugin_manager", "更新完成" );
//}
//

_seal_end
