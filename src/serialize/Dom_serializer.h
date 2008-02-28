
/**
 * -*- C++ -*-
 * -------------------------------------------------------------------------------
 * - °Ë®q°–®r ®q°–®r		            Dom_serializer.h,v 1.0 2005/03/14 09:42:34
 *  ®u®ê®Ä®Ä®é ®q®q °–®r
 * ¶ÚÃÔ¶ÚÃÔÃÔ| ®t------
 * -------------------------------------------------------------------------------
 */

#ifndef _Dom_serializer_H_
#define _Dom_serializer_H_

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif // BOE_LACKS_PRAGMA_ONCE

#include "XML_serializer.h"
#include "bt_stream.h"
//#include "serialize2.h"
#include "Serialize_Helper.h"

#ifndef NO_STATIC_INIT

#ifndef STATIC_INIT
#define STATIC_INIT
#endif // STATIC_INIT

#endif // NO_STATIC_INIT

_bt_serialize_begin

class DOMParseHandlers : public XERCES_CPP_NAMESPACE_QUALIFIER DOMErrorHandler
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

    bool handleError(const XERCES_CPP_NAMESPACE_QUALIFIER DOMError& domError);
    void resetErrors();
};


class Dom_serializer :
	public XML_serializer
{
public:
	Dom_serializer( const char* file_name );
	Dom_serializer( bt_ostream& istream );
	Dom_serializer( BIN_OUT_Source bos );
	~Dom_serializer(void);

	XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument* createDocument( );
	int serializeDOM(  );
private:
	BT_Scope_Ptr< XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument >  doc_;
	BIN_OUT_Source bos_;
};


class Dom_deserializer : public XML_deserializer
{
public:
	Dom_deserializer( const char* file_name );
	Dom_deserializer( const void * buf, size_t lenght );
	Dom_deserializer( bt_istream& istream );
	~Dom_deserializer(void);

	void make_Parser( );
private:
	XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument*  doc_;
	XERCES_CPP_NAMESPACE_QUALIFIER DOMBuilder* parser_;
};

_bt_serialize_end

#endif // _Dom_serializer_H_