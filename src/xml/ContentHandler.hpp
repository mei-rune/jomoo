


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
	 * 接收字符数据的通知
	 * @param[ in ] chars 字符数据据
	 * @param[ in ] length 字符数据据的长度
	 * @remarks 注意，它不是以"\0"结尾的。它也并不一定一次调用返回所有的字符数据
	 */
    virtual void characters
    (
        const   XMLCh* const    chars
        , const unsigned int    length
    ) = 0;


	/**
	 * 接收文档结束通知
	 */
    virtual void endDocument () = 0;

	/**
	 * 每当遇到一结束标记时调用。
	 * @param[ in ] uri 包含一个识别命名空间的URI字符串
	 * @param[ in ] localname 包含不以命名空间为前缀命名的元素
	 * @param[ in ] qname 包含元素名称的认证版(有前缀)
	 */
    virtual void endElement
	(
		const XMLCh* const uri,
		const XMLCh* const localname,
		const XMLCh* const qname
	) = 0;


	/**
	 * 与@see characters类似，它返回文档中所有的非语法性空白.
	 * @param[ in ] chars 字符数据据
	 * @param[ in ] length 字符数据据的长度
	 * @remarks 注意，它不是以"\0"结尾的。它也并不一定一次调用返回所有的字符数据
	 */
    virtual void ignorableWhitespace
    (
        const   XMLCh* const    chars
        , const unsigned int    length
    ) = 0;

	/**
	 * 接收文档中所有出现的处理指令PI。如<? Target "data" ?>
	 * @param[ in ] chars 字符数据据
	 * @param[ in ] length 字符数据据的长度
	 * @remarks 注意XML 和 文本的定义( <? Xml version="1.0" ?>)不被认为是处理器指令
	 */
    virtual void processingInstruction
    (
        const   XMLCh* const    target
        , const XMLCh* const    data
    ) = 0;

	/**
	 * 定位器是一种可以返回SAX事件信息的对象。解析器使用本方法来传递它们的定位器，确
	 * 保在需要的时候它们可以得到客户端的位置信息。
	 * @remarks 注意，它不面向客户的方法。
	 */
    virtual void setDocumentLocator(const Locator* const locator) = 0;


	/**
	 * 每一个文档仅调用一次，发生在所有此接口中所有其它通知处理方法之前
	 */
    virtual void startDocument() = 0;

	/**
	 * 每当遇到一开始标记时调用。第一个调用都有一个相应的@see endElement 调
	 * 用对应，
	 * @param[ in ] uri 包含一个识别命名空间的URI字符串
	 * @param[ in ] localname 包含不以命名空间为前缀命名的元素
	 * @param[ in ] qname 包含元素名称的认证版(有前缀)
	 * @param[ in ] attrs 包含被封装在以SAX定义的类的属性的实例中的属性的集合
	 * @remarks  例如下面的文档:
	 * <movies xmlns:kubrick="http://www.kubrick_movies.com">
	 * <kubrick:movie>Eyes Wide Shut</kubrick:movie>
	 * </movies>
	 * 当解析器处理到起始元素movie时，它必须凭借以下参数调用
	 * uri    http://www.kubrick_movies.com
 	 * localname    movie
	 * qname    kubrick:movie
	 * attrs    空
	 */
    virtual void startElement
    (
        const   XMLCh* const    uri,
        const   XMLCh* const    localname,
        const   XMLCh* const    qname,
        const   Attributes&     attrs
    ) = 0;

  
	/**
	 * 无论何时当发现有新的前缀映射时都会被调用。前缀映射通常是以特殊的属性
	 * xmlns:[optional name ]的形式出现的
	 * param[ in ] prefir 前缀
	 * param[ in ] uri 命名空间的URI字符串
	 * @remarks  例如下面的文档:
	 * <movies xmlns:kubrick="http://www.kubrick_movies.com">
	 * <kubrick:movie>Eyes Wide Shut</kubrick:movie>
	 * </movies>
	 * 当解析器处理它时，它必须凭借以下参数调用
	 * prefix    kubrick:movie
	 * uri    http://www.kubrick_movies.com
	 */
	virtual void startPrefixMapping
	(
		const	XMLCh* const	prefix,
		const	XMLCh* const	uri
	) = 0 ;

 
	/**
	 * 通知一个特定的命名空间的前缀映射结束
	 * param[ in ] prefir 前缀
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
