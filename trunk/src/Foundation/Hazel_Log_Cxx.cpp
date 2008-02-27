#include "BT_Log_Cxx.h"

#ifndef NOLOG4CXX

#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/helpers/exception.h>



_boe_begin

BT_Log_Cxx::BT_Log_Cxx( const tchar* name )
:  rootLogger_( name == 0 ? log4cxx:: Logger::getRootLogger() : log4cxx:: Logger::getLogger( name ) )
{
	if( name != 0 )
		m_NDCs_.push_back( name );
	else
		m_NDCs_.push_back( "" );

}

BT_Log_Cxx::~BT_Log_Cxx(void)
{
}

void BT_Log_Cxx::assertLog(bool assertion, const StringStream& msg, const char* file, int line )
{
	rootLogger_->assertLog( assertion, msg.str() );
}

bool BT_Log_Cxx::isFatalEnabled() const
{
	return rootLogger_->isFatalEnabled( );
}

void BT_Log_Cxx::fatal(const StringStream& message, const char* file, int line)
{
	return rootLogger_->forcedLog( log4cxx::Level::FATAL, message.str(), file, line);
}

bool BT_Log_Cxx::isErrorEnabled() const
{
	return rootLogger_->isErrorEnabled( );
}

void BT_Log_Cxx::error(const StringStream& message, const char* file, int line)
{
	return rootLogger_->forcedLog( log4cxx::Level::ERROR, message.str(), file, line);
}

bool BT_Log_Cxx::isInfoEnabled() const
{
	return rootLogger_->isInfoEnabled( );
}

void BT_Log_Cxx::info(const StringStream& message, const char* file, int line)
{
	return rootLogger_->forcedLog( log4cxx::Level::INFO, message.str(), file, line);
}

bool BT_Log_Cxx::isDebugEnabled() const
{
	return rootLogger_->isDebugEnabled( );
}

void BT_Log_Cxx::debug(const StringStream& message, const char* file, int line)
{
	return rootLogger_->forcedLog( log4cxx::Level::DEBUG, message.str(), file, line);
}

bool BT_Log_Cxx::isWarnEnabled() const
{
	return rootLogger_->isWarnEnabled( );
}

void BT_Log_Cxx::warn(const StringStream& message, const char* file, int line)
{
	return rootLogger_->forcedLog( log4cxx::Level::WARN, message.str(), file, line);
}


bool BT_Log_Cxx::isTraceEnabled() const
{
	return rootLogger_->isDebugEnabled( );
}

void BT_Log_Cxx::trace(const StringStream& message, const char* file, int line )
{
	return rootLogger_->forcedLog( log4cxx::Level::DEBUG, message.str(), file, line);
}

bool BT_Log_Cxx::isEnabledFor(const LevelPtr& level) const
{
	return rootLogger_->isEnabledFor( log4cxx:: Level::toLevel( LevelPtrtoLog4CxxLevel( level ) ) );
}

void BT_Log_Cxx::log(const LevelPtr& level, const StringStream& message,
	const char* file, int line)
{
	return rootLogger_->forcedLog( log4cxx:: Level::toLevel( LevelPtrtoLog4CxxLevel( level ) ),
		message.str(), file, line);
}

const BOE_Log_Impl::LevelPtr& BT_Log_Cxx::getLevel() const
{
	level_ = Log4CxxLeveltoLevelPtr( rootLogger_->getLevel()->toInt() );
	return   level_;
}

BOE_Log_Impl::LevelPtr BT_Log_Cxx::Log4CxxLeveltoLevelPtr( int level ) const
{
	LevelPtr val = Fatal;
	switch( level )
	{
	case log4cxx::Level:: FATAL_INT:
		val = Fatal;
		break;
	case log4cxx::Level:: ERROR_INT:
		val = Error;
		break;
	case log4cxx::Level:: INFO_INT:
		val = Info;
		break;
	case log4cxx::Level:: DEBUG_INT:
		val = Debug;
		break;
	case log4cxx::Level:: WARN_INT:
		val = Warn;
		break;
	}
	return val;
}

int BT_Log_Cxx::LevelPtrtoLog4CxxLevel( LevelPtr level ) const
{
	int val = log4cxx::Level:: ALL_INT;
	switch( level )
	{
	case Fatal:
		val = log4cxx::Level:: FATAL_INT;
		break;
	case Error:
		val = log4cxx::Level:: ERROR_INT;
		break;
	case Info:
		val = log4cxx::Level:: INFO_INT;
		break;
	case Debug:
		val = log4cxx::Level:: DEBUG_INT;
		break;
	case Trace:
		val = log4cxx::Level:: DEBUG_INT;
		break;
	}
	return val;
};

void BT_Log_Cxx::createLog_i()
{
	
	tstring name;
	for( std::list< tstring >::iterator it = m_NDCs_.begin()
		; it != m_NDCs_.end()
		; it ++ )
		if( !it->empty() )
		{
			if( !name.empty() )
				name += ".";
			name += *it;
		}
	rootLogger_ = log4cxx:: Logger::getLogger( name );
}

void BT_Log_Cxx::pushNDC( const tchar* str )
{
	if( str != 0 )
	{
		m_NDCs_.push_back( str );
		createLog_i();
	}
	else
		m_NDCs_.push_back( "" );
	
}

void BT_Log_Cxx::popNDC( )
{
	if( m_NDCs_.size() > 1 )
	{
		m_NDCs_.pop_back();
		createLog_i();
	}
}

void BT_Log_Cxx::clearNDC()
{
	bool change = false;
	while( m_NDCs_.size() > 1 )
	{
		m_NDCs_.pop_back();
		change = true;
	}
	if( change )
		createLog_i();
}

void BT_Log_NDC_Cxx::pushNDC( const tchar* str )
{
	log4cxx:: NDC::push( str );
}

void BT_Log_NDC_Cxx::popNDC( )
{
	log4cxx:: NDC::pop();
	//std::cout << "NDC:" << log4cplus:: getNDC().pop() << std::endl;
}

BOE_Log_NDC_Base* make_BT_NDC_Cxx( )
{
	return new BT_Log_NDC_Cxx( );
}

BOE_Log_Impl* make_BT_Log_Cxx( const tchar* name )
{
	return new BT_Log_Cxx( name );
}


int init_BT_Log_Cxx(  )
{
	log4cxx::BasicConfigurator::configure();
	log4cxx::LoggerPtr rootLogger = log4cxx::Logger::getRootLogger();
	return 0;
}

void shutdown_BT_Log_Cxx(  )
{
}

_boe_end

#endif // #ifndef NOLOG4CXX