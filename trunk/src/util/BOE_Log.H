

/**
* -*- C++ -*-
* -------------------------------------------------------------------------------
* - ¤╭⌒╮ ╭⌒╮							  BOE_Log.h,v 1.0 2005/03/25 09:50:54
*  ╱◥██◣ ╭╭ ⌒╮
* ︱田︱田田| ╰------
* -------------------------------------------------------------------------------
*/

#ifndef _BOE_Log_H_
#define _BOE_Log_H_

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include "BOE_Log_Base.H"

namespace LOG
{
	
	class BOE_Endl { };
	class BOE_Fatal { };
	class BOE_Error	{ };
	class BOE_Info { };
	class BOE_Debug { };
	class BOE_Warn { };
	class BOE_Trace { };
	const static BOE_Endl endl;
	const static BOE_Fatal Fatal;
	const static BOE_Error	Error;
	const static BOE_Info Info;
	const static BOE_Debug Debug;
	const static BOE_Warn Warn;
	const static BOE_Trace Trace;
}

_bt_begin

class BOE_Log
{
public:
		
	typedef BOE_Log_Facetory::LoggerPtr LoggerPtr;
	typedef BOE_Log_Impl::LevelPtr LevelPtr;

	BOE_Log( const tchar* name , const tchar* description = 0 )
		: m_log_( ( BOE_Log_Impl* ) 0 )
		, m_name_( name == 0 ? "" : name )
		, m_description_( description == 0? "":description )
	{
		initialize();
	}

	BOE_Log( const tstring& name , const tchar* description = 0 )
	: m_log_( ( BOE_Log_Impl* ) 0 )
	, m_name_( name )
	, m_description_( description == 0? "":description )
	{
		initialize();
	}

	BOE_Log( const tchar* name , const tstring& description )
		: m_log_( ( BOE_Log_Impl* ) 0 )
		, m_name_( name == 0 ? "" : name )
		, m_description_( description  )
	{
		initialize();
	}

	BOE_Log( const tstring& name , const tstring& description = 0 )
	: m_log_( ( BOE_Log_Impl* ) 0 )
	, m_name_( name )
	, m_description_( description )
	{
		initialize();
	}

	BOE_Log( const BOE_Log& log )
		: m_log_( ( LoggerPtr&)log.m_log_ )
		, m_name_( log.m_name_ )
		, m_description_( log.m_description_ )
	{
		m_stm_ << m_description_;
	}

	BOE_Log &operator=( const BOE_Log& log )
	{
		m_log_ =  ( LoggerPtr& )log.m_log_;
		m_name_ = log.m_name_;
		m_description_ = log.m_description_;
		
		m_stm_ << m_description_;
		return *this;
	}

	void set( const tchar* description )
	{
		m_description_ = ( description == 0 ? "" : description );
	}

	void append( const tchar* description )
	{
		if( description )
			m_description_ += description;
	}

	void set( const tstring& description )
	{
		m_description_ = description;
	}

	void append( const tstring& description )
	{
		m_description_ += description;
	}

	/**
	 * assert 语句
	 * @param[ in ] assertion 条件是否为真
	 * @param[ in ] message 日志内容
	 * @param[ in ] file 日志记录的源文件名
	 * @param[ in ] line 日志记录的源文件的当前行
	 */
	void assertLog(bool assertion, const StringStream& msg, const char* file=0, int line=-1)
	{
		if( m_log_.get() )
			m_log_->assertLog( assertion,msg, file, line );
	}

	/**
	 * fatal级的日志是否可以记日志
	 * @return 可以true,不可以false
	 */
	bool isFatalEnabled() const
	{
		if( m_log_.get() )
			return m_log_->isFatalEnabled( );
		return false;
	}
	
	/**
	 * 记录fatal级的日志
	 * @param[ in ] message 日志内容
	 * @param[ in ] file 日志记录的源文件名
	 * @param[ in ] line 日志记录的源文件的当前行
	 */
	void fatal(const StringStream& message, const char* file=0, int line=-1)
	{
		if( m_log_.get() )
			m_log_->fatal( message, file, line );
	}

