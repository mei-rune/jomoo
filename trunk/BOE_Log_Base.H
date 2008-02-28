

/**
* -*- C++ -*-
* -------------------------------------------------------------------------------
* - ¤╭⌒╮ ╭⌒╮							  BOE_Log.h,v 1.0 2005/03/25 09:50:54
*  ╱◥██◣ ╭╭ ⌒╮
* ︱田︱田田| ╰------
* -------------------------------------------------------------------------------
*/

#ifndef _BOE_Log_Impl_H_
#define _BOE_Log_Impl_H_

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include "util/tstring.h"
#include "boost/shared_ptr.hpp"
#include "BT_Export.h"

_bt_begin

/**
 * @Brief BOE_Log_Impl 日志接口
 * 这是BT的日志接口，每一个具体的日志都必须从它继承，每一个需要记日志的都可以得到一个这样的接，
 * 但不推荐直接使用它。有一组预定义好的宏，请使用宏
 */
class BOE_Log_Impl
{
public:

	typedef long LevelPtr;

	enum {
		 Fatal
		,Error
		,Info
		,Debug
		,Warn
		,Trace
	};

	/**
	 * virtual BOE_Log_Impl destructor
	 */
	virtual ~BOE_Log_Impl(){};

	/**
	 * assert 语句
	 * @param[ in ] assertion 条件是否为真
	 * @param[ in ] message 日志内容
	 * @param[ in ] file 日志记录的源文件名
	 * @param[ in ] line 日志记录的源文件的当前行
	 */
	virtual void assertLog(bool assertion, const StringStream& msg, const char* file=0, int line=-1) = 0;

	/**
	 * fatal级的日志是否可以记日志
	 * @return 可以true,不可以false
	 */
	virtual bool isFatalEnabled() const = 0;
	
	/**
	 * 记录fatal级的日志
	 * @param[ in ] message 日志内容
	 * @param[ in ] file 日志记录的源文件名
	 * @param[ in ] line 日志记录的源文件的当前行
	 */
	virtual void fatal(const StringStream& message, const char* file=0, int line=-1) = 0;

	/**
	 * error级的日志是否可以记日志
	 * @return 可以true,不可以false
	 */
	virtual bool isErrorEnabled() const = 0;

	/**
	 * 记录error级的日志
	 * @param[ in ] message 日志内容
	 * @param[ in ] file 日志记录的源文件名
	 * @param[ in ] line 日志记录的源文件的当前行
	 */
	virtual void error(const StringStream& message, const char* file=0, int line=-1) = 0;

	/**
	 * info级的日志是否可以记日志
	 * @return 可以true,不可以false
	 */
	virtual bool isInfoEnabled() const = 0;

	/**
	 * 记录info级的日志
	 * @param[ in ] message 日志内容
	 * @param[ in ] file 日志记录的源文件名
	 * @param[ in ] line 日志记录的源文件的当前行
	 */
	virtual void info(const StringStream& message, const char* file=NULL, int line=-1) = 0;

	/**
	 * debug级的日志是否可以记日志
	 * @return 可以true,不可以false
	 */
	virtual bool isDebugEnabled() const = 0;

	/**
	 * 记录debug级的日志
	 * @param[ in ] message 日志内容
	 * @param[ in ] file 日志记录的源文件名
	 * @param[ in ] line 日志记录的源文件的当前行
	 */
	virtual void debug(const StringStream& message, const char* file=0, int line=-1) = 0;

	/**
	 * warn级的日志是否可以记日志
	 * @return 可以true,不可以false
	 */
	virtual bool isWarnEnabled() const = 0;

	/**
	 * 记录warn级的日志
	 * @param[ in ] message 日志内容
	 * @param[ in ] file 日志记录的源文件名
	 * @param[ in ] line 日志记录的源文件的当前行
	 */
	virtual void warn(const StringStream& message, const char* file=NULL, int line=-1) = 0;

	/**
	 * Trace级的日志是否可以记日志
	 * @return 可以true,不可以false
	 */
	virtual bool isTraceEnabled() const = 0;

