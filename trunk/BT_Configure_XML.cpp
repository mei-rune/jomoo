#include "BT_Configure_XML.h"
#include "xml/xml_helper.h"
_bt_begin

BT_Configure_XML_Node::BT_Configure_XML_Node( BT_Configure_Base* parent )
: parentNode_( parent )
{
}

BT_Configure_XML_Node::BT_Configure_XML_Node( const tchar* file_name , BT_Configure_Base* parent)
: parentNode_( parent )
{
	if( _bt_xml xml_dom_parse( xml_, file_name ) != 0 || xml_.doc_ == 0 )
		throw std::runtime_error( "从文件[" + tstring ( file_name ) + "]中载入配置时，xml解析出错" );
	
	init( xml_.doc_->getDocumentElement() );
}

BT_Configure_XML_Node::BT_Configure_XML_Node( const tchar* buf, size_t len , BT_Configure_Base* parent)
: parentNode_( parent )
{
	if( _bt_xml xml_dom_parse( xml_, buf, len ) != 0 )
		throw std::runtime_error( "从内存中载入配置时，xml解析出错" );
	init(xml_.doc_->getDocumentElement() );
}

BT_Configure_XML_Node::BT_Configure_XML_Node( _bt_xml DOM_Node_Ptr node_ , BT_Configure_Base* parent )
: parentNode_( parent )
{
	init( node_ );
}

BT_Configure_XML_Node::~BT_Configure_XML_Node(void)
{
	for( container_type::iterator it = node_map_.begin()
		; it != node_map_.end()
		; it ++ )
		delete (it->second);
	node_map_.clear();
}


bool BT_Configure_XML_Node::open( const tchar* file_name )
{
	for( container_type::iterator it = node_map_.begin()
		; it != node_map_.end()
		; it ++ )
		delete (it->second);
	node_map_.clear();

	if( _bt_xml xml_dom_parse( xml_, file_name ) != 0 )
		return false;
	init( xml_.doc_->getDocumentElement() );
	return true;
}

bool BT_Configure_XML_Node::open( const tchar* buf, size_t len )
{
	for( container_type::iterator it = node_map_.begin()
		; it != node_map_.end()
		; it ++ )
		delete (it->second);
	node_map_.clear();

	if( _bt_xml xml_dom_parse( xml_, buf, len ) != 0 )
		return false;
	init(xml_.doc_->getDocumentElement() );
	return true;
}


void BT_Configure_XML_Node::init( _bt_xml DOM_Node_Ptr node )
{
	if( node == 0 )
		return;
	setName( _bt_xml StrX( node->getNodeName() ).localForm() );
	for( _bt_xml DOM_Node_Ptr n = node->getFirstChild(); n != 0 ; n = n->getNextSibling() )
	{
		if( n->getNodeType() != _bt_xml DOM_Node:: ELEMENT_NODE )
			continue;

		_bt_xml DOM_Node_List_Ptr nodes = n->getChildNodes();
		if( nodes == 0 )
			continue;
		switch( nodes -> getLength() )
		{
		case 0:
			break;
		case 1:
			{
				_bt_xml DOM_Node_Ptr child = nodes->item( 0 );
				if( child == 0 )
					break;
				switch( child->getNodeType() )
				{
				case _bt_xml DOM_Node:: TEXT_NODE:

					{	
						_bt_xml DOM_Text_Ptr text = ( _bt_xml DOM_Text_Ptr )child;
						if( text->isIgnorableWhitespace() )
							break;

						_bt_xml StrX value( child->getNodeValue() );
						_bt_xml StrX name( n->getNodeName() );

						if( isWhiteSpaceString( name.localForm() ) || isWhiteSpaceString( value.localForm() ) )
							break;

						std::auto_ptr< BT_Configure_XML_Text > xml_node(
							new BT_Configure_XML_Text( name.localForm()
							, value.localForm() ,this ) );
						if( appendChild( xml_node.get() ) )
							xml_node.release();
						break;
					}
				case _bt_xml DOM_Node:: ELEMENT_NODE:
					{
						std::auto_ptr< BT_Configure_XML_Node > xml_node ( new BT_Configure_XML_Node( n ,this ) );
						if( appendChild( xml_node.get() ) )
							xml_node.release();
						break;
					}
				}
				break;
			}
		default:
			{
				std::auto_ptr< BT_Configure_XML_Node > xml_node ( new BT_Configure_XML_Node( n ,this ) );
				if( appendChild( xml_node.get() ) )
					xml_node.release();
			}
		}

	}
}

