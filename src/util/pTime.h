

/**
* -*- C++ -*-
* -------------------------------------------------------------------------------
* - °Ë®q°–®r ®q°–®r						        ptime.H,v 1.0 2005/05/11 12:29:54
*  ®u®ê®Ä®Ä®é ®q®q °–®r
* ¶ÚÃÔ¶ÚÃÔÃÔ| ®t------
* -------------------------------------------------------------------------------
*/

#ifndef _ptime_h_
#define _ptime_h_


#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#pragma pack(push,8)
#pragma warning(push,3)

 #pragma warning(disable: 4244)

#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/date_time/gregorian/gregorian.hpp"

 #pragma warning(default: 4244)
#pragma warning(pop)
#pragma pack(pop)

#include "serialize/serialize2.h"

_bt_begin

typedef  boost::posix_time::ptime ptime;
typedef  boost::gregorian::date pdate;
typedef  boost::posix_time::time_duration ptime_duration;
typedef  boost::gregorian::date_duration pdate_duration;

#define invailptime ptime( pdate( 1900,boost::gregorian::Jan,10), boost::posix_time::time_duration(1,2,3) )


bool inline serialize(const ptime& t, _bt serialize_ostream_base& stream, const tchar* name="ptime")
{
	return serialize( boost::posix_time::to_simple_string( t ) , stream, name );
}
bool inline deserialize( ptime& t, _bt serialize_istream_base& stream, const tchar* name="ptime")
{
	std::string str;
	if( deserialize( str, stream, name ) )
	{
		t = boost::posix_time::time_from_string( str );
		return true;
	}
	return false;
}


bool inline serialize(const pdate& t, _bt serialize_ostream_base& stream, const tchar* name="ptime")
{
	return serialize( boost::gregorian::to_iso_string( t ) , stream, name );
}

bool inline deserialize( pdate& t, _bt serialize_istream_base& stream, const tchar* name="ptime")
{
	std::string str;
	if( deserialize( str, stream, name ) )
	{
		t = boost::gregorian::from_undelimited_string( str );
		return true;
	}
	return false;
}

_bt_end

#endif // _ptime_h_