	/**
	 * 记录warn级的日志
	 * @param[ in ] message 日志内容
	 * @param[ in ] file 日志记录的源文件名
	 * @param[ in ] line 日志记录的源文件的当前行
	 */
	virtual void trace(const StringStream& message, const char* file=NULL, int line=-1) = 0;

	/**
	 * level级的日志是否可以记日志
	 * @return 可以true,不可以false
	 */
	virtual bool isEnabledFor(const LevelPtr& level) const = 0;

	/**
	 * 记录level级的日志
	 * @param[ in ] message 日志内容
	 * @param[ in ] file 日志记录的源文件名
	 * @param[ in ] line 日志记录的源文件的当前行
	 */
	virtual void log(const LevelPtr& level, const StringStream& message,
		const char* file=0, int line=-1) = 0;

	/**
	 * 取得当前的日志的级别
	 * @return 日志的级别
	 */
	virtual const LevelPtr& getLevel() const = 0;

	/**
	 * 基于对象的NDC,与下面的基于线程的不一样，它是只有使用这个日志对象才有
	 * 会在日志中打印NDC
	 * 加一个NDC
	 * @param[ in ] str 描述字符串
	 */
	virtual void pushNDC( const tchar* str ) = 0;

	/**
	 * 取出一个NDC
	 */
	virtual void popNDC( ) = 0;

	/**
	 * 清空NDC
	 */
	virtual void clearNDC() = 0;
};


class BOE_Log_NDC_Base
{
public:
	virtual ~BOE_Log_NDC_Base(){}
	virtual void pushNDC( const tchar* str ) = 0;
	virtual void popNDC( ) = 0;
};

_bt_end

namespace LOG
{
BT_Export_C int ___init_log( );
BT_Export_C void ___shutdown_log( );

BT_Export_C _bt BOE_Log_Impl* ___make_BOE_Log( const tchar* descr = 0 );
BT_Export_C _bt BOE_Log_NDC_Base* ___make_BOE_NDC( );
}
_bt_begin


/**
 * @Brief BOE_Log_Facetory 日志工厂
 */
class BOE_Log_Facetory
{
public:

	typedef boost::shared_ptr < BOE_Log_Impl > LoggerPtr;

	/**
	 * 创建一个日志对象
	 * @param[ in ] descr 日志名称
	 * @return 成功返回日志对象，失败返回0
	 */
	LoggerPtr createLog( const tchar* descr = 0 )
	{
		return LoggerPtr( LOG::___make_BOE_Log( descr ) );
	}
};

namespace BOE_Log_Facetory_Implementation
{
	inline BOE_Log_Facetory* get()
	{
		static BOE_Log_Facetory factory_;
		return &factory_;
	}
}


class BOE_Log_NDC
{
public:
	BOE_Log_NDC( const tstring& str )
		: ndc_( LOG:: ___make_BOE_NDC() )
	{
		if( ndc_.get() != 0 )
			ndc_->pushNDC( str.c_str() );
	}


	BOE_Log_NDC( const tchar* str )
		: ndc_( LOG::___make_BOE_NDC() )
	{
		if( ndc_.get() != 0 && str != 0 )
			ndc_->pushNDC( str );
	}


	~BOE_Log_NDC()
	{
		if( ndc_.get() != 0 )
			ndc_ -> popNDC( );
	}

private:
	std::auto_ptr< BOE_Log_NDC_Base > ndc_;
};

_bt_end

namespace LOG
{
	typedef BOE_Log_Facetory::LoggerPtr LoggerPtr;
}

#ifndef _NO_BT_LOG_

#ifndef BT_NDC
#define BT_NDC( ndc , msg )		 _bt BT_Log_NDC ndc( msg )
#endif //BT_LOG_NDC

#ifndef BT_LOG
#define BT_LOG(logger, level, message) { \
	if ( logger != 0 && logger->isEnabledFor(level)) {\
	StringStream oss; \
	oss << message; \
	logger->fatal(level, oss, __FILE__, __LINE__); }}

