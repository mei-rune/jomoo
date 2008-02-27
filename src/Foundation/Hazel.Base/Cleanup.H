
/**
* -*- C++ -*-
* -------------------------------------------------------------------------------
* - °Ë®q°–®r ®q°–®r						Hazel_Cleanup.H.h,v 1.0 2006/01/05 15:05:54
*  ®u®ê®Ä®Ä®é ®q®q °–®r
* ¶ÚÃÔ¶ÚÃÔÃÔ| ®t------
* -------------------------------------------------------------------------------
*/

#ifndef Hazel_CLEANUP_H
# define Hazel_CLEANUP_H


# include "config.h"

# if !defined (Hazel_LACKS_PRAGMA_ONCE)
#  pragma once
# endif /* Hazel_LACKS_PRAGMA_ONCE */

_hazel_begin

class Hazel_Cleanup
{
public:

	virtual ~Hazel_Cleanup (void){}

	virtual void cleanup ( ) = 0;
};

_hazel_end

#endif /* ACE_CLEANUP_H */
