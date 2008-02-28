

#if !defined(XMLCHAR_HPP)
#define XMLCHAR_HPP

#include <XMLUniDefs.hpp>

namespace UTIL {

// ---------------------------------------------------------------------------
//  This file defines Char and utility that conforms to XML 1.0 and XML 1.1
// ---------------------------------------------------------------------------
// Masks for the fgCharCharsTable1_0 array
const XMLByte   gLetterCharMask             = 0x1;
const XMLByte   gFirstNameCharMask          = 0x2;
const XMLByte   gNameCharMask               = 0x4;
const XMLByte   gPlainContentCharMask       = 0x8;
const XMLByte   gSpecialStartTagCharMask    = 0x10;
const XMLByte   gControlCharMask            = 0x20;
const XMLByte   gXMLCharMask                = 0x40;
const XMLByte   gWhitespaceCharMask         = 0x80;

// ---------------------------------------------------------------------------
//  This class is for XML 1.0
// ---------------------------------------------------------------------------
class XMLUTIL_EXPORT XMLChar1_0
{
public:
    /**
	 * 指定的字符串是不是全都是空白符
	 * @param[ in ] toCheck 待检测的字符串
	 * @param[ in ] count 待检测的字符串的长度
	 * @return 全都是空白符返回true,否则返回false
	 */
    static bool isAllSpaces
    (
        const   XMLCh* const    toCheck
        , const unsigned int    count
    );

	/**
	 * 指定的字符串是不是含有空白符
	 * @param[ in ] toCheck 待检测的字符串
	 * @param[ in ] count 待检测的字符串的长度
	 * @return 含有空白符返回true,否则返回false
	 */
    static bool containsWhiteSpace
    (
        const   XMLCh* const    toCheck
        , const unsigned int    count
    );

    static bool isValidNmtoken
    (
        const   XMLCh*        const    toCheck
      , const   unsigned int           count
    );

    static bool isValidName
    (
        const   XMLCh* const    toCheck
        , const unsigned int    count
    );

    static bool isValidNCName
    (
        const   XMLCh* const    toCheck
        , const unsigned int    count
    );

    static bool isValidQName
    (
        const   XMLCh* const    toCheck
        , const unsigned int    count
    );

    // -----------------------------------------------------------------------
    //  Public, static methods, check the XMLCh
    //  surrogate pair is assumed if second parameter is not null
    // -----------------------------------------------------------------------
    static bool isXMLLetter(const XMLCh toCheck, const XMLCh toCheck2 = 0);
    static bool isFirstNameChar(const XMLCh toCheck, const XMLCh toCheck2 = 0);
    static bool isNameChar(const XMLCh toCheck, const XMLCh toCheck2 = 0);
    static bool isPlainContentChar(const XMLCh toCheck, const XMLCh toCheck2 = 0);
    static bool isSpecialStartTagChar(const XMLCh toCheck, const XMLCh toCheck2 = 0);
    static bool isXMLChar(const XMLCh toCheck, const XMLCh toCheck2 = 0);

	/**
	 * 指定的字符是不是空白符
	 * @param[ in ] toCheck 待检测的字符
	 * @return 是空白符返回true,否则返回false
	 */
    static bool isWhitespace(const XMLCh toCheck);
    static bool isWhitespace(const XMLCh toCheck, const XMLCh toCheck2);
    static bool isControlChar(const XMLCh toCheck, const XMLCh toCheck2 = 0);

    static bool isPublicIdChar(const XMLCh toCheck, const XMLCh toCheck2 = 0);

    // -----------------------------------------------------------------------
    //  Special Non-conformant Public, static methods
    // -----------------------------------------------------------------------
    /**
      * Return true if NEL (0x85) and LSEP (0x2028) to be treated as white space char.
      */
    static bool isNELRecognized();

    /**
      * Method to enable NEL (0x85) and LSEP (0x2028) to be treated as white space char.
      */
    static void enableNELWS();

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XMLChar1_0();

    // -----------------------------------------------------------------------
    //  Static data members
    //
    //  fgCharCharsTable1_0
    //      The character characteristics table. Bits in each byte, represent
    //      the characteristics of each character. It is generated via some
    //      code and then hard coded into the cpp file for speed.
    //
    //  fNEL
    //      Flag to respresents whether NEL and LSEP newline recognition is enabled
    //      or disabled
    // -----------------------------------------------------------------------
    static XMLByte  fgCharCharsTable1_0[0x10000];
    static bool     enableNEL;

