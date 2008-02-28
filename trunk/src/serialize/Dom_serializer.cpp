#include "StdAfx.h"
#include "dom_serializer.h"
#include "serializer_factory.h"
#include "serialize/XML_Adapter.H"
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/framework/Wrapper4InputSource.hpp>
#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include "xml/xml_helper.h"
_bt_serialize_begin



// ---------------------------------------------------------------------------
//  MemParseHandlers: Constructors and Destructor
// ---------------------------------------------------------------------------
DOMParseHandlers::DOMParseHandlers()
{
}

DOMParseHandlers::~DOMParseHandlers()
{
}

bool DOMParseHandlers::handleError(const XERCES_CPP_NAMESPACE_QUALIFIER DOMError& domError)
{
	if (domError.getSeverity() == XERCES_CPP_NAMESPACE_QUALIFIER DOMError::DOM_SEVERITY_WARNING)
        XERCES_STD_QUALIFIER cerr << "\nWarning at file ";
    else if (domError.getSeverity() == XERCES_CPP_NAMESPACE_QUALIFIER DOMError::DOM_SEVERITY_ERROR)
        XERCES_STD_QUALIFIER cerr << "\nError at file ";
    else
        XERCES_STD_QUALIFIER cerr << "\nFatal Error at file ";

    XERCES_STD_QUALIFIER cerr << _bt_xml StrX(domError.getLocation()->getURI())
         << ", line " << domError.getLocation()->getLineNumber()
         << ", char " << domError.getLocation()->getColumnNumber()
         << "\n  Message: " << _bt_xml StrX(domError.getMessage()) << XERCES_STD_QUALIFIER endl;

    return true;
}
void DOMParseHandlers::resetErrors()
{
}


static const char*  gMemBufId = "prodInfo";

Dom_serializer::Dom_serializer( const char* file_name )
: doc_( createDocument() )
, bos_( file_name )
{
	init( doc_->getDocumentElement() );
}

Dom_serializer::Dom_serializer( bt_ostream& ostream )
: doc_( createDocument( ) )
, bos_( &ostream )
{
	init( doc_->getDocumentElement() );
}

Dom_serializer::Dom_serializer( BIN_OUT_Source bos )
: doc_( createDocument( ) )
, bos_( bos )
{
	init( doc_->getDocumentElement() );
}

Dom_serializer::~Dom_serializer(void)
{
	if( bos_.type_ == BIN_OUT_Source::stream_source )
	{
		DomNode_Adapter* adapter = dynamic_cast< DomNode_Adapter* >(  bos_.ostream_ );
		if( adapter != 0 )
		{
			adapter->setDOMDocument( doc_.get() );
			doc_.release();
			return ;
		}
	}
	serializeDOM( );
}

XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument* Dom_serializer::createDocument(void)
{
	XERCES_CPP_NAMESPACE_QUALIFIER DOMString str( "Core" );
	XERCES_CPP_NAMESPACE_QUALIFIER DOMImplementation* impl = XERCES_CPP_NAMESPACE_QUALIFIER DOMImplementationRegistry::getDOMImplementation( str.rawBuffer() );


	XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument* doc = impl->createDocument( );
	str = "serialize";
	doc->appendChild( doc->createElement( str.rawBuffer() ) );

	return doc;
}

