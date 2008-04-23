# ifndef DateTimeFormatter_H
# define DateTimeFormatter_H

# include "jomoo/config.h"

# if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
# endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include <time.h>
# include "jomoo/string.hpp"
# include "jomoo/Timestamp.h"
# include "jomoo/DateTime.h"
# include "util/NumberFormatter.h"

_jomoo_begin

class DateTimeFormatter
{
public:

	enum DATETIME_FORMAT
	{

	/// The date/time format defined in the ISO 8601 standard.
	///
	/// Examples: 
	///   2005-01-01T12:00:00+01:00
	///   2005-01-01T11:00:00Z
	ISO8601_FORMAT,

	/// The date/time format defined in RFC 822 (obsoleted by RFC 1123).
	///
	/// Examples: 
	///   Sat, 1 Jan 05 12:00:00 +0100
	///   Sat, 1 Jan 05 11:00:00 GMT
	RFC822_FORMAT,

	/// The date/time format defined in RFC 1123 (obsoletes RFC 822).
	///
	/// Examples: 
	///   Sat, 1 Jan 2005 12:00:00 +0100
	///   Sat, 1 Jan 2005 11:00:00 GMT
	RFC1123_FORMAT,

	/// The date/time format defined in the HTTP specification (RFC 2616),
	/// which is basically a variant of RFC 1036 with a zero-padded day field.
	///
	/// Examples: 
	///   Sat, 01 Jan 2005 12:00:00 +0100
	///   Sat, 01 Jan 2005 11:00:00 GMT
	HTTP_FORMAT,

	/// The date/time format defined in RFC 850 (obsoleted by RFC 1036).
	///
	/// Examples: 
	///   Saturday, 1-Jan-05 12:00:00 +0100
	///   Saturday, 1-Jan-05 11:00:00 GMT
	RFC850_FORMAT,

	/// The date/time format defined in RFC 1036 (obsoletes RFC 850).
	///
	/// Examples: 
	///   Saturday, 1 Jan 05 12:00:00 +0100
	///   Saturday, 1 Jan 05 11:00:00 GMT
	RFC1036_FORMAT,


	/// The date/time format produced by the ANSI C asctime() function.
	///
	/// Example: 
	///   Sat Jan  1 12:00:00 2005
	ASCTIME_FORMAT,

	/// A simple, sortable date/time format.
	///
	/// Example:
	///   2005-01-01 12:00:00
	SORTABLE_FORMAT
	};

	static const tchar* getWeekName( int week )
	{
		// names used by formatter and parser
		/// English names of week days (Sunday, Monday, Tuesday, ...).
		static tchar* WEEKDAY_NAMES[7] = {
			_T("Sunday"),
			_T("Monday"),
			_T("Tuesday"),
			_T("Wednesday"),
			_T("Thursday"),
			_T("Friday"),
			_T("Saturday")	};

			return WEEKDAY_NAMES[ week ];
	}

	static const tchar* getMonthName( int month )
	{
		/// English names of months (January, February, ...).	
		static tchar* MONTH_NAMES[] = 
		{
			_T("January"),
			_T("February"),
			_T("March"),
			_T("April"),
			_T("May"),
			_T("June"),
			_T("July"),
			_T("August"),
			_T("September"),
			_T("October"),
			_T("November"),
			_T("December")
		};
		return MONTH_NAMES[ month ];
	}

	static const tchar* getFormatString( DATETIME_FORMAT fmt )
	{
		static const tchar* formats[8]  = { _T("%Y-%m-%dT%H:%M:%S%z"),
											 _T("%w, %e %b %y %H:%M:%S %Z"),
											 _T("%w, %e %b %Y %H:%M:%S %Z"),
											 _T("%w, %d %b %Y %H:%M:%S %Z"),
											 _T("%W, %e-%b-%y %H:%M:%S %Z"),
											 _T("%W, %e %b %y %H:%M:%S %Z"),
											 _T("%w %b %f %H:%M:%S %Y"),
											 _T("%Y-%m-%d %H:%M:%S") };
		return formats[ fmt ];
	}

	enum
	{
		UTC = 0xFFFF /// Special value for timeZoneDifferential denoting UTC. 
	};

