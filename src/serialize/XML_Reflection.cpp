// XML_Reflection.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "xml_reflection.h"

_bt_serialize_begin

XML_Reflection::XML_Reflection(void)
: edit_( true )
, edited_( false )
{
}

XML_Reflection::~XML_Reflection(void)
{
}

const std::list< std::string >& XML_Reflection::get_MemberName() const
{
	return member_;
}

const char* XML_Reflection::get_Member( const char* name ) const
{
	assoc_container_type::const_iterator it = member_node_map_.find( name );
	if( it == member_node_map_.end() )
		return 0;
	if( it->second == 0 )
		return 0;
	const XMLCh* value = it->second->getNodeValue();
	if( value == 0 )
		return 0;

	unsigned int len = XERCES_CPP_NAMESPACE_QUALIFIER XMLString::stringLen( value ) ;
	value_str_.resize( len + 10 );
	XERCES_CPP_NAMESPACE_QUALIFIER XMLString::transcode( value, &value_str_[0], len + 5 ); 
	return (&value_str_[ 0 ]);
}

bool XML_Reflection::set_Member( const char* name , const char* value )
{
	if( !edit_ )
		return false;

	assoc_container_type::const_iterator it = member_node_map_.find( name );
	if( it == member_node_map_.end() )
		return false;
	if( it->second == 0 )
		return false;
	try
	{
		XERCES_CPP_NAMESPACE_QUALIFIER DOMString str( value );
		it->second->setData( str.rawBuffer() );
		edited_ = true;
		return true;
	}
	catch( ... )
	{
	}

	return false;
}

struct TreeWalker
{
	TreeWalker( std::list< std::string >* member, XML_Reflection::assoc_container_type* member_node_map )
		: member_( member )
		, member_node_map_( member_node_map )
	{
	}
	std::list< std::string >* member_;
	XML_Reflection::assoc_container_type* member_node_map_;
	std::string str;
	bool walk( XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* root )
	{
		bool ret = true;
		for( XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* node = root->getFirstChild() ;
			node != 0 && ret ; node = node->getNextSibling( ) )
		{
			if( node ->getNodeType() != XERCES_CPP_NAMESPACE_QUALIFIER DOMNode::ELEMENT_NODE )
				continue;
			XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* child = node->getFirstChild( );
			if( child == 0 )
				continue;
			if( child->getNodeType() == XERCES_CPP_NAMESPACE_QUALIFIER DOMNode::TEXT_NODE )
			{
				const XMLCh* nodename = node->getNodeName();
				if( nodename != 0 )
				{
					unsigned int len = XERCES_CPP_NAMESPACE_QUALIFIER XMLString::stringLen( nodename ) ;
					std::vector< char > value_str_( len + 10 );
					XERCES_CPP_NAMESPACE_QUALIFIER XMLString::transcode( nodename, &value_str_[0], len + 5 );
					std::string name = str;

					name += &value_str_[ 0 ];
					member_->push_back( name );
					member_node_map_->insert( std::make_pair( member_->rbegin( )->c_str(), ( XERCES_CPP_NAMESPACE_QUALIFIER DOMText* )child ) );
				}
			}
			else if( child->getNodeType() == XERCES_CPP_NAMESPACE_QUALIFIER DOMNode::ELEMENT_NODE )
			{
				const XMLCh* nodename = node->getNodeName();
				if( nodename != 0 )
				{
					unsigned int len = XERCES_CPP_NAMESPACE_QUALIFIER XMLString::stringLen( nodename ) ;
					std::vector< char > value_str_( len + 10 );
					XERCES_CPP_NAMESPACE_QUALIFIER XMLString::transcode( nodename, &value_str_[0], len + 5 );

				TreeWalker walker( member_, member_node_map_ );
				walker.str = str;
				walker.str += &value_str_[ 0 ];
				walker.str += ".";
				ret = walker.walk( node );

				}

			}

		}
		return ret;		
	}
};

bool XML_Reflection::createmap( XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* root )
{
	if( root == 0 )
		return false;
	TreeWalker walker( &member_,&member_node_map_ );
	return walker.walk( root );
}

_bt_serialize_end

