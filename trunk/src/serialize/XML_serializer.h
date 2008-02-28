
/**
 * -*- C++ -*-
 * -------------------------------------------------------------------------------
 * - ¤╭⌒╮ ╭⌒╮		            XML_serializer.h,v 1.0 2005/03/11 11:33:34
 *  ╱◥██◣ ╭╭ ⌒╮
 * ︱田︱田田| ╰------
 * -------------------------------------------------------------------------------
 */

#ifndef _XML_serializer_H_
#define _XML_serializer_H_

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/deprecated/DOM.hpp>
#include <xercesc/dom/deprecated/DOMString.hpp>
#include <xercesc/util/XMLUniDefs.hpp>
#include "serialize2.h"
#include "serialize_def.h"
#include "framework/BT_Ptr.h"
#include "util/tstring.h"
#include <stack>
#include <iostream>
#include "xml/xml_helper.h"

_bt_serialize_begin

#define XMLNODESIZENAME "xmlnodesize"

/**
 * @brief XML_serializer xml序列化类
 * 本类继承序列化接口下来的，它将一个可序列化的类序列化到一个dom模型中。
 */
class XML_serializer : public serialize_ostream_base
{
public:

	XML_serializer( XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* node )
		: node_( 0 )
		, document_( 0 )
	{
		init( node );
	}

	virtual ~XML_serializer(void)
	{
	}

	bool open(const tchar* ClassName)
	{
		return open( ClassName , -1 );
	}

	bool open(const tchar* ClassName, const size_t& size)
	{
		XERCES_CPP_NAMESPACE_QUALIFIER DOMString name( ClassName );

		BT_Scope_Ptr< XERCES_CPP_NAMESPACE_QUALIFIER DOMElement > aNode =
			document_->createElement( name.rawBuffer() );
		if( aNode.get() == 0 )
			return false;

		if( size != -1 )
		{
			XERCES_CPP_NAMESPACE_QUALIFIER DOMString attrstr( XMLNODESIZENAME );
#pragma pack(push,8)
#pragma warning(push,3)
 #pragma warning(disable: 4267)
			XERCES_CPP_NAMESPACE_QUALIFIER DOMString attrvalue( convertIntegerToString( size ).c_str() );
 #pragma warning(default: 4267)
#pragma warning(pop)
#pragma pack(pop)
			aNode ->setAttribute( attrstr.rawBuffer() ,attrvalue.rawBuffer() );
		}

		if( node_->appendChild( aNode.get() ) == 0 )
			return false;
		//XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* tmp_node = aNode.release();
		node_ = aNode.release();//tmp_node;
		return true;
	}

	bool close(const tchar* ClassName)
	{
		XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* aNode =	node_->getParentNode();
		if( aNode == 0 )
			return false;
		node_ = aNode;
		return true;
	}

	template< typename T >
		bool write_( const T& t, const tchar* fieldname  )
	{
		if( node_ == 0 )
			return false;

		try{
			BT_Scope_Ptr< XERCES_CPP_NAMESPACE_QUALIFIER DOMNode > aNode(	
				document_->createElement( XERCES_CPP_NAMESPACE_QUALIFIER DOMString( fieldname ).rawBuffer() ) );
			if( aNode.get() == 0 )
				return false;
			node_->appendChild( aNode.get() );
			XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* node = aNode.release();

			XERCES_CPP_NAMESPACE_QUALIFIER DOMString str(  convertIntegerToString( t ).c_str() );

			BT_Scope_Ptr< XERCES_CPP_NAMESPACE_QUALIFIER DOMText > textNode(
				document_->createTextNode( str.rawBuffer() ) );
			if( textNode.get() == 0 )
				return false;
			if( node->appendChild(textNode.get() ) == 0 )	
				return false;
			textNode.release();
			return true;
		}
		catch( ... )
		{
		}
		return false;
	}
	template< typename T >
		bool write_str( const T& t, const tchar* fieldname  )
	{
		if( node_ == 0 )
			return false;

		try{
			BT_Scope_Ptr< XERCES_CPP_NAMESPACE_QUALIFIER DOMNode > aNode(	
				document_->createElement( XERCES_CPP_NAMESPACE_QUALIFIER DOMString( fieldname ).rawBuffer() ) );
			if( aNode.get() == 0 )
				return false;
			node_->appendChild( aNode.get() );
			XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* node = aNode.release();

			XERCES_CPP_NAMESPACE_QUALIFIER DOMString str( t.c_str() );

			BT_Scope_Ptr< XERCES_CPP_NAMESPACE_QUALIFIER DOMText > textNode(
				document_->createTextNode( str.rawBuffer() ) );
			if( textNode.get() == 0 )
				return false;
			if( node->appendChild(textNode.get() ) == 0 )	
				return false;
			textNode.release();
			return true;
		}
		catch( ... )
		{
		}
		return false;
	}
	bool write(const bool& t, const tchar* fieldname = "bool")
	{
		return write_( t, fieldname );
	}

