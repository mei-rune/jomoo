
#ifndef DEFAULTHANDLER_HPP
#define DEFAULTHANDLER_HPP

# include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_MicroKernel.h"
#include "IContentHandler.hpp"
#include "IDTDHandler.hpp"
#include "IErrorHandler.hpp"
#include "SAXParseException.hpp"

_micro_kernel_xml_begin

class DefaultHandler :
	public IDTDHandler,
	public IContentHandler,
    public IErrorHandler
{
public:
	virtual ~DefaultHandler(){}

	/**
	 * �����ĵ������г��ֵĴ���ָ��PI����<? Target "data" ?>
	 * @param[ in ] chars �ַ����ݾ�
	 * @param[ in ] length �ַ����ݾݵĳ���
	 * @remarks ע��XML �� �ı��Ķ���( <? Xml version="1.0" ?>)������Ϊ�Ǵ�����ָ��
	 */
    virtual void processingInstruction
    (
          const string_view&    target
        , const string_view&    data
    ){}

	/**
	 * ��λ����һ�ֿ��Է���SAX�¼���Ϣ�Ķ��󡣽�����ʹ�ñ��������������ǵĶ�λ����ȷ
	 * ������Ҫ��ʱ�����ǿ��Եõ��ͻ��˵�λ����Ϣ��
	 * @remarks ע�⣬��������ͻ��ķ�����
	 */
    virtual void setDocumentLocator(const ILocator* const locator){}

	/**
	 * ÿһ���ĵ�������һ�Σ����������д˽ӿ�����������֪ͨ������֮ǰ
	 */
    virtual void startDocument(){}

	/**
	 * �����ĵ�����֪ͨ
	 */
    virtual void endDocument (){}

	/**
	 * ÿ������һ��ʼ���ʱ���á���һ�����ö���һ����Ӧ��@see endElement ��
	 * �ö�Ӧ��
	 * @param[ in ] uri ����һ��ʶ�������ռ��URI�ַ���
	 * @param[ in ] localname �������������ռ�Ϊǰ׺������Ԫ��
	 * @param[ in ] qname ����Ԫ�����Ƶ���֤��(��ǰ׺)
	 * @param[ in ] attrs ��������װ����SAX�����������Ե�ʵ���е����Եļ���
	 * @remarks  ����������ĵ�:
	 * <movies xmlns:kubrick="http://www.kubrick_movies.com">
	 * <kubrick:movie>Eyes Wide Shut</kubrick:movie>
	 * </movies>
	 * ��������������ʼԪ��movieʱ��������ƾ�����²�������
	 * uri    http://www.kubrick_movies.com
 	 * localname    movie
	 * qname    kubrick:movie
	 * attrs    ��
	 */
    virtual void startElement
    (
        const   ElementName&    name,
        const   Attributes&     attrs
    ){}

	/**
	 * ÿ������һ�������ʱ���á�
	 * @param[ in ] uri ����һ��ʶ�������ռ��URI�ַ���
	 * @param[ in ] localname �������������ռ�Ϊǰ׺������Ԫ��
	 * @param[ in ] qname ����Ԫ�����Ƶ���֤��(��ǰ׺)
	 */
    virtual void endElement
	(
		const   ElementName&    name
	){}

	/**
	 * �����ַ����ݵ�֪ͨ
	 * @param[ in ] chars �ַ����ݾ�
	 * @param[ in ] length �ַ����ݾݵĳ���
	 * @remarks ע�⣬��������"\0"��β�ġ���Ҳ����һ��һ�ε��÷������е��ַ�����
	 */
    virtual void characters
    (
        const  string_view&    chars
    ){}

	/**
	 * ��@see characters���ƣ��������ĵ������еķ��﷨�Կհ�.
	 * @param[ in ] chars �ַ����ݾ�
	 * @param[ in ] length �ַ����ݾݵĳ���
	 * @remarks ע�⣬��������"\0"��β�ġ���Ҳ����һ��һ�ε��÷������е��ַ�����
	 */
    virtual void ignorableWhitespace
    (
        const  string_view&    chars
    ){}

	/**
	 * ���ۺ�ʱ���������µ�ǰ׺ӳ��ʱ���ᱻ���á�ǰ׺ӳ��ͨ���������������
	 * xmlns:[optional name ]����ʽ���ֵ�
	 * param[ in ] prefir ǰ׺
	 * param[ in ] uri �����ռ��URI�ַ���
	 * @remarks  ����������ĵ�:
	 * <movies xmlns:kubrick="http://www.kubrick_movies.com">
	 * <kubrick:movie>Eyes Wide Shut</kubrick:movie>
	 * </movies>
	 * ��������������ʱ��������ƾ�����²�������
	 * prefix    kubrick:movie
	 * uri    http://www.kubrick_movies.com
	 */
	virtual void startPrefixMapping
	(
		const	string_view&	prefix,
		const	string_view&	uri
	){}

 
	/**
	 * ֪ͨһ���ض��������ռ��ǰ׺ӳ�����
	 * param[ in ] prefir ǰ׺
	 */
	virtual void endPrefixMapping
	(
		const	string_view&	prefix
	){}

	virtual void skippedEntity
	(
		const	string_view&	name
	){}

	
	virtual void notationDecl
    (
          const string_view&    name
        , const string_view&    publicId
        , const string_view&    systemId
	) {}

    virtual void unparsedEntityDecl
    (
          const string_view&    name
        , const string_view&    publicId
        , const string_view&    systemId
        , const string_view&    notationName
		) {}

	virtual void resetDocType() {}

	virtual void warning(const SAXParseException& exc){}

	virtual void error(const SAXParseException& exc) {}

	virtual void fatalError(const SAXParseException& exc) {}

	virtual void resetErrors() {}

private:
	DECLARE_NO_COPY_CLASS(DefaultHandler);
};

_micro_kernel_xml_end

#endif // ! DEFAULTHANDLER_HPP
