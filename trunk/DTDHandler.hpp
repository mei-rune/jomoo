


#ifndef DTDHANDLER_HPP
#define DTDHANDLER_HPP

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */



/**
 * @Brief DTDHandler 
 * <p>DTDHandler不会接受任何文档的定义申明，它只回应两种类型的事件：标记声明和未经解
 * 析的实体申明事件</p>
 */
class DTDHandler
{
public:

    /** Destructor */
    virtual ~DTDHandler()
    {
    }

   
    
  /**
    * 接受请求的消息
    * @param[ in ] name 名字.
    * @param[ in ] publicId 符号的公共标识， 可能为空
    * @param[ in ] systemId 符号的系统标识, 可能为空
    * @remarks 注意，例如下面的例子
	*          <! NOTATION ISO3116 PUBLIC "ISO/IEC 3166:1933//NOTATION Code
	*                for the Representation of Language//EN" "ie3116" >
	* 解析器必须向notationDecl发出使用以下值的信号：
	* name ISO3116
    * publicId	"ISO/IEC 3166:1933//NOTATION Code
	*                for the Representation of Language//EN"
    * systemId "ie3116"
    * @see #unparsedEntityDecl
    * @see AttributeList#AttributeList
    */
	virtual void notationDecl
    (
        const   XMLCh* const    name
        , const XMLCh* const    publicId
        , const XMLCh* const    systemId
    ) = 0;

  /**
    * 接受与下例同类的的未解析实体声明：
    * <p><! ENTIRY myVRMLmap PUBLIC "..//Icelad/VRML map" "vrml/Iceland.vrml" NDATA vrml ></p>
    * @param[ in ] name 未解析实体名称.
    * @param[ in ] publicId 符号的公共标识， 可能为空
    * @param[ in ] systemId 符号的系统标识, 可能为空
    * @param[ in ] notationName 相关的符号名字.
    * @see #notationDecl
    * @see AttributeList#AttributeList
	* @remarks  注意，所接受的请求是以四个字符串的形式出现的--每一个字符串代表一个部分，如
	* <! NOTATION gif PUBLIC "-//Compuserve Information Service// NOTATION Graphics Interchange Format//EM">
    * <! ENTITY marylin SYSTEM "fabio/marylin.gif" NDATA gif>
	* <p>解析器将以下参数调用</p>
    * name marylin.
    * publicId NULL
    * systemId fabio/marylin.gif
    * notationName gif
    */
    virtual void unparsedEntityDecl
    (
        const   XMLCh* const    name
        , const XMLCh* const    publicId
        , const XMLCh* const    systemId
        , const XMLCh* const    notationName
    ) = 0;


    //virtual void resetDocType() = 0;



private :

    DTDHandler(const DTDHandler&);

    DTDHandler& operator=(const DTDHandler&);

};

} ///namespace UTIL

#endif
