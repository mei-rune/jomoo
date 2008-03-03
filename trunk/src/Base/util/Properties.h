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
	 * ȡ��������ֵ��key
	 * @return ����һ���ַ�������
	 */
    virtual StringSeqPtr getPropertiesKeys( ) const = 0;

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

	///**
	// * �������õ��ļ���
	// * @param[ in ] file �ļ���
	// */
	//virtual void save( const ::std::string& file )const = 0;

	/**
	 * ����һ����ʵ���Ŀ���
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
