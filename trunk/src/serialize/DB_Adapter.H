
/**
 * -*- C++ -*-
 * -------------------------------------------------------------------------------
 * - °Ë®q°–®r ®q°–®r		                DB_Adapter.h,v 1.0 2005/04/07 14:11:34
 *  ®u®ê®Ä®Ä®é ®q®q °–®r
 * ¶ÚÃÔ¶ÚÃÔÃÔ| ®t------
 * -------------------------------------------------------------------------------
 */

#ifndef _DB_Adapter_H_
#define _DB_Adapter_H_

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include "DB_Adapter_Base.H"

_bt_serialize_begin

class DB_Adapter : public DB_Adapter_Base
{
public:
	DB_Adapter( PDbExecute& executer )
		: executer_( executer )
	{
	}
	DB_Adapter( PDbQuery& query )
		: query_( query )
	{
	}

	DB_Adapter( PDbExecute& executer,PDbQuery& query )
		: executer_( executer )
		, query_( query )
	{
	}

	DB_Adapter( PDbQuery& query,PDbExecute& executer )
		: executer_( executer )
		, query_( query )
	{
	}

	DbExecute* getExecute()
	{
		return &(*executer_)
	}
	
	DbQuery* getQuery( )
	{
		return &(*query_)
	}
private:
	PDbExecute executer_;
	PDbQuery query_;
};



_bt_serialize_end

#endif // _DB_Adapter_H_