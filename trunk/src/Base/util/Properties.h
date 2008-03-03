#ifndef __Properties_h__
#define __Properties_h__

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
#include "config_Util.h"
#include "jomoo_export.h"

_util_begin


class Properties 
{
public:

	typedef counter_ptr< Properties > PropertiesPtr;

	virtual ~Properties(){}

	/**
	 * 读属性
	 * @param[ in ] key 属性名
	 * @return 成功返回属性值，失败返回空
	 */
    virtual const ::std::string& getProperty(const ::std::string& key) const = 0;

	/**
	 * 读属性
	 * @param[ in ] key 属性名
	 * @param[ in ] value 缺省属性值
	 * @return 成功返回属性值，失败返回缺省值
	 */
    virtual const ::std::string& getPropertyWithDefault(const ::std::string& key, const ::std::string& value) const = 0;

	/**
	 * 读属性
	 * @param[ in ] key 属性名
	 * @param[ in ] value 缺省属性值
	 * @return 成功返回属性值，失败返回0
	 */
    virtual int getPropertyAsInt(const ::std::string& key) const = 0;

	/**
	 * 读属性
	 * @param[ in ] key 属性名
	 * @param[ in ] value 缺省属性值
	 * @return 成功返回属性值，失败返回缺省值
	 * @remarks 注意如果有该属性，但格式不正确返回0
	 */
    virtual int getPropertyAsIntWithDefault(const ::std::string& key, int value) const = 0;

	/**
	 * 取得指定前缀的所有属性
	 * @param[ in ] prefix 前缀字符
	 * @param[ in ] deleteprefix 在生成属性集类时，是否将key删掉前缀( true 删掉，false 不删除 )
	 * @return 返回一个属性集类
	 * @remarks 注意，在deleteprefix为true时,如果有一个属性名等于前缀时，该属性将也包含在新的属
	 * 性集类中，不过属性名改为"_";
	 */
    virtual PropertiesPtr getPropertiesForPrefix(const ::std::string& prefix , bool deleteprefix = false ) const = 0;

	/**
	 * 取得所属性值的key
	 * @return 返回一个字符串数组
	 */
    virtual StringSeqPtr getPropertiesKeys( ) const = 0;

	/**
	 * 添加或设置属性值
	 * @param[ in ] key 属性名
	 * @param[ in ] value 属性值
	 */
    virtual void setProperty(const ::std::string& key, const ::std::string& value ) = 0;

	/**
	 * 将属性转换成一个字符串数组
	 * @return 返回一个字符串数组
	 * @remarks 注意，它将每一个属性转换成一个字符串，形式为 --属性名=属性值
	 */
    virtual StringSeqPtr getCommandLineOptions() const = 0;

	/**
	 * 将指定的选项数组中的以指定前缀开头的选项添加到属性集中，如果选项不是以指定前缀开头的将它放入
	 * 返回数组中
	 * @param[ in ] prefix 前缀字符
	 * @param[ in ] options 指定的选项数组
	 * @return 返回指定的选项数组中的不以指定前缀开头的选项
	 */
    virtual StringSeqPtr parseCommandLineOptions(const ::std::string& prefix, const StringSeq& options) = 0;

	/**
	 * 从文件中载入配置
	 * @param[ in ] file 文件名
	 */
    virtual void load(const ::std::string& file ) = 0;

	///**
	// * 保存配置到文件中
	// * @param[ in ] file 文件名
	// */
	//virtual void save( const ::std::string& file )const = 0;

	/**
	 * 生成一个本实例的拷贝
	 */
    virtual PropertiesPtr clone() = 0;
};

typedef  Properties::PropertiesPtr PropertiesPtr;

_util_end

JOMOO_Export_C _util Properties* ___createProperties();
JOMOO_Export_C _util Properties* ___createProperties_args(const StringSeq&);
JOMOO_Export_C _util Properties* ___createProperties_vec(int, char*[]);
JOMOO_Export_C void ___freeProperties( _util Properties* );


typedef std::vector<tstring> StringSeq;

inline _util PropertiesPtr createProperties()
{
	return _util PropertiesPtr( ___createProperties(),___freeProperties );
}

inline _util PropertiesPtr createProperties( const StringSeq& args )
{
	return _util PropertiesPtr( ___createProperties_args( args ),___freeProperties );
}

inline _util PropertiesPtr createProperties(int argc , char* argv[] )
{
	return _util PropertiesPtr( ___createProperties_vec( argc, argv ),___freeProperties );
}

inline  StringSeq argsToStringSeq(int argc, char* argv[])
{
    StringSeq result;
    for(int i = 0; i < argc; i++)
    {
        result.push_back(argv[i]);
    }
    return result;
}

#endif
