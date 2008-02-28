

#if !defined(QNAME_HPP)
#define QNAME_HPP

//#include <xercesc/util/XMLString.hpp>
//#include <xercesc/util/XMLUniDefs.hpp>
//#include <xercesc/util/XMemory.hpp>
//#include <xercesc/util/PlatformUtils.hpp>
//#include <xercesc/internal/XSerializable.hpp>

namespace XML
{

class XMLUTIL_EXPORT QName
{
public :

	QName(MemoryManager* const manager = BOEPlatformUtils::fgMemoryManager);


	QName
    (
          const XMLCh* const   prefix
        , const XMLCh* const   localPart
	    , const unsigned int   uriId
        , MemoryManager* const manager = BOEPlatformUtils::fgMemoryManager
    );


	QName
    (
          const XMLCh* const   rawName
	    , const unsigned int   uriId
        , MemoryManager* const manager = BOEPlatformUtils::fgMemoryManager
    );


	QName(const QName& qname);

    ~QName();

    // -----------------------------------------------------------------------
    //  Getters
    // -----------------------------------------------------------------------
    const XMLCh* getPrefix() const;
    XMLCh* getPrefix();

    const XMLCh* getLocalPart() const;
    XMLCh* getLocalPart();

    unsigned int getURI() const;

    const XMLCh* getRawName() const;
    XMLCh* getRawName();

    MemoryManager* getMemoryManager() const;

    // -----------------------------------------------------------------------
    //  Setters
    // -----------------------------------------------------------------------
    void setName
    (
        const XMLCh* const        prefix
      , const XMLCh* const        localPart
	   , const unsigned int        uriId
    );

    void setName
    (
        const XMLCh* const        rawName
	   , const unsigned int        uriId
    );

    void setPrefix(const XMLCh*) ;
    void setLocalPart(const XMLCh*) ;
    void setNPrefix(const XMLCh*, const unsigned int) ;
    void setNLocalPart(const XMLCh*, const unsigned int) ;
    void setURI(const unsigned int) ;

    void setValues(const QName& qname);

    // -----------------------------------------------------------------------
    //  comparison
    // -----------------------------------------------------------------------
    bool operator==(const QName&) const;

    // -----------------------------------------------------------------------
    //  Misc
    // -----------------------------------------------------------------------
    void cleanUp();

private :

    QName& operator=(const QName&);

    MemoryManager*      fMemoryManager;
    XMLCh*              fPrefix;
    unsigned int        fPrefixBufSz;
    XMLCh*              fLocalPart;
    unsigned int        fLocalPartBufSz;
    XMLCh*              fRawName;
    unsigned int        fRawNameBufSz;
    unsigned int        fURIId;
};

// ---------------------------------------------------------------------------
//  QName: Getter methods
// ---------------------------------------------------------------------------
inline const XMLCh* QName::getPrefix() const
{
	return fPrefix;
}

inline XMLCh* QName::getPrefix()
{
	return fPrefix;
}

inline const XMLCh* QName::getLocalPart() const
{
	return fLocalPart;
}

inline XMLCh* QName::getLocalPart()
{
	return fLocalPart;
}

inline unsigned int QName::getURI() const
{
	return fURIId;
}

inline MemoryManager* QName::getMemoryManager() const
{
    return fMemoryManager;
}

// ---------------------------------------------------------------------------
//  QName: Setter methods
// ---------------------------------------------------------------------------
inline void QName::setURI(const unsigned int uriId)
{
    fURIId = uriId;
}

}

#endif
