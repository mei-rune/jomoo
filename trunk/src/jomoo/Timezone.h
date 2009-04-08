# ifndef Timezone_H
# define Timezone_H

# include "jomoo/config.h"

# if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
# endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include <time.h>
# include "Timestamp.h"
# include "string.hpp"
_jomoo_begin

class Timezone
{
public:

	static int tzd()
	{
		return utcOffset() + dst();
	}

	static int utcOffset()
	{
		TIME_ZONE_INFORMATION tzInfo;
		DWORD dstFlag = GetTimeZoneInformation(&tzInfo);
		return -tzInfo.Bias*60;
	}


	static int dst()
	{
		TIME_ZONE_INFORMATION tzInfo;
		DWORD dstFlag = GetTimeZoneInformation(&tzInfo);
		return dstFlag == TIME_ZONE_ID_DAYLIGHT ? -tzInfo.DaylightBias*60 : 0;
	}


	static bool isDst(const Timestamp& timestamp)
	{
		time_t time = timestamp.epochTime();
		struct std::tm* tms = ::localtime(&time);
		return tms->tm_isdst > 0;
	}


	static tstring name()
	{
		TIME_ZONE_INFORMATION tzInfo;
		DWORD dstFlag = GetTimeZoneInformation(&tzInfo);
		WCHAR* ptr = dstFlag == TIME_ZONE_ID_DAYLIGHT ? tzInfo.DaylightName : tzInfo.StandardName;
#ifdef  _UNICODE
		return tstring( ptr );
#else
		tstring result ;
		result.resize( 256 );
		int rc = WideCharToMultiByte(CP_ACP, 0, ptr, -1, ( char_t* )result.c_str(), result.size(), NULL, NULL);
		if (rc)
			result.resize( rc );
		return result;
#endif
	}

	static tstring standardName()
	{
		TIME_ZONE_INFORMATION tzInfo;
		DWORD dstFlag = GetTimeZoneInformation(&tzInfo);
		WCHAR* ptr = tzInfo.StandardName;
#ifdef  _UNICODE
		return tstring( ptr );
#else
		tstring result;
		result.resize( 256 );
		int rc = WideCharToMultiByte(CP_ACP, 0, ptr, -1, ( char_t* )result.c_str(), result.size(), NULL, NULL);
		if (rc)
			result.resize( rc );
		return result;
#endif
	}


	static tstring dstName()
	{
		TIME_ZONE_INFORMATION tzInfo;
		DWORD dstFlag = GetTimeZoneInformation(&tzInfo);
		WCHAR* ptr = tzInfo.DaylightName;
#ifdef  _UNICODE
		return tstring( ptr );
#else
		tstring result;
		result.resize( 256 );
		int rc = WideCharToMultiByte(CP_ACP, 0, ptr, -1, ( char_t* )result.c_str(), result.size(), NULL, NULL);
		if (rc)
			result.resize( rc );
		return result;
#endif
	}
};


_jomoo_end


#endif // Timezone_H
