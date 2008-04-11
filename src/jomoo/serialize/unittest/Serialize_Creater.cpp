#include "StdAfx.h"
#ifdef UNITTEST
#include "serialize_creater.h"

#include "../XML_serializer.H"
// 不用再包含所有TestFixture子类的头文件
#include <iostream>
#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>


class dom_stream : public in_stream, public out_stream
{
public:
	dom_stream()
		: doc_( 0 )
	{
		doc_ = createDocument( );
		dsr.reset( new _bt_serialize XML_deserializer( doc_->getDocumentElement() ) );
		sr.reset( new _bt_serialize XML_serializer( doc_->getDocumentElement() ) );
	}
	virtual ~dom_stream()
	{
		if( doc_ != 0 )
			doc_->release();
	}

	virtual bt_o_stream_base& get_o_stream( )
	{
		return *sr;
	}

	virtual bt_i_stream_base& get_i_stream( )
	{
		return *dsr;
	}

	XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument* createDocument( )
	{
		XERCES_CPP_NAMESPACE_QUALIFIER DOMString str( "Core" );
		XERCES_CPP_NAMESPACE_QUALIFIER DOMImplementation* impl = XERCES_CPP_NAMESPACE_QUALIFIER DOMImplementationRegistry::getDOMImplementation( str.rawBuffer() );


		XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument* doc = impl->createDocument( );
		str = "serialize";
		doc->appendChild( doc->createElement( str.rawBuffer() ) );

		return doc;
	}

	XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument* doc_;
	std::auto_ptr< _bt_serialize XML_deserializer > dsr;
	std::auto_ptr< _bt_serialize XML_serializer > sr;
};

Serialize_Creater::Serialize_Creater(void)
{
}

Serialize_Creater::~Serialize_Creater(void)
{
}


out_stream* Serialize_Creater::create_o_stream( const char* file )
{
	return new dom_stream();
}

in_stream* Serialize_Creater::create_i_stream( const char* file )
{
	return new dom_stream();
}

#endif