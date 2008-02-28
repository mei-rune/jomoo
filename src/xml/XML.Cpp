#include "stdafx.h"
#include "xml.h"
#include "xml_helper.h"
#include <iostream>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/deprecated/DOM.hpp>
#include <xercesc/dom/deprecated/DOMString.hpp>
#include <xercesc/util/XMLUniDefs.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/framework/Wrapper4InputSource.hpp>
#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <vector>
#include <iostream>

_bt_xml_begin

class DOMParseHandlers : public DOMErrorHandler
{
public:
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    DOMParseHandlers();
    ~DOMParseHandlers();

    // -----------------------------------------------------------------------
    //  Implementation of the DOM ErrorHandler interface
    // -----------------------------------------------------------------------

    bool handleError(const DOMError& domError);
    void resetErrors();
};


DOMParseHandlers::DOMParseHandlers()
{
}

DOMParseHandlers::~DOMParseHandlers()
{
}

bool DOMParseHandlers::handleError(const DOMError& domError)
{
	if (domError.getSeverity() == DOMError::DOM_SEVERITY_WARNING)
		std:: cerr << "\nWarning at file ";
    else if (domError.getSeverity() == DOMError::DOM_SEVERITY_ERROR)
        std:: cerr << "\nError at file ";
    else
        std:: cerr << "\nFatal Error at file ";

    std:: cerr << StrX(domError.getLocation()->getURI())
         << ", line " << domError.getLocation()->getLineNumber()
         << ", char " << domError.getLocation()->getColumnNumber()
         << "\n  Message: " << StrX(domError.getMessage()) << std:: endl;

    return true;
}
void DOMParseHandlers::resetErrors()
{
}

DOM_Node_Ptr ___find_child( DOM_Node_Ptr node , const XMLCh* name , int lenght, bool casestr )
{
	for( DOM_Node_Ptr n = node->getFirstChild(); n != 0 ; n = n->getNextSibling() )
	{
		if( casestr )
		{
			if( XMLString::compareNIString( name, n->getNodeName() ,lenght ) == 0 )
				return n;
		}
		else
		{
			if( XMLString::compareNString( name, n->getNodeName() ,lenght ) == 0 )
				return n;
		}
	}
	return 0;
}

DOM_Node_Ptr ___find_child( DOM_Node_Ptr node , const XMLCh* name , bool casestr )
{
	for( DOM_Node_Ptr n = node->getFirstChild(); n != 0 ; n = n->getNextSibling() )
	{
		if( casestr )
		{
			if( XMLString::compareIString( name, n->getNodeName() ) == 0 )
				return n;
		}
		else
		{
			if( XMLString::compareString( name, n->getNodeName() ) == 0 )
				return n;
		}
	}
	return 0;
}

DOM_Node_Ptr find_child( DOM_Node_Ptr node , const tchar* name , bool casestr  )
{
	if( node == 0 || name == 0 )
		return 0;
	DOMString Name( name );

	return ___find_child( node , Name.rawBuffer(), casestr );
}

DOM_Node_Ptr ___find_extent_child( DOM_Node_Ptr node , const XMLCh* name ,int depth ,bool casestr )
{
	if( node == 0 || name == 0 )
		return 0;

	/// 当前节点名是不是等于name;
	if( casestr )
	{
		if( XMLString::compareIString( name, node->getNodeName() ) == 0 )
			return node;
	}
	else
	{
		if( XMLString::compareString( name, node->getNodeName() ) == 0 )
			return node;
	}

	/// 在当前节点的子节点中查找名叫name的节点;
	DOM_Node_Ptr c = ___find_child( node, name , casestr );
	if( c != 0 )
		return c;

	/// 深度不够
	if( depth == 0 )
		return 0;
	depth --;
	for( DOM_Node_Ptr n = node->getFirstChild(); n != 0 ; n = n->getNextSibling() )
	{
		DOM_Node_Ptr child = ___find_extent_child( n , name , depth, casestr );
		if( child != 0 )
			return child;
	}
	return 0;
}

DOM_Node_Ptr find_extent_child( DOM_Node_Ptr node , const tchar* name ,int depth ,bool casestr )
{
	if( node == 0 || name == 0 )
		return 0;
	DOMString Name( name );

	return ___find_extent_child( node , Name.rawBuffer(), depth , casestr );
}

DOM_Node_Ptr ___copy_node( DOM_Document_Ptr doc , DOM_Node_Ptr node )
{
	if( doc == 0 || node == 0 )
		return 0;
	DOM_Node_Ptr n = 0;
	switch( node->getNodeType() )
	{
	case DOM_Node:: ELEMENT_NODE:
		n = doc->createElement( node -> getNodeName() );
		break;
	case DOM_Node:: TEXT_NODE:
		n = doc->createTextNode( node -> getNodeValue() );
		break;
	}
	return n;
}