	/// Formats the given timestamp according to the given format.
	/// The format string is used as a template to format the date and
	/// is copied character by character except for the following special characters,
	/// which are replaced by the corresponding value.
	///
	///   * %w - abbreviated weekday (Mon, Tue, ...)
	///   * %W - full weekday (Monday, Tuesday, ...)
	///   * %b - abbreviated month (Jan, Feb, ...)
	///   * %B - full month (January, February, ...)
	///   * %d - zero-padded day of month (01 .. 31)
	///   * %e - day of month (1 .. 31)
	///   * %f - space-padded day of month ( 1 .. 31)
	///   * %m - zero-padded month (01 .. 12)
	///   * %n - month (1 .. 12)
	///   * %o - space-padded month ( 1 .. 12)
	///   * %y - year without century (70)
	///   * %Y - year with century (1970)
	///   * %H - hour (00 .. 23)
	///   * %h - hour (00 .. 12)
	///   * %a - am/pm
	///   * %A - AM/PM
	///   * %M - minute (00 .. 59)
	///   * %S - second (00 .. 59)
	///   * %i - millisecond (000 .. 999)
	///   * %c - centisecond (0 .. 9)
	///   * %z - time zone differential in ISO 8601 format (Z or +NN.NN).
	///   * %Z - time zone differential in RFC format (GMT or +NNNN)
	///   * %% - percent sign
	///
	/// Class DateTimeFormat defines format strings for various standard date/time formats.
	static tstring format(const Timestamp& timestamp, const tstring& fmt, int timeZoneDifferential = UTC)
	{
		DateTime dateTime(timestamp);
		return format(dateTime, fmt, timeZoneDifferential);
	}
	
	static tstring format(const Timestamp& timestamp, DATETIME_FORMAT fmt = ISO8601_FORMAT, int timeZoneDifferential = UTC )
	{
		DateTime dateTime(timestamp);
		return format( dateTime, getFormatString( fmt ), timeZoneDifferential );
	}

	/// Formats the given date and time according to the given format.
	/// See format(const Timestamp&, const tstring&, int) for more information.
	static tstring format(const DateTime& dateTime, const tstring& fmt, int timeZoneDifferential = UTC)
	{
		return format( dateTime, fmt.c_str(), timeZoneDifferential );
	}

	static tstring format( const DateTime& dateTime, DATETIME_FORMAT fmt = ISO8601_FORMAT, int timeZoneDifferential = UTC )
	{
		return format( dateTime, getFormatString( fmt ), timeZoneDifferential );
	}
	
	static tstring format(const DateTime& dateTime, const tchar* fmt, int timeZoneDifferential = UTC)
	{

		tstring result;
		const tchar* it  = fmt;
		while ( *it )
		{
			if (*it != _T('%'))
			{	
				result += *it++;
				continue;
			}

			if (0 == *++it)
				break;


			switch (*it)
			{
			case _T('w'): result.append(getWeekName(dateTime.dayOfWeek()), 0, 3); break;
			case _T('W'): result.append(getWeekName(dateTime.dayOfWeek())); break;
			case _T('b'): result.append(getMonthName(dateTime.month() - 1), 0, 3); break;
			case _T('B'): result.append(getMonthName(dateTime.month() - 1)); break;
			case _T('d'): result.append(NumberFormatter::format0(dateTime.day(), 2)); break;
			case _T('e'): result.append(NumberFormatter::format(dateTime.day())); break;
			case _T('f'): result.append(NumberFormatter::format(dateTime.day(), 2)); break;
			case _T('m'): result.append(NumberFormatter::format0(dateTime.month(), 2)); break;
			case _T('n'): result.append(NumberFormatter::format(dateTime.month())); break;
			case _T('o'): result.append(NumberFormatter::format(dateTime.month(), 2)); break;
			case _T('y'): result.append(NumberFormatter::format0(dateTime.year() % 100, 2)); break;
			case _T('Y'): result.append(NumberFormatter::format0(dateTime.year(), 4)); break;
			case _T('H'): result.append(NumberFormatter::format0(dateTime.hour(), 2)); break;
			case _T('h'): result.append(NumberFormatter::format0(dateTime.hourAMPM(), 2)); break;
			case _T('a'): result.append(dateTime.isAM() ? _T("am") : _T("pm")); break;
			case _T('A'): result.append(dateTime.isAM() ? _T("AM") : _T("PM")); break;
			case _T('M'): result.append(NumberFormatter::format0(dateTime.minute(), 2)); break;
			case _T('S'): result.append(NumberFormatter::format0(dateTime.second(), 2)); break;
			case _T('i'): result.append(NumberFormatter::format0(dateTime.millisecond(), 3)); break;
			case _T('c'): result.append(NumberFormatter::format(dateTime.millisecond()/100)); break;
			case _T('z'): result.append(tzdISO(timeZoneDifferential)); break;
			case _T('Z'): result.append(tzdRFC(timeZoneDifferential)); break;
			default:  result += *it;
			}
			++it;	
		}
		return result;
	}