	bool write(const char& t, const tchar* fieldname = "char")
	{
		return write_( t, fieldname );
	}
	bool write(const short& t, const tchar* fieldname = "short")
	{
		return write_( t, fieldname );
	}
	bool write(const int& t, const tchar* fieldname = "int")
	{
		return write_( t, fieldname );
	}
	bool write(const long& t, const tchar* fieldname = "long")
	{
		return write_( t, fieldname );
	}

	bool write(const __int64& t, const tchar* fieldname = "__int64")
	{
		return write_( t, fieldname );
	}
	bool write(const unsigned char& t, const tchar* fieldname = "unsignedchar")
	{
		return write_( t, fieldname );
	}
	bool write(const unsigned short& t, const tchar* fieldname = "unsingedshort")
	{
		return write_( t, fieldname );
	}

	bool write(const unsigned int& t, const tchar* fieldname = "unsignedint")
	{
		return write_( t, fieldname );
	}
	bool write(const unsigned long& t, const tchar* fieldname = "unsignedlong")
	{
		return write_( t, fieldname );
	}

	bool write(const unsigned __int64& t, const tchar* fieldname = "unsigned__int64")
	{
		return write_( t, fieldname );
	}

	bool write(const  double& t, const tchar* fieldname = "double")
	{
		return write_( t, fieldname );
	}
	bool write(const float& t, const tchar* fieldname = "float")
	{
		return write_( t, fieldname );
	}
	bool write(const tstring& t, const tchar* fieldname = "string")
	{
		return write_str( t, fieldname );
	}

protected:

	XML_serializer( )
		: document_( 0 )
		, node_( 0 )
	{
	}

	void init( XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* node )
	{
		node_ = node;
		if( node_ == 0 )
			throw( std::runtime_error( "XML_serializer打开根节点失败" ) );
		document_ = node_->getOwnerDocument();
		if( document_ == 0 )
			throw( std::runtime_error( "XML_serializer的document对象不能为空" ) );
	}
private:

	XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument*  document_;
	XERCES_CPP_NAMESPACE_QUALIFIER DOMNode*       node_;	
};

//#define XMLOUT( NODE )	if( NODE != 0 ){	char* coutstring = XERCES_CPP_NAMESPACE_QUALIFIER DOMString( NODE -> getNodeName() ).transcode(); \
//	std::cout << "open"<< coutstring << std::endl; }
//
//#define CXMLOUT( NODE )		if( NODE != 0 ){ char* coutstring = XERCES_CPP_NAMESPACE_QUALIFIER DOMString( NODE -> getNodeName() ).transcode(); \
//	std::cout << "Close" << coutstring << std::endl; }

#define XMLOUT( NODE )
#define CXMLOUT( NODE )

/**
 * @brief XML_deserializer xml反序列化类
 * 本类继承反序列化接口下来的，它将一个可序列化的类从一个dom模型中读从来。
 */
class XML_deserializer : public serialize_istream_base
{
public:
	XML_deserializer( XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* node )
		: document_( 0 )
		, node_( node )
		, isjump_( true )
	{
		init( node );
	}

	~XML_deserializer(void)
	{
		node_stack_.pop();
	}
	
	XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* find_child_node( const XERCES_CPP_NAMESPACE_QUALIFIER DOMString& str
		,XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* node )
	{
		XERCES_CPP_NAMESPACE_QUALIFIER DOMNodeList* nodes = node->getChildNodes();
		unsigned int l = nodes->getLength();
		XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* aNode = 0;
		for( unsigned int i = 0; i < l ; i ++ )
		{
			XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* tmp = nodes->item( i );
			if( tmp == 0 )
				continue;
			if( tmp->getNodeType() != XERCES_CPP_NAMESPACE_QUALIFIER DOMNode:: ELEMENT_NODE	
				|| ( XERCES_CPP_NAMESPACE_QUALIFIER XMLString::compareIString( str.rawBuffer(), tmp->getNodeName() ) != 0 ) )
				continue;
			aNode = tmp;
			break;
		}
		return aNode;
	}


