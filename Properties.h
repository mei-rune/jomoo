// **********************************************************************
//
// Copyright (c) 2003-2005 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 2.1.2
// Generated from file `Properties.ice'

#ifndef __Ice_Properties_h__
#define __Ice_Properties_h__

#include <config>


#include "boost/shared_ptr.hpp"
#include "include/BTNM_Export.Hpp"


class Properties 
{
public:

	typedef boost::shared_ptr< Properties > PropertiesPtr;

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

	/**
	 * 生成一个本实例的拷贝
	 */
    virtual PropertiesPtr clone() = 0;
};

typedef  Properties::Properties PropertiesPtr;

BTNM_Export_C PropertiesPtr createProperties();
BTNM_Export_C PropertiesPtr createProperties(const StringSeq&);
BTNM_Export_C PropertiesPtr createProperties(int&, char*[]);


inline StringSeqPtr argsToStringSeq(int argc, char* argv[])
{
    StringSeq result;
    for(int i = 0; i < argc; i++)
    {
        result.push_back(argv[i]);
    }
    return result;
}

#endif