#endif // BT_LOG

#ifndef BT_LOG_RETURN
#define BT_LOG_RETURN(logger, level, message,ret) { \
	StringStream oss; \
	oss << message; \
	if ( logger != 0 && logger->isEnabledFor(level)) {\
	logger->fatal(level, oss, __FILE__, __LINE__); } return ( ret );}

#endif // BT_LOG_RETURN

#ifndef BT_LOG_THROW
#define BT_LOG_THROW(logger, level, message ) { \
	StringStream oss; \
	oss << message; \
	if ( logger != 0 && logger->isEnabledFor(level)) {\
	logger->fatal(level, oss, __FILE__, __LINE__); } throw std::runtime_error ( oss.str() );}

#endif // BT_LOG_THROW

#ifndef BT_LOG_DEBUG
#define BT_LOG_DEBUG(logger, message) { \
	if ( logger != 0 && logger->isDebugEnabled()) {\
	StringStream oss; \
	oss << message; \
	logger->debug( oss, __FILE__, __LINE__); }}
#endif // BT_LOG_DEBUG

#ifndef BT_LOG_DEBUG_RETURN
#define BT_LOG_DEBUG_RETURN(logger, message, ret ) { \
	if ( logger != 0 && logger->isDebugEnabled()) {\
	StringStream oss; \
	oss << message; \
	logger->debug( oss, __FILE__, __LINE__); } return ( ret );}
#endif // BT_LOG_DEBUG_RETURN

#ifndef BT_LOG_DEBUG_THROW
#define BT_LOG_DEBUG_THROW(logger, message ) { \
	StringStream oss; \
	oss << message; \
	if ( logger != 0 && logger->isDebugEnabled()) {\
	logger->debug( oss, __FILE__, __LINE__); } throw std::runtime_error ( oss.str() ); }
#endif // BT_LOG_DEBUG_THROW

#ifndef BT_LOG_INFO
#define BT_LOG_INFO(logger, message) { \
	if ( logger != 0 && logger->isInfoEnabled()) {\
	StringStream oss; \
	oss << message; \
	logger->info( oss, __FILE__, __LINE__); }}
#endif // BT_LOG_INFO

#ifndef BT_LOG_INFO_RETURN
#define BT_LOG_INFO_RETURN(logger, message, ret ) { \
	if ( logger != 0 && logger->isInfoEnabled()) {\
	StringStream oss; \
	oss << message; \
	logger->info( oss, __FILE__, __LINE__); } return ( ret ); }
#endif // BT_LOG_INFO_RETURN

#ifndef BT_LOG_INFO_THROW
#define BT_LOG_INFO_THROW(logger, message ) { \
	StringStream oss; \
	oss << message; \
	if ( logger != 0 && logger->isInfoEnabled()) {\
	logger->info( oss, __FILE__, __LINE__); } throw std::runtime_error ( oss.str() ); }
#endif // BT_LOG_INFO_THROW

#ifndef BT_LOG_WARN
#define BT_LOG_WARN(logger, message) { \
	if ( logger != 0 && logger->isWarnEnabled()) {\
	StringStream oss; \
	oss << message; \
	logger->warn( oss, __FILE__, __LINE__); }}
#endif // BT_LOG_WARN

#ifndef BT_LOG_WARN_RETURN
#define BT_LOG_WARN_RETURN(logger, message, ret ) { \
	if ( logger != 0 && logger->isWarnEnabled()) {\
	StringStream oss; \
	oss << message; \
	logger->warn( oss, __FILE__, __LINE__); } return ( ret ); }
#endif // BT_LOG_WARN_RETURN

#ifndef BT_LOG_WARN_THROW
#define BT_LOG_WARN_THROW(logger, message ) { \
	StringStream oss; \
	oss << message; \
	if ( logger != 0 && logger->isWarnEnabled()) {\
	logger->warn( oss, __FILE__, __LINE__); } throw std::runtime_error ( oss.str() ); }
#endif // BT_LOG_WARN_THROW

