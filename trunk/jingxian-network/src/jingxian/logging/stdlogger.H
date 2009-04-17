
#ifndef _StdLogger_H_
#define _StdLogger_H_

#include "jingxian/config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
#include <iostream>
#include "jingxian/logging/Logger.h"

_jingxian_begin


#ifdef  _UNICODE
#define tcout std::wcout
#else
#define tcout std::cout
#endif


class StdLogger : public logger
{
public:

	StdLogger()
	{
	 l = Trace;
	}

	void assertLog(bool assertion, const StringStream& message, const char* file=0, int line=-1)
	{
		tcout << message.str() << std::endl;
		assert( assertion );
	}

	bool isFatalEnabled() const
	{
		return true;
	}

	void fatal(const StringStream& message, const char* file=0, int line=-1)
	{
		tcout << message.str() << std::endl;
	}


	bool isErrorEnabled() const
	{
		return true;
	}

	void error(const StringStream& message, const char* file=0, int line=-1)
	{
		tcout << message.str() << std::endl;
	}


	bool isInfoEnabled() const
	{
		return true;
	}

	void info(const StringStream& message, const char* file=NULL, int line=-1)
	{
		tcout << message.str() << std::endl;
	}

	bool isDebugEnabled() const
	{
		return true;
	}

	void debug(const StringStream& message, const char* file=0, int line=-1)
	{
		tcout << message.str() << std::endl;
	}

	bool isWarnEnabled() const
	{
		return true;
	}

	void warn(const StringStream& message, const char* file=NULL, int line=-1)
	{
		tcout << message.str() << std::endl;
	}

	bool isTraceEnabled() const
	{
		return true;
	}

	void trace(const StringStream& message, const char* file=NULL, int line=-1)
	{
		tcout << message.str() << std::endl;
	}

	bool isEnabledFor(const LevelPtr& level) const
	{
		return true;
	}

	void log(const LevelPtr& level, const StringStream& message,
		const char* file=0, int line=-1)
	{
		tcout << message.str() << std::endl;
	}

	const LevelPtr& getLevel() const
	{
		return l;
	}

	void pushNDC( const tchar* str )
	{
	}

	void popNDC( )
	{
	}

	virtual void clearNDC()
	{
	}

private:
	LevelPtr l;
};

_jingxian_end

#endif // _StdLogger_H_