	bool open(const tchar* ClassName)
	{
		XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* aNode = node_stack_.top().second;
		if( aNode != 0 )
		{
			XERCES_CPP_NAMESPACE_QUALIFIER DOMString str( ClassName );
			for( ; aNode != 0 ; aNode = aNode->getNextSibling() )
			{
				if( aNode->getNodeType() != XERCES_CPP_NAMESPACE_QUALIFIER DOMNode::ELEMENT_NODE )
					continue;
				if( XERCES_CPP_NAMESPACE_QUALIFIER XMLString::compareIString( str.rawBuffer(), aNode->getNodeName() ) == 0 )
					break;
			}
			if( aNode == 0 )
				return false;

			node_ = aNode;
			XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* next = node_->getNextSibling();
			node_stack_.top().second = next;
			if( next == 0 )
				node_stack_.top().first = 0;
			node_stack_.push( std::make_pair( node_, ( XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* )0 ) );
			XMLOUT( node_ );
			return true;
		}
		if( node_ == 0 || !node_->hasChildNodes() )
			return false;
		XERCES_CPP_NAMESPACE_QUALIFIER DOMString str( ClassName );
		aNode = find_child_node( str,node_ );										
		if( aNode == 0 )
			return false;
		node_ = aNode;
		node_stack_.push( std::make_pair( node_, ( XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* )0 ) );
		XMLOUT( node_ );
		return true;
	}

	bool getListSize( XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* Node , size_t& size )
	{
		if( Node == 0 )
			return false;

		if( Node->getNodeType() != XERCES_CPP_NAMESPACE_QUALIFIER DOMNode::ELEMENT_NODE )
			return false;
		XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* de = ( XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* ) Node;
		XERCES_CPP_NAMESPACE_QUALIFIER DOMString atrrname( XMLNODESIZENAME );
		XERCES_CPP_NAMESPACE_QUALIFIER DOMAttr* attr = de->getAttributeNode( atrrname.rawBuffer() );
		if( attr == 0 )
			return false;
		const XMLCh* v = attr->getNodeValue();
		if( v == 0 )
			return false;
		_bt_xml StrX x( v );
		size = 0;
		if( x.localForm() == 0 )
			return false;
		size = convertStringToInteger< size_t >( x.localForm() );
		return true;
	}

	bool open(const tchar* ClassName, size_t& size)
	{
//		#define XMLNODESIZENAME "xmlnodesize"

		XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* aNode = node_stack_.top().second;
		if( aNode != 0 )
		{
			XERCES_CPP_NAMESPACE_QUALIFIER DOMString str( ClassName );
			for( ; aNode != 0 ; aNode = aNode->getNextSibling() )
			{
				if( aNode->getNodeType() != XERCES_CPP_NAMESPACE_QUALIFIER DOMNode::ELEMENT_NODE )
					continue;
				if( XERCES_CPP_NAMESPACE_QUALIFIER XMLString::compareIString( str.rawBuffer(), aNode->getNodeName() ) == 0 )
					break;					
			}
			if( aNode == 0 )
				return false;

			node_ = aNode;
			node_stack_.top().second = node_->getNextSibling();
			node_stack_.push( std::make_pair( node_, ( XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* )0 ) );

			XMLOUT( node_ );
			return true; //getListSize( node_, size );
		}

		if( node_ == 0 || !node_->hasChildNodes() )
			return false;
		
		XERCES_CPP_NAMESPACE_QUALIFIER DOMString str( ClassName );
		aNode = find_child_node( str, node_ );
		if( aNode == 0 )																
			return false;
		node_ = aNode;
		node_stack_.push( std::make_pair( node_, node_->getFirstChild() ) );
		XMLOUT( node_ );
		return true;
	}

	bool close(const tchar* ClassName)
	{
			CXMLOUT( node_ );
		node_stack_.pop();
		node_ = node_stack_.top().first;
	
		return true;
	}

	template< typename T >
	bool read_( T& t, const tchar* fieldname )
	{
		XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* aNode = node_stack_.top().second;
		if( aNode != 0 )
		{
			XERCES_CPP_NAMESPACE_QUALIFIER DOMString str( fieldname );
			for( ; aNode != 0 ; aNode = aNode->getNextSibling() )
			{
				if( aNode->getNodeType() != XERCES_CPP_NAMESPACE_QUALIFIER DOMNode::ELEMENT_NODE )
					continue;
				if( XERCES_CPP_NAMESPACE_QUALIFIER XMLString::compareIString( str.rawBuffer(), aNode->getNodeName() ) == 0 )
					break;					
			}
			if( aNode == 0 )
				return false;

			XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* next = aNode->getNextSibling();
			node_stack_.top().second = next;
			if( next == 0 )
			{
				node_stack_.top().first = 0;
				node_ = 0;
			}
		}

		if( aNode == 0 )
		{
			if( node_ == 0 || !node_->hasChildNodes() )
				return false;
			XERCES_CPP_NAMESPACE_QUALIFIER DOMString str( fieldname );
			aNode = find_child_node( str, node_ );
			if( aNode == 0 && isjump_ )
				return true;
		}
		
		if( aNode == 0 )
			return false;
		aNode = aNode->getFirstChild();
		if( aNode == 0 )
			return true;

		_bt_xml StrX sx( aNode->getNodeValue() );
		//XERCES_CPP_NAMESPACE_QUALIFIER DOMString value(  );
		//std::vector< char > cc( value.length() + 3,'\0' );
		//XERCES_CPP_NAMESPACE_QUALIFIER XMLString::transcode( value.rawBuffer() , &cc[0], value.length() + 2 );
		if( sx.localForm() != 0 )
		t = convertStringToInteger< T >( sx.localForm() );
		return true;
	}

