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
	 * ������
	 * @param[ in ] key ������
	 * @return �ɹ���������ֵ��ʧ�ܷ��ؿ�
	 */
    virtual const ::std::string& getProperty(const ::std::string& key) const = 0;

	/**
	 * ������
	 * @param[ in ] key ������
	 * @param[ in ] value ȱʡ����ֵ
	 * @return �ɹ���������ֵ��ʧ�ܷ���ȱʡֵ
	 */
    virtual const ::std::string& getPropertyWithDefault(const ::std::string& key, const ::std::string& value) const = 0;

	/**
	 * ������
	 * @param[ in ] key ������
	 * @param[ in ] value ȱʡ����ֵ
	 * @return �ɹ���������ֵ��ʧ�ܷ���0
	 */
    virtual int getPropertyAsInt(const ::std::string& key) const = 0;

	/**
	 * ������
	 * @param[ in ] key ������
	 * @param[ in ] value ȱʡ����ֵ
	 * @return �ɹ���������ֵ��ʧ�ܷ���ȱʡֵ
	 * @remarks ע������и����ԣ�����ʽ����ȷ����0
	 */
    virtual int getPropertyAsIntWithDefault(const ::std::string& key, int value) const = 0;

	/**
	 * ȡ��ָ��ǰ׺����������
	 * @param[ in ] prefix ǰ׺�ַ�
	 * @param[ in ] deleteprefix ���������Լ���ʱ���Ƿ�keyɾ��ǰ׺( true ɾ����false ��ɾ�� )
	 * @return ����һ�����Լ���
	 * @remarks ע�⣬��deleteprefixΪtrueʱ,�����һ������������ǰ׺ʱ�������Խ�Ҳ�������µ���
	 * �Լ����У�������������Ϊ"_";
	 */
    virtual PropertiesPtr getPropertiesForPrefix(const ::std::string& prefix , bool deleteprefix = false ) const = 0;

	/**
	 * ��ӻ���������ֵ
	 * @param[ in ] key ������
	 * @param[ in ] value ����ֵ
	 */
    virtual void setProperty(const ::std::string& key, const ::std::string& value ) = 0;

	/**
	 * ������ת����һ���ַ�������
	 * @return ����һ���ַ�������
	 * @remarks ע�⣬����ÿһ������ת����һ���ַ�������ʽΪ --������=����ֵ
	 */
    virtual StringSeqPtr getCommandLineOptions() const = 0;

	/**
	 * ��ָ����ѡ�������е���ָ��ǰ׺��ͷ��ѡ����ӵ����Լ��У����ѡ�����ָ��ǰ׺��ͷ�Ľ�������
	 * ����������
	 * @param[ in ] prefix ǰ׺�ַ�
	 * @param[ in ] options ָ����ѡ������
	 * @return ����ָ����ѡ�������еĲ���ָ��ǰ׺��ͷ��ѡ��
	 */
    virtual StringSeqPtr parseCommandLineOptions(const ::std::string& prefix, const StringSeq& options) = 0;

	/**
	 * ���ļ�����������
	 * @param[ in ] file �ļ���
	 */
    virtual void load(const ::std::string& file ) = 0;

	/**
	 * ����һ����ʵ���Ŀ���
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