    friend class XMLReader;
};


// ---------------------------------------------------------------------------
//  XMLReader: Public, static methods
// ---------------------------------------------------------------------------
inline bool XMLChar1_0::isXMLLetter(const XMLCh toCheck, const XMLCh toCheck2)
{
    if (!toCheck2)
        return ((fgCharCharsTable1_0[toCheck] & gLetterCharMask) != 0);
    return false;
}

inline bool XMLChar1_0::isFirstNameChar(const XMLCh toCheck, const XMLCh toCheck2)
{
    if (!toCheck2)
        return ((fgCharCharsTable1_0[toCheck] & gFirstNameCharMask) != 0);
    return false;
}

inline bool XMLChar1_0::isNameChar(const XMLCh toCheck, const XMLCh toCheck2)
{
    if (!toCheck2)
        return ((fgCharCharsTable1_0[toCheck] & gNameCharMask) != 0);
    return false;
}

inline bool XMLChar1_0::isPlainContentChar(const XMLCh toCheck, const XMLCh toCheck2)
{
    if (!toCheck2)
        return ((fgCharCharsTable1_0[toCheck] & gPlainContentCharMask) != 0);
    else {
        if ((toCheck >= 0xD800) && (toCheck <= 0xDBFF))
           if ((toCheck2 >= 0xDC00) && (toCheck2 <= 0xDFFF))
               return true;
    }
    return false;
}


inline bool XMLChar1_0::isSpecialStartTagChar(const XMLCh toCheck, const XMLCh toCheck2)
{
    if (!toCheck2)
        return ((fgCharCharsTable1_0[toCheck] & gSpecialStartTagCharMask) != 0);
    return false;
}

inline bool XMLChar1_0::isXMLChar(const XMLCh toCheck, const XMLCh toCheck2)
{
    if (!toCheck2)
        return ((fgCharCharsTable1_0[toCheck] & gXMLCharMask) != 0);
    else {
        if ((toCheck >= 0xD800) && (toCheck <= 0xDBFF))
           if ((toCheck2 >= 0xDC00) && (toCheck2 <= 0xDFFF))
               return true;
    }
    return false;
}

inline bool XMLChar1_0::isWhitespace(const XMLCh toCheck)
{
    return ((fgCharCharsTable1_0[toCheck] & gWhitespaceCharMask) != 0);
}

inline bool XMLChar1_0::isWhitespace(const XMLCh toCheck, const XMLCh toCheck2)
{
    if (!toCheck2)
        return ((fgCharCharsTable1_0[toCheck] & gWhitespaceCharMask) != 0);
    return false;
}

inline bool XMLChar1_0::isControlChar(const XMLCh toCheck, const XMLCh toCheck2)
{
    if (!toCheck2)
        return ((fgCharCharsTable1_0[toCheck] & gControlCharMask) != 0);
    return false;
}

inline bool XMLChar1_0::isNELRecognized() {

    return enableNEL;
}


// ---------------------------------------------------------------------------
//  This class is for XML 1.1
// ---------------------------------------------------------------------------
class XMLUTIL_EXPORT XMLChar1_1
{
public:
    // -----------------------------------------------------------------------
    //  Public, static methods, check the string
    // -----------------------------------------------------------------------
    static bool isAllSpaces
    (
        const   XMLCh* const    toCheck
        , const unsigned int    count
    );

    static bool containsWhiteSpace
    (
        const   XMLCh* const    toCheck
        , const unsigned int    count
    );

    static bool isValidNmtoken
    (
        const   XMLCh*        const    toCheck
      , const   unsigned int           count
    );

    static bool isValidName
    (
        const   XMLCh* const    toCheck
        , const unsigned int    count
    );

    static bool isValidNCName
    (
        const   XMLCh* const    toCheck
        , const unsigned int    count
    );

    static bool isValidQName
    (
        const   XMLCh* const    toCheck
        , const unsigned int    count
    );

