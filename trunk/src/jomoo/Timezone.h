# ifndef Timezone_H
# define Timezone_H

# include "jomoo/config.h"

# if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
# endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include <time.h>
# include "Timestamp.h"

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


	static std::string name()
	{
		std::string result;
		TIME_ZONE_INFORMATION tzInfo;
		DWORD dstFlag = GetTimeZoneInformation(&tzInfo);
		WCHAR* ptr = dstFlag == TIME_ZONE_ID_DAYLIGHT ? tzInfo.DaylightName : tzInfo.StandardName;
#if defined(POCO_WIN32_UTF8)
		UnicodeConverter::toUTF8(ptr, result);
#else
		char buffer[256];
		DWORD rc = WideCharToMultiByte(CP_ACP, 0, ptr, -1, buffer, sizeof(buffer), NULL, NULL);
		if (rc) result = buffer;
#endif
		return result;
	}

	static std::string standardName()
	{
		std::string result;
		TIME_ZONE_INFORMATION tzInfo;
		DWORD dstFlag = GetTimeZoneInformation(&tzInfo);
		WCHAR* ptr = tzInfo.StandardName;
#if defined(POCO_WIN32_UTF8)
		UnicodeConverter::toUTF8(ptr, result);
#else
		char buffer[256];
		DWORD rc = WideCharToMultiByte(CP_ACP, 0, ptr, -1, buffer, sizeof(buffer), NULL, NULL);
		if (rc) result = buffer;
#endif
		return result;
	}


	static std::string dstName()
	{
		std::string result;
		TIME_ZONE_INFORMATION tzInfo;
		DWORD dstFlag = GetTimeZoneInformation(&tzInfo);
		WCHAR* ptr = tzInfo.DaylightName;
#if defined(POCO_WIN32_UTF8)
		UnicodeConverter::toUTF8(ptr, result);
#else
		char buffer[256];
		DWORD rc = WideCharToMultiByte(CP_ACP, 0, ptr, -1, buffer, sizeof(buffer), NULL, NULL);
		if (rc) result = buffer;
#endif
		return result;
	}
};


_jomoo_end


#endif // Timezone_H
