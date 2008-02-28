

/**
 * -*- C++ -*-
 * -------------------------------------------------------------------------------
 * - °Ë®q°–®r ®q°–®r		                    Malloc.h,v 1.0 2005/01/05 15:58:34
 *  ®u®ê®Ä®Ä®é ®q®q °–®r
 * ¶ÚÃÔ¶ÚÃÔÃÔ| ®t------
 * -------------------------------------------------------------------------------
 */

#ifndef _Malloc_T_H_
#define _Malloc_T_H_

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */



#define BT_MALLOC( X,CLASS,ALLOCATER,SIZE ) X = ( CLASS ) ALLOCATER( SIZE )
#define BT_CALLOC( X,CLASS,ALLOCATER,SIZE ) X = ( CLASS ) ALLOCATER( SIZE )
#define BT_FREE( X,ALLOCATER ) ALLOCATER( X )


#endif // _Malloc_T_H_