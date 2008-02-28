/**
 * -*- C++ -*-
 * -------------------------------------------------------------------------------
 * - ��q�Шr �q�Шr		                       XML.h,v 1.0 2005/03/18 12:41:54
 *  �u�������� �q�q �Шr
 * ���������| �t------
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
 * ��node�ĺ��ӽڵ�������Ϊname�Ľڵ�
 * @param[ in ] node ��ǰ�ڵ�
 * @param[ in ] name Ҫ�ҵĽڵ���
 * @param[ in ] lenght �ڵ�������
 * @param[ in ] casestr �Ƿ�����ַ����Ĵ�Сд( true ���� �� false ������ )
 * @return  �ɹ���������ڵ㣬���ɹ�����0;
 */
DOM_Node_Ptr ___find_child( DOM_Node_Ptr node , const XMLCh* name , int lenght, bool casestr );

/**
 * ��node�ĺ��ӽڵ�������Ϊname�Ľڵ�
 * @param[ in ] node ��ǰ�ڵ�
 * @param[ in ] name Ҫ�ҵĽڵ���
 * @param[ in ] casestr �Ƿ�����ַ����Ĵ�Сд( true ���� �� false ������ )
 * @return  �ɹ���������ڵ㣬���ɹ�����0;
 */
DOMNode* ___find_child( DOM_Node_Ptr node , const XMLCh* name , bool casestr );

/**
 * ��node�ĺ��ӽڵ�������Ϊname�Ľڵ�
 * @param[ in ] node ��ǰ�ڵ�
 * @param[ in ] name Ҫ�ҵĽڵ���
 * @param[ in ] casestr �Ƿ�����ַ����Ĵ�Сд( true ���� �� false ������ )
 * @return  �ɹ���������ڵ㣬���ɹ�����0;
 */
DOM_Node_Ptr find_child( DOM_Node_Ptr node , const tchar* name , bool casestr = true );

/**
 * ��node�����ڵ�������Ϊname�Ľڵ�( ������� )
 * @param[ in ] node ��ǰ�ڵ�
 * @param[ in ] name Ҫ�ҵĽڵ���
 * @param[ in ] depth �������( -1 ���� )
 * @param[ in ] casestr �Ƿ�����ַ����Ĵ�Сд( true ���� �� false ������ )
 * @return  �ɹ���������ڵ㣬���ɹ�����0;
 */
DOM_Node_Ptr ___find_extent_child( DOM_Node_Ptr node , const XMLCh* name ,int depth ,bool casestr );

/**
 * ��node�����ڵ�������Ϊname�Ľڵ�( ������� )
 * @param[ in ] node ��ǰ�ڵ�
 * @param[ in ] name Ҫ�ҵĽڵ���
 * @param[ in ] depth �������( -1 ���� )
 * @param[ in ] casestr �Ƿ�����ַ����Ĵ�Сд( true ���� �� false ������ )
 * @return  �ɹ���������ڵ㣬���ɹ�����0;
 */
DOM_Node_Ptr find_extent_child( DOM_Node_Ptr node , const tchar* name ,int depth = -1 ,bool casestr = true );


/**
 * ��node�����doc����һ��( ֻ�������ڵ㣬�������ӽڵ�)
 * @param[ in ] doc dom�ڵ㿽���ĸ��ĵ�
 * @param[ in ] node �������Ľڵ�
 * @return �ɹ�����dom�ڵ�Ŀ��������򷵻�0
 * @remarks ע�� ÿһ��dom�ڵ㶼��һ��ָ���ĵ����ڲ�ָ�룬����ֱ�ӽ�һ���ĵ�
 * ȡ�����ŵ���һ���ĵ��С�ע��Ŀǰֻ֧��ELEMENT_NODE��TEXT_NODE;
 */
DOM_Node_Ptr ___copy_node( DOM_Document_Ptr doc , DOM_Node_Ptr node );

/**
 * ��node�ڵ㼰�ӽڵ���doc����һ��
 * @param[ in ] doc dom�ڵ㿽���ĸ��ĵ�
 * @param[ in ] node �������Ľڵ�
 * @return �ɹ�����dom�ڵ�Ŀ��������򷵻�0
 * @remarks ע�� ÿһ��dom�ڵ㶼��һ��ָ���ĵ����ڲ�ָ�룬����ֱ�ӽ�һ���ĵ�
 * ȡ�����ŵ���һ���ĵ��С�ע��Ŀǰֻ֧��ELEMENT_NODE��TEXT_NODE;
 */
