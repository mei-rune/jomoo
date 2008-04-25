# ifndef DateTimeParser_H
# define DateTimeParser_H

# include "jomoo/config.h"

# if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
# endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include <time.h>
# include <ctype.h>
# include "jomoo/exception.hpp"
# include "DateTime.h"
# include "DateTimeFormatter.h"


_jomoo_begin

#define SKIP_JUNK() \
	while (*it && !::isdigit(*it)) ++it


#define PARSE_NUMBER(var) \
	while (*it && ::isdigit(*it)) var = var*10 + ((*it++) - '0')


#define PARSE_NUMBER_N(var, n) \
{ int i = 0; while (i++ < n && *it && ::isdigit(*it)) var = var*10 + ((*it++) - '0'); }

class DateTimeParser
{
public:
	
	void parse(const tstring& fmt, const tstring& str, DateTime& dateTime )
	{
		int timeZoneDifferential = 0;
		parse( fmt.c_str(), str.c_str(), dateTime, timeZoneDifferential );
	}

	void parse(const tchar* fmt, const tchar* str, DateTime& dateTime)
	{
		int timeZoneDifferential = 0;
		parse( fmt, str, dateTime, timeZoneDifferential );
	}

	void parse(const tstring& fmt, const tstring& str, DateTime& dateTime, int& timeZoneDifferential)
	{
		parse( fmt.c_str(), str.c_str(), dateTime, timeZoneDifferential );
	}

	void parse(const tchar* fmt, const tchar* str, DateTime& dateTime, int& timeZoneDifferential)
	{
		if( !tryParse( fmt, str, dateTime,timeZoneDifferential) )
			ThrowException( TimeSyntaxException );
	}


	DateTime parse(const tstring& fmt, const tstring& str, int& timeZoneDifferential)
	{
		DateTime result;
		parse(fmt, str, result, timeZoneDifferential);
		return result;
	}

	DateTime parse(const tchar* fmt, const tchar* str, int& timeZoneDifferential)
	{
		DateTime result;
		parse(fmt, str, result, timeZoneDifferential);
		return result;
	}

	bool tryParse(const tchar* fmt, const tchar* str, DateTime& dateTime, int& timeZoneDifferential);
	
	bool tryParse(DateTime::DATETIME_FORMAT fmt, const tchar* str, DateTime& dateTime, int& timeZoneDifferential)
	{
		return tryParse( DateTimeFormatter::getFormatStr( fmt ), str, dateTime, timeZoneDifferential );
	}

	void parse(const tstring& str, DateTime& dateTime, int& timeZoneDifferential)
	{
		if (!tryParse(str, dateTime, timeZoneDifferential))
			ThrowException( TimeSyntaxException );
	}

	DateTime parse(const tstring& str, int& timeZoneDifferential)
	{
		DateTime result;
		if (tryParse(str, result, timeZoneDifferential))
			return result;
		
		ThrowException( TimeSyntaxException );
	}

	bool tryParse(const tstring& str, DateTime& dateTime, int& timeZoneDifferential);

	int parseMonth(const tchar* it );


	int parseDayOfWeek(const tchar* it);

protected:
	int parseTZD(const tchar* it);

	int parseAMPM(const tchar* it, int hour);
};

#if defined (JOMOO_HAS_INLINED)
#include "DateTimeParser.inl"
#endif /* JOMOO_HAS_INLINED */

_jomoo_end


#endif // Foundation_DateTimeParser_INCLUDED
