#ifndef MODULE_DESCRIPTOR_BUILDER_H
# define MODULE_DESCRIPTOR_BUILDER_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_PluginManager.h"
# include "ModuleDescriptor.H"
# include "IModuleDescriptorBuilder.H"
# include "IPluginManager.H"
# include "Hazel.Base/directory.H"
# include <vector>
# include <string>
_seal_begin

const char BuilderTag[] = "Builder";

class ModuleDescriptorBuilder : public IModuleDescriptorBuilder
{
public:

	typedef IPluginManager::LoggerPtr LoggerPtr;

	ModuleDescriptorBuilder( IPluginManager& manager );

	template< typename IT >
	ModuleDescriptorPtr parse( IT begin, IT end )
	{
		ModuleDescriptorPtr ret = createDescriptor( PluginInfoDOMTag );
		for( ; begin != end ; begin ++ )
		{
			try
			{
				ModuleDescriptorPtr p = parse( _hazel simplify( *begin + BT_TEXT( "/.cache" ) ) );
				if( !is_null( p ) )
					ret->addChild( p );
				continue;
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

			ModuleDescriptorPtr p = createDescriptor( ModuleCacheTag, *begin );
			if( !is_null( p ) )
					ret->addChild( p );
		}
		return ret;
	}

	ModuleDescriptorPtr parse( const tstring &file );

	ModuleDescriptorPtr createDescriptor (
		const tstring &t1 = "" ,
		const tstring &t2 = "" ,
		const tstring &t3 = "" ,
		const tstring &t4 = "" ,
		const tstring &t5 = "" ,
		const tstring &t6 = "" ,
		const tstring &t7 = "" ,
		const tstring &t8 = "" ) ;

	ModuleDescriptorPtr createDescriptor(	const std::vector<tstring> &tokens ) ;

	ModuleDescriptorPtr dup ( ModuleDescriptorPtr to ) ;

	IPluginManager& manager()
	{
		return manager_;
	}

	LoggerPtr getLogger()
	{
		return manager().getLogger();
	}

	const tstring& toString() const;

private:
	IPluginManager& manager_;
	tstring toString_;
};

_seal_end

#endif // MODULE_DESCRIPTOR_BUILDER_H