int Dom_serializer::serializeDOM(  )
{


	try {
		XMLCh tempStr[100];
		XERCES_CPP_NAMESPACE_QUALIFIER XMLString::transcode("LS", tempStr, 99);
		XERCES_CPP_NAMESPACE_QUALIFIER DOMImplementation *impl =
			XERCES_CPP_NAMESPACE_QUALIFIER DOMImplementationRegistry::getDOMImplementation(tempStr);
		BT_Scope_Ptr< XERCES_CPP_NAMESPACE_QUALIFIER DOMWriter > theSerializer = 
			((XERCES_CPP_NAMESPACE_QUALIFIER DOMImplementationLS*)impl)->createDOMWriter();

		// optionally you can set some features on this serializer
		if (theSerializer->canSetFeature( XERCES_CPP_NAMESPACE_QUALIFIER XMLUni::fgDOMWRTDiscardDefaultContent, true))
			theSerializer->setFeature( XERCES_CPP_NAMESPACE_QUALIFIER XMLUni::fgDOMWRTDiscardDefaultContent, true);

		if (theSerializer->canSetFeature(XERCES_CPP_NAMESPACE_QUALIFIER XMLUni::fgDOMWRTFormatPrettyPrint, true))
			theSerializer->setFeature(XERCES_CPP_NAMESPACE_QUALIFIER XMLUni::fgDOMWRTFormatPrettyPrint, true);


		std::auto_ptr< XERCES_CPP_NAMESPACE_QUALIFIER XMLFormatTarget > myFormTarget;
		switch( bos_.type_ )
		{
		case BIN_OUT_Source::file_source:
			myFormTarget.reset( new XERCES_CPP_NAMESPACE_QUALIFIER LocalFileFormatTarget( bos_.file_name_ ) );
			break;
		case BIN_OUT_Source::stream_source:
			myFormTarget.reset( new TBinOutputStream( *bos_.ostream_ ) );
			break;
		}


		// do the serialization through DOMWriter::writeNode();
		if( myFormTarget.get() != 0  )
			theSerializer->writeNode(myFormTarget.get(), *doc_ );
	}
	catch (const XERCES_CPP_NAMESPACE_QUALIFIER XMLException& toCatch) {
		std::cout << "Exception message is: \n"
			<< _bt_xml StrX( toCatch.getMessage() ) << "\n";
		return -1;
	}
	catch (const XERCES_CPP_NAMESPACE_QUALIFIER DOMException& toCatch) {
		std::cout << "Exception message is: \n"
			<<  _bt_xml StrX( toCatch.msg ) << "\n";
		return -1;
	}
	catch (...) {
		std::cout << "Unexpected Exception \n" ;
		return -1;
	}

	return 0;
}

Dom_deserializer::Dom_deserializer( const char* file_name )
: doc_( 0 )
, parser_( 0 )
{
		// And create our error handler and install it
	make_Parser();
	DOMParseHandlers errorHandler;
	parser_->setErrorHandler(&errorHandler);

	doc_ = parser_->parseURI( file_name );
	if( doc_ == NULL )
		throw std::runtime_error( "文件" + tstring( file_name ) + "打不开" );
	init( doc_->getDocumentElement() );
}

Dom_deserializer::Dom_deserializer( const void * buf, size_t lenght )
: doc_( 0 )
, parser_( 0 )
{
	// And create our error handler and install it
	make_Parser();
	DOMParseHandlers errorHandler;
	parser_->setErrorHandler(&errorHandler);

	std::auto_ptr< XERCES_CPP_NAMESPACE_QUALIFIER MemBufInputSource > memBufIS ( 
		new XERCES_CPP_NAMESPACE_QUALIFIER MemBufInputSource
		(
		(const XMLByte*)buf
		, ( u_int_t )lenght
		, gMemBufId
		, false
		) );

	XERCES_CPP_NAMESPACE_QUALIFIER Wrapper4InputSource ins( memBufIS.get() );
	doc_ = parser_->parse( ins );
	init( doc_->getDocumentElement() );

}

Dom_deserializer::Dom_deserializer( bt_istream& istream )
: doc_( 0 )
, parser_( 0 )
{
	DomNode_Adapter* adapter = dynamic_cast< DomNode_Adapter* >( &istream );
	if( adapter != 0 )
	{
		doc_ = adapter->getDOMDocument();
		init( doc_->getDocumentElement() );
		return ;
	}
	// And create our error handler and install it
	make_Parser();
	DOMParseHandlers errorHandler;
	parser_->setErrorHandler(&errorHandler);

	TInputStreamInputSource ins( istream );

	doc_ = parser_->parse( XERCES_CPP_NAMESPACE_QUALIFIER Wrapper4InputSource( &ins ) );
	init( doc_->getDocumentElement() );
}

