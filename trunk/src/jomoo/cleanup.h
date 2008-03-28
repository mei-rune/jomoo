
/**
* -*- C++ -*-
* -------------------------------------------------------------------------------
* - ��q�Шr �q�Шr						JOMOO_Cleanup.H.h,v 1.0 2006/01/05 15:05:54
*  �u�������� �q�q �Шr
* ���������| �t------
* -------------------------------------------------------------------------------
*/

#ifndef JOMOO_CLEANUP_H
# define JOMOO_CLEANUP_H


# include "config.h"

# if !defined (JOMOO_LACKS_PRAGMA_ONCE)
#  pragma once
# endif /* JOMOO_LACKS_PRAGMA_ONCE */

_jomoo_begin

class ICleanup
{
public:

	virtual ~ICleanup (void){}

	virtual void cleanup ( ) = 0;
};

_jomoo_end

#endif /* ACE_CLEANUP_H */