bool BT_Configure_XML_Node::setName( const tchar* name )
{
	if( name == 0 )
		name_.clear();
	else
		name_  = name;
	return true;
}

bool BT_Configure_XML_Node::setValue( const tchar* value )
{
	return false;
}

bool BT_Configure_XML_Node::appendChild( BT_Configure_Base* node )
{
	if( node == 0 )
		return false;
	if( node->getParentNode() != this)
		return false;
	 node_map_.insert( std::make_pair( node->getName(), node ) );
	return true;
}

bool BT_Configure_XML_Node::deleteChild( BT_Configure_Base* node )
{
	if( node == 0 )
		return false;
	container_type::iterator it = node_map_.find( node->getName() );
	if( it == node_map_.end() )
		return false;

	if( it->second != node || it->second == 0 || it->second -> getParentNode() != this )	
		throw std::runtime_error( "BT_Configure_XML_Node > 删除节点时发现迭代器不正确" );

	node_map_.erase( it );
	delete node;
	return true;
}

bool BT_Configure_XML_Node::deleteChild( const tchar* name )
{
	if( name == 0 )
		return false;
	container_type::iterator it = node_map_.find( name );
	if( it == node_map_.end() )
		return false;
	node_map_.erase( it );
	delete it->second;
	return true;
}

const tchar* BT_Configure_XML_Node::getValue() const
{
	return 0;
}

const tchar* BT_Configure_XML_Node::getName() const
{
	return name_.c_str();
}

BT_Configure_Base* BT_Configure_XML_Node::findChild( const tchar* name )
{
	if( name == 0 )
		return 0;
	tstring Header;
	const tchar* Tmp = name;
	while( (*Tmp) != 0 )
	{
		if( *Tmp == '.' )
		{
			if( Header.empty() )
				return findChild( ++Tmp );

			container_type::iterator it = node_map_.find( Header );
			if( it == node_map_.end() )
				return 0;
			if( it->second == 0 )
				return 0;
			return it->second->findChild( ++Tmp );
		}
		Header.append( 1, (*Tmp) );
		Tmp ++;
	}
	container_type::iterator it = node_map_.find( name );
	if( it == node_map_.end() )
		return 0;
	return ( it->second );
}

const BT_Configure_Base* BT_Configure_XML_Node::findChild( const tchar* name ) const
{
	if( name == 0 )
		return 0;
	tstring Header;
	const tchar* Tmp = name;
	while( (*Tmp) != 0 )
	{
		if( *Tmp == '.' )
		{
			if( Header.empty() )
				return findChild( ++Tmp );

			container_type::const_iterator it = node_map_.find( Header );
			if( it == node_map_.end() )
				return 0;
			if( it->second == 0 )
				return 0;
			return it->second->findChild( ++Tmp );
		}
		Header.append( 1, (*Tmp) );
		Tmp ++;
	}
	container_type::const_iterator it = node_map_.find( name );
	if( it == node_map_.end() )
		return 0;
	return ( it->second );
}

const tchar* BT_Configure_XML_Node::findValue( const tchar* name ) const
{
	const BT_Configure_Base* node = findChild( name );
	if( node == 0 )
		return 0;
	return node->getValue();
}

BT_Configure_Base* BT_Configure_XML_Node::getParentNode()
{
	return parentNode_;
}

