

#ifndef DEFAULTHANDLER_HPP
#define DEFAULTHANDLER_HPP

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include <xercesc/sax2/ContentHandler.hpp>
#include <xercesc/sax2/LexicalHandler.hpp>
#include <xercesc/sax2/DeclHandler.hpp>
#include <xercesc/sax/DTDHandler.hpp>
#include <xercesc/sax/EntityResolver.hpp>
#include <xercesc/sax/ErrorHandler.hpp>
#include <xercesc/sax/SAXParseException.hpp>

namespace XML
{

class Locator;
class Attributes;



class SAX2_EXPORT DefaultHandler :
    public EntityResolver,
	public DTDHandler,
	public ContentHandler,
    public ErrorHandler,
    public LexicalHandler,
    public DeclHandler
{
public:

    virtual void characters
    (
        const   XMLCh* const    chars
        , const unsigned int    length
    );


    virtual void endDocument();

    virtual void endElement
	(
		const XMLCh* const uri,
		const XMLCh* const localname,
		const XMLCh* const qname
	);

  
    virtual void ignorableWhitespace
    (
        const   XMLCh* const    chars
        , const unsigned int    length
    );

  
    virtual void processingInstruction
    (
        const   XMLCh* const    target
        , const XMLCh* const    data
    );

    
    virtual void resetDocument();
    
    virtual void setDocumentLocator(const Locator* const locator);

  
    virtual void startDocument();

  
    virtual void startElement
    (
        const   XMLCh* const    uri,
        const   XMLCh* const    localname,
        const   XMLCh* const    qname
        , const Attributes&	attrs
    );

  
	virtual void startPrefixMapping
	(
		const	XMLCh* const	prefix,
		const	XMLCh* const	uri
	) ;

  
	virtual void endPrefixMapping
	(
		const	XMLCh* const	prefix
	) ;

  
	virtual void skippedEntity
	(
		const	XMLCh* const	name
	) ;

    
    virtual InputSource* resolveEntity
    (
        const   XMLCh* const    publicId
        , const XMLCh* const    systemId
    );

    
    virtual void error(const SAXParseException& exc);

  
    virtual void fatalError(const SAXParseException& exc);

  
    virtual void warning(const SAXParseException& exc);

    
    virtual void resetErrors();

    
    virtual void notationDecl
    (
        const   XMLCh* const    name
        , const XMLCh* const    publicId
        , const XMLCh* const    systemId
    );

    
    virtual void resetDocType();

  
    virtual void unparsedEntityDecl
    (
        const   XMLCh* const    name
        , const XMLCh* const    publicId
        , const XMLCh* const    systemId
        , const XMLCh* const    notationName
    );
    
    virtual void comment
    (
        const   XMLCh* const    chars
        , const unsigned int    length
    );

  
    virtual void endCDATA ();

  
    virtual void endDTD ();

  
    virtual void endEntity (const XMLCh* const name);

  
    virtual void startCDATA ();

  
    virtual void startDTD
    (
        const   XMLCh* const    name
        , const   XMLCh* const    publicId
        , const   XMLCh* const    systemId
    );

  
    virtual void startEntity (const XMLCh* const name);

    
    virtual void elementDecl
    (
        const   XMLCh* const    name
        , const XMLCh* const    model
    );

   
    virtual void attributeDecl
    (
        const   XMLCh* const    eName
        , const XMLCh* const    aName
        , const XMLCh* const    type
        , const XMLCh* const    mode
        , const XMLCh* const    value
    );

   
    virtual void internalEntityDecl
    (
        const   XMLCh* const    name
        , const XMLCh* const    value
    );

   
    virtual void externalEntityDecl
    (
        const   XMLCh* const    name
        , const XMLCh* const    publicId
        , const XMLCh* const    systemId
    );

    DefaultHandler() {};
    virtual ~DefaultHandler() {};

private:
	
    DefaultHandler(const DefaultHandler&);
    DefaultHandler& operator=(const DefaultHandler&);    
};



inline void DefaultHandler::characters(const   XMLCh* const
                                       ,const   unsigned int)
{
}

inline void DefaultHandler::endDocument()
{
}

inline void DefaultHandler::endElement(const	XMLCh* const
										, const XMLCh* const
										, const XMLCh* const)
{
}

inline void DefaultHandler::error(const SAXParseException&)
{
}

inline void DefaultHandler::fatalError(const SAXParseException& exc)
{
    throw exc;
}

inline void
DefaultHandler::ignorableWhitespace( const   XMLCh* const
                                    , const unsigned int)
{
}

inline void DefaultHandler::notationDecl(  const   XMLCh* const
											, const XMLCh* const
											, const XMLCh* const)
{
}

inline void
DefaultHandler::processingInstruction( const   XMLCh* const
										, const XMLCh* const)
{
}

inline void DefaultHandler::resetErrors()
{
}

inline void DefaultHandler::resetDocument()
{
}

inline void DefaultHandler::resetDocType()
{
}

inline InputSource*
DefaultHandler::resolveEntity( const   XMLCh* const
								, const XMLCh* const)
{
    return 0;
}

inline void
DefaultHandler::unparsedEntityDecl(const   XMLCh* const
									, const XMLCh* const
									, const XMLCh* const
									, const XMLCh* const)
{
}

inline void DefaultHandler::setDocumentLocator(const Locator* const)
{
}

inline void DefaultHandler::startDocument()
{
}

inline void
DefaultHandler::startElement(  const     XMLCh* const
								, const   XMLCh* const
								, const   XMLCh* const
								, const   Attributes&
)
{
}

inline void DefaultHandler::warning(const SAXParseException&)
{
}

inline void DefaultHandler::startPrefixMapping ( const	XMLCh* const
												,const	XMLCh* const)
{
}

inline void DefaultHandler::endPrefixMapping ( const	XMLCh* const)
{
}

inline void DefaultHandler::skippedEntity ( const	XMLCh* const)
{
}

inline void DefaultHandler::comment(  const   XMLCh* const
                                       , const unsigned int)
{
}

inline void DefaultHandler::endCDATA ()
{
}

inline void DefaultHandler::endDTD ()
{
}

inline void DefaultHandler::endEntity (const XMLCh* const)
{
}

inline void DefaultHandler::startCDATA ()
{
}

inline void DefaultHandler::startDTD(  const   XMLCh* const
                                        , const   XMLCh* const
                                        , const   XMLCh* const)
{
}

inline void DefaultHandler::startEntity (const XMLCh* const)
{
}

inline void DefaultHandler::attributeDecl(const XMLCh* const,
                                          const XMLCh* const,
                                          const XMLCh* const,
                                          const XMLCh* const,
                                          const XMLCh* const)
{
}

inline void DefaultHandler::elementDecl(const XMLCh* const,
                                        const XMLCh* const)
{
}

inline void DefaultHandler::externalEntityDecl(const XMLCh* const,
                                               const XMLCh* const,
                                               const XMLCh* const)
{
}

inline void DefaultHandler::internalEntityDecl(const XMLCh* const,
                                               const XMLCh* const)
{
}

}

#endif // ! DEFAULTHANDLER_HPP
