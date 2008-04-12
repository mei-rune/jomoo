# ifndef timespan_h
# define timespan_h

# include "jomoo/config.h"

# if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
# endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include <time.h>

_jomoo_begin


class Timespan
{
public:

	const static int64_t MILLISECONDS = 1000;
	const static int64_t SECONDS      = 1000*MILLISECONDS;
	const static int64_t MINUTES      =   60*SECONDS;
	const static int64_t HOURS        =   60*MINUTES;
	const static int64_t DAYS         =   24*HOURS;

	Timespan():	_span(0)
	{
	}


	explict Timespan(int64_t microseconds)
		: _span(microseconds)
	{
	}

	Timespan(long seconds, long microseconds)
		: _span( int64_t(seconds)*SECONDS + microseconds)
	{
	}

	Timespan(int days, int hours, int minutes, int seconds, int microseconds)
		: _span(int64_t(microseconds) + int64_t(seconds)*SECONDS + int64_t(minutes)*MINUTES + int64_t(hours)*HOURS + int64_t(days)*DAYS)
	{
	}
	Timespan(const Timespan& timespan)
		: _span(timespan._span)
	{
	}

	~Timespan()
	{
	}

	Timespan& operator = (const Timespan& timespan)
	{
		_span = timespan._span;
		return *this;
	}

	Timespan& operator = (int64_t microseconds)
	{
		_span = microseconds;
		return *this;
	}

	Timespan& assign(int days, int hours, int minutes, int seconds, int microseconds)
	{
		_span = int64_t(microseconds) + int64_t(seconds)*SECONDS + int64_t(minutes)*MINUTES + int64_t(hours)*HOURS + int64_t(days)*DAYS;
		return *this;
	}

	Timespan& assign(long seconds, long microseconds)
	{
		_span = int64_t(seconds)*SECONDS + int64_t(microseconds);
		return *this;
	}

	void swap(Timespan& timespan)
	{
		std::swap(_span, timespan._span);
	}

	Timespan operator + (const Timespan& d) const
	{
		return Timespan(_span + d._span);
	}

	Timespan operator - (const Timespan& d) const
	{
		return Timespan(_span - d._span);
	}

	Timespan& operator += (const Timespan& d)
	{
		_span += d._span;
		return *this;
	}

	Timespan& operator -= (const Timespan& d)
	{
		_span -= d._span;
		return *this;
	}

	Timespan operator + (int64_t microseconds) const
	{
		return Timespan(_span + microseconds);
	}
	Timespan operator - (int64_t microseconds) const
	{
		return Timespan(_span - microseconds);
	}
	Timespan& operator += (int64_t microseconds)
	{
		_span += microseconds;
		return *this;
	}
	Timespan& operator -= (int64_t microseconds)
	{
		_span -= microseconds;
		return *this;
	}

	int days() const
	{
		return int(_span/DAYS);
	}


	int hours() const
	{
		return int((_span/HOURS) % 24);
	}


	int totalHours() const
	{
		return int(_span/HOURS);
	}


	int minutes() const
	{
		return int((_span/MINUTES) % 60);
	}


	int totalMinutes() const
	{
		return int(_span/MINUTES);
	}


	int seconds() const
	{
		return int((_span/SECONDS) % 60);
	}


	int totalSeconds() const
	{
		return int(_span/SECONDS);
	}


	int milliseconds() const
	{
		return int((_span/MILLISECONDS) % 1000);
	}


	int64_t totalMilliseconds() const
	{
		return _span/MILLISECONDS;
	}


	int microseconds() const
	{
		return int(_span % 1000);
	}


	int useconds() const
	{
		return int(_span % 1000000);
	}


	int64_t totalMicroseconds() const
	{
		return _span;
	}


	bool operator == (const Timespan& ts) const
	{
		return _span == ts._span;
	}


	bool operator != (const Timespan& ts) const
	{
		return _span != ts._span;
	}


	bool operator >  (const Timespan& ts) const
	{
		return _span > ts._span;
	}


	bool operator >= (const Timespan& ts) const
	{
		return _span >= ts._span;
	}


	bool operator <  (const Timespan& ts) const
	{
		return _span < ts._span;
	}


	bool operator <= (const Timespan& ts) const
	{
		return _span <= ts._span;
	}


	bool operator == (int64_t microseconds) const
	{
		return _span == microseconds;
	}


	bool operator != (int64_t microseconds) const
	{
		return _span != microseconds;
	}


	bool operator >  (int64_t microseconds) const
	{
		return _span > microseconds;
	}


	bool operator >= (int64_t microseconds) const
	{
		return _span >= microseconds;
	}


	bool operator <  (int64_t microseconds) const
	{
		return _span < microseconds;
	}


	bool operator <= (int64_t microseconds) const
	{
		return _span <= microseconds;
	}

private:
	int64_t _span;
};

inline void swap(Timespan& s1, Timespan& s2)
{
	s1.swap(s2);
}

_jomoo_end

#endif // timespan_h
