#ifndef PLUGININFO_H
# define PLUGININFO_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_PluginManager.h"
# include "PluginInfoBase.H"
# include "PluginFactoryImplBase.H"
# include "IModule.H"
# include "ModuleDescriptor.H"

_seal_begin

class PluginInfo //: public PluginInfoBase
{
public:
	typedef IModule::LoggerPtr LoggerPtr;

	PluginInfo ( IModule& module,
		const ModuleDescriptor &details,
		const tstring &category)
		: m_module (module),
		m_name ( details.token (1) ),
		m_category (category),
		is_default_( false )
	{
		toString_ = "PlugIn[";
		toString_ += m_category;
		toString_ += ":";
		toString_ += m_name;
		toString_ += "]";

		BT_LOG_TRACE( getLogger(), toString() << BT_TEXT("> 构造 ") );
		Hazel_ASSERT ( getLogger(),! m_name.empty ());
		Hazel_ASSERT ( getLogger(),! m_category.empty ());

		for( size_t i= 2; i < details.tokens(); i ++ )
		{
			if( "default" == details.token( i ) )
			{
				is_default_ = true;
			}
		}
		//module->attachInfo( this );
	}

	virtual ~PluginInfo (void)
	{
		//module->detachInfo( this );

		BT_LOG_TRACE( getLogger(), toString() << BT_TEXT("> 析构对象 ") );
	}

	IModule&		module (void) const
	{
		return m_module;
	}

	const tstring &	name (void) const
	{
		return m_name;
	}
	const tstring &	category (void) const
	{
		return m_category;
	}

	const tstring& toString() const
	{
		return toString_;
	}

	LoggerPtr getLogger()
	{
		return m_module.manager().getLogger();
	}

	bool is_default() const
	{
		return is_default_;
	}
protected:
	void		noFactory (void) const
	{
		ThrowException3( NoFactoryError, category(), name() ,"没有工厂!" );
	}

private:
	IModule& m_module;	//< Provider module.
	tstring		m_name;		//< Object name.
	const tstring	&m_category;	//< Cache category label.
	tstring toString_;
	bool is_default_;
};

_seal_end

#endif // PLUGININFO_H