	/**
	 * error级的日志是否可以记日志
	 * @return 可以true,不可以false
	 */
	bool isErrorEnabled() const
	{
		if( m_log_.get() )
			return m_log_->isErrorEnabled( );
		return false;
	}

	/**
	 * 记录error级的日志
	 * @param[ in ] message 日志内容
	 * @param[ in ] file 日志记录的源文件名
	 * @param[ in ] line 日志记录的源文件的当前行
	 */
	void error(const StringStream& message, const char* file=0, int line=-1)
	{
		if( m_log_.get() )
			m_log_->error( message, file, line );
	}

	/**
	 * info级的日志是否可以记日志
	 * @return 可以true,不可以false
	 */
	bool isInfoEnabled() const
	{
		if( m_log_.get() )
			return m_log_->isInfoEnabled( );
		return false;
	}

	/**
	 * 记录info级的日志
	 * @param[ in ] message 日志内容
	 * @param[ in ] file 日志记录的源文件名
	 * @param[ in ] line 日志记录的源文件的当前行
	 */
	void info(const StringStream& message, const char* file=NULL, int line=-1)
	{
		if( m_log_.get() )
			m_log_->info( message, file, line );
	}

	/**
	 * debug级的日志是否可以记日志
	 * @return 可以true,不可以false
	 */
	bool isDebugEnabled() const
	{
		if( m_log_.get() )
			return m_log_->isDebugEnabled( );
		return false;
	}

	/**
	 * 记录debug级的日志
	 * @param[ in ] message 日志内容
	 * @param[ in ] file 日志记录的源文件名
	 * @param[ in ] line 日志记录的源文件的当前行
	 */
	void debug(const StringStream& message, const char* file=0, int line=-1)
	{
		if( m_log_.get() )
			m_log_->debug( message, file, line );
	}

	/**
	 * warn级的日志是否可以记日志
	 * @return 可以true,不可以false
	 */
	bool isWarnEnabled() const
	{
		if( m_log_.get() )
			return m_log_->isWarnEnabled( );
		return false;
	}

	/**
	 * 记录warn级的日志
	 * @param[ in ] message 日志内容
	 * @param[ in ] file 日志记录的源文件名
	 * @param[ in ] line 日志记录的源文件的当前行
	 */
	void warn(const StringStream& message, const char* file=NULL, int line=-1)
	{
		if( m_log_.get() )
			m_log_->warn( message, file, line );
	}

	/**
	 * Trace级的日志是否可以记日志
	 * @return 可以true,不可以false
	 */
	bool isTraceEnabled() const
	{
		if( m_log_.get() )
			return m_log_->isTraceEnabled( );
		return false;
	}

	/**
	 * 记录warn级的日志
	 * @param[ in ] message 日志内容
	 * @param[ in ] file 日志记录的源文件名
	 * @param[ in ] line 日志记录的源文件的当前行
	 */
	void trace(const StringStream& message, const char* file=NULL, int line=-1)
	{
		if( m_log_.get() )
			m_log_->trace( message, file, line );
	}

	/**
	 * level级的日志是否可以记日志
	 * @return 可以true,不可以false
	 */
	bool isEnabledFor(const LevelPtr& level) const
	{
		if( m_log_.get() )
			return m_log_->isEnabledFor( level );
		return false;
	}

	/**
	 * 记录level级的日志
	 * @param[ in ] message 日志内容
	 * @param[ in ] file 日志记录的源文件名
	 * @param[ in ] line 日志记录的源文件的当前行
	 */
	void log(const LevelPtr& level, const StringStream& message,
		const char* file=0, int line=-1)
	{
		if( m_log_.get() )
			m_log_->log( level, message, file, line );
	}


	const tchar* name() const
	{
		return m_name_.c_str();
	}

	const tstring& toString() const
	{
		return m_name_;
	}

	BOE_Log& operator<< ( const LOG::BOE_Fatal& t )
	{
		m_level_ = BOE_Log_Impl::Fatal;
		return *this;
	}

	BOE_Log& operator<< ( const LOG::BOE_Error& t )
	{
		m_level_ = BOE_Log_Impl::Error;
		return *this;
	}