DOM_Node_Ptr copy_node_tree( DOM_Document_Ptr doc , DOM_Node_Ptr node );

/**
 * ��node������doc���ӽڵ�����
 * @param[ in ] doc ���ڱ��ڵ���
 * @param[ in ] node ���ŵĽڵ�
 * @param[ in ] deep �Ƿ񿽱�����ڵ�
 */
int merge_xml_tree( DOM_Node_Ptr doc , DOM_Node_Ptr node , bool deep = true );

/**
 * ����һ��DOM������
 * @return �ɹ�����DOMBuilder���󣬲��ɹ�����0
 * @remarks ע������ʹ����ɺ�ɾ����
 */
DOM_Builder_Ptr ___make_xml_dom_parser( );

/**
 * ��һ���ڴ��������dom�ĵ�
 * @param[ in ] builder xml������
 * @param[ in ] buf �ڴ��ָ��
 * @param[ in ] lenght �ڴ���С
 * @return �ɹ�����dom�ĵ���ʧ�ܷ���0
 * @remarks ע�ⲻ��ͼɾ��dom�ĵ�������������������builderһ�£���
 * builder�ƻ�ʱ��dom�ĵ������Զ�ɾ����
 */
DOM_Document_Ptr ___xml_dom_parse( DOM_Builder_Ptr builder , const void* buf, size_t lenght );

/**
 * ��һ���ĵ�������dom�ĵ�
 * @param[ in ] builder xml������
 * @param[ in ] filename �ĵ���
 * @return �ɹ�����dom�ĵ���ʧ�ܷ���0
 * @remarks ע�ⲻ��ͼɾ��dom�ĵ�������������������builderһ�£���
 * builder�ƻ�ʱ��dom�ĵ������Զ�ɾ�����ĵ���������һ������url;
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
 * ��һ���ڴ��������dom�ĵ�
 * @param[ in/out ] doc dom�ĵ�
 * @param[ in ] buf �ڴ��ָ��
 * @param[ in ] lenght �ڴ���С
 * @return �ɹ�����0��ʧ�ܷ��ط�0
 * @remarks ע��doc����һ���ṹ���û����ù���parser_��Ա
 */
int xml_dom_parse( XMLDoc& doc , const void* buf, size_t lenght );

/**
 * ��һ���ĵ�������dom�ĵ�
 * @param[ in/out ] doc dom�ĵ�
 * @param[ in ] filename �ĵ���
 * @return �ɹ�����0��ʧ�ܷ��ط�0
 * @remarks ע��doc����һ���ṹ���û����ù���parser_��Ա
 */
int xml_dom_parse( XMLDoc& doc , const char* filename );

/**
 * ȡ���ĵ��ĸ��ڵ�
 * @param[ in/out ] doc dom�ĵ�
 * @return �ҵ����ؽڵ㣬ʧ�ܷ���0;
 */
DOM_Node_Ptr get_xml_root_node( XMLDoc& doc );

/**
 * ��node�ӽڵ��е�һ����Ϊname�Ľڵ��µ��ı��ڵ�����Ե�ֵ
 * @param[ in ] doc node�ڵ�ĸ��ĵ�
 * @param[ in ] node dom�ڵ�
 * @param[ in ] name �ڵ������( ���ĸ�ʽΪ xxxx.xxxx.xxx..... )
 * @param[ in ] casestr �Ƿ�����ַ����Ĵ�Сд( true ���� �� false ������ )
 * @return �ҵ������ı��ڵ�����Ե�ֵ��ʧ�ܷ���0;
 * @remarks ע�⣬��������name�ַ�������һ����"."�������ַ�����ÿһ��
 * "."��ʾ�ڵ�����һ������"a.b.c"��ʾ,��һ����Ϊc�Ľڵ㣬���ĸ��ڵ�Ϊ
 * һ����Ϊb�ڵ�,����Ϊb�Ľڵ�ĸ��ڵ���һ����Ϊa�Ľڵ㡣
 * ����������ʱ��node�ڵ���ӽڵ��п�ʼ�ҡ�
 */
const XMLCh* ___read_xml_node( DOM_Document_Ptr doc, DOM_Node_Ptr node , const XMLCh* name , bool casestr );

