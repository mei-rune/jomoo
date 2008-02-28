


#ifndef CONTENTHANDLER_HPP
#define CONTENTHANDLER_HPP

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */


namespace XML
{

class Attributes;
class Locator;


class ContentHandler
{
public:
    ContentHandler()
    {
    }

    virtual ~ContentHandler()
    {
    }

	/**
	 * �����ַ����ݵ�֪ͨ
	 * @param[ in ] chars �ַ����ݾ�
	 * @param[ in ] length �ַ����ݾݵĳ���
	 * @remarks ע�⣬��������"\0"��β�ġ���Ҳ����һ��һ�ε��÷������е��ַ�����
	 */
    virtual void characters
    (
        const   XMLCh* const    chars
        , const unsigned int    length
    ) = 0;


	/**
	 * �����ĵ�����֪ͨ
	 */
    virtual void endDocument () = 0;

	/**
	 * ÿ������һ�������ʱ���á�
	 * @param[ in ] uri ����һ��ʶ�������ռ��URI�ַ���
	 * @param[ in ] localname �������������ռ�Ϊǰ׺������Ԫ��
	 * @param[ in ] qname ����Ԫ�����Ƶ���֤��(��ǰ׺)
	 */
    virtual void endElement
	(
		const XMLCh* const uri,
		const XMLCh* const localname,
		const XMLCh* const qname
	) = 0;


	/**
	 * ��@see characters���ƣ��������ĵ������еķ��﷨�Կհ�.
	 * @param[ in ] chars �ַ����ݾ�
	 * @param[ in ] length �ַ����ݾݵĳ���
	 * @remarks ע�⣬��������"\0"��β�ġ���Ҳ����һ��һ�ε��÷������е��ַ�����
	 */
    virtual void ignorableWhitespace
    (
        const   XMLCh* const    chars
        , const unsigned int    length
    ) = 0;

	/**
	 * �����ĵ������г��ֵĴ���ָ��PI����<? Target "data" ?>
	 * @param[ in ] chars �ַ����ݾ�
	 * @param[ in ] length �ַ����ݾݵĳ���
	 * @remarks ע��XML �� �ı��Ķ���( <? Xml version="1.0" ?>)������Ϊ�Ǵ�����ָ��
	 */
    virtual void processingInstruction
    (
        const   XMLCh* const    target
        , const XMLCh* const    data
    ) = 0;

	/**
	 * ��λ����һ�ֿ��Է���SAX�¼���Ϣ�Ķ��󡣽�����ʹ�ñ��������������ǵĶ�λ����ȷ
	 * ������Ҫ��ʱ�����ǿ��Եõ��ͻ��˵�λ����Ϣ��
	 * @remarks ע�⣬��������ͻ��ķ�����
	 */
    virtual void setDocumentLocator(const Locator* const locator) = 0;


	/**
	 * ÿһ���ĵ�������һ�Σ����������д˽ӿ�����������֪ͨ������֮ǰ
	 */
    virtual void startDocument() = 0;

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
        const   XMLCh* const    uri,
        const   XMLCh* const    localname,
        const   XMLCh* const    qname,
        const   Attributes&     attrs
    ) = 0;

  
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
		const	XMLCh* const	prefix,
		const	XMLCh* const	uri
	) = 0 ;

 
	/**
	 * ֪ͨһ���ض��������ռ��ǰ׺ӳ�����
	 * param[ in ] prefir ǰ׺
	 */
	virtual void endPrefixMapping
	(
		const	XMLCh* const	prefix
	) = 0 ;

	virtual void skippedEntity
	(
		const	XMLCh* const	name
	) = 0 ;

private :

    ContentHandler(const ContentHandler&);

    ContentHandler& operator=(const ContentHandler&);
};


}

#endif
