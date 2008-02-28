
/**
 * -*- C++ -*-
 * -------------------------------------------------------------------------------
 * - ¤╭⌒╮ ╭⌒╮		            XML_Reflection_T.CPP,v 1.0 2005/03/11 11:33:34
 *  ╱◥██◣ ╭╭ ⌒╮
 * ︱田︱田田| ╰------
 * -------------------------------------------------------------------------------
 */
#include "stdafx.h"
#include "XML_Reflection.h"

#ifndef _XML_Reflection_T_CPP_
#define _XML_Reflection_T_CPP_

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

_bt_serialize_begin

template< XML_Reflection_T_ST_1 >
XML_Reflection_T< XML_Reflection_T_ST_2 >::XML_Reflection_T( const T &t )
: t_( 0 )
, document_( createDocument( ) )
{
	if( document_.get() == 0 )
		throw( std::runtime_error( "DOM创建失败" ) );
	if( init( t ) == 0 )
		throw( std::runtime_error( "类分析失败，不能继续" ) );
	edit_ = false;
}

template< XML_Reflection_T_ST_1 >
XML_Reflection_T< XML_Reflection_T_ST_2 >::XML_Reflection_T( T &t )
: t_( &t )
, document_( createDocument( ) )
{
	init( t );
	edit_ = true;
}

template< XML_Reflection_T_ST_1 >
XML_Reflection_T< XML_Reflection_T_ST_2 >::~XML_Reflection_T( )
{
	fini();
}

template< XML_Reflection_T_ST_1 >
bool XML_Reflection_T< XML_Reflection_T_ST_2 >::init( const T &t )
{
	XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* node = document_->getDocumentElement();
	if( node == 0 )
		return false;

	XML_serializer sr( node );
	serialize( t,sr );
	return createmap( node );
}

template< XML_Reflection_T_ST_1 >
void XML_Reflection_T< XML_Reflection_T_ST_2 >::fini( )
{

	flush();
}

template< XML_Reflection_T_ST_1 >
void XML_Reflection_T< XML_Reflection_T_ST_2 >::flush( )
{
	if( t_ == 0 || !edit_ || !edited_ )
		return ; // 不能编辑或，没有编辑
	XML_deserializer sr( document_->getDocumentElement() );
	deserialize( *t_,sr );
}

template< XML_Reflection_T_ST_1 >
XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument* XML_Reflection_T< XML_Reflection_T_ST_2 >::createDocument( )
{
	XERCES_CPP_NAMESPACE_QUALIFIER DOMString str( "Core" );
	XERCES_CPP_NAMESPACE_QUALIFIER DOMImplementation* impl = XERCES_CPP_NAMESPACE_QUALIFIER DOMImplementationRegistry::getDOMImplementation( str.rawBuffer() );


	XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument* doc = impl->createDocument( );
	str = "serialize";
	doc->appendChild( doc->createElement( str.rawBuffer() ) );
	return doc;
}

_bt_serialize_end

#endif // _XML_Reflection_T_CPP_