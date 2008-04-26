

JOMOO_INLINE bool DateTimeParser::tryParse(const tchar* fmt, const tchar* str, DateTime& dateTime, int& timeZoneDifferential)
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
			while ( *it && ::isspace(*it)) ++it;
			while ( *it && ::isalpha(*it)) ++it;
			break;
		case _T('b'):
		case _T('B'):
			month = parseMonth(it );
			break;
		case _T('d'):
		case _T('e'):
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
			hour = parseAMPM(it, hour);
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
			tzd = parseTZD(it);
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

JOMOO_INLINE bool DateTimeParser::tryParse(const tstring& str, DateTime& dateTime, int& timeZoneDifferential)
{
	if (str.length() < 4) return false;

	if (str[3] == ',')
		return tryParse(DateTime::RFC822_FORMAT, str.c_str(), dateTime, timeZoneDifferential);
	else if (str[3] == ' ')
		return tryParse(DateTime::ASCTIME_FORMAT, str.c_str(), dateTime, timeZoneDifferential);
	else if (str.find(',') != tstring::npos)
		return tryParse(DateTime::RFC850_FORMAT, str.c_str(), dateTime, timeZoneDifferential);
	else if (::isdigit(str[0]))
	{
		if (str.find(' ') != tstring::npos || str.length() == 10)
			return tryParse(DateTime::SORTABLE_FORMAT, str.c_str(), dateTime, timeZoneDifferential);
		else
			return tryParse(DateTime::ISO8601_FORMAT, str.c_str(), dateTime, timeZoneDifferential);
	}
	else return false;
}


JOMOO_INLINE int DateTimeParser::parseMonth(const tchar* it )
{
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

	tstring month;
	while (*it && ::isspace(*it) || ::ispunct(*it)) ++it;
	bool isFirst = true;
	while (*it && ::isalpha(*it)) 
	{
		char ch = (*it++);
		if (isFirst) { month += ::toupper(ch); isFirst = false; }
		else month += ::tolower(ch);
	}
	if (month.length() < 3)
		ThrowException1( TimeSyntaxException, _T("Month name must be at least three characters long") );

	for (int i = 0; i < 12; ++i) 
	{
		if ( string_traits<tchar>::stricmp( MONTH_NAMES[i], month.c_str() ) == 0)
			return i + 1;
	}

	ThrowException1( TimeSyntaxException, _T("Not a valid month name") );		
}


JOMOO_INLINE int DateTimeParser::parseDayOfWeek(const tchar* it )
{
			static tchar* WEEKDAY_NAMES[7] = {
			_T("Sunday"),
			_T("Monday"),
			_T("Tuesday"),
			_T("Wednesday"),
			_T("Thursday"),
			_T("Friday"),
			_T("Saturday")	};

	tstring dow;
	while ( *it && ::isspace(*it) || ::ispunct(*it)) ++it;
	bool isFirst = true;
	while (*it && ::isalpha(*it)) 
	{
		char ch = (*it++);
		if (isFirst) { dow += ::toupper(ch); isFirst = false; }
		else dow += ::tolower(ch);
	}
	if (dow.length() < 3)
		ThrowException1( TimeSyntaxException, _T("Weekday name must be at least three characters long") );

	for (int i = 0; i < 7; ++i) 
	{
		if ( string_traits<tchar>::stricmp( WEEKDAY_NAMES[i], dow.c_str() ) == 0)
			return i;
	}
	ThrowException1( TimeSyntaxException,_T("Not a valid weekday name") );
}


JOMOO_INLINE int DateTimeParser::parseTZD(const tchar* it )
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

	while (*it && ::isspace(*it)) ++it;
	if (*it)
	{
		if (::isalpha(*it))
		{
			tstring designator;
			designator += *it++;
			if (*it && ::isalpha(*it)) designator += *it++;
			if (*it && ::isalpha(*it)) designator += *it++;
			if (*it && ::isalpha(*it)) designator += *it++;
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
			if (*it && *it == ':') ++it;
			int minutes = 0;
			PARSE_NUMBER_N(minutes, 2);
			return sign*(hours*3600 + minutes*60);
		}
	}
	return 0;
}


JOMOO_INLINE int DateTimeParser::parseAMPM(const tchar* it, int hour)
{
	tstring ampm;
	while (*it && ::isspace(*it) || ::ispunct(*it)) ++it;
	while (*it && ::isalpha(*it)) 
	{
		char ch = (*it++);
		ampm += ::toupper(ch);
	}
	if (ampm == _T("AM"))
	{
		if (hour == 12)
			return 0;
		else
			return hour;
	}
	else if (ampm == _T("PM"))
	{
		if (hour < 12)
			return hour + 12;
		else
			return hour;
	}
	else 
		ThrowException( TimeSyntaxException );
}
