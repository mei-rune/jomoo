#include "stdafx.h"

#ifdef UNITTEST
#include <iostream>
#include "serializetestfixture.h"
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>

XERCES_CPP_NAMESPACE_USE

XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument* createDocument( )
{
	XERCES_CPP_NAMESPACE_QUALIFIER DOMString str( "Core" );
	XERCES_CPP_NAMESPACE_QUALIFIER DOMImplementation* impl = XERCES_CPP_NAMESPACE_QUALIFIER DOMImplementationRegistry::getDOMImplementation( str.rawBuffer() );


	XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument* doc = impl->createDocument( );
	str = "serialize";
	doc->appendChild( doc->createElement( str.rawBuffer() ) );
	
	return doc;
}

int serializeDOM(DOMNode* node, const char* file = 0 ) {

        XMLCh tempStr[100];
        XMLString::transcode("LS", tempStr, 99);
        DOMImplementation *impl = DOMImplementationRegistry::getDOMImplementation(tempStr);
        DOMWriter* theSerializer = ((DOMImplementationLS*)impl)->createDOMWriter();

        // optionally you can set some features on this serializer
        if (theSerializer->canSetFeature(XMLUni::fgDOMWRTDiscardDefaultContent, true))
            theSerializer->setFeature(XMLUni::fgDOMWRTDiscardDefaultContent, true);

        if (theSerializer->canSetFeature(XMLUni::fgDOMWRTFormatPrettyPrint, true))
             theSerializer->setFeature(XMLUni::fgDOMWRTFormatPrettyPrint, true);


        // StdOutFormatTarget prints the resultant XML stream
        // to stdout once it receives any thing from the serializer.

        XMLFormatTarget *myFormTarget = 0;
		if( file == 0 )
		myFormTarget = new StdOutFormatTarget();
		else
			myFormTarget = new LocalFileFormatTarget( file );

        try {
            // do the serialization through DOMWriter::writeNode();
            theSerializer->writeNode(myFormTarget, *node);
        }
        catch (const XMLException& toCatch) {
            char* message = XMLString::transcode(toCatch.getMessage());
			std::cout << "Exception message is: \n"
                 << message << "\n";
            XMLString::release(&message);
            return -1;
        }
        catch (const DOMException& toCatch) {
            char* message = XMLString::transcode(toCatch.msg);
			std::cout << "Exception message is: \n"
                 << message << "\n";
            XMLString::release(&message);
            return -1;
        }
        catch (...) {
			std::cout << "Unexpected Exception \n" ;
            return -1;
        }


        theSerializer->release();

        delete myFormTarget;
        return 0;
    }


CPPUNIT_TEST_SUITE_REGISTRATION( SerializeTestCase );