DOM_Node_Ptr copy_node_tree( DOM_Document_Ptr doc , DOM_Node_Ptr node )
{
	if( node == 0 || doc == 0 )
		return 0;
	
	DOM_Node_Ptr tmp = ___copy_node( doc, node );
	if( tmp == 0 )
		return 0;

	for( DOM_Node_Ptr child = node->getFirstChild(); child != 0 ; child = child -> getNextSibling() )
	{
		DOM_Node_Ptr c = copy_node_tree( doc, child );
		if( c  == 0 )
			continue;
		tmp->appendChild( c );
	}
	return tmp;
}

int merge_xml_tree( DOM_Node_Ptr doc , DOM_Node_Ptr node, bool deep )
{
	if( node == 0 || doc == 0 )
		return ERR_BAD_PARAM;
	
	DOM_Node_Ptr tmp = ___copy_node( doc->getOwnerDocument(), node );
	if( tmp == 0 )
		return -1;
	if( deep )
	{
		for( DOM_Node_Ptr child = node->getFirstChild(); child != 0 ; child = child -> getNextSibling() )
		{
			if( merge_xml_tree( tmp , child, deep ) != 0 )
				return -1;
		}
	}
	doc->appendChild( tmp );
	return 0;
}



DOM_Builder_Ptr ___make_xml_dom_parser( )
{
	// Instantiate the DOM parser.
	static const XMLCh gLS[] = { XERCES_CPP_NAMESPACE_QUALIFIER chLatin_L
		, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_S
		, XERCES_CPP_NAMESPACE_QUALIFIER chNull };

	DOMImplementation *impl = DOMImplementationRegistry::getDOMImplementation(gLS);
	BT_Scope_Ptr< DOMBuilder > parser( (( DOMImplementationLS*)
		impl)->createDOMBuilder( DOMImplementationLS::MODE_SYNCHRONOUS, 0) );

	parser->setFeature(  XMLUni::fgDOMWhitespaceInElementContent , true );
	 
	//parser->setFeature(XMLUni::fgDOMNamespaces, true );
	/*parser->setFeature( XMLUni::fgXercesSchema, true);
	parser->setFeature( XMLUni::fgXercesSchemaFullChecking, true);


	parser->setFeature( XMLUni::fgDOMValidateIfSchema, true);*/

	//parser->setFeature( XMLUni::fgDOMValidation, false);

	//parser->setFeature( XMLUni::fgDOMValidation, true);

	//parser->setFeature( XMLUni::fgDOMDatatypeNormalization, true);

	return parser.release();
}
static const char*  gMemBufId = "prodInfo";

DOM_Document_Ptr ___xml_dom_parse( DOM_Builder_Ptr builder , const void* buf, size_t lenght )
{
	DOMParseHandlers errorHandler;
	builder->setErrorHandler(&errorHandler);

	MemBufInputSource memBufIS( (const XMLByte*)buf
		, lenght
		, gMemBufId
		, false
		);

	Wrapper4InputSource ins( &memBufIS ,false );
	return builder->parse( ins );
}

DOM_Document_Ptr ___xml_dom_parse( DOM_Builder_Ptr builder , const char* filename )
{
	DOMParseHandlers errorHandler;
	builder->setErrorHandler(&errorHandler);
	return builder->parseURI( filename );
}

int xml_dom_parse( XMLDoc& doc , const void* buf, size_t lenght )
{
	DOM_Builder_Ptr parser = ___make_xml_dom_parser( );
	if( parser == 0 )
		return -1;
	doc.parser_.reset( parser );
	doc.doc_ = 0;
	doc.doc_ = ___xml_dom_parse( doc.parser_.get(), buf, lenght );
	if( doc.doc_ == 0 )
		return -1;
	return 0;	
}

int xml_dom_parse( XMLDoc& doc , const char* filename )
{
	DOM_Builder_Ptr parser = ___make_xml_dom_parser( );
	if( parser == 0 )
		return -1;
	doc.parser_ .reset( parser );
	doc.doc_ = 0;
	doc.doc_ = ___xml_dom_parse( doc.parser_.get(), filename );
	if( doc.doc_ == 0 )
		return -1;
	return 0;	
}

DOM_Node_Ptr get_xml_root_node( XMLDoc& doc )
{
	if( doc.doc_ == 0 )
		return 0;
	return doc.doc_->getDocumentElement();
}

