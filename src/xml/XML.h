/**
 * -*- C++ -*-
 * -------------------------------------------------------------------------------
 * - ¤╭⌒╮ ╭⌒╮		                       XML.h,v 1.0 2005/03/18 12:41:54
 *  ╱◥██◣ ╭╭ ⌒╮
 * ︱田︱田田| ╰------
 * -------------------------------------------------------------------------------
 */

#ifndef _XML_H_
#define _XML_H_


#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */


#include "xml_def.h"
#include "util/tstring.h"
#include <xercesc/dom/DOM.hpp>
#include "util/BT_Ptr.h"

_bt_xml_begin

XERCES_CPP_NAMESPACE_USE

typedef XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* DOM_Node_Ptr;
typedef XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument* DOM_Document_Ptr;
typedef XERCES_CPP_NAMESPACE_QUALIFIER DOMBuilder* DOM_Builder_Ptr;
typedef XERCES_CPP_NAMESPACE_QUALIFIER DOMNode DOM_Node;
typedef XERCES_CPP_NAMESPACE_QUALIFIER DOMNamedNodeMap Attributes_Map;
typedef XERCES_CPP_NAMESPACE_QUALIFIER DOMNamedNodeMap* Attributes_Map_Ptr;
typedef XERCES_CPP_NAMESPACE_QUALIFIER DOMText DOM_Text;
typedef XERCES_CPP_NAMESPACE_QUALIFIER DOMText* DOM_Text_Ptr;
typedef XERCES_CPP_NAMESPACE_QUALIFIER DOMAttr* DOM_Attr_Ptr;
typedef XERCES_CPP_NAMESPACE_QUALIFIER DOMNodeList* DOM_Node_List_Ptr;
/**
 * 在node的孩子节点中找名为name的节点
 * @param[ in ] node 当前节点
 * @param[ in ] name 要找的节点名
 * @param[ in ] lenght 节点名长度
 * @param[ in ] casestr 是否忽略字符串的大小写( true 忽略 ， false 不忽略 )
 * @return  成功返回这个节点，不成功返回0;
 */
DOM_Node_Ptr ___find_child( DOM_Node_Ptr node , const XMLCh* name , int lenght, bool casestr );

/**
 * 在node的孩子节点中找名为name的节点
 * @param[ in ] node 当前节点
 * @param[ in ] name 要找的节点名
 * @param[ in ] casestr 是否忽略字符串的大小写( true 忽略 ， false 不忽略 )
 * @return  成功返回这个节点，不成功返回0;
 */
DOMNode* ___find_child( DOM_Node_Ptr node , const XMLCh* name , bool casestr );

/**
 * 在node的孩子节点中找名为name的节点
 * @param[ in ] node 当前节点
 * @param[ in ] name 要找的节点名
 * @param[ in ] casestr 是否忽略字符串的大小写( true 忽略 ， false 不忽略 )
 * @return  成功返回这个节点，不成功返回0;
 */
DOM_Node_Ptr find_child( DOM_Node_Ptr node , const tchar* name , bool casestr = true );

/**
 * 在node的树节点中找名为name的节点( 广度优先 )
 * @param[ in ] node 当前节点
 * @param[ in ] name 要找的节点名
 * @param[ in ] depth 查找深度( -1 无限 )
 * @param[ in ] casestr 是否忽略字符串的大小写( true 忽略 ， false 不忽略 )
 * @return  成功返回这个节点，不成功返回0;
 */
DOM_Node_Ptr ___find_extent_child( DOM_Node_Ptr node , const XMLCh* name ,int depth ,bool casestr );

/**
 * 在node的树节点中找名为name的节点( 广度优先 )
 * @param[ in ] node 当前节点
 * @param[ in ] name 要找的节点名
 * @param[ in ] depth 查找深度( -1 无限 )
 * @param[ in ] casestr 是否忽略字符串的大小写( true 忽略 ， false 不忽略 )
 * @return  成功返回这个节点，不成功返回0;
 */