Dom_deserializer::~Dom_deserializer(void)
{
	BT_Scope_Ptr< XERCES_CPP_NAMESPACE_QUALIFIER DOMBuilder > parser( parser_ );
}


void Dom_deserializer::make_Parser( )
{
	// Instantiate the DOM parser.
	static const XMLCh gLS[] = { XERCES_CPP_NAMESPACE_QUALIFIER chLatin_L
		, XERCES_CPP_NAMESPACE_QUALIFIER chLatin_S
		, XERCES_CPP_NAMESPACE_QUALIFIER chNull };
	
	XERCES_CPP_NAMESPACE_QUALIFIER DOMImplementation *impl = XERCES_CPP_NAMESPACE_QUALIFIER DOMImplementationRegistry::getDOMImplementation(gLS);
	BT_Scope_Ptr< XERCES_CPP_NAMESPACE_QUALIFIER DOMBuilder > parser( (( XERCES_CPP_NAMESPACE_QUALIFIER DOMImplementationLS*)
		impl)->createDOMBuilder( XERCES_CPP_NAMESPACE_QUALIFIER DOMImplementationLS::MODE_SYNCHRONOUS, 0) );

	parser->setFeature(XERCES_CPP_NAMESPACE_QUALIFIER XMLUni::fgDOMNamespaces, true );
	/*parser->setFeature(XERCES_CPP_NAMESPACE_QUALIFIER XMLUni::fgXercesSchema, true);
	parser->setFeature(XERCES_CPP_NAMESPACE_QUALIFIER XMLUni::fgXercesSchemaFullChecking, true);


	parser->setFeature(XERCES_CPP_NAMESPACE_QUALIFIER XMLUni::fgDOMValidateIfSchema, true);*/

	//parser->setFeature(XERCES_CPP_NAMESPACE_QUALIFIER XMLUni::fgDOMValidation, false);

	//parser->setFeature(XERCES_CPP_NAMESPACE_QUALIFIER XMLUni::fgDOMValidation, true);

	//parser->setFeature(XERCES_CPP_NAMESPACE_QUALIFIER XMLUni::fgDOMDatatypeNormalization, true);

	BT_Scope_Ptr< XERCES_CPP_NAMESPACE_QUALIFIER DOMBuilder > parserguard( parser_ );
	parser_ = parser.release();
}



serialize_ostream_base* make_XML_serializer( BIN_OUT_Source* bos )
{
	if( bos == 0 )
		return 0;

	return new Dom_serializer( *bos );
}

serialize_istream_base* make_XML_deserializer( BIN_INPUT_Source* bos )
{
	if( bos == 0 )
		return 0;

	switch( bos->type_ )
	{
	case BIN_INPUT_Source::file_source:
		if( bos->file_name_ != 0 )
		return new Dom_deserializer( bos->file_name_ );
		break;
	case BIN_INPUT_Source::mem_source:
		if( bos->buf_ != 0 && bos->buf_len_ != -1 )
		return new Dom_deserializer( bos->buf_,bos->buf_len_ );
		break;
	case BIN_INPUT_Source::stream_source:
		if( bos->istream_ != 0 )
		return new Dom_deserializer( *(bos->istream_ ) );
	};

	return 0;
}





#ifdef STATIC_INIT

bool dom_serializer = BTOUTSerializeFactory_Singleton::instance()->Register( dom_stream, make_XML_serializer );
bool dom_deserializer = BTINPUTSerializeFactory_Singleton::instance()->Register( dom_stream, make_XML_deserializer );

#endif // 

_bt_serialize_end
