
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

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "config_serializing.h"
#include "jomoo/string.hpp"

#ifndef XERCES_XML

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/deprecated/DOM.hpp>
#include <xercesc/dom/deprecated/DOMString.hpp>
#include <xercesc/util/XMLUniDefs.hpp>


_serializing_begin

#define _XERCES XERCES_CPP_NAMESPACE_QUALIFIER;

/**
 * @brief XML_serializer xml序列化类
 * 本类继承序列化接口下来的，它将一个可序列化的类序列化到一个dom模型中。
 */
 template< typename T >
class XML_serializer : T
{
public:

	XML_serializer( _XERCES DOMNode* node )
		: node_( 0 )
		, document_( 0 )
	{
		init( node );
	}

	virtual ~XML_serializer(void)
	{
	}

	bool open(serialize_context& context, const tchar* className, const tchar* field)
	{
		_XERCES DOMString name( ClassName );

		BT_Scope_Ptr< _XERCES DOMElement > aNode =
			document_->createElement( name.rawBuffer() );
		if( aNode.get() == 0 )
			return false;

		if( size != -1 )
		{
			_XERCES DOMString attrstr( XMLNODESIZENAME );

			_XERCES DOMString attrvalue( convertIntegerToString( size ).c_str() );
			aNode ->setAttribute( attrstr.rawBuffer() ,attrvalue.rawBuffer() );
		}

		if( node_->appendChild( aNode.get() ) == 0 )
			return false;

		node_ = aNode.release();//tmp_node;
		return true;
	}

	bool close( serialize_context& context )
	{
		_XERCES DOMNode* aNode =	node_->getParentNode();
		if( aNode == 0 )
			return false;

		node_ = aNode;
		return true;
	}
	
	/**
	 * 流是否正常
	 */
	bool is_good() const
	{
		return _is_good;
	}

	/**
	 * 取得最后一次错误描述
	 */
	const tstring& last_error() const
	{
		return _last_error;
	}

	/**
	 * 设置最后一次错误描述
	 */
	void last_error( const tstring& err )
	{
		_is_good = false;
		_last_error = err;
	}

protected:

	XML_serializer( )
		: document_( 0 )
		, node_( 0 )
		, _is_good( true )
	{
	}

	void init( _XERCES DOMNode* node )
	{
		node_ = node;
		if( 0 == node_ )
			throw( std::runtime_error( "XML_serializer打开根节点失败" ) );

		document_ = node_->getOwnerDocument();
		if( 0 == document_ )
			throw( std::runtime_error( "XML_serializer的document对象不能为空" ) );
	}

	bool _is_good;
	tstring _last_error;

private:

	_XERCES DOMDocument*  document_;
	_XERCES DOMNode*       node_;	
};

class XML_Writer : XML_serializer< serialize_writer >
{
public:

	template< typename T >
		bool write_( const T& t, const tchar* fieldname  )
	{
		if( node_ == 0 )
		{
			last_error( _T("内部错误 - 节点为null!") )
			return false;
		}

		try{
			BT_Scope_Ptr< _XERCES DOMNode > aNode(	
				document_->createElement( _XERCES DOMString( fieldname ).rawBuffer() ) );
			if( aNode.get() == 0 )
				return false;
			node_->appendChild( aNode.get() );
			_XERCES DOMNode* node = aNode.release();

			_XERCES DOMString str(  convertIntegerToString( t ).c_str() );

			BT_Scope_Ptr< _XERCES DOMText > textNode(
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

	bool write(serialize_context& context, bool t, const tchar* fieldName )
	{
		return write_(context, t, fieldname );
	}
	bool write(serialize_context& context, int8_t t, const tchar* fieldName )
	{
		return write_(context, t, fieldname );
	}
	bool write(serialize_context& context, int16_t t, const tchar* fieldName )
	{
		return write_(context, t, fieldname );
	}
	bool write(serialize_context& context, int32_t t, const tchar* fieldName)
	{
		return write_(context, t, fieldname );
	}
	bool write(serialize_context& context, int64_t t, const tchar* fieldName)
	{
		return write_(context, t, fieldname );
	}
	bool write(serialize_context& context, const void* blob, size_t len, const tchar* fieldName)
	{
		return write_str(context, t, fieldname );
	}

};

#define XMLOUT( NODE )
#define CXMLOUT( NODE )

/**
 * @brief XML_deserializer xml反序列化类
 * 本类继承反序列化接口下来的，它将一个可序列化的类从一个dom模型中读从来。
 */
class XML_deserializer : public serialize_istream_base
{
public:
	XML_deserializer( _XERCES DOMNode* node )
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
	
	_XERCES DOMNode* find_child_node( const _XERCES DOMString& str
		,_XERCES DOMNode* node )
	{
		_XERCES DOMNodeList* nodes = node->getChildNodes();
		unsigned int l = nodes->getLength();
		_XERCES DOMNode* aNode = 0;
		for( unsigned int i = 0; i < l ; i ++ )
		{
			_XERCES DOMNode* tmp = nodes->item( i );
			if( tmp == 0 )
				continue;
			if( tmp->getNodeType() != _XERCES DOMNode:: ELEMENT_NODE	
				|| ( _XERCES XMLString::compareIString( str.rawBuffer(), tmp->getNodeName() ) != 0 ) )
				continue;
			aNode = tmp;
			break;
		}
		return aNode;
	}


	bool open(const tchar* ClassName)
	{
		_XERCES DOMNode* aNode = node_stack_.top().second;
		if( aNode != 0 )
		{
			_XERCES DOMString str( ClassName );
			for( ; aNode != 0 ; aNode = aNode->getNextSibling() )
			{
				if( aNode->getNodeType() != _XERCES DOMNode::ELEMENT_NODE )
					continue;
				if( _XERCES XMLString::compareIString( str.rawBuffer(), aNode->getNodeName() ) == 0 )
					break;
			}
			if( aNode == 0 )
				return false;

			node_ = aNode;
			_XERCES DOMNode* next = node_->getNextSibling();
			node_stack_.top().second = next;
			if( next == 0 )
				node_stack_.top().first = 0;
			node_stack_.push( std::make_pair( node_, ( _XERCES DOMNode* )0 ) );
			XMLOUT( node_ );
			return true;
		}
		if( node_ == 0 || !node_->hasChildNodes() )
			return false;
		_XERCES DOMString str( ClassName );
		aNode = find_child_node( str,node_ );										
		if( aNode == 0 )
			return false;
		node_ = aNode;
		node_stack_.push( std::make_pair( node_, ( _XERCES DOMNode* )0 ) );
		XMLOUT( node_ );
		return true;
	}

	bool getListSize( _XERCES DOMNode* Node , size_t& size )
	{
		if( Node == 0 )
			return false;

		if( Node->getNodeType() != _XERCES DOMNode::ELEMENT_NODE )
			return false;
		_XERCES DOMElement* de = ( _XERCES DOMElement* ) Node;
		_XERCES DOMString atrrname( XMLNODESIZENAME );
		_XERCES DOMAttr* attr = de->getAttributeNode( atrrname.rawBuffer() );
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

		_XERCES DOMNode* aNode = node_stack_.top().second;
		if( aNode != 0 )
		{
			_XERCES DOMString str( ClassName );
			for( ; aNode != 0 ; aNode = aNode->getNextSibling() )
			{
				if( aNode->getNodeType() != _XERCES DOMNode::ELEMENT_NODE )
					continue;
				if( _XERCES XMLString::compareIString( str.rawBuffer(), aNode->getNodeName() ) == 0 )
					break;					
			}
			if( aNode == 0 )
				return false;

			node_ = aNode;
			node_stack_.top().second = node_->getNextSibling();
			node_stack_.push( std::make_pair( node_, ( _XERCES DOMNode* )0 ) );

			XMLOUT( node_ );
			return true; //getListSize( node_, size );
		}

		if( node_ == 0 || !node_->hasChildNodes() )
			return false;
		
		_XERCES DOMString str( ClassName );
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
		_XERCES DOMNode* aNode = node_stack_.top().second;
		if( aNode != 0 )
		{
			_XERCES DOMString str( fieldname );
			for( ; aNode != 0 ; aNode = aNode->getNextSibling() )
			{
				if( aNode->getNodeType() != _XERCES DOMNode::ELEMENT_NODE )
					continue;
				if( _XERCES XMLString::compareIString( str.rawBuffer(), aNode->getNodeName() ) == 0 )
					break;					
			}
			if( aNode == 0 )
				return false;

			_XERCES DOMNode* next = aNode->getNextSibling();
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
			_XERCES DOMString str( fieldname );
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
		//_XERCES DOMString value(  );
		//std::vector< char > cc( value.length() + 3,'\0' );
		//_XERCES XMLString::transcode( value.rawBuffer() , &cc[0], value.length() + 2 );
		if( sx.localForm() != 0 )
		t = convertStringToInteger< T >( sx.localForm() );
		return true;
	}

	template< typename T >
		bool read_str( T& t, const tchar* fieldname )
	{
		_XERCES DOMNode* aNode = node_stack_.top().second;
		if( aNode != 0 )
		{
			_XERCES DOMString str( fieldname );
			for( ; aNode != 0 ; aNode = aNode->getNextSibling() )
			{
				if( aNode->getNodeType() != _XERCES DOMNode::ELEMENT_NODE )
					continue;
				if( _XERCES XMLString::compareIString( str.rawBuffer(), aNode->getNodeName() ) == 0 )
					break;					
			}
			if( aNode == 0 )
				return false;

			_XERCES DOMNode* next = aNode->getNextSibling();
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
			_XERCES DOMString str( fieldname );
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
		//_XERCES DOMString value(  );
		//std::vector< char > cc( value.length() + 3,'\0' );
		//_XERCES XMLString::transcode( value.rawBuffer() , &cc[0], value.length() + 2 );
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

	void init( _XERCES DOMNode* node )
	{
		node_ = node;
		if( node_ == 0 )
			throw( std::runtime_error( "XML_deserializer打开根节点失败" ) );
		document_ = node_->getOwnerDocument();
		if( document_ == 0 )
			throw( std::runtime_error( "XML_deserializer的document对象不能为空" ) );
		node_stack_.push( std::make_pair( node_, ( _XERCES DOMNode* ) 0 ) );
	}

private:

	bool isjump_;

	_XERCES DOMDocument*  document_;
	_XERCES DOMNode*       node_;
	std::stack < std::pair< _XERCES DOMNode*,_XERCES DOMNode* >  > node_stack_;
};

_serializing_end

#endif //XERCES_XML

#endif // _XML_serializer_H_