	/// Formats the given local date and time according to the given format.
	/// See format(const Timestamp&, const tstring&, int) for more information.
	//static tstring format(const LocalDateTime& dateTime, const tstring& fmt)
	//{
	//	return format(dateTime._dateTime, fmt, dateTime._tzd);
	//}
	/// Formats the given timespan according to the given format.
	/// The format string is used as a template to format the date and
	/// is copied character by character except for the following special characters,
	/// which are replaced by the corresponding value.
	///
	///   * %d - days
	///   * %H - hours	 (00 .. 23)
	///   * %h - total hours (0 .. n)
	///   * %M - minutes (00 .. 59)
	///   * %m - total minutes (0 .. n)
	///   * %S - seconds (00 .. 59)
	///   * %s - total seconds (0 .. n)
	///   * %i - milliseconds (000 .. 999)
	///   * %c - centisecond (0 .. 9)
	///   * %% - percent sign
	static tstring format(const Timespan& timespan, const tstring& fmt)
	{
		return format( timespan, fmt );
	}

	static tstring format(const Timespan& timespan, const tchar* fmt = _T("%dd %H:%M:%S.%i"))
	{
		tstring result;
		const tchar* it  = fmt;
		while ( *it )
		{
			if (*it != _T('%'))
			{	
				result += *it++;
				continue;
			}

			if (0 == *++it)
				break;

			switch (*it)
			{
			case _T('d'): result.append(NumberFormatter::format(timespan.days())); break;
			case _T('H'): result.append(NumberFormatter::format0(timespan.hours(), 2)); break;
			case _T('h'): result.append(NumberFormatter::format(timespan.totalHours())); break;
			case _T('M'): result.append(NumberFormatter::format0(timespan.minutes(), 2)); break;
			case _T('m'): result.append(NumberFormatter::format(timespan.totalMinutes())); break;
			case _T('S'): result.append(NumberFormatter::format0(timespan.seconds(), 2)); break;
			case _T('s'): result.append(NumberFormatter::format(timespan.totalSeconds())); break;
			case _T('i'): result.append(NumberFormatter::format0(timespan.milliseconds(), 3)); break;
			case _T('c'): result.append(NumberFormatter::format(timespan.milliseconds()/100)); break;
			default:  result += *it;
			}
			++it;
		}
		return result;
	}

	/// Formats the given timezone differential in ISO format.
	/// If timeZoneDifferential is UTC, "Z" is returned,
	/// otherwise, +HH.MM (or -HH.MM) is returned.
	static tstring tzdISO(int timeZoneDifferential)
	{
		tstring tzd;
		if (timeZoneDifferential != UTC)
		{
			if (timeZoneDifferential >= 0)
			{
				tzd += _T('+');
				tzd += NumberFormatter::format0(timeZoneDifferential/3600, 2);
				tzd += _T(':');
				tzd += NumberFormatter::format0((timeZoneDifferential%3600)/60, 2);
			}
			else
			{
				tzd += _T('-');
				tzd += NumberFormatter::format0(-timeZoneDifferential/3600, 2);
				tzd += _T(':');
				tzd += NumberFormatter::format0((-timeZoneDifferential%3600)/60, 2);
			}
		}
		else tzd = _T("Z");
		return tzd;
	}

	/// Formats the given timezone differential in RFC format.
	/// If timeZoneDifferential is UTC, "GMT" is returned,
	/// otherwise ++HHMM (or -HHMM) is returned.	
	static tstring tzdRFC(int timeZoneDifferential)
	{
		tstring tzd;
		if (timeZoneDifferential != UTC)
		{
			if (timeZoneDifferential >= 0)
			{
				tzd += _T('+');
				tzd += NumberFormatter::format0(timeZoneDifferential/3600, 2);
				tzd += NumberFormatter::format0((timeZoneDifferential%3600)/60, 2);
			}
			else
			{
				tzd += _T('-');
				tzd += NumberFormatter::format0(-timeZoneDifferential/3600, 2);
				tzd += NumberFormatter::format0((-timeZoneDifferential%3600)/60, 2);
			}		
		}
		else tzd = _T("GMT");
		return tzd;
	}

};

_jomoo_end

#endif // DateTimeFormatter_H
