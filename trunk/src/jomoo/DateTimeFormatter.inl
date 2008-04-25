
JOMOO_INLINE tstring DateTimeFormatter::format(const DateTime& dateTime, const tchar* fmt, int timeZoneDifferential)
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
		case _T('w'): result.append(GET_WEEKDAY_NAME(dateTime.dayOfWeek()), 0, 3); break;
		case _T('W'): result.append(GET_WEEKDAY_NAME(dateTime.dayOfWeek())); break;
		case _T('b'): result.append(GET_MONTH_NAME(dateTime.month() - 1), 0, 3); break;
		case _T('B'): result.append(GET_MONTH_NAME(dateTime.month() - 1)); break;
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

JOMOO_INLINE tstring DateTimeFormatter::format(const Timespan& timespan, const tchar* fmt )
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
JOMOO_INLINE tstring DateTimeFormatter::tzdISO(int timeZoneDifferential)
{
	tstring tzd;
	if (timeZoneDifferential != DateTime::UTC)
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
JOMOO_INLINE tstring DateTimeFormatter::tzdRFC(int timeZoneDifferential)
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