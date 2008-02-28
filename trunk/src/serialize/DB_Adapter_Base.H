
/**
 * -*- C++ -*-
 * -------------------------------------------------------------------------------
 * - °Ë®q°–®r ®q°–®r		           DB_Adapter_Base.h,v 1.0 2005/04/07 14:11:34
 *  ®u®ê®Ä®Ä®é ®q®q °–®r
 * ¶ÚÃÔ¶ÚÃÔÃÔ| ®t------
 * -------------------------------------------------------------------------------
 */

#ifndef _DB_Adapter_Base_H_
#define _DB_Adapter_Base_H_

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include "serialize/bt_stream.h"
#include "serialize/serialize_def.h"


_bt_serialize_begin

class DB_Adapter_Base : public bt_istream
	,public bt_ostream
	,public DbExecute
	, public DbQuery
{
public:
	virtual ~DB_Adapter_Base(){}

	virtual size_t read( void *pBufferForRead, size_t Len )
	{
		return -1;
	}

	virtual size_t write( const void *pBufferForWrite, size_t Len )
	{
		return -1;
	}

	virtual size_t seek( size_t offset, int start_pos)
	{
		return -1;
	}

	virtual DbExecute* getExecute() = 0;
	virtual DbQuery* getQuery( ) = 0;
};


_bt_serialize_end

#endif // _DB_Adapter_Base_H_