
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
	 * 接收文档中所有出现的处理指令PI。如<? Target "data" ?>
	 * @param[ in ] chars 字符数据据
	 * @param[ in ] length 字符数据据的长度
	 * @remarks 注意XML 和 文本的定义( <? Xml version="1.0" ?>)不被认为是处理器指令
	 */
    virtual void processingInstruction
    (
          const string_view&    target
        , const string_view&    data
    ){}

	/**
	 * 定位器是一种可以返回SAX事件信息的对象。解析器使用本方法来传递它们的定位器，确
	 * 保在需要的时候它们可以得到客户端的位置信息。
	 * @remarks 注意，它不面向客户的方法。
	 */
    virtual void setDocumentLocator(const ILocator* const locator){}

	/**
	 * 每一个文档仅调用一次，发生在所有此接口中所有其它通知处理方法之前
	 */
    virtual void startDocument(){}

	/**
	 * 接收文档结束通知
	 */
    virtual void endDocument (){}

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
        const   ElementName&    name,
        const   Attributes&     attrs
    ){}

	/**
	 * 每当遇到一结束标记时调用。
	 * @param[ in ] uri 包含一个识别命名空间的URI字符串
	 * @param[ in ] localname 包含不以命名空间为前缀命名的元素
	 * @param[ in ] qname 包含元素名称的认证版(有前缀)
	 */
    virtual void endElement
	(
		const   ElementName&    name
	){}

	/**
	 * 接收字符数据的通知
	 * @param[ in ] chars 字符数据据
	 * @param[ in ] length 字符数据据的长度
	 * @remarks 注意，它不是以"\0"结尾的。它也并不一定一次调用返回所有的字符数据
	 */
    virtual void characters
    (
        const  string_view&    chars
    ){}

	/**
	 * 与@see characters类似，它返回文档中所有的非语法性空白.
	 * @param[ in ] chars 字符数据据
	 * @param[ in ] length 字符数据据的长度
	 * @remarks 注意，它不是以"\0"结尾的。它也并不一定一次调用返回所有的字符数据
	 */
    virtual void ignorableWhitespace
    (
        const  string_view&    chars
    ){}

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
		const	string_view&	prefix,
		const	string_view&	uri
	){}

 
	/**
	 * 通知一个特定的命名空间的前缀映射结束
	 * param[ in ] prefir 前缀
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