const XMLCh* ___read_dom_node( DOM_Node_Ptr node , const XMLCh* name , bool casestr )
{
	if( node == 0 || name == 0 )
		return 0;

	int index = XMLString::indexOf( name , '.' );
	if( index == -1 )
	{
		DOM_Node_Ptr child = ___find_child( node, name , index , casestr );
		if( child == 0 )
		{
			if( !node -> hasAttributes() )
				return 0;
			Attributes_Map_Ptr attrs = node ->getAttributes();
			if( attrs == 0 )
				return 0;
			DOM_Node_Ptr attr = attrs -> getNamedItem( name );
			if( attr == 0 )
				return 0;
			return attr->getNodeValue();	
		}

		for( DOM_Node_Ptr subchild = child->getFirstChild( )
			; subchild != 0 
			; subchild = subchild->getNextSibling() )
		{
			if( subchild -> getNodeType() == DOM_Node::TEXT_NODE )
				return subchild -> getNodeValue();
		}
		return 0;	
	}
	else
	{
		DOM_Node_Ptr child = ___find_child( node, name , index  , casestr );
		if( child == 0 )
			return 0;
		return ___read_dom_node( child, name + index + 1 , casestr );
	}
}

DOM_Node_Ptr ___find_and_create_xml_node(  DOM_Document_Ptr doc, DOM_Node_Ptr node , const XMLCh* name ,bool create , bool casestr )
{
	int index = XMLString::indexOf( name , '.' );
	if( index == -1 )
	{
		DOM_Node_Ptr child = ___find_child( node, name , casestr );
		if( child == 0 && create )
		{
			child = doc -> createElement( name );
			if( child != 0 )
				node -> appendChild( child );
		}
		return child;		
	}
	else
	{
		DOM_Node_Ptr child = ___find_child( node, name , index  , casestr );
		if( child == 0 )
		{
			if( !create )
				return 0;

			std::vector< XMLCh > TagName( index + 10 );
			if( !XMLString::copyNString( &TagName[0], name, index ) )
				return 0;
			TagName[ index + 1 ] = chNull;
			child = doc -> createElement( &TagName[0] );

			if( child == 0 )
				return 0;
			node -> appendChild( child );

		}
		
		return ___find_and_create_xml_node( doc, child, name + index + 1, create, casestr );
	}
}

DOM_Node_Ptr ___find_and_create_xml_attr_node(  DOM_Document_Ptr doc, DOM_Node_Ptr node , const XMLCh* name ,bool create , bool casestr )
{
	int index = XMLString::indexOf( name , '.' );
	if( index != -1 )
	{
		DOM_Node_Ptr child = ___find_child( node, name , index  , casestr );
		if( child == 0 )
		{
			if( !create )
				return 0;

			std::vector< XMLCh > TagName( index + 10 );
			if( !XMLString::copyNString( &TagName[0], name, index ) )
				return 0;
			TagName[ index + 1 ] = chNull;
			child = doc -> createElement( &TagName[0] );

			if( child == 0 )
				return 0;
			node -> appendChild( child );
		}
		return ___find_and_create_xml_node( doc, node, name + index + 1, create, casestr );
	}
	else
	{
		if( !node -> hasAttributes() )
		{
			Attributes_Map_Ptr attrs = node ->getAttributes();
			if( attrs != 0 )
			{
				DOM_Node_Ptr attr = attrs -> getNamedItem( name );
				if( attr != 0 )
					return attr;
			}
		}
		DOM_Attr_Ptr attrnode = doc -> createAttribute( name );
		if( attrnode == 0 )
			return 0;
		node -> appendChild( attrnode );
		return attrnode;
	}
}


DOM_Node_Ptr ___find_and_create_xml_node( DOM_Node_Ptr node , const XMLCh* name ,bool create , bool casestr )
{
	if( node == 0 || name == 0 )
		return 0;
	DOM_Document_Ptr doc = node->getOwnerDocument();
	if( doc == 0 )
		return 0;
	return ___find_and_create_xml_node(doc, node , name,true,casestr );
}

DOM_Node_Ptr ___find_and_create_xml_attr_node( DOM_Node_Ptr node , const XMLCh* name ,bool create , bool casestr )
{
	if( node == 0 || name == 0 )
		return 0;
	DOM_Document_Ptr doc = node->getOwnerDocument();
	if( doc == 0 )
		return 0;
	return ___find_and_create_xml_attr_node(doc, node , name,true,casestr );
}


