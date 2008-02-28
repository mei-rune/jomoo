
/**
 * -*- C++ -*-
 * -------------------------------------------------------------------------------
 * - °Ë®q°–®r ®q°–®r		                XML_Helper.h,v 1.0 2005/03/18 12:41:54
 *  ®u®ê®Ä®Ä®é ®q®q °–®r
 * ¶ÚÃÔ¶ÚÃÔÃÔ| ®t------
 * -------------------------------------------------------------------------------
 */

#ifndef _XML_Helper_H_
#define _XML_Helper_H_


#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include "xml_def.h"
#include "util/tstring.h"
#include <xercesc/dom/DOM.hpp>
#include <iostream>

_bt_xml_begin

XERCES_CPP_NAMESPACE_USE

class StrX
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    StrX(const XMLCh* const toTranscode)
    {
        // Call the private transcoding method
        fLocalForm = XERCES_CPP_NAMESPACE_QUALIFIER XMLString::transcode(toTranscode);
    }

    ~StrX()
    {
        XERCES_CPP_NAMESPACE_QUALIFIER XMLString::release(&fLocalForm);
    }


    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    const char* localForm() const
    {
        return fLocalForm;
    }

private :
    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fLocalForm
    //      This is the local code page form of the string.
    // -----------------------------------------------------------------------
    char*   fLocalForm;
};

inline std:: ostream& operator<<(std:: ostream& target, const StrX& toDump)
{
    target << toDump.localForm();
    return target;
}

_bt_xml_end

#endif // _XML_Helper_H_