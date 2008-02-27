#ifndef PLUGIN_MANAGER_PLUGIN_BASE_DB_H
# define PLUGIN_MANAGER_PLUGIN_BASE_DB_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_PluginManager.h"
# include "PluginFeedback.H"
# include "PluginFactoryImplBase.H"
# include "FactoryKey.H"
# include "Hazel.Base/exception.hpp"

_seal_begin

/**
 * @Brief IPluginManager 是所有插件机制的重点实现一种功能的插件可以有多个版本，每
 * 一个版本可以分布在多个动态库中，也可以在一个动态库中每一个功能插件发布时要，有下面
 * 两个部分： 
 * 1. 插口也就是虚类
 * 2. 生成插口的工厂
 * 
 * 为了方便生成插口的工厂统一用模板实现了，只要用模板实例化就可以了，但模板实例化时，
 * 每一个使用它的动态库都会有一个实例，这样可能会有问题。因此利用 Bridge 模式将它分为
 * 抽象部分和实现部分两个部分：实现部分在各动态库中实例化，实例化时，从IPluginManager
 * 中查找抽象部分的实例作为自已功能的实现。注意，抽象部分的实例部分的实例化比较复杂，
 * 具体由谁来实例比较麻烦，如果由插件自已完成的话，插件可能根本不会被载入，或有多个版
 * 本，由哪一个版本实现难以确定，由IPluginManager来决定的话，IPluginManager无法
 * 知道需要载入哪些。因此、由决定第一个使用者来实例化它。
 *
 * IPluginManager 主要有三个功能，－、如上所述抽象部分的实例的管理功能；二、动态库
 * 的管理功能；三、插件信息的管理(即有哪些插件，这些插件在位置)
 * 
 * 插件信息的管理
 * 插件是按三层管理的，一、目录；二、注册文件；三、动态库
 * 如下图
 *
 * root
 *  |
 *  +-------目录1(.cache)
 *  |        |
 *  |        +---注册文件1( .reg )
 *  |        |		|
 *  |        |		+---动态库1( dll )
 *  |        |		|		|
 *  |        |		|		+---插件1.1
 *  |        |		|		|
 *  |        |		|		+---插件2.1
 *  |        |		|		|
 *  |        |		|		+---插件2.2
 *  |        |		|
 *  |        |		+---动态库2( dll )
 *  |        |				|
 *  |        |				+---插件1.2
 *  |        |				|
 *  |        |				+---插件2.3
 *  |        |
 *  |        +---注册文件2( .reg )
 *  |        		|
 *  |        		+---动态库( dll )
 *  |        				|
 *  |        				+---插件3.1
 *  |        				|
 *  |        				+---插件3.2
 *  |
 *  +-------目录2(.cache)
 *           |
 *           +---注册文件1( .reg )
 *           		|
 *           		+---动态库1( dll )
 *           		|		|
 *           		|		+---插件1.3
 *           		|		|
 *           		|		+---插件2.4
 *           		|		|
 *           		|		+---插件3.3
 *           		|
 *           		+---动态库2( dll )
 *           				|
 *           				+---插件4.1
 *           				|
 *           				+---插件4.2
 *
 * 图中共有4个插件，12个版本
 * 插件1.1、插件1.2、插件1.3是同一种插件的不同版本
 * 插件2.1、插件2.2、插件2.3、插件2.4是同一种插件的不同版本
 * 插件3.1、插件3.2、插件3.3是同一种插件的不同版本
 * 插件4.1、插件4.2是同一种插件的不同版本
 * 
 * IPluginManager会维护一个如上所示的插件结构树，以管理动态库和插件信息，并向外提供了遍
 * 历它的接口。
 * 
 * 插件结构树是程序启动时建立的，为了加快载入速度，一、每一个动态库并马上载入，而是需要时才
 * 载入,二、在每一个目录下建立一个叫".cache"的文件，用于记录这个目录下的所有插件。
 * 
 */

class ModuleDescriptor;
typedef counter_ptr< ModuleDescriptor > ModuleDescriptorPtr;
class IModuleDescriptorBuilder;
class IModule;
class IModuleReg;
class IModuleCache;

