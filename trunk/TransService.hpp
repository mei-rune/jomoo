

#ifndef TRANSSERVICE_HPP
#define TRANSSERVICE_HPP

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */


_xml_begin

class XMLTransService
{
public :

	virtual ~XMLTransService(){};


    XMLTranscoder* makeNewTranscoderFor
    (
        const   XMLCh* const            encodingName
        ,       XMLTransService::Codes& resValue
        , const unsigned int            blockSize
        , MemoryManager* const          manager = 0
    ) = 0;

    XMLTranscoder* makeNewTranscoderFor
    (
        const   char* const             encodingName
        ,       XMLTransService::Codes& resValue
        , const unsigned int            blockSize
        , MemoryManager* const          manager = 0
    ) = 0;

    XMLTranscoder* makeNewTranscoderFor
    (
        XMLRecognizer::Encodings        encodingEnum
        ,       XMLTransService::Codes& resValue
        , const unsigned int            blockSize
        , MemoryManager* const          manager = 0
    ) = 0;

private :

    DECLARE_NO_COPY_CLASS( XMLTransService );
};



 /**
  *   <code>XMLTranscoder</code> 用于非本地字符编码的字符串之间的转换
  */
class XMLTranscoder 
{
public :

	virtual ~XMLTranscoder(){};

    virtual unsigned int transcodeFrom
    (
        const   XMLByte* const          srcData
        , const unsigned int            srcCount
        ,       XMLCh* const            toFill
        , const unsigned int            maxChars
        ,       unsigned int&           bytesEaten
        ,       unsigned char* const    charSizes
    ) = 0;

    virtual unsigned int transcodeTo
    (
        const   XMLCh* const    srcData
        , const unsigned int    srcCount
        ,       XMLByte* const  toFill
        , const unsigned int    maxBytes
        ,       unsigned int&   charsEaten
        , const UnRepOpts       options
    ) = 0;

    const XMLCh* getEncodingName() const = 0;

private :

    DECLARE_NO_COPY_CLASS( XMLTranscoder);
};



class XMLLCPTranscoder
{
public :

    virtual ~XMLLCPTranscoder();

    virtual unsigned int calcRequiredSize(const char* const srcText ) = 0;

    virtual unsigned int calcRequiredSize(const XMLCh* const srcText ) = 0;

    virtual char* transcode(const XMLCh* const toTranscode) = 0;
    virtual char* transcode(const XMLCh* const toTranscode,
                            MemoryManager* const manager) = 0;

    virtual XMLCh* transcode(const char* const toTranscode) = 0;
    virtual XMLCh* transcode(const char* const toTranscode,
                             MemoryManager* const manager) = 0;

    virtual bool transcode
    (
        const   char* const     toTranscode
        ,       XMLCh* const    toFill
        , const unsigned int    maxChars
    ) = 0;

    virtual bool transcode
    (
        const   XMLCh* const    toTranscode
        ,       char* const     toFill
        , const unsigned int    maxBytes
    ) = 0;

private :
    DECLARE_NO_COPY_CLASS( XMLLCPTranscoder );

};

_xml_end

#endif