const BT_Configure_Base* BT_Configure_XML_Node::getParentNode() const
{
	return parentNode_;
}

BT_Configure_Base* BT_Configure_XML_Node::getRootNode()
{
	BT_Configure_Base* n = this;
	while( n->getParentNode() != 0 )
		n = n->getParentNode();
	return n;
}

const BT_Configure_Base* BT_Configure_XML_Node::getRootNode() const
{
	const BT_Configure_Base* n = this;
	while( n->getParentNode() != 0 )
		n = n->getParentNode();
	return n;
}

BT_Configure_Base::IIterator* BT_Configure_XML_Node::begin_( )
{
	return new IIterator_XML( node_map_.begin(), node_map_.end() );
}

BT_Configure_Base::IIterator* BT_Configure_XML_Node::end_( )
{
	
	return new IIterator_XML( node_map_.end(), node_map_.end() );
}

BT_Configure_Base::IConstIterator* BT_Configure_XML_Node::begin_( ) const
{
	return new IConstIterator_XML( node_map_.begin(), node_map_.end() );
}

BT_Configure_Base::IConstIterator* BT_Configure_XML_Node::end_( ) const
{
	return new IConstIterator_XML( node_map_.end(), node_map_.end() );
}



BT_Configure_XML_Text::BT_Configure_XML_Text( BT_Configure_Base* parent   )
: parentNode_( parent )
{
}

BT_Configure_XML_Text::BT_Configure_XML_Text( const tchar* name, const tchar* value ,BT_Configure_Base* parent )
: parentNode_( parent )
{
setName( name );
setValue( value );
}


BT_Configure_XML_Text::~BT_Configure_XML_Text(void)
{
}

bool BT_Configure_XML_Text::setName( const tchar* name )
{
	if( name == 0 )
		name_.clear();
	else
		name_  = name;
	return true;
}

bool BT_Configure_XML_Text::setValue( const tchar* value )
{
	if( value == 0 )
		value_.clear();
	else
		value_ = value;
	return true;
}

bool BT_Configure_XML_Text::appendChild( BT_Configure_Base* node )
{
	return false;
}

bool BT_Configure_XML_Text::deleteChild( BT_Configure_Base* node )
{
	return false;
}

bool BT_Configure_XML_Text::deleteChild( const tchar* name )
{
	return false;
}

const tchar* BT_Configure_XML_Text::getValue() const
{
	return value_.c_str( );
}

const tchar* BT_Configure_XML_Text::getName() const
{
	return name_.c_str();
}

BT_Configure_Base* BT_Configure_XML_Text::findChild( const tchar* name )
{
		return 0;
}

const BT_Configure_Base* BT_Configure_XML_Text::findChild( const tchar* name ) const
{
	return 0;
}

const tchar* BT_Configure_XML_Text::findValue( const tchar* name ) const
{
	return 0;
}

BT_Configure_Base* BT_Configure_XML_Text::getParentNode()
{
	return parentNode_;
}

const BT_Configure_Base* BT_Configure_XML_Text::getParentNode() const
{
	return parentNode_;
}

BT_Configure_Base* BT_Configure_XML_Text::getRootNode()
{
	BT_Configure_Base* n = this;
	while( n->getParentNode() != 0 )
		n = n->getParentNode();
	return n;
}

const BT_Configure_Base* BT_Configure_XML_Text::getRootNode() const
{
	const BT_Configure_Base* n = this;
	while( n->getParentNode() != 0 )
		n = n->getParentNode();
	return n;
}

BT_Configure_Base::IIterator* BT_Configure_XML_Text::begin_( )
{
	return 0;
}

BT_Configure_Base::IIterator* BT_Configure_XML_Text::end_( )
{
	
	return 0;
}

BT_Configure_Base::IConstIterator* BT_Configure_XML_Text::begin_( ) const
{
	return 0;
}

BT_Configure_Base::IConstIterator* BT_Configure_XML_Text::end_( ) const
{
	return 0;
}

_bt_end