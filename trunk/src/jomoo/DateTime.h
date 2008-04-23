# ifndef DateTime_H
# define DateTime_H

# include "jomoo/config.h"

# if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
# endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include <time.h>
# include <cmath>
# include <assert.h>
# include "Timespan.h"
# include "Timestamp.h"

_jomoo_begin


/**
 * 注意月是从 1 开始的 ( dt.month() == ( tt.tm_mon + 1 )  )
 * 而 dayOfYear 与 tm 结构相差一天( tt.tm_yday+1) == dt.dayOfYear() )
 */
class DateTime
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



	enum Months
	{
		JANUARY = 1,
		FEBRUARY,
		MARCH,
		APRIL,
		MAY,
		JUNE,
		JULY,
		AUGUST,
		SEPTEMBER,
		OCTOBER,
		NOVEMBER,
		DECEMBER
	};

	enum DaysOfWeek
	{
		SUNDAY = 0,
		MONDAY,
		TUESDAY,
		WEDNESDAY,
		THURSDAY,
		FRIDAY,
		SATURDAY
	};

	DateTime(const Timestamp& stamp)
		: _utcTime(stamp.utcTime())
	{
		computeGregorian(julianDay());
		computeDaytime();
	}

	DateTime()
	{
		Timestamp now;
		_utcTime = now.utcTime();
		computeGregorian(julianDay());
		computeDaytime();
	}

	DateTime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int microsecond = 0)
	:   _year(year),
		_month(month),
		_day(day),
		_hour(hour),
		_minute(minute),
		_second(second),
		_millisecond(millisecond),
		_microsecond(microsecond)
	{
		jomoo_assert (year >= 0 && year <= 9999);
		jomoo_assert (month >= 1 && month <= 12);
		jomoo_assert (day >= 1 && day <= daysOfMonth(year, month));
		jomoo_assert (hour >= 0 && hour <= 23);
		jomoo_assert (minute >= 0 && minute <= 59);
		jomoo_assert (second >= 0 && second <= 59);
		jomoo_assert (millisecond >= 0 && millisecond <= 999);
		jomoo_assert (microsecond >= 0 && microsecond <= 999);

		_utcTime = toUtcTime(toJulianDay(year, month, day)) + 10*(hour*Timespan::HOURS + minute*Timespan::MINUTES + second*Timespan::SECONDS + millisecond*Timespan::MILLISECONDS + microsecond);
	}

	DateTime(double julianDay)
		: _utcTime(toUtcTime(julianDay))
	{
		computeGregorian(julianDay);
	}

	DateTime(int64_t utcTime, int64_t diff)
		: _utcTime(utcTime + diff*10)
	{
		computeGregorian(julianDay());
		computeDaytime();
	}

	DateTime(const DateTime& dateTime)
		: _utcTime(dateTime._utcTime),
		_year(dateTime._year),
		_month(dateTime._month),
		_day(dateTime._day),
		_hour(dateTime._hour),
		_minute(dateTime._minute),
		_second(dateTime._second),
		_millisecond(dateTime._millisecond),
		_microsecond(dateTime._microsecond)
	{
	}
	~DateTime()
	{
	}

	DateTime& operator = (const DateTime& dateTime)
	{
		if (&dateTime != this)
		{
			_utcTime     = dateTime._utcTime;
			_year        = dateTime._year;
			_month       = dateTime._month;
			_day         = dateTime._day;
			_hour        = dateTime._hour;
			_minute      = dateTime._minute;
			_second      = dateTime._second;
			_millisecond = dateTime._millisecond;
			_microsecond = dateTime._microsecond;
		}
		return *this;
	}


	DateTime& operator= (const Timestamp& stamp)
	{
		_utcTime = stamp.utcTime();
		computeGregorian(julianDay());
		computeDaytime();
		return *this;
	}


	DateTime& operator = (double julianDay)
	{
		_utcTime = toUtcTime(julianDay);
		computeGregorian(julianDay);
		return *this;
	}


	DateTime& assign(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int microsecond = 0)
	{
		jomoo_assert (year >= 0 && year <= 9999);
		jomoo_assert (month >= 1 && month <= 12);
		jomoo_assert (day >= 1 && day <= daysOfMonth(year, month));
		jomoo_assert (hour >= 0 && hour <= 23);
		jomoo_assert (minute >= 0 && minute <= 59);
		jomoo_assert (second >= 0 && second <= 59);
		jomoo_assert (millisecond >= 0 && millisecond <= 999);
		jomoo_assert (microsecond >= 0 && microsecond <= 999);

		_utcTime     = toUtcTime(toJulianDay(year, month, day)) + 10*(hour*Timespan::HOURS + minute*Timespan::MINUTES + second*Timespan::SECONDS + millisecond*Timespan::MILLISECONDS + microsecond);
		_year        = year;
		_month       = month;
		_day         = day;
		_hour        = hour;
		_minute      = minute;
		_second      = second;
		_millisecond = millisecond;
		_microsecond = microsecond;

		return *this;
	}


	void swap(DateTime& dateTime)
	{
		std::swap(_utcTime, dateTime._utcTime);
		std::swap(_year, dateTime._year);
		std::swap(_month, dateTime._month);
		std::swap(_day, dateTime._day);
		std::swap(_hour, dateTime._hour);
		std::swap(_minute, dateTime._minute);
		std::swap(_second, dateTime._second);
		std::swap(_millisecond, dateTime._millisecond);
		std::swap(_microsecond, dateTime._microsecond);
	}

	int dayOfWeek() const
	{
		return int((std::floor(julianDay() + 1.5))) % 7;
	}


	int dayOfYear() const
	{
		int doy = 0;
		for (int month = 1; month < _month; ++month)
			doy += daysOfMonth(_year, month);
		doy += _day;
		return doy;
	}

	int year() const
	{
		return _year;
	}


	int month() const
	{
		return _month;
	}
	
	int week(int firstDayOfWeek = MONDAY) const
	{
		jomoo_assert (firstDayOfWeek >= 0 && firstDayOfWeek <= 6);

		/// find the first firstDayOfWeek.
		int baseDay = 1;
		while (DateTime(_year, 1, baseDay).dayOfWeek() != firstDayOfWeek) ++baseDay;

		int doy  = dayOfYear();
		int offs = baseDay <= 4 ? 0 : 1; 
		if (doy < baseDay)
			return offs;
		else
			return (doy - baseDay)/7 + 1 + offs;
	}


	int day() const
	{
		return _day;
	}


	int hour() const
	{
		return _hour;
	}


	int hourAMPM() const
	{
		if (_hour < 1)
			return 12;
		else if (_hour > 12)
			return _hour - 12;
		else
			return _hour;
	}


	bool isAM() const
	{
		return _hour < 12;
	}


	bool isPM() const
	{
		return _hour >= 12;
	}


	int minute() const
	{
		return _minute;
	}


	int second() const
	{
		return _second;
	}


	int millisecond() const
	{
		return _millisecond;
	}


	int microsecond() const
	{
		return _microsecond;
	}

	double julianDay() const
	{
		return toJulianDay(_utcTime);
	}

	Timestamp timestamp() const
	{
		return Timestamp::fromUtcTime(_utcTime);
	}


	int64_t utcTime() const
	{
		return _utcTime;
	}

	bool operator == (const DateTime& dateTime) const
	{
		return _utcTime == dateTime._utcTime;
	}

	bool operator != (const DateTime& dateTime) const	
	{
		return _utcTime != dateTime._utcTime;
	}


	bool operator <  (const DateTime& dateTime) const	
	{
		return _utcTime < dateTime._utcTime;
	}


	bool operator <= (const DateTime& dateTime) const
	{
		return _utcTime <= dateTime._utcTime;
	}


	bool operator >  (const DateTime& dateTime) const
	{
		return _utcTime > dateTime._utcTime;
	}


	bool operator >= (const DateTime& dateTime) const	
	{
		return _utcTime >= dateTime._utcTime;
	}


	DateTime operator + (const Timespan& span) const
	{
		return DateTime(_utcTime, span.totalMicroseconds());
	}


	DateTime operator - (const Timespan& span) const
	{
		return DateTime(_utcTime, -span.totalMicroseconds());
	}


	Timespan operator - (const DateTime& dateTime) const
	{
		return Timespan((_utcTime - dateTime._utcTime)/10);
	}


	DateTime& operator += (const Timespan& span)
	{
		_utcTime += span.totalMicroseconds()*10;
		computeGregorian(julianDay());
		computeDaytime();
		return *this;
	}


	DateTime& operator -= (const Timespan& span)
	{
		_utcTime -= span.totalMicroseconds()*10;
		computeGregorian(julianDay());
		computeDaytime();
		return *this;
	}


	void makeUTC(int tzd)
	{
		operator -= (Timespan(((int64_t) tzd)*Timespan::SECONDS));
	}


	void makeLocal(int tzd)
	{
		operator += (Timespan(((int64_t) tzd)*Timespan::SECONDS));
	}

	static bool isLeapYear(int year)
	{
		return (year % 4) == 0 && ((year % 100) != 0 || (year % 400) == 0);
	}

	static DateTime now()
	{
		return DateTime();
	}

	static int daysOfMonth(int year, int month)
	{
		jomoo_assert (month >= 1 && month <= 12);

		static int daysOfMonthTable[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

		if (month == 2 && isLeapYear(year))
			return 29;
		else
			return daysOfMonthTable[month];
	}

	static bool isValid(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int microsecond = 0)
	{
		return
			(year >= 0 && year <= 9999) &&
			(month >= 1 && month <= 12) &&
			(day >= 1 && day <= daysOfMonth(year, month)) &&
			(hour >= 0 && hour <= 23) &&
			(minute >= 0 && minute <= 59) &&
			(second >= 0 && second <= 59) &&
			(millisecond >= 0 && millisecond <= 999) &&
			(microsecond >= 0 && microsecond <= 999);
	}

protected:	
	static double toJulianDay(int64_t utcTime)
	{
		double utcDays = double(utcTime)/864000000000.0;
		return utcDays + 2299160.5; // first day of Gregorian reform (Oct 15 1582)
	}

	static double toJulianDay(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int microsecond = 0)
	{
		// lookup table for (153*month - 457)/5 - note that 3 <= month <= 14.
		static int lookup[] = {-91, -60, -30, 0, 31, 61, 92, 122, 153, 184, 214, 245, 275, 306, 337};

		// day to double
		double dday = double(day) + ((double((hour*60 + minute)*60 + second)*1000 + millisecond)*1000 + microsecond)/86400000000.0;
		if (month < 3)
		{
			month += 12;
			--year;
		}
		double dyear = double(year);
		return dday + lookup[month] + 365*year + std::floor(dyear/4) - std::floor(dyear/100) + std::floor(dyear/400) + 1721118.5;
	}
	static int64_t toUtcTime(double julianDay)
	{
		return int64_t((julianDay - 2299160.5)*864000000000.0);
	}

	void computeGregorian(double julianDay)
	{
		double z    = std::floor(julianDay - 1721118.5);
		double r    = julianDay - 1721118.5 - z;
		double g    = z - 0.25;
		double a    = std::floor(g / 36524.25);
		double b    = a - std::floor(a/4);
		_year       = short(std::floor((b + g)/365.25));
		double c    = b + z - std::floor(365.25*_year);
		_month      = short(std::floor((5*c + 456)/153));
		double dday = c - std::floor((153.0*_month - 457)/5) + r;
		_day        = short(dday);
		if (_month > 12)
		{
			++_year;
			_month -= 12;
		}
		r      *= 24;
		_hour   = short(std::floor(r));
		r      -= std::floor(r);
		r      *= 60;
		_minute = short(std::floor(r));
		r      -= std::floor(r);
		r      *= 60;
		_second = short(std::floor(r));
		r      -= std::floor(r);
		r      *= 1000;
		_millisecond = short(std::floor(r));
		r      -= std::floor(r);
		r      *= 1000;
		_microsecond = short(r + 0.5);

		normalize();

		jomoo_assert (_month >= 1 && _month <= 12);
		jomoo_assert (_day >= 1 && _day <= daysOfMonth(_year, _month));
		jomoo_assert (_hour >= 0 && _hour <= 23);
		jomoo_assert (_minute >= 0 && _minute <= 59);
		jomoo_assert (_second >= 0 && _second <= 59);
		jomoo_assert (_millisecond >= 0 && _millisecond <= 999);
		jomoo_assert (_microsecond >= 0 && _microsecond <= 999);
	}

	void computeDaytime()
	{
		Timespan span(_utcTime/10);
		_hour        = span.hours();
		_minute      = span.minutes();
		_second      = span.seconds();
		_millisecond = span.milliseconds();
		_microsecond = span.microseconds();
	}
private:
	void checkLimit(short& lower, short& higher, short limit)
	{
		if (lower > limit)
		{
			higher += short(lower / limit);
			lower   = short(lower % limit);
		}
	}
	void normalize()
	{
		checkLimit(_microsecond, _millisecond, 999);
		checkLimit(_millisecond, _second, 999);
		checkLimit(_second, _minute, 59);
		checkLimit(_minute, _hour, 59);
		checkLimit(_hour, _day, 23);

		if (_day > daysOfMonth(_year, _month))
		{
			_day -= daysOfMonth(_year, _month);
			if (++_month > 12)
			{
				++_year;
				_month -= 12;
			}
		}
	}
	int64_t _utcTime;
	short  _year;
	short  _month;
	short  _day;
	short  _hour;
	short  _minute;
	short  _second;
	short  _millisecond;
	short  _microsecond;
};

inline void swap(DateTime& d1, DateTime& d2)
{
	d1.swap(d2);
}

_jomoo_end

#endif // DateTime_H