#define serialize_MEMBER( TYPE, STREAM )		if(	!serialize( t_##TYPE,STREAM,STR( t_##TYPE ) ) ) return false;		\
	if(	!serialize( t_##TYPE##_list,STREAM,STR( t_##TYPE##_list ) ) ) return false;											\
	if(	!serialize( t_##TYPE##_vector,STREAM ,STR( t_##TYPE##_vector ) ) ) return false;											\
	if(	!serialize( t_##TYPE##_set,STREAM,STR( t_##TYPE##_set ) ) ) return false;


#define deserialize_MEMBER( TYPE, STREAM )		if(	!deserialize( t_##TYPE,STREAM ,STR( t_##TYPE ) ) ) return false;		\
	if(	!deserialize( t_##TYPE##_list,STREAM ,STR( t_##TYPE##_list ) ) ) return false;											\
	if(	!deserialize( t_##TYPE##_vector,STREAM,STR( t_##TYPE##_vector ) ) ) return false;											\
	if(	!deserialize( t_##TYPE##_set,STREAM,STR( t_##TYPE##_set ) ) ) return false;					

bool Tester::serialize1( serialize_ostream_base& s ) const
{

	if( !serialize( bt_list_ , s ) ) return false;
	serialize_MEMBER( T_A , s );
		serialize_MEMBER( T_B , s );
#ifdef _TEST_LIST_
		serialize_MEMBER( T_AS ,s );
		serialize_MEMBER( T_BS ,s );
#endif // 
		serialize_MEMBER( bool , s );
		serialize_MEMBER( char , s );
		serialize_MEMBER( short , s );
		serialize_MEMBER( int , s );

		serialize_MEMBER( long , s );
		serialize_MEMBER( __int64 , s );
		serialize_MEMBER( u_char , s );

		serialize_MEMBER( u_short , s );
		serialize_MEMBER( u_int , s );
		serialize_MEMBER( u_long , s );
		serialize_MEMBER( u_int64 , s );
		serialize_MEMBER( double , s );
		serialize_MEMBER( float , s );
		serialize_MEMBER( string , s );
		return true;
}

bool Tester::deserialize1( serialize_istream_base& s )
{
	if( !deserialize( bt_list_ , s ) ) return false;
		deserialize_MEMBER( T_A , s );
		deserialize_MEMBER( T_B , s );
#ifdef _TEST_LIST_
		deserialize_MEMBER( T_AS ,s );
		deserialize_MEMBER( T_BS ,s );
#endif // 
		deserialize_MEMBER( bool , s );
		deserialize_MEMBER( char , s );
		deserialize_MEMBER( short , s );
		deserialize_MEMBER( int , s );

		deserialize_MEMBER( long , s );
		deserialize_MEMBER( __int64 , s );
		deserialize_MEMBER( u_char , s );

		deserialize_MEMBER( u_short , s );
		deserialize_MEMBER( u_int , s );
		deserialize_MEMBER( u_long , s );
		deserialize_MEMBER( u_int64 , s );
		deserialize_MEMBER( double , s );
		deserialize_MEMBER( float , s );
		deserialize_MEMBER( string , s );
		return true;
}

bool Tester2::serialize1( serialize_ostream_base& s ) const
{

	if( !serialize( bt_list_ , s ) ) return false;
	serialize_MEMBER( T_A , s );
		serialize_MEMBER( T_B , s );
		return true;
}

bool Tester2::deserialize1( serialize_istream_base& s )
{
	if( !deserialize( bt_list_ , s ) ) return false;
		deserialize_MEMBER( T_A , s );
		deserialize_MEMBER( T_B , s );
		return true;
}

SerializeTestCase::SerializeTestCase(void)
{
}

SerializeTestCase::~SerializeTestCase(void)
{
}

	// 初始化函数
void SerializeTestCase::setUp ()
{
	ptr.reset( new Tester( 7 ) );
}
	// 清理函数
void SerializeTestCase::tearDown()
{
	ptr.reset( 0 );
}

void SerializeTestCase::testDB()
{
	Tester2 t( 7 );
	{
	_bt_serialize BIN_OUT_Source out( "tmp.sqlite" );
	std::auto_ptr< _bt serialize_ostream_base > sr( _bt_serialize BTOUTSerializeFactory_Singleton::instance()->CreateObject( _bt_serialize db_stream ,&out )  );
	t.serialize1( *sr );
	}
	//_bt_xml XMLDoc doc;
	//_bt_xml xml_dom_parse( doc , "tmp.xml" );
	//serializeDOM( doc.doc_ );

	Tester2 t2( 0 );
	_bt_serialize BIN_INPUT_Source in( "tmp.sqlite" );
	std::auto_ptr< _bt serialize_istream_base > dsr( _bt_serialize BTINPUTSerializeFactory_Singleton::instance()->CreateObject( _bt_serialize db_stream ,&in  ) );

	t2.deserialize1( *dsr ); 

	CPPUNIT_ASSERT( t == t2 );
}

void SerializeTestCase::testSerialize ()
{
	//Tester t( 7 );
	//std::auto_ptr< out_stream > sr( Serialize_Creater::create_o_stream( 0 ) );
	//t.serialize( sr->get_o_stream() );

	//Tester t2( 0 );
	//std::auto_ptr< in_stream > dsr( Serialize_Creater::create_i_stream( 0 ) );
	//t2.deserialize( dsr->get_i_stream() ); 

	//CPPUNIT_ASSERT( t == t2 );
	//	std::cout << "ok" << std::endl;
	//else
	//	std::cout << "error" << std::endl;
}

void SerializeTestCase::testSerialize2 ()
{
	Tester t( 7 );
	{
	_bt_serialize BIN_OUT_Source out( "tmp.xml" );
	std::auto_ptr< _bt serialize_ostream_base > sr( _bt_serialize BTOUTSerializeFactory_Singleton::instance()->CreateObject( _bt_serialize dom_stream ,&out )  );
	t.serialize1( *sr );
	}
	//_bt_xml XMLDoc doc;
	//_bt_xml xml_dom_parse( doc , "tmp.xml" );
	//serializeDOM( doc.doc_ );

	Tester t2( 0 );
	_bt_serialize BIN_INPUT_Source in( "tmp.xml" );
	std::auto_ptr< _bt serialize_istream_base > dsr( _bt_serialize BTINPUTSerializeFactory_Singleton::instance()->CreateObject( _bt_serialize dom_stream ,&in  ) );

	t2.deserialize1( *dsr ); 

	CPPUNIT_ASSERT( t == t2 );
	//	std::cout << "ok" << std::endl;
	//else
	//	std::cout << "error" << std::endl;
}
void SerializeTestCase::testRefletion( )
{

	//T_B t( 4 );
	//_bt_serialize XML_Reflection_T< T_B > reflection( t );
	//for( std::list< std::string >::const_iterator it = reflection.get_MemberName().begin()
	//	; it != reflection.get_MemberName().end() ; it ++ )
	//{
	//	std::cout << *it << " = "<< reflection.get_Member( it->c_str() ) << std::endl ; 
	//}

	//if( )
}

void SerializeTestCase::testDomAdapter( )
{
	_bt_serialize Dom_Adapter adapter( 0 );
	Tester t( 7 );
	{
	_bt_serialize BT_Out_Stream out( adapter );
	out.serialize( t );
	}
	Tester t2( 0 );
	{
	_bt_serialize BT_Input_Stream in( adapter );
	in.deserialize( t2 );
	}
	CPPUNIT_ASSERT( t == t2 );
	//	std::cout << "ok" << std::endl;
	//else
	//	std::cout << "error" << std::endl;

}
void SerializeTestCase::testStream2( )
{
	Tester t( 7 );
	std::string str;
	{
		
		bt_o_strstream stream( str );
	_bt_serialize BT_Out_Stream out( stream );
	out.serialize( t );
	}
	Tester t2( 0 );
	{
		bt_i_strstream stream( str.c_str(), str.size() );
	_bt_serialize BT_Input_Stream in( stream );
	in.deserialize( t2 );
	}
	CPPUNIT_ASSERT( t == t2 );
	//	std::cout << "ok" << std::endl;
	//else
	//	std::cout << "error" << std::endl;
}

void SerializeTestCase::testcostumlist()
{

}
void SerializeTestCase::testStream( )
{
	Tester t( 7 );
	{
	_bt_serialize BT_Out_Stream out( "STREAM.XML" );
	out.serialize( t );
	}
	Tester t2( 0 );
	{
	_bt_serialize BT_Input_Stream in( "STREAM.XML" );
	in.deserialize( t2 );
	}
	CPPUNIT_ASSERT( t == t2 );
	//	std::cout << "ok" << std::endl;
	//else
	//	std::cout << "error" << std::endl;
}

void SerializeTestCase::testArray()
{
	char* index[] = {
		  "name1"
		, "name2"
	};
	char* buf[] ={
	//tstring name;
	//int InterfaceConfIndex;
	"1" //int InterfaceLabelEdgeType;
	,"2" //int InterfaceVpnClassification ;
	,"3" //tstring InterfaceVpnRouteDistProtocol; 
	,"4" //int InterfaceConfStorageType; 
	,"5" //int InterfaceConfRowStatus;

	,"11" //int InterfaceLabelEdgeType;
	,"12" //int InterfaceVpnClassification ;
	,"13" //tstring InterfaceVpnRouteDistProtocol; 
	,"14" //int InterfaceConfStorageType; 
	,"15" //int InterfaceConfRowStatus;
	};

	std::list< Mpls_Vpn_Interface_Conf_Table > t;
	VArray_Reader_Accessor ar( buf,index, 2,5 ,Mpls_Vpn_Interface_Conf_Table_Vector );
	_bt_serialize BT_Input_Stream is( ar , _bt_serialize array_stream );
			is >> t;
	CPPUNIT_ASSERT( t.size() == 2 );
	if( t.size() == 2 )
	{
		const Mpls_Vpn_Interface_Conf_Table& a = *(t.begin());
		CPPUNIT_ASSERT( a.name.empty() );
		CPPUNIT_ASSERT( a.InterfaceLabelEdgeType == 1 );
		CPPUNIT_ASSERT( a.InterfaceVpnClassification == 2 );
		CPPUNIT_ASSERT( a.InterfaceVpnRouteDistProtocol == "3" );
		CPPUNIT_ASSERT( a.InterfaceConfStorageType == 4 );
		CPPUNIT_ASSERT( a.InterfaceConfRowStatus == 5 );

		const Mpls_Vpn_Interface_Conf_Table& b = *(++t.begin());
		CPPUNIT_ASSERT( b.name.empty() );
		CPPUNIT_ASSERT( b.InterfaceLabelEdgeType == 11 );
		CPPUNIT_ASSERT( b.InterfaceVpnClassification == 12 );
		CPPUNIT_ASSERT( b.InterfaceVpnRouteDistProtocol == "13" );
		CPPUNIT_ASSERT( b.InterfaceConfStorageType == 14 );
		CPPUNIT_ASSERT( b.InterfaceConfRowStatus == 15 );

	}

}

void SerializeTestCase::show( Tester& t , const char* file )
{
	DOMDocument* doc = createDocument( );
	DOMNode * node = doc->getDocumentElement();
	_bt_serialize XML_serializer ds( node );
	t.serialize1( ds );


	// create an iterator to visit all text nodes.
	//DOMNodeIterator iterator = 
	//	doc.createNodeIterator( node , DOMNodeFilter::SHOW_TEXT, NULL, true);
	//// use the tree walker to print out the text nodes.
	//for ( current = iterator.nextNode(); current != 0; current = iterator.nextNode() )
	//	// note: this leaks memory!
	//	std::cout << current.getNodeValue().transcode();
	//std::cout << std::endl;


	// create a walker to visit all text nodes.
	DOMTreeWalker * walker = 
		((DOMDocumentTraversal*)doc)->createTreeWalker( node, DOMNodeFilter::SHOW_ALL, NULL, true);
	// use the tree walker to print out the text nodes.
	for (DOMNode* current = walker->nextNode(); current != 0; current = walker->nextNode() )
		// note: this leaks memory!
	{
		switch( current->getNodeType() )
		{

		case DOMNode::ELEMENT_NODE:
			std::cout << DOMString( current->getNodeName() ).transcode() << std::endl;
			break;
		case DOMNode::ATTRIBUTE_NODE              :
			std::cout << DOMString( current->getNodeName() ).transcode() << "= "<< DOMString( current->getNodeValue() ).transcode() << std::endl;
			break;
		case DOMNode::TEXT_NODE                   :
			std::cout << DOMString( current->getNodeValue() ).transcode() << std::endl;
			break;
		case DOMNode::CDATA_SECTION_NODE          :
			std::cout << DOMString( current->getNodeValue() ).transcode() << std::endl;
			break;
		case DOMNode::ENTITY_REFERENCE_NODE       :
			std::cout << DOMString( current->getNodeValue() ).transcode() << std::endl;
			break;
		case DOMNode::ENTITY_NODE                 :
			std::cout << DOMString( current->getNodeValue() ).transcode() << std::endl;
			break;
		case DOMNode::PROCESSING_INSTRUCTION_NODE :
			std::cout << DOMString( current->getNodeValue() ).transcode() << std::endl;
			break;
		case DOMNode::COMMENT_NODE                :
			std::cout << DOMString( current->getNodeValue() ).transcode() << std::endl;
			break;
		case DOMNode::DOCUMENT_NODE               :
			std::cout << DOMString( current->getNodeValue() ).transcode() << std::endl;
			break;
		case DOMNode::DOCUMENT_TYPE_NODE          :
			std::cout << DOMString( current->getNodeValue() ).transcode() << std::endl;
			break;
		case DOMNode::DOCUMENT_FRAGMENT_NODE      :
			std::cout << DOMString( current->getNodeValue() ).transcode() << std::endl;
			break;
		case DOMNode::NOTATION_NODE               :
			std::cout << DOMString( current->getNodeValue() ).transcode() << std::endl;
			break;
		};

		std::cout << DOMString( current->getNodeValue() ).transcode() << std::endl;
	
	}

	doc->release();
}



int _tmain(int argc, char* argv[])
{
	try {
		XERCES_CPP_NAMESPACE_QUALIFIER XMLPlatformUtils::Initialize();
	}
	catch (const XERCES_CPP_NAMESPACE_QUALIFIER XMLException& toCatch) {
		// Do your failure processing here
		return 1;
	}

	_bt ___DB_Init( SQLITE_DRIVER , 0 );

	//XERCES_CPP_NAMESPACE_QUALIFIER DOMString str( "Core" );
 //   XERCES_CPP_NAMESPACE_QUALIFIER DOMImplementation* impl = XERCES_CPP_NAMESPACE_QUALIFIER DOMImplementationRegistry::getDOMImplementation( str.rawBuffer() );

	// 	
	//XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument* doc = impl->createDocument( );
	//str = "serialize";
	//XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* root = doc->createElement( str.rawBuffer() );
	//doc->appendChild( root );
	//XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* node = root;
	//XML_serializer sr( node );
	//serialize( 23, sr );
	//serialize( 23, sr );
	//serializeDOM( doc );
	//XML_deserializer dsr( node );
	//doc->release();

	//SerializeTestCase cases;
	//cases.setUp();
	//cases.testStream2( );
	//cases.tearDown();
	//cases.setUp();
	//cases.testDomAdapter();
	//cases.tearDown();
	//cases.setUp();
	//cases.testRefletion();
	//cases.tearDown();
	//cases.setUp();
	//cases.testSerialize2();
	//cases.tearDown();
	//cases.setUp();
	//cases.testStream( );
	//cases.tearDown();


	CppUnit::TextUi::TestRunner runner;
	
	// 从注册的TestSuite中获取特定的TestSuite, 没有参数获取未命名的TestSuite.
	CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
	// 添加这个TestSuite到TestRunner中
	runner.addTest( registry.makeTest() );
	// 运行测试
	runner.run();


	_bt ___DB_Fini( );
	// Do your actual work with Xerces-C++ here.
	XERCES_CPP_NAMESPACE_QUALIFIER XMLPlatformUtils::Terminate();
	return 0;
}

#endif