DOM_Node_Ptr find_extent_child( DOM_Node_Ptr node , const tchar* name ,int depth = -1 ,bool casestr = true );


/**
 * 将node结点用doc拷内一份( 只拷贝本节点，不拷贝子节点)
 * @param[ in ] doc dom节点拷贝的父文档
 * @param[ in ] node 被拷贝的节点
 * @return 成功返回dom节点的拷贝，否则返回0
 * @remarks 注意 每一个dom节点都有一个指向父文档的内部指针，不能直接将一个文档
 * 取出，放到另一个文档中。注意目前只支持ELEMENT_NODE和TEXT_NODE;
 */
DOM_Node_Ptr ___copy_node( DOM_Document_Ptr doc , DOM_Node_Ptr node );

/**
 * 将node节点及子节点用doc拷内一份
 * @param[ in ] doc dom节点拷贝的父文档
 * @param[ in ] node 被拷贝的节点
 * @return 成功返回dom节点的拷贝，否则返回0
 * @remarks 注意 每一个dom节点都有一个指向父文档的内部指针，不能直接将一个文档
 * 取出，放到另一个文档中。注意目前只支持ELEMENT_NODE和TEXT_NODE;
 */
DOM_Node_Ptr copy_node_tree( DOM_Document_Ptr doc , DOM_Node_Ptr node );

/**
 * 将node结点放在doc的子节点下面
 * @param[ in ] doc 放在本节点下
 * @param[ in ] node 被放的节点
 * @param[ in ] deep 是否拷贝这个节点
 */
int merge_xml_tree( DOM_Node_Ptr doc , DOM_Node_Ptr node , bool deep = true );

/**
 * 创建一个DOM创建器
 * @return 成功返回DOMBuilder对象，不成功返回0
 * @remarks 注意在它使用完成后，删除它
 */
DOM_Builder_Ptr ___make_xml_dom_parser( );

/**
 * 从一个内存块中析出dom文档
 * @param[ in ] builder xml解析器
 * @param[ in ] buf 内存块指针
 * @param[ in ] lenght 内存块大小
 * @return 成功返回dom文档，失败返回0
 * @remarks 注意不试图删除dom文档对象，它的生命周期与builder一致，在
 * builder破坏时，dom文档对象自动删除。
 */
DOM_Document_Ptr ___xml_dom_parse( DOM_Builder_Ptr builder , const void* buf, size_t lenght );

/**
 * 从一个文档中析出dom文档
 * @param[ in ] builder xml解析器
 * @param[ in ] filename 文档名
 * @return 成功返回dom文档，失败返回0
 * @remarks 注意不试图删除dom文档对象，它的生命周期与builder一致，在
 * builder破坏时，dom文档对象自动删除。文档名可以是一个任意url;
 */
DOM_Document_Ptr ___xml_dom_parse( DOM_Builder_Ptr builder , const char* filename );

struct XMLDoc
{
	XMLDoc()
		:doc_( 0 )
	{
	}
BT_Scope_Ptr< DOMBuilder > parser_;
DOM_Document_Ptr doc_;
};

/**
 * 从一个内存块中析出dom文档
 * @param[ in/out ] doc dom文档
 * @param[ in ] buf 内存块指针
 * @param[ in ] lenght 内存块大小
 * @return 成功返回0，失败返回非0
 * @remarks 注意doc中是一个结构，用户不用关心parser_成员
 */
int xml_dom_parse( XMLDoc& doc , const void* buf, size_t lenght );

/**
 * 从一个文档中析出dom文档
 * @param[ in/out ] doc dom文档
 * @param[ in ] filename 文档名
 * @return 成功返回0，失败返回非0
 * @remarks 注意doc中是一个结构，用户不用关心parser_成员
 */
int xml_dom_parse( XMLDoc& doc , const char* filename );

/**
 * 取得文档的根节点
 * @param[ in/out ] doc dom文档
 * @return 找到返回节点，失败返回0;
 */
DOM_Node_Ptr get_xml_root_node( XMLDoc& doc );

