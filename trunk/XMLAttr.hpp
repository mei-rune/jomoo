

#if !defined(XMLATTR_HPP)
#define XMLATTR_HPP

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/QName.hpp>
#include <xercesc/framework/XMLAttDef.hpp>
#include <xercesc/validators/datatype/DatatypeValidator.hpp>

namespace XML
{

class XMLAttr
{
public:
  
    XMLAttr(MemoryManager* const manager = BOEPlatformUtils::fgMemoryManager);

    XMLAttr
    (
          const unsigned int        uriId
        , const XMLCh* const        attrName
        , const XMLCh* const        attrPrefix
        , const XMLCh* const        attrValue
        , const XMLAttDef::AttTypes type = XMLAttDef::CData
        , const bool                specified = true
        , MemoryManager* const      manager = BOEPlatformUtils::fgMemoryManager
        , DatatypeValidator * datatypeValidator = 0
        , const bool isSchema = false
    );
    XMLAttr
    (
        const unsigned int uriId
        , const XMLCh* const rawName
        , const XMLCh* const attrValue
        , const XMLAttDef::AttTypes type = XMLAttDef::CData
        , const bool specified = true
        , MemoryManager* const manager = BOEPlatformUtils::fgMemoryManager
        , DatatypeValidator * datatypeValidator = 0
        , const bool isSchema = false
    );

    
    ~XMLAttr();
    
    QName* getAttName() const;

    
    const XMLCh* getName() const;

    
    const XMLCh* getPrefix() const;

    
    const XMLCh* getQName() const;

    
    bool getSpecified() const;

    
    XMLAttDef::AttTypes getType() const;

    
    const XMLCh* getValue() const;

    
    unsigned int getURIId() const;

    
    const XMLCh* getValidatingTypeURI() const;

    
    const XMLCh* getValidatingTypeName() const;

    
    void set
    (
        const   unsigned int        uriId
        , const XMLCh* const        attrName
        , const XMLCh* const        attrPrefix
        , const XMLCh* const        attrValue
        , const XMLAttDef::AttTypes type = XMLAttDef::CData
        , DatatypeValidator * datatypeValidator = 0
        , const bool isSchema = false
    );

    
    void set
    (
        const   unsigned int        uriId
        , const XMLCh* const        attrRawName
        , const XMLCh* const        attrValue
        , const XMLAttDef::AttTypes type = XMLAttDef::CData
        , DatatypeValidator * datatypeValidator = 0
        , const bool isSchema = false
    );

    
    void setName
    (
        const   unsigned int        uriId
        , const XMLCh* const        attrName
        , const XMLCh* const        attrPrefix
    );

    
    void setSpecified(const bool newValue);

    
    void setType(const XMLAttDef::AttTypes newType);

    
    void setValue(const XMLCh* const newValue);

    
    void setURIId(const unsigned int uriId);

    
    void setDatatypeValidator(DatatypeValidator * datatypeValidator);

    
    void setSchemaValidated(const bool isSchema);

    



private :
    
    XMLAttr(const XMLAttr&);
    XMLAttr& operator=(const XMLAttr&);


    
    void cleanUp();


    
    bool                fSpecified;
    XMLAttDef::AttTypes fType;
    unsigned int        fValueBufSz;
    XMLCh*              fValue;
    QName*              fAttName;
    MemoryManager*      fMemoryManager;
    DatatypeValidator * fDatatypeValidator;
    bool                fIsSchemaValidated;
};


inline XMLAttr::~XMLAttr()
{
    cleanUp();
}



inline QName* XMLAttr::getAttName() const
{
    return fAttName;
}

inline const XMLCh* XMLAttr::getName() const
{
    return fAttName->getLocalPart();
}

inline const XMLCh* XMLAttr::getPrefix() const
{
    return fAttName->getPrefix();
}

inline bool XMLAttr::getSpecified() const
{
    return fSpecified;
}

inline XMLAttDef::AttTypes XMLAttr::getType() const
{
    return fType;
}

inline const XMLCh* XMLAttr::getValue() const
{
    return fValue;
}

inline unsigned int XMLAttr::getURIId() const
{
    return fAttName->getURI();
}

inline const XMLCh* XMLAttr::getValidatingTypeName() const
{
    if(fIsSchemaValidated)
    {
        if(!fDatatypeValidator || fDatatypeValidator->getAnonymous())
            return 0; 
        return fDatatypeValidator->getTypeLocalName();
    }
    else
    {
        return XMLAttDef::getAttTypeString(fType, fMemoryManager);
    }
}

inline const XMLCh* XMLAttr::getValidatingTypeURI() const
{
    if(fIsSchemaValidated)
    {
        if(!fDatatypeValidator || fDatatypeValidator->getAnonymous())
            return 0; 
        return fDatatypeValidator->getTypeUri();
    }
    else
    {
        return 0;
    }
}

// ---------------------------------------------------------------------------
//  XMLAttr: Setter methods
// ---------------------------------------------------------------------------
inline void XMLAttr::set(const  unsigned int        uriId
                        , const XMLCh* const        attrName
                        , const XMLCh* const        attrPrefix
                        , const XMLCh* const        attrValue
                        , const XMLAttDef::AttTypes type
                        , DatatypeValidator * datatypeValidator 
                        , const bool isSchema )
{
    // Set the name info and the value via their respective calls
    fAttName->setName(attrPrefix, attrName, uriId);
    setValue(attrValue);

    // And store the type
    fType = type;

    // and set up info for DOM type info 
    fIsSchemaValidated = isSchema;
    fDatatypeValidator = datatypeValidator;
}

inline void XMLAttr::set(const  unsigned int        uriId
                        , const XMLCh* const        attrRawName
                        , const XMLCh* const        attrValue
                        , const XMLAttDef::AttTypes type
                        , DatatypeValidator * datatypeValidator 
                        , const bool isSchema )
{
    // Set the name info and the value via their respective calls
    fAttName->setName(attrRawName, uriId);
    setValue(attrValue);

    // And store the type
    fType = type;

    // and set up info for DOM type info 
    fIsSchemaValidated = isSchema;
    fDatatypeValidator = datatypeValidator;
}

inline void XMLAttr::setType(const XMLAttDef::AttTypes newValue)
{
    fType = newValue;
}

inline void XMLAttr::setSpecified(const bool newValue)
{
    fSpecified = newValue;
}

inline void XMLAttr::setDatatypeValidator(DatatypeValidator *datatypeValidator)
{
    fDatatypeValidator = datatypeValidator;
}

inline void XMLAttr::setSchemaValidated(const bool isSchema)
{
    fIsSchemaValidated = isSchema;
}

}

#endif
