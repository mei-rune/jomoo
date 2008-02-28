//<<<<<< INCLUDES                                                       >>>>>>

#include "DefaultPluginManager.h"
#include "PluginInfo.h"
#include "ModuleCache.h"
#include "Module.h"
#include "ModuleDescriptor.h"
#include "ModuleDescriptorBuilder.H"
//#include "Hazel.Base/string.hpp"

_seal_begin

DefaultPluginManager * DefaultPluginManager::get ( const tchar* pa  )
{
	static DefaultPluginManager *db = 0;
	if ( !is_null(db) )
		return db;

	DefaultPluginManager::SearchPath paths;
	paths.push_back( combinePath( get_application_directory() , "Module") );
	if( !is_null( pa ) )
		paths.push_back( pa );

	const char *path = getenv ("SEAL_PLUGINS");
	if( is_null(path) )
	{
		db = new DefaultPluginManager ( paths );
		return db;
	}

	const char* first = path;
	while( *path != 0 )
	{
		if( *path == ';' )
		{
			paths.push_back( tstring( first, path ) );
			first = path + 1;
		}
		path ++;
	}
	if( first != 0 && *first != 0 )
		paths.push_back( tstring( first ) );

	db = new DefaultPluginManager ( paths );
	return db;
}

DefaultPluginManager::DefaultPluginManager (const SearchPath &path )
: IPluginManager( )
, m_searchPath (path)
, initialize_( false )
, toString_( "DefaultPluginManager" )
{
	//initialize ( );
}

DefaultPluginManager::~DefaultPluginManager (void)
{
}

void  DefaultPluginManager::addFeedback (FeedbackCB callback)
{
	m_feedbacks.add (callback);
}

void  DefaultPluginManager::removeFeedback (FeedbackCB callback)
{
	m_feedbacks.remove (callback);
}

IPluginFeedback& DefaultPluginManager::getFeedback()
{ return m_feedbacks; }

DefaultPluginManager::factory_ptr_type DefaultPluginManager::findFactory (const FactoryKey &category)
{
	Hazel_GUARD( guard , factory_mutex_ );
	FactoryIterator pos = m_factories.find( category );
	return pos != m_factories.end () ? pos->second : factory_ptr_type((factory_type*)( 0 ));
}

void DefaultPluginManager::addFactory ( const FactoryKey& category,factory_ptr_type factory)
{
	Hazel_GUARD( guard , factory_mutex_ );

	FactoryIterator pos = m_factories.find( category );
	if( pos != m_factories.end () )
		ThrowException2( FactoryExistError, category ,BT_TEXT("已有同名的工厂!") );
	m_factories[ category ] = factory;
}

void DefaultPluginManager::removeFactory ( const FactoryKey& category )
{
	Hazel_GUARD( guard , factory_mutex_ );
	FactoryIterator pos = m_factories.find( category );
	if( pos == m_factories.end () )
		ThrowException2( FactoryNoExistError, category , BT_TEXT("没有找到工厂!") );
	//FactoryIterator pos = std::find (m_factories.begin (), m_factories.end (), factory);
	//SEAL_ASSERT (pos != m_factories.end ());
	//m_factories.erase (pos);
}

void DefaultPluginManager::walk( PluginInfoWalker& walker )
{
	if ( !initialized() )
		ThrowException1( RuntimeException, BT_TEXT( "没有初始化!" ) );

	Hazel_GUARD( guard , dom_mutex_ );
	dom_.walk( walker );
}

bool DefaultPluginManager::initialized (void)
{
	return initialize_;
}

void DefaultPluginManager::initialize (void)
{
	Hazel_GUARD( guard , dom_mutex_ );

	if ( initialized() )
		return;
	initialize_ = true;

	dom_.manager( *this );
	ModuleDescriptorBuilder builder( *this );
	ModuleDescriptorPtr descriptor = builder.parse( m_searchPath.begin () ,m_searchPath.end() );
	dom_.initDOM( descriptor );
}

DefaultPluginManager::LoggerPtr DefaultPluginManager::getLogger()
{
	return 0;
}

const tstring& DefaultPluginManager::toString() const
{
	return toString_;
}

_seal_end

Hazel_Export_C _seal IPluginManager& ___getPluginManager()
{
	return * _seal DefaultPluginManager::get( 0 );
}

Hazel_Export_C _seal IPluginManager& ___initPluginManager( const tchar* pa )
{
	_seal IPluginManager& manager = * _seal DefaultPluginManager::get( pa );
	manager.initialize();
	return manager;
}