	BOE_Log& operator<< ( const LOG::BOE_Info& t )
	{
		m_level_ = BOE_Log_Impl::Info;
		return *this;
	}

	BOE_Log& operator<< ( const LOG::BOE_Debug& t )
	{
		m_level_ = BOE_Log_Impl::Debug;
		return *this;
	}

	BOE_Log& operator<< ( const LOG::BOE_Warn& t )
	{
		m_level_ = BOE_Log_Impl::Warn;
		return *this;
	}

	BOE_Log& operator<< ( const LOG::BOE_Trace & t )
	{
		m_level_ = BOE_Log_Impl::Trace;
		return *this;
	}

	BOE_Log& operator<< ( const LOG::BOE_Endl& t )
	{
		log( m_level_, m_stm_, 0, -1);
		m_stm_.clear();
		m_stm_ << m_description_;
		return *this;
	}

	template< typename T >
		BOE_Log& operator<< ( T t )
	{
		m_stm_ << t;
		return *this;
	}

private:

	void initialize( )
	{
		if( m_name_.empty() )
			throw std::runtime_error( "BT_Log 名不能为空" );
		m_log_ = BOE_Log_Facetory_Implementation::get()->createLog( m_name_.c_str() );

		m_stm_ << m_description_;
	}

	LoggerPtr m_log_;

	tstring m_name_;

	StringStream m_stm_;

	BOE_Log_Impl::LevelPtr m_level_;

	tstring m_description_;
};

_bt_end


#ifndef _NO_BOE_LOG_

#ifndef BOE_NDC
#define BOE_NDC( ndc , msg )		 _bt BOE_Log_NDC ndc( msg )
#endif //BOE_LOG_NDC

#ifndef BOE_LOG

#define BOE_LOG(logger, level, message) { \
	if ( logger.isEnabledFor(level)) {\
	StringStream oss; \
	oss << message; \
	logger.fatal(level, oss, __FILE__, __LINE__); }}

#endif // BOE_LOG

#ifndef BOE_LOG_RETURN

#define BOE_LOG_RETURN(logger, level, message,ret) { \
	StringStream oss; \
	oss << message; \
	if ( logger.isEnabledFor(level)) {\
	logger.fatal(level, oss, __FILE__, __LINE__); } return ( ret );}

#endif // BOE_LOG_RETURN

#ifndef BOE_LOG_THROW

#define BOE_LOG_THROW(logger,  message ) { \
	StringStream oss; \
	oss << message; \
	if ( logger.isFatalEnabled( )) {\
	logger.fatal( oss, __FILE__, __LINE__); } throw std::runtime_error ( oss.str() );}

#endif // BOE_LOG_THROW

#ifndef BOE_LOG_DEBUG

#define BOE_LOG_DEBUG(logger, message) { \
	if ( logger.isDebugEnabled()) {\
	StringStream oss; \
	oss << message; \
	logger.debug( oss, __FILE__, __LINE__); }}
#endif // BOE_LOG_DEBUG

#ifndef BOE_LOG_DEBUG_RETURN

#define BOE_LOG_DEBUG_RETURN(logger, message, ret ) { \
	if ( logger.isDebugEnabled()) {\
	StringStream oss; \
	oss << message; \
	logger.debug( oss, __FILE__, __LINE__); } return ( ret );}
#endif // BOE_LOG_DEBUG_RETURN

#ifndef BOE_LOG_DEBUG_THROW

#define BOE_LOG_DEBUG_THROW(logger, message ) { \
	StringStream oss; \
	oss << message; \
	if ( logger.isDebugEnabled()) {\
	logger.debug( oss, __FILE__, __LINE__); } throw std::runtime_error ( oss.str() ); }
#endif // BOE_LOG_DEBUG_THROW

#ifndef BOE_LOG_INFO

#define BOE_LOG_INFO(logger, message) { \
	if ( logger.isInfoEnabled()) {\
	StringStream oss; \
	oss << message; \
	logger.info( oss, __FILE__, __LINE__); }}
#endif // BOE_LOG_INFO

