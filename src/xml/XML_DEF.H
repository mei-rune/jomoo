/**
 * -*- C++ -*-
 * -------------------------------------------------------------------------------
 * - °Ë®q°–®r ®q°–®r		                   XML_Def.h,v 1.0 2005/03/18 12:41:54
 *  ®u®ê®Ä®Ä®é ®q®q °–®r
 * ¶ÚÃÔ¶ÚÃÔÃÔ| ®t------
 * -------------------------------------------------------------------------------
 */

#ifndef _XML_Def_H_
#define _XML_Def_H_


#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include <stdexcept>

#define _bt_xml_begin _bt_begin namespace XML_NAMESPACE{

#define _bt_xml_end }; _bt_end

#define _bt_xml _bt XML_NAMESPACE::


#endif // _XML_Def_H_