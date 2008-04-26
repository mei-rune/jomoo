# ifndef Timestamp_H
# define Timestamp_H

# include "jomoo/config.h"

# if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
# endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include <time.h>

_jomoo_begin

class Timestamp
{
public:

	Timestamp()
	{
		update();
	}


	Timestamp(int64_t tv)
	{
		_ts = tv;
	}


	Timestamp(const Timestamp& other)
	{
		_ts = other._ts;
	}


	~Timestamp()
	{
	}


	Timestamp& operator = (const Timestamp& other)
	{
		_ts = other._ts;
		return *this;
	}


	Timestamp& operator = (int64_t tv)
	{
		_ts = tv;
		return *this;
	}

	void swap(Timestamp& timestamp)
	{
		std::swap(_ts, timestamp._ts);
	}

	void update()
	{
		FILETIME ft;

		GetSystemTimeAsFileTime(&ft);
		ULARGE_INTEGER epoch; // UNIX epoch (1970-01-01 00:00:00) expressed in Windows NT FILETIME
		epoch.LowPart  = 0xD53E8000;
		epoch.HighPart = 0x019DB1DE;

		ULARGE_INTEGER ts;
		ts.LowPart  = ft.dwLowDateTime;
		ts.HighPart = ft.dwHighDateTime;
		ts.QuadPart -= epoch.QuadPart;
		_ts = ts.QuadPart/10;
	}

	time_t epochTime() const
	{
		return time_t(_ts/resolution());
	}

	int64_t utcTime() const
	{
		return _ts*10 + (int64_t(0x01b21dd2) << 32) + 0x13814000;
	}

	int64_t epochMicroseconds() const
	{
		return _ts;
	}

	int64_t elapsed() const
	{
		Timestamp now;
		return now - *this;
	}

	bool isElapsed(int64_t interval) const
	{
		Timestamp now;
		int64_t diff = now - *this;
		return diff >= interval;
	}

	bool operator == (const Timestamp& ts) const
	{
		return _ts == ts._ts;
	}

	bool operator != (const Timestamp& ts) const
	{
		return _ts != ts._ts;
	}

	bool operator >  (const Timestamp& ts) const
	{
		return _ts > ts._ts;
	}

	bool operator >= (const Timestamp& ts) const
	{
		return _ts >= ts._ts;
	}

	bool operator <  (const Timestamp& ts) const
	{
		return _ts < ts._ts;
	}

	bool operator <= (const Timestamp& ts) const
	{
		return _ts <= ts._ts;
	}

	Timestamp operator + (int64_t d) const
	{
		return Timestamp(_ts + d);
	}

	Timestamp operator - (int64_t d) const
	{
		return Timestamp(_ts - d);
	}

	int64_t operator - (const Timestamp& ts) const
	{
		return _ts - ts._ts;
	}

	Timestamp& operator += (int64_t d)
	{
		_ts += d;
		return *this;
	}

	Timestamp& operator -= (int64_t d)
	{
		_ts -= d;
		return *this;
	}

	static Timestamp fromEpochTime(time_t t)
	{
		return Timestamp(int64_t(t)*resolution());
	}

	static Timestamp fromUtcTime(int64_t val)
	{
		val -= (int64_t(0x01b21dd2) << 32) + 0x13814000;
		val /= 10;
		return Timestamp(val);
	}

	static int64_t resolution()
	{
		return 1000000;
	}

	static Timestamp fromFileTimeNP(u_int32_t fileTimeLow, u_int32_t fileTimeHigh)
	{
		ULARGE_INTEGER epoch; // UNIX epoch (1970-01-01 00:00:00) expressed in Windows NT FILETIME
		epoch.LowPart  = 0xD53E8000;
		epoch.HighPart = 0x019DB1DE;

		ULARGE_INTEGER ts;
		ts.LowPart  = fileTimeLow;
		ts.HighPart = fileTimeHigh;
		ts.QuadPart -= epoch.QuadPart;

		return Timestamp(ts.QuadPart/10);
	}

	void toFileTimeNP(u_int32_t& fileTimeLow, u_int32_t& fileTimeHigh) const
	{
		ULARGE_INTEGER epoch; // UNIX epoch (1970-01-01 00:00:00) expressed in Windows NT FILETIME
		epoch.LowPart  = 0xD53E8000;
		epoch.HighPart = 0x019DB1DE;

		ULARGE_INTEGER ts;
		ts.QuadPart  = _ts*10;
		ts.QuadPart += epoch.QuadPart;
		fileTimeLow  = ts.LowPart;
		fileTimeHigh = ts.HighPart;
	}

private:
	int64_t _ts;

	friend std::ostream& operator<<( std::ostream& target, const Timestamp& );
};

inline void swap(Timestamp& s1, Timestamp& s2)
{
	s1.swap(s2);
}

_jomoo_end

inline std::ostream& operator<<( std::ostream& target, const Timestamp& ts)
{
	target << ts._ts;
}

#endif // Timestamp_H
