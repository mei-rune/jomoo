#ifndef PLUGINFACTORYIMPL_H
#define PLUGINFACTORYIMPL_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_PluginManager.h"
# include "MapUniqueIterator.H"
# include "PluginFactoryImplBase.h"
# include "PluginFactoryImplTypes.H"
# include "ModuleDescriptor.H"
# include "IPluginManager.H"
# include "IModuleDef.H"
# include <map>

_seal_begin

template < typename T >
class PluginInfoWalkerT : public PluginInfoWalker
{
public:

	PluginInfoWalkerT( T& t )
		: t_( t )
	{
	}

	virtual void onPlugInfo( ModuleDescriptor& info )
	{
		if( module_ != 0 && info.token( 0 ) == t_.category() )
			t_.add( *module_ , info );
	}

	virtual void onModule( IModule& info )
	{
		module_ = &info;
	}

	virtual void onModuleReg( IModuleReg& info )
	{
		module_ = 0;
	}

	virtual void onModuleCache( IModuleCache& info )
	{
		module_ = 0;
	}

private:
	IModule* module_;
	T& t_;
};

template <typename T >
class PluginFactoryImplDB : public PluginFactoryImplBase
{
public:

	typedef T	Types;

	typedef typename Types::Object		Object;

	typedef typename Types::Factory		Factory;

	typedef typename Types::Info		Info;


	typedef PluginFactoryImplDB< Types > this_type;
	typedef typename Types::Info		Info;
	typedef std::map<tstring, Info *>	Map;
	typedef typename Map::value_type		MapValue;
	typedef MapUniqueIterator<Map>		Iterator;

	enum
	{
		params_value = Types::params_value
	};

	PluginFactoryImplDB ( IPluginManager& manager ,const tstring& category, const tstring& version )
		: manager_( manager )
		, category_( category )
		, version_( version )
		, info_( 0 )
	{
		Hazel_ASSERT ( getLogger(), ! category.empty ());
	}

	virtual ~PluginFactoryImplDB (void)
	{
		m_map.clear();
	}

	const tstring &	category (void) const
	{
		return category_;
	}

	const tstring & version (void) const
	{
		return version_;
	}

	Info*	default_factory () const
	{
		if( is_null( info_ ) )
			return info_;
		if( m_map.empty() )
			return NULL;
		info_ = (*begin());
		return info_;
	}

	virtual void	rebuild (void)
	{
		m_map.clear();
		PluginInfoWalkerT< this_type > walker( *this );
		manager_.walk( walker );
	}

	void add( IModule& module, const ModuleDescriptor &descriptor )
	{
		if( category() != descriptor.token( 0 ) )
			return ;
		Map::iterator it = m_map.find( descriptor.token( 1 ) );
		if( it != m_map.end() )
			ThrowException3( PluginInfoExistError, category_, descriptor.token( 1 ),"已经有一个同名的" );
		Info* info = new Info( module, descriptor , category_ );
		m_map.insert( std::make_pair( descriptor.token( 1 ) ,info ));
		if( !info->is_default() )
			return ;
		if( !is_null( info_ ) && info->is_default() )
			ThrowException4( PluginInfoExistDefaultInfo
			, category_
			, info_->name()
			, info->name()
			, "已经有一个同名的" );
		info_ = info;
	}

	void remove( const tstring& name )
	{
		Map::iterator it = m_map.find( name );
		if( it == m_map.end() )
			ThrowException3( PluginInfoNoExistError, name , category(),"已经有一个同名的" );
		m_map.erase( it );
		if( info_ == &(*it) )
			info_ = NULL;
	}

	Iterator		begin (void) const
	{
		return Iterator (m_map.begin (), &m_map);
	}

	Iterator		end (void) const
	{
		return Iterator (m_map.end (), &m_map);
	}

	Iterator		locate (const tstring &name) const
	{
		return Iterator (m_map.find (name), &m_map);
	}

	Info*		info (const tstring &name) const
	{
		Iterator pos (locate (name));
		if( pos == end () )
			ThrowException3( PluginInfoNoExistError, name , category_,"没有找到" );
		return  *pos;
	}

	IPluginManager::LoggerPtr getLogger()
	{
		return manager_.getLogger();
	}

private:
	IPluginManager& manager_;
	tstring category_;
	tstring version_;
	Map			m_map;
	mutable Info* info_;
};


template <typename Proto>
class PluginFactoryImpl
	: public PluginFactoryImplDB< PluginFactoryImplTypes<Proto> >
{
public:

	typedef counter_ptr< PluginFactoryImpl< Proto > > ptr_type;

	PluginFactoryImpl (IPluginManager& manager , const tstring &category , const tstring& version )
		: PluginFactoryImplDB<Types> ( manager , category ,version )
	{
		toString_ = BT_TEXT( "PluginFactoryImpl[ category=" );
		toString_ += category;
		toString_ += BT_TEXT( ",version=");
		toString_ += version;
		toString_ += BT_TEXT( "]" );

		rebuild();
	}

	void	installFactory ( IModuleDef& def , const tstring& name,
		Factory *factory )
	{

		Info *info = this->info (name);
		if( info == 0 )
		{
			BT_LOG_TRACE( getLogger(), toString() << BT_TEXT( "> 安装工厂时，没有找到PluginInfo!") )
			return ;
		}
		info->attach ( factory );
	}

	void	uninstallFactory ( IModuleDef& def , const tstring& name )
	{
		Info *info = this->info (name);
		if( info == 0 )
		{
			BT_LOG_TRACE( getLogger(), toString() << BT_TEXT( "> 卸装工厂时，没有找到PluginInfo!") )
			return ;
		}
		info->detach (  );
	}
	const tstring& toString() const
	{
		return toString_;
	}
private:
	tstring toString_;
};

template <>
class PluginFactoryImpl<void>
{
public:
	typedef PluginFactoryImplTypes<void>	Types;
	typedef counter_ptr< PluginFactoryImpl< Types > > ptr_type;

	PluginFactoryImpl (IPluginManager& manager ,const tstring &name)
	{
	}
};

_seal_end

#endif // PLUGINFACTORYIMPL_H