	template< typename T >
		bool read_str( T& t, const tchar* fieldname )
	{
		XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* aNode = node_stack_.top().second;
		if( aNode != 0 )
		{
			XERCES_CPP_NAMESPACE_QUALIFIER DOMString str( fieldname );
			for( ; aNode != 0 ; aNode = aNode->getNextSibling() )
			{
				if( aNode->getNodeType() != XERCES_CPP_NAMESPACE_QUALIFIER DOMNode::ELEMENT_NODE )
					continue;
				if( XERCES_CPP_NAMESPACE_QUALIFIER XMLString::compareIString( str.rawBuffer(), aNode->getNodeName() ) == 0 )
					break;					
			}
			if( aNode == 0 )
				return false;

			XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* next = aNode->getNextSibling();
			node_stack_.top().second = next;
			if( next == 0 )
			{
				node_stack_.top().first = 0;
				node_ = 0;
			}
		}

		if( aNode == 0 )
		{
			if( node_ == 0 || !node_->hasChildNodes() )
				return false;
			XERCES_CPP_NAMESPACE_QUALIFIER DOMString str( fieldname );
			aNode = find_child_node( str, node_ );
			if( aNode == 0 && isjump_ )
				return true;
		}

		if( aNode == 0 )
			return false;
				aNode = aNode->getFirstChild();
		if( aNode == 0 )
			return true;
		_bt_xml StrX sx( aNode->getNodeValue() );
		//XERCES_CPP_NAMESPACE_QUALIFIER DOMString value(  );
		//std::vector< char > cc( value.length() + 3,'\0' );
		//XERCES_CPP_NAMESPACE_QUALIFIER XMLString::transcode( value.rawBuffer() , &cc[0], value.length() + 2 );
		if( sx.localForm() != 0 )
			t = sx.localForm();
		return true;
	}
	bool read( bool& t, const tchar* fieldname = "bool")
	{
		return read_( t, fieldname );
	}
	
	bool read( char& t, const tchar* fieldname = "char")
	{
		return read_( t, fieldname );
	}

	bool read( short& t, const tchar* fieldname = "short")
	{
		return read_( t, fieldname );
	}

	bool read( int& t, const tchar* fieldname = "int")
	{
		return read_( t, fieldname );
	}
	bool read( long& t, const tchar* fieldname = "long")
	{
		return read_( t, fieldname );
	}
	bool read( __int64& t, const tchar* fieldname = "__int64")
	{
		return read_( t, fieldname );
	}
	bool read( unsigned char& t, const tchar* fieldname = "unsignedchar")
	{
		return read_( t, fieldname );
	
	}
	bool read( unsigned short& t, const tchar* fieldname = "unsingedshort")
	{
		return read_( t, fieldname );
	}
	bool read( unsigned int& t, const tchar* fieldname = "unsignedint")
	{
		return read_( t, fieldname );
	}

	bool read( unsigned long& t, const tchar* fieldname = "unsignedlong")
	{
		return read_( t, fieldname );
	}
	bool read( unsigned __int64& t, const tchar* fieldname = "unsigned__int64")
	{
		return read_( t, fieldname );
	}

	bool read( double& t, const tchar* fieldname = "double")
	{
		return read_( t, fieldname );
	}

	bool read( float& t, const tchar* fieldname = "float")
	{
		return read_( t, fieldname );
	}

	bool read( tstring& t, const tchar* fieldname = "string")
	{
		return read_( t, fieldname );
	}

	bool read( string_helper_base2& t, const tchar* fieldname = "string")
	{
		t.clear();
		return read_str( t, fieldname );	
	}

protected:

	XML_deserializer( )
	: document_( 0 )
	, node_( 0 )
	{
	}

	void init( XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* node )
	{
		node_ = node;
		if( node_ == 0 )
			throw( std::runtime_error( "XML_deserializer打开根节点失败" ) );
		document_ = node_->getOwnerDocument();
		if( document_ == 0 )
			throw( std::runtime_error( "XML_deserializer的document对象不能为空" ) );
		node_stack_.push( std::make_pair( node_, ( XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* ) 0 ) );
	}

private:

	bool isjump_;

	XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument*  document_;
	XERCES_CPP_NAMESPACE_QUALIFIER DOMNode*       node_;
	std::stack < std::pair< XERCES_CPP_NAMESPACE_QUALIFIER DOMNode*,XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* >  > node_stack_;
};

_bt_serialize_end

#endif // _XML_serializer_H_

