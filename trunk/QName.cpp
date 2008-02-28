
#include <xercesc/util/QName.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>

namespace XML 
{

// ---------------------------------------------------------------------------
//  QName: Constructors �� Destructor
// ---------------------------------------------------------------------------
QName::QName(MemoryManager* const manager) :

    fMemoryManager(manager)
    , fPrefix(0)
    , fPrefixBufSz(0)
    , fLocalPart(0)
    , fLocalPartBufSz(0)
    , fRawName(0)
    , fRawNameBufSz(0)
    , fURIId(0)
{
}

QName::QName( const XMLCh* const   prefix
            , const XMLCh* const   localPart
            , const unsigned int   uriId
            , MemoryManager* const manager) :

    fMemoryManager(manager)
    , fPrefix(0)
    , fPrefixBufSz(0)
    , fLocalPart(0)
    , fLocalPartBufSz(0)
    , fRawName(0)
    , fRawNameBufSz(0)
    , fURIId(0)
{
    try
    {
        setName(prefix, localPart, uriId);
    }
    catch(const OutOfMemoryException&)
    {
        throw;
    }
    catch(...)
    {
        cleanUp();
    }
}

QName::QName( const XMLCh* const rawName
            , const unsigned int uriId
            , MemoryManager* const manager) :

    fMemoryManager(manager)
    , fPrefix(0)
    , fPrefixBufSz(0)
    , fLocalPart(0)
    , fLocalPartBufSz(0)
    , fRawName(0)
    , fRawNameBufSz(0)
    , fURIId(0)
{
    try
    {
        setName(rawName, uriId);
    }
    catch(const OutOfMemoryException&)
    {
        throw;
    }
    catch(...)
    {
        cleanUp();
    }
}

QName::~QName()
{
	cleanUp();
}

// ---------------------------------------------------------------------------
//  QName: Copy Constructors
// ---------------------------------------------------------------------------
QName::QName(const QName& qname) :

