/**
 * -*- C++ -*-
 * -------------------------------------------------------------------------------
 * - °Ë®q°–®r ®q°–®r		             serialize_Def.h,v 1.0 2005/03/14 12:04:54
 *  ®u®ê®Ä®Ä®é ®q®q °–®r
 * ¶ÚÃÔ¶ÚÃÔÃÔ| ®t------
 * -------------------------------------------------------------------------------
 */

#ifndef _serialize_Def_H_
#define _serialize_Def_H_


#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include "config.h"
#include <stdexcept>

#define _bt_serialize_begin _bt_begin namespace SERIALIZE_NAMESPACE{

#define _bt_serialize_end }; _bt_end

#define _bt_serialize _bt SERIALIZE_NAMESPACE::

#define use_bt_serialize using namespace _bt SERIALIZE_NAMESPACE;

#endif // _Alarm_Def_H_