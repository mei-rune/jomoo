

#ifndef _NO_LOGCPLUS_


#include "BT_Log_CPlus.h"
#include "../System_Directory.H"
_bt_begin

class log4cplus_server
{
public:

	static log4cplus_server* get();
	int init( );
	int fini( );
private:
	log4cplus_server()
		: init_( false )
	{
	}
	bool init_;
	std::auto_ptr< _log4 ConfigureAndWatchThread > pwatch_;

	friend class ACE_Singleton< log4cplus_server, ACE_Thread_Mutex >;
};

log4cplus_server* log4cplus_server::get()
{
	return ACE_Singleton< log4cplus_server, ACE_Thread_Mutex >::instance();
}
int log4cplus_server::init()
{
	if( init_ )
		return 0;
	_log4helper LogLog::getLogLog()->setInternalDebugging(true);
	_log4 Logger root = _log4 Logger::getRoot();

	char modename[ MAX_PATH ] = "";
	::GetAppPath( modename, MAX_PATH );
	strcat( modename, "btnm.properties" );
	pwatch_.reset( new _log4 ConfigureAndWatchThread( modename, 5 * 1000 ) );
	init_ = true;
	return 0;
}

int log4cplus_server::fini()
{
	pwatch_.reset( 0 );
	init_ = false;
	return 0;
}


BT_Log_CPlus::BT_Log_CPlus(void)
: rootLogger_ ( log4cplus:: Logger::getInstance( "INIT" ) )
{
	log4cplus_server::get()->init();
	rootLogger_ = log4cplus:: Logger::getInstance( "BTNM" );
}

BT_Log_CPlus::~BT_Log_CPlus(void)
{
	log4cplus_server::get()->fini();
}

void BT_Log_CPlus::assertLog(bool assertion, const StringStream& msg, const char* file, int line )
{
	rootLogger_.forcedLog( log4cplus:: FATAL_LOG_LEVEL, msg.str(), file, line);
}

bool BT_Log_CPlus::isFatalEnabled() const
{
	return rootLogger_.isEnabledFor( log4cplus:: FATAL_LOG_LEVEL );
}

void BT_Log_CPlus::fatal(const StringStream& message, const char* file, int line)
{
	return rootLogger_.forcedLog( log4cplus:: FATAL_LOG_LEVEL, message.str(), file, line);
}

bool BT_Log_CPlus::isErrorEnabled() const
{
	return rootLogger_.isEnabledFor( log4cplus:: ERROR_LOG_LEVEL );
}

void BT_Log_CPlus::error(const StringStream& message, const char* file, int line)
{
	return rootLogger_.forcedLog( log4cplus:: ERROR_LOG_LEVEL, message.str(), file, line);
}

bool BT_Log_CPlus::isInfoEnabled() const
{
	return rootLogger_.isEnabledFor( log4cplus:: INFO_LOG_LEVEL );
}

void BT_Log_CPlus::info(const StringStream& message, const char* file, int line)
{
	return rootLogger_.forcedLog( log4cplus:: INFO_LOG_LEVEL, message.str(), file, line);
}

bool BT_Log_CPlus::isDebugEnabled() const
{
	return rootLogger_.isEnabledFor( log4cplus:: DEBUG_LOG_LEVEL );
}

void BT_Log_CPlus::debug(const StringStream& message, const char* file, int line)
{
	return rootLogger_.forcedLog( log4cplus:: DEBUG_LOG_LEVEL, message.str(), file, line);
}

bool BT_Log_CPlus::isWarnEnabled() const
{
	return rootLogger_.isEnabledFor( log4cplus:: WARN_LOG_LEVEL );
}

void BT_Log_CPlus::warn(const StringStream& message, const char* file, int line)
{
	return rootLogger_.forcedLog( log4cplus:: WARN_LOG_LEVEL, message.str(), file, line);
}

bool BT_Log_CPlus::isEnabledFor(const LevelPtr& level) const
{
	return rootLogger_.isEnabledFor( LevelPtrtoLog4CxxLevel( level ) );
}

void BT_Log_CPlus::log(const LevelPtr& level, const StringStream& message,
	const char* file, int line)
{
	return rootLogger_.forcedLog(  LevelPtrtoLog4CxxLevel( level  ),
		message.str(), file, line);
}

const BT_Log::LevelPtr& BT_Log_CPlus::getLevel() const
{
	level_ = Log4CxxLeveltoLevelPtr( rootLogger_.getLogLevel() );
	return   level_;
}

BT_Log::LevelPtr BT_Log_CPlus::Log4CxxLeveltoLevelPtr( int level ) const
{
	LevelPtr val = Fatal;
	switch( level )
	{
	case log4cplus:: FATAL_LOG_LEVEL:
		val = Fatal;
		break;
	case log4cplus:: ERROR_LOG_LEVEL:
		val = Error;
		break;
	case log4cplus:: INFO_LOG_LEVEL:
		val = Info;
		break;
	case log4cplus:: DEBUG_LOG_LEVEL:
		val = Debug;
		break;
	case log4cplus:: WARN_LOG_LEVEL:
		val = Warn;
		break;
	}
	return val;
}

int BT_Log_CPlus::LevelPtrtoLog4CxxLevel( LevelPtr level ) const
{
	int val = log4cplus:: ALL_LOG_LEVEL;
	switch( level )
	{
	case Fatal:
		val = log4cplus:: FATAL_LOG_LEVEL;
		break;
	case Error:
		val = log4cplus:: ERROR_LOG_LEVEL;
		break;
	case Info:
		val = log4cplus:: INFO_LOG_LEVEL;
		break;
	case Debug:
		val = log4cplus:: DEBUG_LOG_LEVEL;
		break;
	case Warn:
		val = log4cplus:: WARN_LOG_LEVEL;
		break;
	}
	return val;
};


BT_Log_NDC_CPlus::BT_Log_NDC_CPlus( )
{
}


BT_Log_NDC_CPlus::~BT_Log_NDC_CPlus( )
{
}


void BT_Log_NDC_CPlus::pushNDC( const tchar* str )
{
	//log4cplus:: getNDC().push( str );
}

void BT_Log_NDC_CPlus::popNDC( )
{
	//std::cout << "NDC:" << log4cplus:: getNDC().pop() << std::endl;
}

_bt_end

#endif // _NO_LOGCPLUS_