#ifndef BT_LOG_ERROR
#define BT_LOG_ERROR(logger, message) { \
	if ( logger != 0 && logger->isErrorEnabled()) {\
	StringStream oss; \
	oss << message; \
	logger->error( oss, __FILE__, __LINE__); }}
#endif // BT_LOG_ERROR

#ifndef BT_LOG_ERROR_RETURN
#define BT_LOG_ERROR_RETURN(logger, message, ret ) { \
	if ( logger != 0 && logger->isErrorEnabled()) {\
	StringStream oss; \
	oss << message; \
	logger->error( oss, __FILE__, __LINE__); } return ( ret );}
#endif // BT_LOG_ERROR_RETURN

#ifndef BT_LOG_ERROR_THROW
#define BT_LOG_ERROR_THROW(logger, message ) { \
	StringStream oss; \
	oss << message; \
	if ( logger != 0 && logger->isErrorEnabled()) {\
	logger->error( oss, __FILE__, __LINE__); } throw std::runtime_error ( oss.str() ); }
#endif // BT_LOG_ERROR_THROW

#ifndef BT_LOG_FATAL
#define BT_LOG_FATAL(logger, message) { \
	if ( logger != 0 && logger->isFatalEnabled()) {\
	StringStream oss; \
	oss << message; \
	logger->fatal( oss, __FILE__, __LINE__); }}
#endif // BT_LOG_FATAL

#ifndef BT_LOG_FATAL_RETURN
#define BT_LOG_FATAL_RETURN(logger, message, ret ) { \
	if ( logger != 0 && logger->isFatalEnabled()) {\
	StringStream oss; \
	oss << message; \
	logger->fatal( oss, __FILE__, __LINE__); } return ( ret );}
#endif // BT_LOG_FATAL_RETURN

#ifndef BT_LOG_FATAL_THROW
#define BT_LOG_FATAL_THROW(logger, message ) { \
	StringStream oss; \
	oss << message; \
	if ( logger != 0 && logger->isFatalEnabled()) {\
	logger->fatal( oss, __FILE__, __LINE__); } throw std::runtime_error ( oss.str() ); }
#endif // BT_LOG_FATAL_THROW

#ifndef BT_LOG_TRACE
#define BT_LOG_TRACE(logger, message) { \
	if ( logger != 0 && logger->isDebugEnabled()) {\
	StringStream oss; \
	oss << message; \
	logger->debug( oss, __FILE__, __LINE__); }}
#endif // BT_LOG_TRACE

#ifndef BT_LOG_TRACE_RETURN
#define BT_LOG_TRACE_RETURN(logger, message, ret ) { \
	if ( logger != 0 && logger->isDebugEnabled()) {\
	StringStream oss; \
	oss << message; \
	logger->debug( oss, __FILE__, __LINE__); } return ( ret );}
#endif // BT_LOG_TRACE_RETURN

#ifndef BT_LOG_TRACE_THROW
#define BT_LOG_TRACE_THROW(logger, message ) { \
	StringStream oss; \
	oss << message; \
	if ( logger != 0 && logger->isDebugEnabled()) {\
	logger->debug( oss, __FILE__, __LINE__); } throw std::runtime_error ( oss.str() ); }
#endif // BT_LOG_TRACE_THROW

#ifndef BT_ASSERT
#define BT_ASSERT(logger,assertion, message) { \
	if ( logger != 0 ) {\
	StringStream oss; \
	oss << message; \
	logger->assertLog( assertion ,oss, __FILE__, __LINE__); }}

#endif // BT_ASSERT

#else	// _NO_BT_LOG_

#ifndef BT_NDC
#define BT_NDC( logger, ndc , msg )				{}
#endif // BT_NDC

#ifndef BT_LOG
#define BT_LOG(logger, level, message)			{}
#endif // BT_LOG

#ifndef BT_LOG_DEBUG
#define BT_LOG_DEBUG(logger, message)			{}
#endif // BT_LOG_DEBUG

#ifndef BT_LOG_INFO
#define BT_LOG_INFO(logger, message)			{}
#endif // BT_LOG_INFO