int ___write_xml_text_node( DOM_Node_Ptr node ,const XMLCh* name , const XMLCh* value , bool casestr )
{
	if( node == 0 || name == 0 )
		return ERR_BAD_PARAM;
	DOM_Document_Ptr doc = node->getOwnerDocument();
	if( doc == 0 )
		return ERR_UNKNOW;
	DOM_Node_Ptr child = ___find_and_create_xml_node(doc, node , name,true,casestr );
	if( child == 0 )
		return ERR_NO_FIND;

	if( value ==0 )
		return ERR_BAD_PARAM;

	for( DOM_Node_Ptr subchild = child->getFirstChild( )
		; subchild != 0 
		; subchild = subchild->getNextSibling() )
	{
		if( subchild -> getNodeType() == DOM_Node::TEXT_NODE )
		{
			subchild -> setNodeValue( value );
			return 0;
		}
	}
	DOM_Text_Ptr textnode = doc -> createTextNode( value );
	if( textnode == 0 )
		return ERR_UNKNOW;
	child ->appendChild( child );
	return 0;
}

int ___write_xml_attr_node( DOM_Node_Ptr node ,const XMLCh* name , const XMLCh* value , bool casestr )
{
	if( node == 0 || name == 0 )
		return ERR_BAD_PARAM;
	DOM_Document_Ptr doc = node->getOwnerDocument();
	if( doc == 0 )
		return ERR_UNKNOW;
	DOM_Node_Ptr child = ___find_and_create_xml_attr_node(doc, node , name,true,casestr );
	if( child == 0 )
		return ERR_NO_FIND;

	if( value ==0 )
		return ERR_BAD_PARAM;

	child -> setNodeValue( value );
	return 0;
}

int ___compare_node_name( DOM_Node_Ptr node ,const char* name , bool casestr )
{
	if( node == 0 )
		return -1;
	else if ( name == 0 )
		return 1;

	DOMString Name( name );
	if( casestr )
	{
		return XMLString::compareIString( Name.rawBuffer(), node->getNodeName() );
	}
	else
	{
		return XMLString::compareString( Name.rawBuffer(), node->getNodeName() );
	}
}


int ___read_xml_text_node( DOM_Node_Ptr node ,const XMLCh* name , char* buffer , size_t& length ,bool casestr )
{
	if( buffer == 0 || length < 1 )
		return -500;
	buffer[ 0 ] = 0;
	size_t len = length -2;
	length = 0;

	DOM_Node_Ptr child = ___find_and_create_xml_node( node, name, false, casestr );
	if( child == 0 )
		return -1;
	child = child->getFirstChild();
	if( child == 0 )
		return -1;
	if( child -> getNodeType() != DOM_Node::TEXT_NODE )
		return -1;
	const XMLCh* ch = child->getNodeValue();
	if( ch != 0 && ! XMLString::transcode( ch, buffer, len ) )
		return -503;
	length = strlen( buffer );
	return 0;		
}

int ___read_xml_attr_node( DOM_Node_Ptr node ,const XMLCh* name , char* buffer , size_t& length , bool casestr )
{
	if( buffer == 0 || length < 1 )
		return -501;
	buffer[ 0 ] = 0;
	size_t len = length-2;
	length = 0;
	DOM_Node_Ptr child = ___find_and_create_xml_attr_node( node, name, false, casestr );
	if( child == 0 )
		return -1;
	const XMLCh* ch = child->getNodeValue();
	if( ch != 0 && ! XMLString::transcode( ch, buffer, len ) )
		return -503;
	length = strlen( buffer );
	return 0;
}


int read_xml_text_node( DOM_Node_Ptr node ,const char* name , char* buffer , size_t& length ,bool casestr )
{
	if( name == 0 )
		return -501;
	DOMString Name( name );
	return ___read_xml_text_node( node, Name.rawBuffer(),buffer, length, casestr );
}

int read_xml_attr_node( DOM_Node_Ptr node ,const char* name , char* buffer , size_t& length , bool casestr )
{
	if( name == 0 )
		return -501;
	DOMString Name( name );
	return ___read_xml_attr_node( node, Name.rawBuffer(),buffer, length, casestr );
}

DOM_Node_Ptr ___find_and_create_xml_node( DOM_Node_Ptr node , const char* name ,bool create , bool casestr )
{
	if( name == 0 )
		return 0;
	DOMString Name( name );
	return ___find_and_create_xml_node( node, Name.rawBuffer(), create , casestr );
}

DOM_Node_Ptr ___find_and_create_xml_attr_node( DOM_Node_Ptr node , const char* name ,bool create , bool casestr )
{
	if( name == 0 )
		return 0;
	DOMString Name( name );
	return ___find_and_create_xml_attr_node( node, Name.rawBuffer(), create , casestr );
}

_bt_xml_end

