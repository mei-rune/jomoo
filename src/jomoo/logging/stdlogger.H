

/**
* -*- C++ -*-
* -------------------------------------------------------------------------------
* - °Ë®q°–®r ®q°–®r							StdLogger.h,v 1.0 2005/11/16 14:37:54
*  ®u®ê®Ä®Ä®é ®q®q °–®r
* ¶ÚÃÔ¶ÚÃÔÃÔ| ®t------
* -------------------------------------------------------------------------------
*/

#ifndef _StdLogger_H_
#define _StdLogger_H_

#include "jomoo/config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include "Logger.h"
#include <iostream>

_jomoo_begin

namespace logging
{

class StdLogger : public ILogger
{
public:

	StdLogger()
	{
	 l = Trace;
	}

	void assertLog(bool assertion, const StringStream& message, const char* file=0, int line=-1)
	{
		std::cout << message.str() << std::endl;
		assert( assertion );
	}

	bool isFatalEnabled() const
	{
		return true;
	}

	void fatal(const StringStream& message, const char* file=0, int line=-1)
	{
		std::cout << message.str() << std::endl;
	}


	bool isErrorEnabled() const
	{
		return true;
	}

	void error(const StringStream& message, const char* file=0, int line=-1)
	{
		std::cout << message.str() << std::endl;
	}


	bool isInfoEnabled() const
	{
		return true;
	}

	void info(const StringStream& message, const char* file=NULL, int line=-1)
	{
		std::cout << message.str() << std::endl;
	}

	bool isDebugEnabled() const
	{
		return true;
	}

	void debug(const StringStream& message, const char* file=0, int line=-1)
	{
		std::cout << message.str() << std::endl;
	}

	bool isWarnEnabled() const
	{
		return true;
	}

	void warn(const StringStream& message, const char* file=NULL, int line=-1)
	{
		std::cout << message.str() << std::endl;
	}

	bool isTraceEnabled() const
	{
		return true;
	}

	void trace(const StringStream& message, const char* file=NULL, int line=-1)
	{
		std::cout << message.str() << std::endl;
	}

	bool isEnabledFor(const LevelPtr& level) const
	{
		return true;
	}

	void log(const LevelPtr& level, const StringStream& message,
		const char* file=0, int line=-1)
	{
		std::cout << message.str() << std::endl;
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

}

_jomoo_end

#endif // _StdLogger_H_