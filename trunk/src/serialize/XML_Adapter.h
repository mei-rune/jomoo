
/**
 * -*- C++ -*-
 * -------------------------------------------------------------------------------
 * - °Ë®q°–®r ®q°–®r		            XML_Adapter.h,v 1.0 2005/03/11 17:18:34
 *  ®u®ê®Ä®Ä®é ®q®q °–®r
 * ¶ÚÃÔ¶ÚÃÔÃÔ| ®t------
 * -------------------------------------------------------------------------------
 */

#ifndef _XML_Adapter_H_
#define _XML_Adapter_H_

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include "serialize/bt_stream.h"
#include "serialize_def.h"
#include <xercesc/framework/XMLFormatter.hpp>
#include <xercesc/util/BinInputStream.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/sax/InputSource.hpp>
#include <xercesc/dom/DOM.hpp>

_bt_serialize_begin

class DomNode_Adapter : public bt_istream
	, public bt_ostream
{
public:
	virtual ~DomNode_Adapter(){}

	virtual size_t read( void *pBufferForRead, size_t Len )
	{
		return -1;
	}

	virtual size_t write( const void *pBufferForWrite, size_t Len )
	{
		return -1;
	}

	virtual size_t seek( size_t offset, int start_pos)
	{
		return -1;
	}

	virtual XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument* getDOMDocument() = 0;
	virtual void setDOMDocument( XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument* node ) = 0;
};

// implements Xercesc BinInputStream read data from wxInputStream
class TBinInputStreamInputStream : public XERCES_CPP_NAMESPACE_QUALIFIER BinInputStream
{
public:
    TBinInputStreamInputStream( bt_istream& stream);
    virtual ~TBinInputStreamInputStream();

    virtual unsigned int curPos() const;
    virtual unsigned int readBytes(XMLByte *const toFill, const unsigned int maxToRead);

private:
    bt_istream& stream_;

	size_t pos_;

    DECLARE_NO_COPY_CLASS(TBinInputStreamInputStream);
};


// implements Xercesc InputSource read data from wxInputStream
class TInputStreamInputSource : public XERCES_CPP_NAMESPACE_QUALIFIER InputSource
{
public:
    TInputStreamInputSource(bt_istream& stream);
    virtual ~TInputStreamInputSource();

    virtual XERCES_CPP_NAMESPACE_QUALIFIER BinInputStream* makeStream() const;

private:
    bt_istream& stream_;

    DECLARE_NO_COPY_CLASS(TInputStreamInputSource);
};


class TBinOutputStream : public XERCES_CPP_NAMESPACE_QUALIFIER XMLFormatTarget
{
public:
	TBinOutputStream( bt_ostream& stream );
	  void writeChars
    (
          const XMLByte* const      toWrite
        , const unsigned int        count
        ,       XERCES_CPP_NAMESPACE_QUALIFIER XMLFormatter* const formatter
    );
private:
    bt_ostream& stream_;

    DECLARE_NO_COPY_CLASS(TBinOutputStream);

};

_bt_serialize_end


#endif // 