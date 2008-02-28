
/**
 * -*- C++ -*-
 * -------------------------------------------------------------------------------
 * - °Ë®q°–®r ®q°–®r		          XML_Expat_Reader.h,v 1.0 2005/07/14 12:41:54
 *  ®u®ê®Ä®Ä®é ®q®q °–®r
 * ¶ÚÃÔ¶ÚÃÔÃÔ| ®t------
 * -------------------------------------------------------------------------------
 */

#ifndef _XML_EXPAT_READER_H_
#define _XML_EXPAT_READER_H_


#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include "xml/SAX2XMLReader.H"
#include "xml/XML_expat.H"

class XML_Expat_Reader : public SAX2XMLReader
{
public:
	XML_Expat_Reader(void);

	~XML_Expat_Reader(void);
    
    virtual ContentHandler* getContentHandler() const ;

    virtual DTDHandler* getDTDHandler() const ;

    virtual EntityResolver* getEntityResolver() const ;

    virtual ErrorHandler* getErrorHandler() const ;
	
	virtual bool getFeature(const XMLCh* const name) const ;
	
	virtual void* getProperty(const XMLCh* const name) const ;

    virtual void setContentHandler(ContentHandler* const handler) ;

    virtual void setDTDHandler(DTDHandler* const handler) ;

    virtual void setEntityResolver(EntityResolver* const resolver) ;

    virtual void setErrorHandler(ErrorHandler* const handler) ;

	virtual void setFeature(const XMLCh* const name, const bool value) ;

	virtual void setProperty(const XMLCh* const name, void* value) ;

    virtual int parse ( const   char* const  buffer , size_t len,  bool isfinal ) ;
	
    virtual DeclHandler* getDeclarationHandler() const  ;

    virtual LexicalHandler* getLexicalHandler() const ;

    virtual void setDeclarationHandler(DeclHandler* const handler) ;

    virtual void setLexicalHandler(LexicalHandler* const handler) ;

	virtual XMLValidator* getValidator() const;

    virtual int getErrorCount() const ;

    virtual bool getExitOnFirstFatalError() const ;

    virtual bool getValidationConstraintFatal() const ;

    virtual const XMLCh* getURIText(unsigned int uriId) const ;

    virtual unsigned int getSrcOffset() const ;

	virtual void setValidator(XMLValidator* valueToAdopt) ;

    virtual void setValidationConstraintFatal(const bool newState) ;

    virtual void installAdvDocHandler(XMLDocumentHandler* const toInstall);

    virtual bool removeAdvDocHandler(XMLDocumentHandler* const toRemove);

private:

	DECLARE_NO_COPY_CLASS( XML_Expat_Reader );

	XML_Parser _parser;

	XML_Memory_Handling_Suite _suite;

	ContentHandler* contenthandler_;

	DTDHandler* dtdhandler_;

	EntityResolver* entityresolver_;

	ErrorHandler* errorhandler_;

	DeclHandler* declhandler_;

	LexicalHandler* lexicalhandler_;

	XMLValidator* xmlvalidator_; 

	int errorcount_;
};

#endif // _XML_EXPAT_READER_H_