/**
 * ��һ��node�ӽڵ��е�һ����Ϊname�Ľڵ�
 * @param[ in ] node dom�ڵ�
 * @param[ in ] name �ڵ������( ���ĸ�ʽΪ xxxx.xxxx.xxx..... )
 * @param[ in ] create �Ҳ���ʱ�Ƿ񴴽�( true ������ false ������ )
 * @param[ in ] casestr �Ƿ�����ַ����Ĵ�Сд( true ���� �� false ������ )
 * @return �ҵ����ؽڵ㣬ʧ�ܷ���0;
 * @see ___read_xml_node
 */
DOM_Node_Ptr ___find_and_create_xml_node( DOM_Node_Ptr node , const XMLCh* name ,bool create , bool casestr );

/**
 * ��һ��node�ӽڵ��е�һ����Ϊname�����Խڵ�
 * @param[ in ] node dom�ڵ�
 * @param[ in ] name ���Խڵ������( ���ĸ�ʽΪ xxxx.xxxx.xxx..... )
 * @param[ in ] create �Ҳ���ʱ�Ƿ񴴽�( true ������ false ������ )
 * @param[ in ] casestr �Ƿ�����ַ����Ĵ�Сд( true ���� �� false ������ )
 * @return �ҵ��������Խڵ㣬ʧ�ܷ���0;
 * @see ___read_xml_node
 */
DOM_Node_Ptr ___find_and_create_xml_attr_node( DOM_Node_Ptr node , const XMLCh* name ,bool create , bool casestr );

/**
 * ��һ��node�ӽڵ��е�һ����Ϊname�Ľڵ�
 * @param[ in ] node dom�ڵ�
 * @param[ in ] name �ڵ������( ���ĸ�ʽΪ xxxx.xxxx.xxx..... )
 * @param[ in ] create �Ҳ���ʱ�Ƿ񴴽�( true ������ false ������ )
 * @param[ in ] casestr �Ƿ�����ַ����Ĵ�Сд( true ���� �� false ������ )
 * @return �ҵ����ؽڵ㣬ʧ�ܷ���0;
 * @see ___read_xml_node
 */
DOM_Node_Ptr ___find_and_create_xml_node( DOM_Node_Ptr node , const char* name ,bool create , bool casestr );

/**
 * ��һ��node�ӽڵ��е�һ����Ϊname�����Խڵ�
 * @param[ in ] node dom�ڵ�
 * @param[ in ] name ���Խڵ������( ���ĸ�ʽΪ xxxx.xxxx.xxx..... )
 * @param[ in ] create �Ҳ���ʱ�Ƿ񴴽�( true ������ false ������ )
 * @param[ in ] casestr �Ƿ�����ַ����Ĵ�Сд( true ���� �� false ������ )
 * @return �ҵ��������Խڵ㣬ʧ�ܷ���0;
 * @see ___read_xml_node
 */
DOM_Node_Ptr ___find_and_create_xml_attr_node( DOM_Node_Ptr node , const char* name ,bool create , bool casestr );

/**
 * ��node�ӽڵ��е�һ����Ϊname�Ľڵ��µ��ı��ڵ�ֵ��Ϊvalue(û�оʹ���һ��)
 * @param[ in ] node dom�ڵ�
 * @param[ in ] name �ڵ������( ���ĸ�ʽΪ xxxx.xxxx.xxx..... )
 * @param[ in ] casestr �Ƿ�����ַ����Ĵ�Сд( true ���� �� false ������ )
 * @return �ɹ�����0��ʧ�ܷ��ط�0
 * @see ___read_xml_node
 */
int ___write_xml_text_node( DOM_Node_Ptr node ,const XMLCh* name , const XMLCh* value , bool casestr );

/**
 * ��node�ӽڵ��е�һ����Ϊname�Ľڵ��µ����Խڵ�ֵ��Ϊvalue(û�оʹ���һ��)
 * @param[ in ] node dom�ڵ�
 * @param[ in ] name �ڵ������( ���ĸ�ʽΪ xxxx.xxxx.xxx..... )
 * @param[ in ] casestr �Ƿ�����ַ����Ĵ�Сд( true ���� �� false ������ )
 * @return �ɹ�����0��ʧ�ܷ��ط�0
 * @see ___read_xml_node
 */