#ifndef BT_LOG_WARN
#define BT_LOG_WARN(logger, message)			{}
#endif // BT_LOG_WARN

#ifndef BT_LOG_ERROR
#define BT_LOG_ERROR(logger, message)			{}
#endif // BT_LOG_ERROR

#ifndef BT_LOG_FATAL
#define BT_LOG_FATAL(logger, message)			{}
#endif // BT_LOG_FATAL

#ifndef BT_LOG_TRACE
#define BT_LOG_TRACE(logger, message)			{}
#endif // BT_LOG_TRACE

#ifndef BT_ASSERT
#define BT_ASSERT(logger,assertion, message)	{}
#endif // BT_ASSERT

#ifndef BT_LOG_RETURN
#define BT_LOG_RETURN(logger, level, message, ret )			return ( ret );
#endif // BT_LOG_RETURN

#ifndef BT_LOG_DEBUG_RETURN
#define BT_LOG_DEBUG_RETURN(logger, message, ret )			return ( ret );
#endif // BT_LOG_DEBUG_RETURN

#ifndef BT_LOG_INFO_RETURN
#define BT_LOG_INFO_RETURN(logger, message, ret )			return ( ret );
#endif // BT_LOG_INFO_RETURN

#ifndef BT_LOG_WARN_RETURN
#define BT_LOG_WARN_RETURN(logger, message, ret )			return ( ret );
#endif // BT_LOG_WARN_RETURN

#ifndef BT_LOG_ERROR_RETURN
#define BT_LOG_ERROR_RETURN(logger, message, ret )			return ( ret );
#endif // BT_LOG_ERROR_RETURN

#ifndef BT_LOG_FATAL_RETURN
#define BT_LOG_FATAL_RETURN(logger, message, ret )			return ( ret );
#endif // BT_LOG_FATAL_RETURN

#ifndef BT_LOG_TRACE_RETURN
#define BT_LOG_TRACE_RETURN(logger, message, ret )			return ( ret );
#endif // BT_LOG_TRACE_RETURN


#ifndef BT_LOG_THROW
#define BT_LOG_THROW(logger, level, message )			{ \
	StringStream oss; \
	oss << message; \
	throw std::runtime_error( oss.str() );\
}

#endif // BT_LOG_THROW

#ifndef BT_LOG_DEBUG_THROW
#define BT_LOG_DEBUG_THROW(logger, message, ret )		{ \
	StringStream oss; \
	oss << message; \
	throw std::runtime_error( oss.str() );\
}

#endif // BT_LOG_DEBUG_THROW

#ifndef BT_LOG_INFO_THROW
#define BT_LOG_INFO_THROW(logger, message, ret )		{ \
	StringStream oss; \
	oss << message; \
	throw std::runtime_error( oss.str() );\
}
#endif // BT_LOG_INFO_THROW

#ifndef BT_LOG_WARN_THROW
#define BT_LOG_WARN_THROW(logger, message, ret )		{ \
	StringStream oss; \
	oss << message; \
	throw std::runtime_error( oss.str() );\
}
#endif // BT_LOG_WARN_THROW

#ifndef BT_LOG_ERROR_THROW
#define BT_LOG_ERROR_THROW(logger, message, ret )		{ \
	StringStream oss; \
	oss << message; \
	throw std::runtime_error( oss.str() );\
}
#endif // BT_LOG_ERROR_THROW

#ifndef BT_LOG_FATAL_THROW
#define BT_LOG_FATAL_THROW(logger, message, ret )		{ \
	StringStream oss; \
	oss << message; \
	throw std::runtime_error( oss.str() );\
}
#endif // BT_LOG_FATAL_THROW

#ifndef BT_LOG_TRACE_THROW
#define BT_LOG_TRACE_THROW(logger, message, ret )		{ \
	StringStream oss; \
	oss << message; \
	throw std::runtime_error( oss.str() );\
}
#endif // BT_LOG_TRACE_THROW

#endif // _NO_BT_LOG_

#endif // _BOE_Log_H_