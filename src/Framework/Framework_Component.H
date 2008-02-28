
/**
* -*- C++ -*-
* -------------------------------------------------------------------------------
* - °Ë®q°–®r ®q°–®r		    BOE_Framework_Component.H.h,v 1.0 2006/01/05 14:36:54
*  ®u®ê®Ä®Ä®é ®q®q °–®r
* ¶ÚÃÔ¶ÚÃÔÃÔ| ®t------
* -------------------------------------------------------------------------------
*/
#ifndef _BOE_Framework_Component_H_
#define _BOE_Framework_Component_H_

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */


_boe_begin

class BOE_Framework_Component
{
public:
	virtual ~BOE_Framework_Component(){}
	virtual int init( ) = 0;
	virtual void fini( ) = 0;
};

class BOE_Framework_Repository
{
public:
	BOE_Framework_Repository( )
		: components_( 0 )
	{
		components_ = new BOE_Framework_Component[]
		{
		}
	}

	~BOE_Framework_Repository( )
	{
		if( components_ != 0 )
			delete [] components_;
	}

  int open ( );

  int close ( );
private:

	BOE_Framework_Component** components_;
};

_boe_end

#endif // _BOE_Framework_Component_H_
