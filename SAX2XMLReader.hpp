

#ifndef SAX2XMLReader_HPP
#define SAX2XMLReader_HPP

namespace XML
{

class ContentHandler ;
class DTDHandler;
class EntityResolver;
class ErrorHandler;
class InputSource;
class LexicalHandler;
class DeclHandler;
class XMLDocumentHandler;
class Grammar;

class SAX2XMLReader
{
public:
    
    enum ValSchemes
    {
          Val_Never
        , Val_Always
        , Val_Auto
    };
    
    SAX2XMLReader()
    {
    }
    /** The destructor */
    virtual ~SAX2XMLReader()
    {
    }
    
    virtual ContentHandler* getContentHandler() const = 0 ;

    
    virtual DTDHandler* getDTDHandler() const = 0;

    
    virtual EntityResolver* getEntityResolver() const = 0 ;

    
    virtual ErrorHandler* getErrorHandler() const = 0 ;

	
	virtual bool getFeature(const XMLCh* const name) const = 0;

	
	virtual void* getProperty(const XMLCh* const name) const = 0 ;

  
    virtual void setContentHandler(ContentHandler* const handler) = 0;

  
    virtual void setDTDHandler(DTDHandler* const handler) = 0;

    virtual void setEntityResolver(EntityResolver* const resolver) = 0;

    virtual void setErrorHandler(ErrorHandler* const handler) = 0;

	virtual void setFeature(const XMLCh* const name, const bool value) = 0;

	virtual void setProperty(const XMLCh* const name, void* value) = 0 ;

    virtual void parse
    (
        const   InputSource&    source
    ) = 0;

    virtual void parse
    (
        const   XMLCh* const    systemId
    ) = 0;

    virtual void parse
    (
        const   char* const     systemId
    ) = 0;
	
    virtual DeclHandler* getDeclarationHandler() const = 0 ;

    virtual LexicalHandler* getLexicalHandler() const = 0 ;

    virtual void setDeclarationHandler(DeclHandler* const handler) = 0;

    virtual void setLexicalHandler(LexicalHandler* const handler) = 0;

	virtual XMLValidator* getValidator() const = 0;

    virtual int getErrorCount() const = 0 ;

    virtual bool getExitOnFirstFatalError() const = 0;

    virtual bool getValidationConstraintFatal() const = 0;

    virtual const XMLCh* getURIText(unsigned int uriId) const = 0;

    virtual unsigned int getSrcOffset() const = 0;

	virtual void setValidator(XMLValidator* valueToAdopt) = 0;

    virtual void setValidationConstraintFatal(const bool newState) = 0;

    virtual void installAdvDocHandler(XMLDocumentHandler* const toInstall) = 0;

    virtual bool removeAdvDocHandler(XMLDocumentHandler* const toRemove) = 0;

private :
    SAX2XMLReader(const SAX2XMLReader&);

    SAX2XMLReader& operator=(const SAX2XMLReader&);

};

}

#endif
