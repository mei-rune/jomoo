# ifndef DateTimeParser_H
# define DateTimeParser_H

# include "jomoo/config.h"

# if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
# endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include <time.h>
# include "jomoo/exception.hpp"
# include "DateTime.h"


_jomoo_begin

#define SKIP_JUNK() \
	while (it != end && !std::isdigit(*it)) ++it


#define PARSE_NUMBER(var) \
	while (it != end && std::isdigit(*it)) var = var*10 + ((*it++) - '0')


#define PARSE_NUMBER_N(var, n) \
{ int i = 0; while (i++ < n && it != end && std::isdigit(*it)) var = var*10 + ((*it++) - '0'); }

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
		if( !tryParse( fmt, str, dateTime,timeZoneDifferential)
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

	bool tryParse(const tchar* fmt, const tchar* str, DateTime& dateTime, int& timeZoneDifferential)
	{
		int year   = 0;
		int month  = 0;
		int day    = 0;
		int hour   = 0;
		int minute = 0;
		int second = 0;
		int millis = 0;
		int tzd    = 0;

		const tchar* it   = str;
		const tchar* itf  = fmt;

		while ( *itf && *it )
		{
			if (*itf != _T('%'))
			{ 
				++itf;
				continue;
			}

			if (*++itf)
				continue;

			switch (*itf)
			{
			case _T('w'):
			case _T('W'):
				while (it != end && std::isspace(*it)) ++it;
				while (it != end && std::isalpha(*it)) ++it;
				break;
			case _T('b'):
			case _T('B'):
				month = parseMonth(it, end);
				break;
			case _T('d'):
			case _T('e':
			case _T('f'):
				SKIP_JUNK();
				PARSE_NUMBER_N(day, 2);
				break;
			case _T('m'):
			case _T('n'):
			case _T('o'):
				SKIP_JUNK();
				PARSE_NUMBER_N(month, 2);
				break;					 
			case _T('y'):
				SKIP_JUNK();
				PARSE_NUMBER(year);
				if (year < 1000)
				{
					if (year >= 70) 
						year += 1900;
					else
						year += 2000;
				}
				break;
			case _T('Y'):
				SKIP_JUNK();
				PARSE_NUMBER_N(year, 4);
				break;
			case _T('H'):
			case _T('h'):
				SKIP_JUNK();
				PARSE_NUMBER_N(hour, 2);
				break;
			case _T('a'):
			case _T('A'):
				hour = parseAMPM(it, end, hour);
				break;
			case _T('M'):
				SKIP_JUNK();
				PARSE_NUMBER_N(minute, 2);
				break;
			case _T('S'):
				SKIP_JUNK();
				PARSE_NUMBER_N(second, 2);
				break;
			case _T('i'):
				SKIP_JUNK();
				PARSE_NUMBER_N(millis, 3);
				break;
			case _T('c'):
				SKIP_JUNK();
				PARSE_NUMBER_N(millis, 1);
				millis *= 100;
				break;
			case _T('z'):
			case _T('Z'):
				tzd = parseTZD(it, end);
				break;
			}
			++itf;

		}
		if (month == 0)
			month = 1;
		if (day == 0)
			day = 1;
		if (!DateTime::isValid(year, month, day, hour, minute, second, millis))
			return false;

		dateTime.assign(year, month, day, hour, minute, second, millis);
		timeZoneDifferential = tzd;
		return true;
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
		else
			throw SyntaxException("Unsupported or invalid date/time format");
	}

	bool tryParse(const tstring& str, DateTime& dateTime, int& timeZoneDifferential)
	{
		if (str.length() < 4) return false;

		if (str[3] == ',')
			return tryParse(DateTimeFormatter::RFC822_FORMAT, str, dateTime, timeZoneDifferential);
		else if (str[3] == ' ')
			return tryParse(DateTimeFormatter::ASCTIME_FORMAT, str, dateTime, timeZoneDifferential);
		else if (str.find(',') != tstring::npos)
			return tryParse(DateTimeFormatter::RFC850_FORMAT, str, dateTime, timeZoneDifferential);
		else if (std::isdigit(str[0]))
		{
			if (str.find(' ') != tstring::npos || str.length() == 10)
				return tryParse(DateTimeFormatter::SORTABLE_FORMAT, str, dateTime, timeZoneDifferential);
			else
				return tryParse(DateTimeFormatter::ISO8601_FORMAT, str, dateTime, timeZoneDifferential);
		}
		else return false;
	}


	int parseMonth(tstring::const_iterator& it, const tstring::const_iterator& end)
	{
		tstring month;
		while (it != end && std::isspace(*it) || std::ispunct(*it)) ++it;
		bool isFirst = true;
		while (it != end && std::isalpha(*it)) 
		{
			char ch = (*it++);
			if (isFirst) { month += std::toupper(ch); isFirst = false; }
			else month += std::tolower(ch);
		}
		if (month.length() < 3) throw SyntaxException("Month name must be at least three characters long", month);
		for (int i = 0; i < 12; ++i) 
		{
			if (DateTimeFormat::MONTH_NAMES[i].find(month) == 0)
				return i + 1;
		}
		throw SyntaxException("Not a valid month name", month);
	}


	int parseDayOfWeek(tstring::const_iterator& it, const tstring::const_iterator& end)
	{
		tstring dow;
		while (it != end && std::isspace(*it) || std::ispunct(*it)) ++it;
		bool isFirst = true;
		while (it != end && std::isalpha(*it)) 
		{
			char ch = (*it++);
			if (isFirst) { dow += std::toupper(ch); isFirst = false; }
			else dow += std::tolower(ch);
		}
		if (dow.length() < 3) throw SyntaxException("Weekday name must be at least three characters long", dow);
		for (int i = 0; i < 7; ++i) 
		{
			if (DateTimeFormat::WEEKDAY_NAMES[i].find(dow) == 0)
				return i;
		}
		throw SyntaxException("Not a valid weekday name", dow);
	}


protected:
	int parseTZD(tstring::const_iterator& it, const tstring::const_iterator& end)
	{
		struct Zone
		{
			const char* designator;
			int         timeZoneDifferential;
		};

		static Zone zones[] =
		{
			{"Z",           0},
			{"UT",          0},
			{"GMT",         0},
			{"BST",    1*3600},
			{"IST",    1*3600},
			{"WET",         0},
			{"WEST",   1*3600},
			{"CET",    1*3600},
			{"CEST",   2*3600},
			{"EET",    2*3600},
			{"EEST",   3*3600},
			{"MSK",    3*3600},
			{"MSD",    4*3600},
			{"NST",   -3*3600-1800},
			{"NDT",   -2*3600-1800},
			{"AST",   -4*3600},
			{"ADT",   -3*3600},
			{"EST",   -5*3600},
			{"EDT",   -4*3600},
			{"CST",   -6*3600},
			{"CDT",   -5*3600},
			{"MST",   -7*3600},
			{"MDT",   -6*3600},
			{"PST",   -8*3600},
			{"PDT",   -7*3600},
			{"AKST",  -9*3600},
			{"AKDT",  -8*3600},
			{"HST",  -10*3600},
			{"AEST",  10*3600},
			{"AEDT",  11*3600},
			{"ACST",   9*3600+1800},
			{"ACDT",  10*3600+1800},
			{"AWST",   8*3600},
			{"AWDT",   9*3600}
		};

		while (it != end && std::isspace(*it)) ++it;
		if (it != end)
		{
			if (std::isalpha(*it))
			{
				tstring designator;
				designator += *it++;
				if (it != end && std::isalpha(*it)) designator += *it++;
				if (it != end && std::isalpha(*it)) designator += *it++;
				if (it != end && std::isalpha(*it)) designator += *it++;
				for (unsigned i = 0; i < sizeof(zones)/sizeof(Zone); ++i)
				{
					if (designator == zones[i].designator)
						return zones[i].timeZoneDifferential;
				}
			}
			else if (*it == '+' || *it == '-')
			{
				int sign = *it == '+' ? 1 : -1;
				++it;
				int hours = 0;
				PARSE_NUMBER_N(hours, 2);
				if (it != end && *it == ':') ++it;
				int minutes = 0;
				PARSE_NUMBER_N(minutes, 2);
				return sign*(hours*3600 + minutes*60);
			}
		}
		return 0;
	}


	int parseAMPM(tstring::const_iterator& it, const tstring::const_iterator& end, int hour)
	{
		tstring ampm;
		while (it != end && std::isspace(*it) || std::ispunct(*it)) ++it;
		while (it != end && std::isalpha(*it)) 
		{
			char ch = (*it++);
			ampm += std::toupper(ch);
		}
		if (ampm == "AM")
		{
			if (hour == 12)
				return 0;
			else
				return hour;
		}
		else if (ampm == "PM")
		{
			if (hour < 12)
				return hour + 12;
			else
				return hour;
		}
		else throw SyntaxException("Not a valid AM/PM designator", ampm);
	}
};

_jomoo_end


#endif // Foundation_DateTimeParser_INCLUDED
