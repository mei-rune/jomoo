

#include "ModuleDescriptorBuilder.h"
#include "codes.h"
#include "Hazel.Base/exception.hpp"
#include "Hazel.Base/directory.h"
#include <fstream>

_seal_begin

ModuleDescriptorBuilder::ModuleDescriptorBuilder( IPluginManager& manager )
		: manager_( manager )
		, toString_( "ModuleDescriptorBuilder" )
{
}

ModuleDescriptorPtr ModuleDescriptorBuilder::parse (const tstring &file )
{
	BT_LOG_TRACE( getLogger(), toString() << BT_TEXT( "> 开始分析文件 '") << file << BT_TEXT("'.") );

	std::ifstream f( file .c_str(), std::ios_base::in | std::ios_base::binary);
	if (! f)
	{
		BT_LOG_FATAL_THROW3( getLogger()
			, IPluginFeedback::ErrorBadCacheFile
			, BuilderTag
			, toString() << BT_TEXT( "> 不能读文件 '" ) << file <<  BT_TEXT( "' !" )
			, PluginException );
	}

	// 用于保存返回值，
	ModuleDescriptorPtr regdata;

	typedef std::vector< ModuleDescriptorPtr > ContextStack;
	ContextStack	stack;

	int offest = 0;

	//if( !is_null( regdata ) )
	//{
	//	regdata = root;
	//	stack.push_back( root );
	//	offest = 1;
	//}

	char		ch;
	do {
		int		level = 0;
		while ( f.get( ch ) && ch == ' ')
			++level;

		if ( !f.good() )
			break;
		//{
		//	BT_LOG_FATAL_THROW3( getLogger()
		//	, IPluginFeedback::ErrorBadCacheFile
		//	, BuilderTag
		//	, toString() << BT_TEXT( "> 读文件 '" ) << file << BT_TEXT( "'失败.")
		//	, PluginException );
		//}

		level += offest;
		if (level == 0 && !is_null( regdata.get() ) )
		{
			BT_LOG_FATAL_THROW3( getLogger()
			, IPluginFeedback::ErrorBadCacheFile
			, BuilderTag
			, toString() << BT_TEXT( "> 有两个顶层行 '" ) << file << BT_TEXT( "'.")
			, PluginException );
		}

		tstring	token;
		stack.resize ( level+1 );
		ModuleDescriptorPtr doc( createDescriptor ( ) );
		if( level )
			stack [level-1]->addChild( doc );

		stack [level] = doc;
		
		if (level == 0)
			regdata = doc ;

		//解析每一行
		for ( ; f ; f.get( ch )  )
		{
			if (ch == '\n')
			{
				if (! token.empty ())
					doc->addToken (decode (token));

				if (doc->tokens () == 0)
					BT_LOG_FATAL_THROW3( getLogger()
					, IPluginFeedback::ErrorBadCacheFile
					, BuilderTag
					, toString() << BT_TEXT( "> 空行.")
					, PluginException );
				break;
			}
			else if (ch == ' ')
			{
				if (! token.empty ())
					doc->addToken (decode (token));
				token = "";
			}
			else if( ch == '\r' )
			{
			}
			else
			{
				token += ch;
			}
		}

		if ( ! f.good() && ! token.empty ())
		{
			doc->addToken (decode (token));
			token.clear();
		}

	} while ( f.good() );

	BT_LOG_TRACE( getLogger(),
		toString() << BT_TEXT( "> 分析文件 '") << file << BT_TEXT("' 完成.") );

	return regdata;
}

ModuleDescriptorPtr ModuleDescriptorBuilder::createDescriptor ( const tstring &t1 ,
		const tstring &t2 ,
		const tstring &t3 ,
		const tstring &t4 ,
		const tstring &t5 ,
		const tstring &t6 ,
		const tstring &t7 ,
		const tstring &t8 ) 
{
	return ModuleDescriptorPtr( new ModuleDescriptor( *this, t1,t2,t3,t4,t5,t6,t7,t8 ) );
}

ModuleDescriptorPtr ModuleDescriptorBuilder::createDescriptor(	const std::vector<tstring> &tokens) 
{
	return ModuleDescriptorPtr( new ModuleDescriptor( *this, tokens ) );
}


ModuleDescriptorPtr ModuleDescriptorBuilder::dup (ModuleDescriptorPtr from ) 
{
		if( is_null( from ) )
			return from;
		ModuleDescriptorPtr self =createDescriptor ( from->getToken() );
		for (unsigned i = 0; i < from->children (); ++i)
			self->addChild( dup( from->child (i) ) );
		return self;
}

const tstring& ModuleDescriptorBuilder::toString() const
{
	return toString_;
}

_seal_end

Hazel_Export_C _seal IModuleDescriptorBuilder* ___createModuleDescriptorBuilder()
{
	return ( new _seal ModuleDescriptorBuilder( _seal getPluginManager() ) ) ;
}

Hazel_Export_C _seal IModuleDescriptorBuilder* ___createModuleDescriptorBuilderWithManager( _seal IPluginManager& manager )
{
	return ( new _seal ModuleDescriptorBuilder( manager ) ) ;
}

Hazel_Export_C void ___freeModuleDescriptorBuilder( _seal IModuleDescriptorBuilder* builder )
{
	if( builder != 0 )
		delete builder;
}