    fMemoryManager(qname.fMemoryManager)
    , fPrefix(0)
    , fPrefixBufSz(0)
    , fLocalPart(0)
    , fLocalPartBufSz(0)
    , fRawName(0)
    , fRawNameBufSz(0)
    , fURIId(0)
{
    unsigned int newLen;

    newLen = XMLString::stringLen(qname.getLocalPart());
    fLocalPartBufSz = newLen + 8;
    fLocalPart = (XMLCh*) fMemoryManager->allocate
    (
        (fLocalPartBufSz + 1) * sizeof(XMLCh)
    ); //new XMLCh[fLocalPartBufSz + 1];
    XMLString::moveChars(fLocalPart, qname.getLocalPart(), newLen + 1);

    newLen = XMLString::stringLen(qname.getPrefix());
    fPrefixBufSz = newLen + 8;
    fPrefix = (XMLCh*) fMemoryManager->allocate
    (
        (fPrefixBufSz + 1) * sizeof(XMLCh)
    ); //new XMLCh[fPrefixBufSz + 1];
    XMLString::moveChars(fPrefix, qname.getPrefix(), newLen + 1);

    fURIId = qname.getURI();
}

// ---------------------------------------------------------------------------
//  QName: Getter methods
// ---------------------------------------------------------------------------
const XMLCh* QName::getRawName() const
{
    if (!fRawName || !*fRawName)
    {
        if (*fPrefix)
        {
            const unsigned int neededLen = fPrefixBufSz + fLocalPartBufSz + 1;

            if (!fRawName || (neededLen > fRawNameBufSz))
            {
                fMemoryManager->deallocate(fRawName); //delete [] fRawName;

                // We have to cast off the const'ness to do this
                ((QName*)this)->fRawNameBufSz = neededLen;
                ((QName*)this)->fRawName = (XMLCh*) fMemoryManager->allocate
                (
                    (neededLen + 1) * sizeof(XMLCh)
                ); //new XMLCh[neededLen + 1];

                // Make sure its initially empty
                *fRawName = 0;
            }

            const unsigned int prefixLen = XMLString::stringLen(fPrefix);

            XMLString::moveChars(fRawName, fPrefix, prefixLen);
            fRawName[prefixLen] = chColon;
            XMLString::copyString(&fRawName[prefixLen+1], fLocalPart);
        }
         else
        {
            return fLocalPart;
        }
    }
    return fRawName;
}

XMLCh* QName::getRawName()
{
    //
    //  If there is no buffer, or if there is but we've not faulted in the
    //  value yet, then we have to do that now.
    //
    if (!fRawName || !*fRawName)
    {
        //
        //  If we have a prefix, then do the prefix:name version. Else, its
        //  just the name.
        //
        if (*fPrefix)
        {
            //
            //  Calculate the worst case size buffer we will need. We use the
            //  current high water marks of the prefix and name buffers, so it
            //  might be a little wasteful of memory but we don't have to do
            //  string len operations on the two strings.
            //
            const unsigned int neededLen = fPrefixBufSz + fLocalPartBufSz + 1;

            //
            //  If no buffer, or the current one is too small, then allocate one
            //  and get rid of any old one.
            //
            if (!fRawName || (neededLen > fRawNameBufSz))
            {
                fMemoryManager->deallocate(fRawName); //delete [] fRawName;

                // We have to cast off the const'ness to do this
                ((QName*)this)->fRawNameBufSz = neededLen;
                ((QName*)this)->fRawName = (XMLCh*) fMemoryManager->allocate
                (
                    (neededLen + 1) * sizeof(XMLCh)
                ); //new XMLCh[neededLen + 1];

                // Make sure its initially empty
                *fRawName = 0;
            }


            const unsigned int prefixLen = XMLString::stringLen(fPrefix);

            XMLString::moveChars(fRawName, fPrefix, prefixLen);
            fRawName[prefixLen] = chColon;
            XMLString::copyString(&fRawName[prefixLen+1], fLocalPart);
        }
         else
        {
            return fLocalPart;
        }
    }
    return fRawName;
}

// ---------------------------------------------------------------------------
//  QName: Setter methods
// ---------------------------------------------------------------------------
void QName::setName(const XMLCh* const    prefix
                  , const XMLCh* const    localPart
                  , const unsigned int    uriId)
{
    setPrefix(prefix);
    setLocalPart(localPart);

    if (fRawName)
        *fRawName = 0;

    fURIId = uriId;
}

void QName::setName(const XMLCh* const    rawName
                  , const unsigned int    uriId)
{
    unsigned int newLen;

    newLen = XMLString::stringLen(rawName);
    if (!fRawNameBufSz || (newLen > fRawNameBufSz))
    {
        fMemoryManager->deallocate(fRawName); //delete [] fRawName;
        fRawNameBufSz = newLen + 8;
        fRawName = (XMLCh*) fMemoryManager->allocate
        (
            (fRawNameBufSz + 1) * sizeof(XMLCh)
        ); //new XMLCh[fRawNameBufSz + 1];
    }
    XMLString::moveChars(fRawName, rawName, newLen + 1);

    //find out the prefix and localPart from the rawName
    const int colonInd = XMLString::indexOf(rawName, chColon);
    if (colonInd >= 0)
    {
        setNPrefix(rawName, colonInd);
    }
     else
    {
        // No colon, so we just have a name with no prefix
        setPrefix(XMLUni::fgZeroLenString);
    }

    setNLocalPart(&rawName[colonInd+1], newLen-colonInd-1);


    // And finally store the URI id parameter
    fURIId = uriId;
}

void QName::setPrefix(const XMLCh* prefix)
{
    unsigned int newLen;

    newLen = XMLString::stringLen(prefix);
    if (!fPrefixBufSz || (newLen > fPrefixBufSz))
    {
        fMemoryManager->deallocate(fPrefix); //delete [] fPrefix;
        fPrefixBufSz = newLen + 8;
        fPrefix = (XMLCh*) fMemoryManager->allocate
        (
            (fPrefixBufSz + 1) * sizeof(XMLCh)
        ); //new XMLCh[fPrefixBufSz + 1];
    }
    XMLString::moveChars(fPrefix, prefix, newLen + 1);
}

void QName::setNPrefix(const XMLCh* prefix, const unsigned int newLen)
{
    if (!fPrefixBufSz || (newLen > fPrefixBufSz))
    {
        fMemoryManager->deallocate(fPrefix); //delete [] fPrefix;
        fPrefixBufSz = newLen + 8;
        fPrefix = (XMLCh*) fMemoryManager->allocate
        (
            (fPrefixBufSz + 1) * sizeof(XMLCh)
        ); //new XMLCh[fPrefixBufSz + 1];
    }
    XMLString::moveChars(fPrefix, prefix, newLen);
    fPrefix[newLen] = chNull;
}

void QName::setLocalPart(const XMLCh* localPart)
{
    unsigned int newLen;

    newLen = XMLString::stringLen(localPart);
    if (!fLocalPartBufSz || (newLen > fLocalPartBufSz))
    {
        fMemoryManager->deallocate(fLocalPart); //delete [] fLocalPart;
        fLocalPartBufSz = newLen + 8;
        fLocalPart = (XMLCh*) fMemoryManager->allocate
        (
            (fLocalPartBufSz + 1) * sizeof(XMLCh)
        ); //new XMLCh[fLocalPartBufSz + 1];
    }
    XMLString::moveChars(fLocalPart, localPart, newLen + 1);
}

void QName::setNLocalPart(const XMLCh* localPart, const unsigned int newLen)
{
    if (!fLocalPartBufSz || (newLen > fLocalPartBufSz))
    {
        fMemoryManager->deallocate(fLocalPart); //delete [] fLocalPart;
        fLocalPartBufSz = newLen + 8;
        fLocalPart = (XMLCh*) fMemoryManager->allocate
        (
            (fLocalPartBufSz + 1) * sizeof(XMLCh)
        ); //new XMLCh[fLocalPartBufSz + 1];
    }
    XMLString::moveChars(fLocalPart, localPart, newLen);
    fLocalPart[newLen] = chNull;
}

void QName::setValues(const QName& qname)
{
    setPrefix(qname.getPrefix());
    setLocalPart(qname.getLocalPart());
    setURI(qname.getURI());
}

// -----------------------------------------------------------------------
//  comparison
// -----------------------------------------------------------------------
bool QName::operator==(const QName& qname) const
{
    if (fURIId == 0) // null URI
        return (XMLString::equals(getRawName(),qname.getRawName()));

    return ((fURIId == qname.getURI()) &&
           (XMLString::equals(fLocalPart, qname.getLocalPart())));
}

// ---------------------------------------------------------------------------
//  QName: Private, helper methods
// ---------------------------------------------------------------------------
void QName::cleanUp()
{
    fMemoryManager->deallocate(fLocalPart); //delete [] fLocalPart;
    fMemoryManager->deallocate(fPrefix); //delete [] fPrefix;
    fMemoryManager->deallocate(fRawName); //delete [] fRawName;
    fLocalPart = fPrefix = fRawName = 0;
}

}