#ifndef BOE_LOG_INFO_RETURN

#define BOE_LOG_INFO_RETURN(logger, message, ret ) { \
	if ( logger.isInfoEnabled()) {\
	StringStream oss; \
	oss << message; \
	logger.info( oss, __FILE__, __LINE__); } return ( ret ); }
#endif // BOE_LOG_INFO_RETURN

#ifndef BOE_LOG_INFO_THROW
#define BOE_LOG_INFO_THROW(logger, message ) { \
	StringStream oss; \
	oss << message; \
	if ( logger.isInfoEnabled()) {\
	logger.info( oss, __FILE__, __LINE__); } throw std::runtime_error ( oss.str() ); }
#endif // BOE_LOG_INFO_THROW

#ifndef BOE_LOG_WARN

#define BOE_LOG_WARN(logger, message) { \
	if ( logger.isWarnEnabled()) {\
	StringStream oss; \
	oss << message; \
	logger.warn( oss, __FILE__, __LINE__); }}
#endif // BOE_LOG_WARN

#ifndef BOE_LOG_WARN_RETURN

#define BOE_LOG_WARN_RETURN(logger, message, ret ) { \
	if ( logger.isWarnEnabled()) {\
	StringStream oss; \
	oss << message; \
	logger.warn( oss, __FILE__, __LINE__); } return ( ret ); }
#endif // BOE_LOG_WARN_RETURN

#ifndef BOE_LOG_WARN_THROW

#define BOE_LOG_WARN_THROW(logger, message ) { \
	StringStream oss; \
	oss << message; \
	if ( logger.isWarnEnabled()) {\
	logger.warn( oss, __FILE__, __LINE__); } throw std::runtime_error ( oss.str() ); }
#endif // BOE_LOG_WARN_THROW

#ifndef BOE_LOG_ERROR

#define BOE_LOG_ERROR(logger, message) { \
	if ( logger.isErrorEnabled()) {\
	StringStream oss; \
	oss << message; \
	logger.error( oss, __FILE__, __LINE__); }}
#endif // BOE_LOG_ERROR

#ifndef BOE_LOG_ERROR_RETURN

#define BOE_LOG_ERROR_RETURN(logger, message, ret ) { \
	if ( logger.isErrorEnabled()) {\
	StringStream oss; \
	oss << message; \
	logger.error( oss, __FILE__, __LINE__); } return ( ret );}
#endif // BOE_LOG_ERROR_RETURN

#ifndef BOE_LOG_ERROR_THROW
#define BOE_LOG_ERROR_THROW(logger, message ) { \
	StringStream oss; \
	oss << message; \
	if ( logger.isErrorEnabled()) {\
	logger.error( oss, __FILE__, __LINE__); } throw std::runtime_error ( oss.str() ); }
#endif // BOE_LOG_ERROR_THROW

#ifndef BOE_LOG_FATAL

#define BOE_LOG_FATAL(logger, message) { \
	if ( logger.isFatalEnabled()) {\
	StringStream oss; \
	oss << message; \
	logger.fatal( oss, __FILE__, __LINE__); }}
#endif // BOE_LOG_FATAL

#ifndef BOE_LOG_FATAL_RETURN

#define BOE_LOG_FATAL_RETURN(logger, message, ret ) { \
	if ( logger.isFatalEnabled()) {\
	StringStream oss; \
	oss << message; \
	logger.fatal( oss, __FILE__, __LINE__); } return ( ret );}
#endif // BOE_LOG_FATAL_RETURN

#ifndef BOE_LOG_FATAL_THROW
#define BOE_LOG_FATAL_THROW(logger, message ) { \
	StringStream oss; \
	oss << message; \
	if ( logger.isFatalEnabled()) {\
	logger.fatal( oss, __FILE__, __LINE__); } throw std::runtime_error ( oss.str() ); }
#endif // BOE_LOG_FATAL_THROW

#ifndef BOE_ASSERT
#define BOE_ASSERT(logger,assertion, message) { \
	if ( logger != 0 ) {\
	StringStream oss; \
	oss << message; \
	logger.assertLog( assertion ,oss, __FILE__, __LINE__); }}