/**
 * 读node子节点中的一个名为name的节点下的文本节点或属性的值
 * @param[ in ] doc node节点的父文档
 * @param[ in ] node dom节点
 * @param[ in ] name 节点的名称( 它的格式为 xxxx.xxxx.xxx..... )
 * @param[ in ] casestr 是否忽略字符串的大小写( true 忽略 ， false 不忽略 )
 * @return 找到返回文本节点或属性的值，失败返回0;
 * @remarks 注意，本函数的name字符串，是一个以"."隔开的字符串，每一个
 * "."表示节点往下一级，如"a.b.c"表示,有一个名为c的节点，它的父节点为
 * 一个名为b节点,该名为b的节点的父节点是一个名为a的节点。
 * 本函数查找时从node节点的子节点中开始找。
 */
const XMLCh* ___read_xml_node( DOM_Document_Ptr doc, DOM_Node_Ptr node , const XMLCh* name , bool casestr );

/**
 * 找一个node子节点中的一个名为name的节点
 * @param[ in ] node dom节点
 * @param[ in ] name 节点的名称( 它的格式为 xxxx.xxxx.xxx..... )
 * @param[ in ] create 找不到时是否创建( true 创建， false 不创建 )
 * @param[ in ] casestr 是否忽略字符串的大小写( true 忽略 ， false 不忽略 )
 * @return 找到返回节点，失败返回0;
 * @see ___read_xml_node
 */
DOM_Node_Ptr ___find_and_create_xml_node( DOM_Node_Ptr node , const XMLCh* name ,bool create , bool casestr );

/**
 * 找一个node子节点中的一个名为name的属性节点
 * @param[ in ] node dom节点
 * @param[ in ] name 属性节点的名称( 它的格式为 xxxx.xxxx.xxx..... )
 * @param[ in ] create 找不到时是否创建( true 创建， false 不创建 )
 * @param[ in ] casestr 是否忽略字符串的大小写( true 忽略 ， false 不忽略 )
 * @return 找到返回属性节点，失败返回0;
 * @see ___read_xml_node
 */
DOM_Node_Ptr ___find_and_create_xml_attr_node( DOM_Node_Ptr node , const XMLCh* name ,bool create , bool casestr );

/**
 * 找一个node子节点中的一个名为name的节点
 * @param[ in ] node dom节点
 * @param[ in ] name 节点的名称( 它的格式为 xxxx.xxxx.xxx..... )
 * @param[ in ] create 找不到时是否创建( true 创建， false 不创建 )
 * @param[ in ] casestr 是否忽略字符串的大小写( true 忽略 ， false 不忽略 )
 * @return 找到返回节点，失败返回0;
 * @see ___read_xml_node
 */
DOM_Node_Ptr ___find_and_create_xml_node( DOM_Node_Ptr node , const char* name ,bool create , bool casestr );

/**
 * 找一个node子节点中的一个名为name的属性节点
 * @param[ in ] node dom节点
 * @param[ in ] name 属性节点的名称( 它的格式为 xxxx.xxxx.xxx..... )
 * @param[ in ] create 找不到时是否创建( true 创建， false 不创建 )
 * @param[ in ] casestr 是否忽略字符串的大小写( true 忽略 ， false 不忽略 )
 * @return 找到返回属性节点，失败返回0;
 * @see ___read_xml_node
 */
DOM_Node_Ptr ___find_and_create_xml_attr_node( DOM_Node_Ptr node , const char* name ,bool create , bool casestr );

/**
 * 将node子节点中的一个名为name的节点下的文本节点值设为value(没有就创建一个)
 * @param[ in ] node dom节点
 * @param[ in ] name 节点的名称( 它的格式为 xxxx.xxxx.xxx..... )
 * @param[ in ] casestr 是否忽略字符串的大小写( true 忽略 ， false 不忽略 )
 * @return 成功返回0，失败返回非0
 * @see ___read_xml_node
 */
int ___write_xml_text_node( DOM_Node_Ptr node ,const XMLCh* name , const XMLCh* value , bool casestr );