int ___write_xml_attr_node( DOM_Node_Ptr node ,const XMLCh* name , const XMLCh* value , bool casestr );

/**
 * �ж�node�ڵ�������Ƿ����ָ�����ַ���
 * @param[ in ] node �ڵ�
 * @param[ in ] name �ڵ������( ���ĸ�ʽΪ xxxx.xxxx.xxx..... )
 * @param[ in ] casestr �Ƿ�����ַ����Ĵ�Сд( true ���� �� false ������ )
 * @return ���ڷ���1��С�ڷ���-1�����ڷ���0;
 */
int ___compare_node_name( DOM_Node_Ptr node ,const char* name , bool casestr );


/**
 * ����ǰ�ڵ�����Ϊname���ı��ڵ�ֵ
 * @param[ in ] node dom�ڵ�
 * @param[ in ] name �ڵ������( ���ĸ�ʽΪ xxxx.xxxx.xxx..... )
 * @param[ out ] buffer ����ı��ڵ�ֵ�Ļ���
 * @param[ in/out ] buffer ����ʱΪ����ı��ڵ�ֵ�Ļ���ĳ��ȣ�����ȡ�õ��ı��ڵ�ֵ�ĳ���
 * @param[ in ] casestr �Ƿ�����ַ����Ĵ�Сд( true ���� �� false ������ )
 * @return �ɹ�����0��ʧ�ܷ��ط�0
 * @see ___read_xml_node
 */
int ___read_xml_text_node( DOM_Node_Ptr node ,const XMLCh* name , char* buffer , size_t& length ,bool casestr );

/**
 * ����ǰ�ڵ�����Ϊname�����Խڵ�ֵ
 * @param[ in ] node dom�ڵ�
 * @param[ in ] name �ڵ������( ���ĸ�ʽΪ xxxx.xxxx.xxx..... )
 * @param[ out ] buffer ����ı��ڵ�ֵ�Ļ���
 * @param[ in/out ] buffer ����ʱΪ����ı��ڵ�ֵ�Ļ���ĳ��ȣ�����ȡ�õ��ı��ڵ�ֵ�ĳ���
 * @param[ in ] casestr �Ƿ�����ַ����Ĵ�Сд( true ���� �� false ������ )
 * @return �ɹ�����0��ʧ�ܷ��ط�0
 * @see ___read_xml_node
 */
int ___read_xml_attr_node( DOM_Node_Ptr node ,const XMLCh* name , char* buffer , size_t& length , bool casestr );

/**
 * ����ǰ�ڵ�����Ϊname���ı��ڵ�ֵ
 * @param[ in ] node dom�ڵ�
 * @param[ in ] name �ڵ������( ���ĸ�ʽΪ xxxx.xxxx.xxx..... )
 * @param[ out ] buffer ����ı��ڵ�ֵ�Ļ���
 * @param[ in/out ] buffer ����ʱΪ����ı��ڵ�ֵ�Ļ���ĳ��ȣ�����ȡ�õ��ı��ڵ�ֵ�ĳ���
 * @param[ in ] casestr �Ƿ�����ַ����Ĵ�Сд( true ���� �� false ������ )
 * @return �ɹ�����0��ʧ�ܷ��ط�0
 * @see ___read_xml_node
 */
int read_xml_text_node( DOM_Node_Ptr node ,const char* name , char* buffer , size_t& length ,bool casestr );

/**
 * ����ǰ�ڵ�����Ϊname�����Խڵ�ֵ
 * @param[ in ] node dom�ڵ�
 * @param[ in ] name �ڵ������( ���ĸ�ʽΪ xxxx.xxxx.xxx..... )
 * @param[ out ] buffer ����ı��ڵ�ֵ�Ļ���
 * @param[ in/out ] buffer ����ʱΪ����ı��ڵ�ֵ�Ļ���ĳ��ȣ�����ȡ�õ��ı��ڵ�ֵ�ĳ���
 * @param[ in ] casestr �Ƿ�����ַ����Ĵ�Сд( true ���� �� false ������ )
 * @return �ɹ�����0��ʧ�ܷ��ط�0
 * @see ___read_xml_node
 */
int read_xml_attr_node( DOM_Node_Ptr node ,const char* name , char* buffer , size_t& length , bool casestr );

_bt_xml_end

#endif // _XML_H_