#endif // BOE_ASSERT

#else	// _NO_BOE_LOG_

#ifndef BOE_NDC
#define BOE_NDC( logger, ndc , msg )				{}
#endif // BOE_NDC
#ifndef BOE_LOG
#define BOE_LOG(logger, level, message)			{}
#endif // BOE_LOG
#ifndef BOE_LOG_DEBUG
#define BOE_LOG_DEBUG(logger, message)			{}
#endif // BOE_LOG_DEBUG
#ifndef BOE_LOG_INFO
#define BOE_LOG_INFO(logger, message)			{}
#endif // BOE_LOG_INFO
#ifndef BOE_LOG_WARN
#define BOE_LOG_WARN(logger, message)			{}
#endif // BOE_LOG_WARN
#ifndef BOE_LOG_ERROR
#define BOE_LOG_ERROR(logger, message)			{}
#endif // BOE_LOG_ERROR
#ifndef BOE_LOG_FATAL
#define BOE_LOG_FATAL(logger, message)			{}
#endif // BOE_LOG_FATAL
#ifndef BOE_ASSERT
#define BOE_ASSERT(logger,assertion, message)	{}
#endif // BOE_ASSERT

#ifndef BOE_LOG_RETURN
#define BOE_LOG_RETURN(logger, level, message, ret )			return ( ret );
#endif // BOE_LOG_RETURN
#ifndef BOE_LOG_DEBUG_RETURN
#define BOE_LOG_DEBUG_RETURN(logger, message, ret )			return ( ret );
#endif // BOE_LOG_DEBUG_RETURN
#ifndef BOE_LOG_INFO_RETURN
#define BOE_LOG_INFO_RETURN(logger, message, ret )			return ( ret );
#endif // BOE_LOG_INFO_RETURN
#ifndef BOE_LOG_WARN_RETURN
#define BOE_LOG_WARN_RETURN(logger, message, ret )			return ( ret );
#endif // BOE_LOG_WARN_RETURN
#ifndef BOE_LOG_ERROR_RETURN
#define BOE_LOG_ERROR_RETURN(logger, message, ret )			return ( ret );
#endif // BOE_LOG_ERROR_RETURN
#ifndef BOE_LOG_FATAL_RETURN
#define BOE_LOG_FATAL_RETURN(logger, message, ret )			return ( ret );
#endif // BOE_LOG_FATAL_RETURN



#ifndef BOE_LOG_THROW
#define BOE_LOG_THROW(logger, message )			{ \
	StringStream oss; \
	oss << message; \
	throw std::runtime_error( oss.str() );\
}

#endif // BOE_LOG_THROW
#ifndef BOE_LOG_DEBUG_THROW
#define BOE_LOG_DEBUG_THROW(logger, message )		{ \
	StringStream oss; \
	oss << message; \
	throw std::runtime_error( oss.str() );\
}

#endif // BOE_LOG_DEBUG_THROW
#ifndef BOE_LOG_INFO_THROW
#define BOE_LOG_INFO_THROW(logger, message )		{ \
	StringStream oss; \
	oss << message; \
	throw std::runtime_error( oss.str() );\
}
#endif // BOE_LOG_INFO_THROW
#ifndef BOE_LOG_WARN_THROW
#define BOE_LOG_WARN_THROW(logger, message )		{ \
	StringStream oss; \
	oss << message; \
	throw std::runtime_error( oss.str() );\
}
#endif // BOE_LOG_WARN_THROW
#ifndef BOE_LOG_ERROR_THROW
#define BOE_LOG_ERROR_THROW(logger, message )		{ \
	StringStream oss; \
	oss << message; \
	throw std::runtime_error( oss.str() );\
}
#endif // BOE_LOG_ERROR_THROW
#ifndef BOE_LOG_FATAL_THROW
#define BOE_LOG_FATAL_THROW(logger, message )		{ \
	StringStream oss; \
	oss << message; \
	throw std::runtime_error( oss.str() );\
}
#endif // BOE_LOG_FATAL_THROW

#endif // _NO_BOE_LOG_

#endif // _BOE_Log_H_