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
 * @Brief IPluginManager �����в�����Ƶ��ص�ʵ��һ�ֹ��ܵĲ�������ж���汾��ÿ
 * һ���汾���Էֲ��ڶ����̬���У�Ҳ������һ����̬����ÿһ�����ܲ������ʱҪ��������
 * �������֣� 
 * 1. ���Ҳ��������
 * 2. ���ɲ�ڵĹ���
 * 
 * Ϊ�˷������ɲ�ڵĹ���ͳһ��ģ��ʵ���ˣ�ֻҪ��ģ��ʵ�����Ϳ����ˣ���ģ��ʵ����ʱ��
 * ÿһ��ʹ�����Ķ�̬�ⶼ����һ��ʵ�����������ܻ������⡣������� Bridge ģʽ������Ϊ
 * ���󲿷ֺ�ʵ�ֲ����������֣�ʵ�ֲ����ڸ���̬����ʵ������ʵ����ʱ����IPluginManager
 * �в��ҳ��󲿷ֵ�ʵ����Ϊ���ѹ��ܵ�ʵ�֡�ע�⣬���󲿷ֵ�ʵ�����ֵ�ʵ�����Ƚϸ��ӣ�
 * ������˭��ʵ���Ƚ��鷳������ɲ��������ɵĻ���������ܸ������ᱻ���룬���ж����
 * ��������һ���汾ʵ������ȷ������IPluginManager�������Ļ���IPluginManager�޷�
 * ֪����Ҫ������Щ����ˡ��ɾ�����һ��ʹ������ʵ��������
 *
 * IPluginManager ��Ҫ���������ܣ����������������󲿷ֵ�ʵ���Ĺ����ܣ�������̬��
 * �Ĺ����ܣ����������Ϣ�Ĺ���(������Щ�������Щ�����λ��)
 * 
 * �����Ϣ�Ĺ���
 * ����ǰ��������ģ�һ��Ŀ¼������ע���ļ���������̬��
 * ����ͼ
 *
 * root
 *  |
 *  +-------Ŀ¼1(.cache)
 *  |        |
 *  |        +---ע���ļ�1( .reg )
 *  |        |		|
 *  |        |		+---��̬��1( dll )
 *  |        |		|		|
 *  |        |		|		+---���1.1
 *  |        |		|		|
 *  |        |		|		+---���2.1
 *  |        |		|		|
 *  |        |		|		+---���2.2
 *  |        |		|
 *  |        |		+---��̬��2( dll )
 *  |        |				|
 *  |        |				+---���1.2
 *  |        |				|
 *  |        |				+---���2.3
 *  |        |
 *  |        +---ע���ļ�2( .reg )
 *  |        		|
 *  |        		+---��̬��( dll )
 *  |        				|
 *  |        				+---���3.1
 *  |        				|
 *  |        				+---���3.2
 *  |
 *  +-------Ŀ¼2(.cache)
 *           |
 *           +---ע���ļ�1( .reg )
 *           		|
 *           		+---��̬��1( dll )
 *           		|		|
 *           		|		+---���1.3
 *           		|		|
 *           		|		+---���2.4
 *           		|		|
 *           		|		+---���3.3
 *           		|
 *           		+---��̬��2( dll )
 *           				|
 *           				+---���4.1
 *           				|
 *           				+---���4.2
 *
 * ͼ�й���4�������12���汾
 * ���1.1�����1.2�����1.3��ͬһ�ֲ���Ĳ�ͬ�汾
 * ���2.1�����2.2�����2.3�����2.4��ͬһ�ֲ���Ĳ�ͬ�汾
 * ���3.1�����3.2�����3.3��ͬһ�ֲ���Ĳ�ͬ�汾
 * ���4.1�����4.2��ͬһ�ֲ���Ĳ�ͬ�汾
 * 
 * IPluginManager��ά��һ��������ʾ�Ĳ���ṹ�����Թ���̬��Ͳ����Ϣ���������ṩ�˱�
 * �����Ľӿڡ�
 * 
 * ����ṹ���ǳ�������ʱ�����ģ�Ϊ�˼ӿ������ٶȣ�һ��ÿһ����̬�Ⲣ�������룬������Ҫʱ��
 * ����,������ÿһ��Ŀ¼�½���һ����".cache"���ļ������ڼ�¼���Ŀ¼�µ����в����
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


	/// �û��ӿ�
	virtual void		initialize (void) = 0;
    virtual void		addFeedback (FeedbackCB callback) = 0;
    virtual void		removeFeedback (FeedbackCB callback) = 0;
	virtual IPluginFeedback& getFeedback() = 0;

	/// �����ӿ�
	virtual factory_ptr_type		findFactory ( const FactoryKey& category ) = 0;
    virtual void		addFactory ( const FactoryKey& category , factory_ptr_type factory ) = 0;
    /// ע�⣬ʵ��ɾ��ʱ��Ҫע���Ƿ�����������locateFactoryȡ���������ã��оͲ���ɾ����
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