/**
 * 将node子节点中的一个名为name的节点下的属性节点值设为value(没有就创建一个)
 * @param[ in ] node dom节点
 * @param[ in ] name 节点的名称( 它的格式为 xxxx.xxxx.xxx..... )
 * @param[ in ] casestr 是否忽略字符串的大小写( true 忽略 ， false 不忽略 )
 * @return 成功返回0，失败返回非0
 * @see ___read_xml_node
 */
int ___write_xml_attr_node( DOM_Node_Ptr node ,const XMLCh* name , const XMLCh* value , bool casestr );

/**
 * 判断node节点的名称是否等于指定的字符串
 * @param[ in ] node 节点
 * @param[ in ] name 节点的名称( 它的格式为 xxxx.xxxx.xxx..... )
 * @param[ in ] casestr 是否忽略字符串的大小写( true 忽略 ， false 不忽略 )
 * @return 大于返回1，小于返回-1，等于返回0;
 */
int ___compare_node_name( DOM_Node_Ptr node ,const char* name , bool casestr );


/**
 * 读当前节点下名为name的文本节点值
 * @param[ in ] node dom节点
 * @param[ in ] name 节点的名称( 它的格式为 xxxx.xxxx.xxx..... )
 * @param[ out ] buffer 存放文本节点值的缓冲
 * @param[ in/out ] buffer 调用时为存放文本节点值的缓冲的长度，返回取得的文本节点值的长度
 * @param[ in ] casestr 是否忽略字符串的大小写( true 忽略 ， false 不忽略 )
 * @return 成功返回0，失败返回非0
 * @see ___read_xml_node
 */
int ___read_xml_text_node( DOM_Node_Ptr node ,const XMLCh* name , char* buffer , size_t& length ,bool casestr );

/**
 * 读当前节点下名为name的属性节点值
 * @param[ in ] node dom节点
 * @param[ in ] name 节点的名称( 它的格式为 xxxx.xxxx.xxx..... )
 * @param[ out ] buffer 存放文本节点值的缓冲
 * @param[ in/out ] buffer 调用时为存放文本节点值的缓冲的长度，返回取得的文本节点值的长度
 * @param[ in ] casestr 是否忽略字符串的大小写( true 忽略 ， false 不忽略 )
 * @return 成功返回0，失败返回非0
 * @see ___read_xml_node
 */
int ___read_xml_attr_node( DOM_Node_Ptr node ,const XMLCh* name , char* buffer , size_t& length , bool casestr );

/**
 * 读当前节点下名为name的文本节点值
 * @param[ in ] node dom节点
 * @param[ in ] name 节点的名称( 它的格式为 xxxx.xxxx.xxx..... )
 * @param[ out ] buffer 存放文本节点值的缓冲
 * @param[ in/out ] buffer 调用时为存放文本节点值的缓冲的长度，返回取得的文本节点值的长度
 * @param[ in ] casestr 是否忽略字符串的大小写( true 忽略 ， false 不忽略 )
 * @return 成功返回0，失败返回非0
 * @see ___read_xml_node
 */
int read_xml_text_node( DOM_Node_Ptr node ,const char* name , char* buffer , size_t& length ,bool casestr );

/**
 * 读当前节点下名为name的属性节点值
 * @param[ in ] node dom节点
 * @param[ in ] name 节点的名称( 它的格式为 xxxx.xxxx.xxx..... )
 * @param[ out ] buffer 存放文本节点值的缓冲
 * @param[ in/out ] buffer 调用时为存放文本节点值的缓冲的长度，返回取得的文本节点值的长度
 * @param[ in ] casestr 是否忽略字符串的大小写( true 忽略 ， false 不忽略 )
 * @return 成功返回0，失败返回非0
 * @see ___read_xml_node
 */
int read_xml_attr_node( DOM_Node_Ptr node ,const char* name , char* buffer , size_t& length , bool casestr );

_bt_xml_end

#endif // _XML_H_