    // -----------------------------------------------------------------------
    //  Public, static methods, check the XMLCh
    // -----------------------------------------------------------------------
    static bool isXMLLetter(const XMLCh toCheck, const XMLCh toCheck2 = 0);
    static bool isFirstNameChar(const XMLCh toCheck, const XMLCh toCheck2 = 0);
    static bool isNameChar(const XMLCh toCheck, const XMLCh toCheck2 = 0);
    static bool isPlainContentChar(const XMLCh toCheck, const XMLCh toCheck2 = 0);
    static bool isSpecialStartTagChar(const XMLCh toCheck, const XMLCh toCheck2 = 0);
    static bool isXMLChar(const XMLCh toCheck, const XMLCh toCheck2 = 0);
    static bool isWhitespace(const XMLCh toCheck, const XMLCh toCheck2 = 0);
    static bool isControlChar(const XMLCh toCheck, const XMLCh toCheck2 = 0);

    static bool isPublicIdChar(const XMLCh toCheck, const XMLCh toCheck2 = 0);

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XMLChar1_1();

    // -----------------------------------------------------------------------
    //  Static data members
    //
    //  fgCharCharsTable1_1
    //      The character characteristics table. Bits in each byte, represent
    //      the characteristics of each character. It is generated via some
    //      code and then hard coded into the cpp file for speed.
    //
    // -----------------------------------------------------------------------
    static XMLByte  fgCharCharsTable1_1[0x10000];

    friend class XMLReader;
};


// ---------------------------------------------------------------------------
//  XMLReader: Public, static methods
// ---------------------------------------------------------------------------
inline bool XMLChar1_1::isXMLLetter(const XMLCh toCheck, const XMLCh toCheck2)
{
    if (!toCheck2)
        return ((fgCharCharsTable1_1[toCheck] & gLetterCharMask) != 0);
    return false;
}

inline bool XMLChar1_1::isFirstNameChar(const XMLCh toCheck, const XMLCh toCheck2)
{
    if (!toCheck2)
        return ((fgCharCharsTable1_1[toCheck] & gFirstNameCharMask) != 0);
    else {
        if ((toCheck >= 0xD800) && (toCheck <= 0xDB7F))
           if ((toCheck2 >= 0xDC00) && (toCheck2 <= 0xDFFF))
               return true;
    }
    return false;
}

inline bool XMLChar1_1::isNameChar(const XMLCh toCheck, const XMLCh toCheck2)
{
    if (!toCheck2)
        return ((fgCharCharsTable1_1[toCheck] & gNameCharMask) != 0);
    else {
        if ((toCheck >= 0xD800) && (toCheck <= 0xDB7F))
           if ((toCheck2 >= 0xDC00) && (toCheck2 <= 0xDFFF))
               return true;
    }
    return false;
}

inline bool XMLChar1_1::isPlainContentChar(const XMLCh toCheck, const XMLCh toCheck2)
{
    if (!toCheck2)
        return ((fgCharCharsTable1_1[toCheck] & gPlainContentCharMask) != 0);
    else {
        if ((toCheck >= 0xD800) && (toCheck <= 0xDBFF))
           if ((toCheck2 >= 0xDC00) && (toCheck2 <= 0xDFFF))
               return true;
    }
    return false;
}


inline bool XMLChar1_1::isSpecialStartTagChar(const XMLCh toCheck, const XMLCh toCheck2)
{
    if (!toCheck2)
        return ((fgCharCharsTable1_1[toCheck] & gSpecialStartTagCharMask) != 0);
    return false;
}

inline bool XMLChar1_1::isXMLChar(const XMLCh toCheck, const XMLCh toCheck2)
{
    if (!toCheck2)
        return ((fgCharCharsTable1_1[toCheck] & gXMLCharMask) != 0);
    else {
        if ((toCheck >= 0xD800) && (toCheck <= 0xDBFF))
           if ((toCheck2 >= 0xDC00) && (toCheck2 <= 0xDFFF))
               return true;
    }
    return false;
}

inline bool XMLChar1_1::isWhitespace(const XMLCh toCheck, const XMLCh toCheck2)
{
    if (!toCheck2)
        return ((fgCharCharsTable1_1[toCheck] & gWhitespaceCharMask) != 0);
    return false;
}

inline bool XMLChar1_1::isControlChar(const XMLCh toCheck, const XMLCh toCheck2)
{
    if (!toCheck2)
        return ((fgCharCharsTable1_1[toCheck] & gControlCharMask) != 0);
    return false;
}


} ///namespace UTIL

#endif
