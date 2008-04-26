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
	static tstring format(const Timestamp& timestamp, const tstring& fmt, int timeZoneDifferential = DateTime::UTC)
	{
		DateTime dateTime(timestamp);
		return format(dateTime, fmt, timeZoneDifferential);
	}
	
	static tstring format(const Timestamp& timestamp, DateTime::DATETIME_FORMAT fmt = DateTime::ISO8601_FORMAT, int timeZoneDifferential = DateTime::UTC )
	{
		DateTime dateTime(timestamp);
		return format( dateTime, DateTime::getFormatStr( fmt ), timeZoneDifferential );
	}

	/// Formats the given date and time according to the given format.
	/// See format(const Timestamp&, const tstring&, int) for more information.
	static tstring format(const DateTime& dateTime, const tstring& fmt, int timeZoneDifferential = DateTime::UTC)
	{
		return format( dateTime, fmt.c_str(), timeZoneDifferential );
	}

	static tstring format( const DateTime& dateTime, DateTime::DATETIME_FORMAT fmt = DateTime::ISO8601_FORMAT, int timeZoneDifferential = DateTime::UTC )
	{
		return format( dateTime, DateTime::getFormatStr( fmt ), timeZoneDifferential );
	}
	
	static tstring format(const DateTime& dateTime, const tchar* fmt, int timeZoneDifferential = DateTime::UTC);

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

	static tstring format(const Timespan& timespan, const tchar* fmt = _T("%dd %H:%M:%S.%i"));

	/// Formats the given timezone differential in ISO format.
	/// If timeZoneDifferential is UTC, "Z" is returned,
	/// otherwise, +HH.MM (or -HH.MM) is returned.
	static tstring tzdISO(int timeZoneDifferential);

	/// Formats the given timezone differential in RFC format.
	/// If timeZoneDifferential is UTC, "GMT" is returned,
	/// otherwise ++HHMM (or -HHMM) is returned.	
	static tstring tzdRFC(int timeZoneDifferential);

};


#if defined (JOMOO_HAS_INLINED)
#include "DateTimeFormatter.inl"
#endif

_jomoo_end

#endif // DateTimeFormatter_H