class PluginInfoWalker
{
public:
	typedef counter_ptr< PluginInfoWalker > ptr_type;

	virtual ~PluginInfoWalker(){}
	virtual void onPlugInfo( ModuleDescriptor& info ) = 0;
	virtual void onModule( IModule& info ) = 0;
	virtual void onModuleReg( IModuleReg& info ) = 0;
	virtual void onModuleCache( IModuleCache& info ) = 0;
};

class FactoryExistError : public _hazel Exception
{
public:

	FactoryExistError( const   char* const         srcFile
            , size_t        srcLine
			, const FactoryKey& category
			, const tstring& message )
			: _hazel Exception( srcFile, srcLine ,message )
			, category_( category )
	{
	}

	const FactoryKey& category() const
	{
		return category_;
	}
	virtual Exception* clone()
	{
		return new FactoryExistError( *this );
	}

	virtual void rethrow()
	{
		Raise( *this );
	}

	virtual void print(std::ostream& Target ) const
	{
			Target << BT_TEXT( "FactoryExistError" )
			<< what()
			<< std::endl;
			dumpFile( Target );
			Target << BT_TEXT( "\t[ category.first=" )
			<< category().first()
			<< BT_TEXT(", category.second=")
			<< category().second()
			<< BT_TEXT( " ]" );
	}
private:
	FactoryKey category_;
};

class FactoryNoExistError : public _hazel Exception
{
public:

	FactoryNoExistError( const   char* const         srcFile
            , size_t        srcLine
			, const FactoryKey& category
			, const tstring& message )
			: _hazel Exception( srcFile, srcLine ,message )
			, category_( category )
	{
	}

	const FactoryKey& category() const
	{
		return category_;
	}

	virtual Exception* clone()
	{
		return new FactoryNoExistError( *this );
	}

	virtual void rethrow()
	{
		Raise( *this );
	}

	virtual void print(std::ostream& Target ) const
	{
			Target << BT_TEXT( "FactoryNoExistError" )
			<< what()
			<< std::endl;
			dumpFile( Target );
			Target << BT_TEXT( "\t[ category.first=" )
			<< category().first()
			<< BT_TEXT(", category.second=")
			<< category().second()
			<< BT_TEXT( " ]" );
	}
private:
	FactoryKey category_;
};



class IPluginManager //: public Component
{
public:

	typedef PluginManagerLoggerPtr LoggerPtr;
	typedef PluginFactoryImplBase factory_type;
	typedef PluginFactoryImplBasePtr factory_ptr_type;
	typedef IPluginManager* ptr_type;

	virtual ~IPluginManager(){}


	/// 用户接口
	virtual void		initialize (void) = 0;
    virtual void		addFeedback (FeedbackCB callback) = 0;
    virtual void		removeFeedback (FeedbackCB callback) = 0;
	virtual IPluginFeedback& getFeedback() = 0;

	/// 工厂接口
	virtual factory_ptr_type		findFactory ( const FactoryKey& category ) = 0;
    virtual void		addFactory ( const FactoryKey& category , factory_ptr_type factory ) = 0;
    /// 注意，实现删除时，要注意是否有其它人用locateFactory取得它的引用，有就不能删除。
	virtual void		removeFactory ( const FactoryKey& category ) = 0;
	virtual void		walk( PluginInfoWalker& walker ) = 0;

	virtual LoggerPtr getLogger() = 0;
	virtual const tstring& toString() const = 0;
};

typedef IPluginManager::ptr_type PluginManagerPtr;



_seal_end

Hazel_Export_C _seal IPluginManager& ___getPluginManager();

Hazel_Export_C _seal IPluginManager& ___initPluginManager( const tchar* pa );

_seal_begin

inline _seal IPluginManager& getPluginManager()
{
	return ___getPluginManager();
}

inline _seal IPluginManager& initPluginManager( const tchar* pa = 0 )
{
	return ___initPluginManager( pa );
}

inline _seal IPluginManager& initPluginManager( const tstring& pa )
{
	return ___initPluginManager( pa.c_str() );
}

_seal_end

#endif // PLUGIN_MANAGER_PLUGIN_BASE_DB_H
