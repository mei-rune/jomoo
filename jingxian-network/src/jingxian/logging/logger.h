
#ifndef _jingxian_log_h_
#define _jingxian_log_h_

#include "jingxian/config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
# include <assert.h>
# include "jingxian/string/string.hpp"
# include "jingxian/jingxian_export.h"

_jingxian_begin

/**
 * @Brief ILogger 日志接口
 * 这是BT的日志接口，每一个具体的日志都必须从它继承，每一个需要记日志的都可以得到一个这样的接，
 * 但不推荐直接使用它。有一组预定义好的宏，请使用宏
 */
class logger
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
	 * virtual JOMOO_Log_Impl destructor
	 */
	virtual ~logger(){};

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
	 * 记录trace级的日志
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

class ndc
{
public:
	virtual ~ndc(){}
	virtual void pushNDC( const tchar* str ) = 0;
	virtual void popNDC( ) = 0;
};

_jingxian_end

#ifndef _NO_LOG_



#ifndef LOG
#define LOG(logger, level, message) { \
	if ( logger != 0 && logger->isEnabledFor(level)) {\
	StringStream oss; \
	oss << message; \
	logger->fatal(level, oss, __FILE__, __LINE__); }}
#endif // LOG

#ifndef LOG_RETURN
#define LOG_RETURN(logger, level, message,ret) { \
	StringStream oss; \
	oss << message; \
	if ( logger != 0 && logger->isEnabledFor(level)) {\
	logger->fatal(level, oss, __FILE__, __LINE__); } return ( ret );}
#endif // LOG_RETURN

#ifndef LOG_THROW
#define LOG_THROW(logger, level, message ,e ) { \
	StringStream oss; \
	oss << message; \
	if ( logger != 0 && logger->isEnabledFor(level)) {\
	logger->fatal(level, oss, __FILE__, __LINE__); } throw e( __FILE__,__LINE__,  oss.str() );}
#endif // LOG_THROW

#ifndef DEBUG
#define DEBUG(logger, message) { \
	if ( logger != 0 && logger->isDebugEnabled()) {\
	StringStream oss; \
	oss << message; \
	logger->debug( oss, __FILE__, __LINE__); }}
#endif // DEBUG

#ifndef DEBUG_RETURN
#define DEBUG_RETURN(logger, message, ret ) { \
	if ( logger != 0 && logger->isDebugEnabled()) {\
	StringStream oss; \
	oss << message; \
	logger->debug( oss, __FILE__, __LINE__); } return ( ret );}
#endif // DEBUG_RETURN

#ifndef DEBUG_THROW
#define DEBUG_THROW(logger, message ,e) { \
	StringStream oss; \
	oss << message; \
	if ( logger != 0 && logger->isDebugEnabled()) {\
	logger->debug( oss, __FILE__, __LINE__); } throw e( __FILE__,__LINE__, oss.str() ); }
#endif // DEBUG_THROW

#ifndef DEBUG_THROW2
#define DEBUG_THROW2(logger, m1,m2,e ) { \
	StringStream oss; \
	oss << m2; \
	if ( logger != 0 && logger->isDebugEnabled()) {\
	logger->debug( oss, __FILE__, __LINE__); } throw e( __FILE__,__LINE__, m1,oss.str() ); }
#endif // DEBUG_THROW2

#ifndef DEBUG_THROW3
#define DEBUG_THROW3(logger, m1,m2,m3,e ) { \
	StringStream oss; \
	oss << m3; \
	if ( logger != 0 && logger->isDebugEnabled()) {\
	logger->debug( oss, __FILE__, __LINE__); } throw e( __FILE__,__LINE__, m1,m2,oss.str() ); }
#endif // DEBUG_THROW3

#ifndef DEBUG_THROW4
#define DEBUG_THROW4(logger, m1,m2,m3,m4,e ) { \
	StringStream oss; \
	oss << m4; \
	if ( logger != 0 && logger->isDebugEnabled()) {\
	logger->debug( oss, __FILE__, __LINE__); } throw e( __FILE__,__LINE__, m1,m2,m3,oss.str() ); }
#endif // DEBUG_THROW3

#ifndef INFO
#define INFO(logger, message) { \
	if ( logger != 0 && logger->isInfoEnabled()) {\
	StringStream oss; \
	oss << message; \
	logger->info( oss, __FILE__, __LINE__); }}
#endif // INFO

#ifndef INFO_RETURN
#define INFO_RETURN(logger, message, ret ) { \
	if ( logger != 0 && logger->isInfoEnabled()) {\
	StringStream oss; \
	oss << message; \
	logger->info( oss, __FILE__, __LINE__); } return ( ret ); }
#endif // INFO_RETURN

#ifndef INFO_THROW
#define INFO_THROW(logger, message ,e ) { \
	StringStream oss; \
	oss << message; \
	if ( logger != 0 && logger->isInfoEnabled()) {\
	logger->info( oss, __FILE__, __LINE__); } throw e( __FILE__,__LINE__,  oss.str() ); }
#endif // INFO_THROW

#ifndef INFO_THROW2
#define INFO_THROW2(logger, m1,m2,e ) { \
	StringStream oss; \
	oss << m2; \
	if ( logger != 0 && logger->isInfoEnabled()) {\
	logger->info( oss, __FILE__, __LINE__); } throw e( __FILE__,__LINE__, m1,oss.str() ); }
#endif // INFO_THROW2

#ifndef INFO_THROW3
#define INFO_THROW3(logger, m1,m2,m3,e ) { \
	StringStream oss; \
	oss << m3; \
	if ( logger != 0 && logger->isInfoEnabled()) {\
	logger->info( oss, __FILE__, __LINE__); } throw e( __FILE__,__LINE__, m1,m2,oss.str() ); }
#endif // INFO_THROW3

#ifndef INFO_THROW4
#define INFO_THROW4(logger, m1,m2,m3,m4,e ) { \
	StringStream oss; \
	oss << m4; \
	if ( logger != 0 && logger->isInfoEnabled()) {\
	logger->info( oss, __FILE__, __LINE__); } throw e( __FILE__,__LINE__, m1,m2,m3,oss.str() ); }
#endif // INFO_THROW3

#ifndef WARN
#define WARN(logger, message ) { \
	if ( logger != 0 && logger->isWarnEnabled()) {\
	StringStream oss; \
	oss << message; \
	logger->warn( oss, __FILE__, __LINE__); }}
#endif // WARN

#ifndef WARN_RETURN
#define WARN_RETURN(logger, message, ret ) { \
	if ( logger != 0 && logger->isWarnEnabled()) {\
	StringStream oss; \
	oss << message; \
	logger->warn( oss, __FILE__, __LINE__); } return ( ret ); }
#endif // WARN_RETURN

#ifndef WARN_THROW
#define WARN_THROW(logger, message ,r ) { \
	StringStream oss; \
	oss << message; \
	if ( logger != 0 && logger->isWarnEnabled()) {\
	logger->warn( oss, __FILE__, __LINE__); } throw e( __FILE__,__LINE__, oss.str() ); }
#endif // WARN_THROW

#ifndef WARN_THROW2
#define WARN_THROW2(logger, m1,m2,e ) { \
	StringStream oss; \
	oss << m2; \
	if ( logger != 0 && logger->isWarnEnabled()) {\
	logger->warn( oss, __FILE__, __LINE__); } throw e( __FILE__,__LINE__, m1,oss.str() ); }
#endif // WARN_THROW2

#ifndef WARN_THROW3
#define WARN_THROW3(logger, m1,m2,m3,e ) { \
	StringStream oss; \
	oss << m3; \
	if ( logger != 0 && logger->isWarnEnabled()) {\
	logger->warn( oss, __FILE__, __LINE__); } throw e( __FILE__,__LINE__, m1,m2,oss.str() ); }
#endif // WARN_THROW3

#ifndef WARN_THROW4
#define WARN_THROW4(logger, m1,m2,m3,m4,e ) { \
	StringStream oss; \
	oss << m4; \
	if ( logger != 0 && logger->isWarnEnabled()) {\
	logger->warn( oss, __FILE__, __LINE__); } throw e( __FILE__,__LINE__, m1,m2,m3,oss.str(); }
#endif // WARN_THROW3

#ifndef ERROR
#define ERROR(logger, message) { \
	if ( logger != 0 && logger->isErrorEnabled()) {\
	StringStream oss; \
	oss << message; \
	logger->error( oss, __FILE__, __LINE__); }}
#endif // ERROR

#ifndef ERROR_RETURN
#define ERROR_RETURN(logger, message, ret ) { \
	if ( logger != 0 && logger->isErrorEnabled()) {\
	StringStream oss; \
	oss << message; \
	logger->error( oss, __FILE__, __LINE__); } return ( ret );}
#endif // ERROR_RETURN

#ifndef ERROR_THROW
#define ERROR_THROW(logger, message ,e ) { \
	StringStream oss; \
	oss << message; \
	if ( logger != 0 && logger->isErrorEnabled()) {\
	logger->error( oss, __FILE__, __LINE__); } throw e( __FILE__,__LINE__, oss.str() ); }
#endif // ERROR_THROW

#ifndef ERROR_THROW2
#define ERROR_THROW2(logger, m1,m2,e ) { \
	StringStream oss; \
	oss << m2; \
	if ( logger != 0 && logger->isErrorEnabled()) {\
	logger->error( oss, __FILE__, __LINE__); } throw e( __FILE__,__LINE__, m1,oss.str() ); }
#endif // ERROR_THROW2

#ifndef ERROR_THROW3
#define ERROR_THROW3(logger, m1,m2,m3,e ) { \
	StringStream oss; \
	oss << m3; \
	if ( logger != 0 && logger->isErrorEnabled()) {\
	logger->error( oss, __FILE__, __LINE__); } throw e( __FILE__,__LINE__, m1,m2,oss.str() ); }
#endif // ERROR_THROW3

#ifndef ERROR_THROW4
#define ERROR_THROW4(logger, m1,m2,m3,m4,e ) { \
	StringStream oss; \
	oss << m4; \
	if ( logger != 0 && logger->isErrorEnabled()) {\
	logger->error( oss, __FILE__, __LINE__); } throw e( __FILE__,__LINE__, m1,m2,m3,oss.str(); }
#endif // ERROR_THROW3


#ifndef FATAL
#define FATAL(logger, message) { \
	if ( logger != 0 && logger->isFatalEnabled()) {\
	StringStream oss; \
	oss << message; \
	logger->fatal( oss, __FILE__, __LINE__); }}
#endif // FATAL

#ifndef FATAL_RETURN
#define FATAL_RETURN(logger, message, ret ) { \
	if ( logger != 0 && logger->isFatalEnabled()) {\
	StringStream oss; \
	oss << message; \
	logger->fatal( oss, __FILE__, __LINE__); } return ( ret );}
#endif // FATAL_RETURN

#ifndef FATAL_THROW
#define FATAL_THROW(logger, message ,e ) { \
	StringStream oss; \
	oss << message; \
	if ( logger != 0 && logger->isFatalEnabled()) {\
	logger->fatal( oss, __FILE__, __LINE__); } throw e( __FILE__,__LINE__, message ); }
#endif // FATAL_THROW

#ifndef FATAL_THROW2
#define FATAL_THROW2(logger, m1,m2,e ) { \
	StringStream oss; \
	oss << m2; \
	if ( logger != 0 && logger->isFatalEnabled()) {\
	logger->fatal( oss, __FILE__, __LINE__); } throw e( __FILE__,__LINE__, m1,oss.str() ); }
#endif // FATAL_THROW2

#ifndef FATAL_THROW3
#define FATAL_THROW3(logger, m1,m2,m3,e ) { \
	StringStream oss; \
	oss << m3; \
	if ( logger != 0 && logger->isFatalEnabled()) {\
	logger->fatal( oss, __FILE__, __LINE__); } throw e( __FILE__,__LINE__, m1,m2,oss.str() ); }
#endif // FATAL_THROW3


#ifndef FATAL_THROW4
#define FATAL_THROW4(logger, m1,m2,m3,m4,e ) { \
	StringStream oss; \
	oss << m4; \
	if ( logger != 0 && logger->isFatalEnabled()) {\
	logger->fatal( oss, __FILE__, __LINE__); } throw e( __FILE__,__LINE__, m1,m2,m3,oss.str() ); }
#endif // FATAL_THROW3

#ifndef TRACE
#define TRACE(logger, message) { \
	if ( logger != 0 && logger->isDebugEnabled()) {\
	StringStream oss; \
	oss << message; \
	logger->debug( oss, __FILE__, __LINE__); }}
#endif // TRACE

#ifndef TRACE_RETURN
#define TRACE_RETURN(logger, message, ret ) { \
	if ( logger != 0 && logger->isDebugEnabled()) {\
	StringStream oss; \
	oss << message; \
	logger->debug( oss, __FILE__, __LINE__); } return ( ret );}
#endif // TRACE_RETURN

#ifndef TRACE_THROW
#define TRACE_THROW(logger, message , e ) { \
	StringStream oss; \
	oss << message; \
	if ( logger != 0 && logger->isDebugEnabled()) {\
	logger->debug( oss, __FILE__, __LINE__); } throw e( __FILE__,__LINE__,  oss.str() ); }
#endif // TRACE_THROW

#ifndef TRACE_THROW2
#define TRACE_THROW2(logger, m1,m2,e ) { \
	StringStream oss; \
	oss << m2; \
	if ( logger != 0 && logger->isDebugEnabled()) {\
	logger->debug( oss, __FILE__, __LINE__); } throw e( __FILE__,__LINE__, m1,oss.str() ); }
#endif // TRACE_THROW2

#ifndef TRACE_THROW3
#define TRACE_THROW3(logger, m1,m2,m3,e ) { \
	StringStream oss; \
	oss << m3; \
	if ( logger != 0 && logger->isDebugEnabled()) {\
	logger->debug( oss, __FILE__, __LINE__); } throw e( __FILE__,__LINE__, m1,m2,oss.str() ); }
#endif // TRACE_THROW3

#ifndef TRACE_THROW4
#define TRACE_THROW4(logger, m1,m2,m3,m4,e ) { \
	StringStream oss; \
	oss << m4; \
	if ( logger != 0 && logger->isDebugEnabled()) {\
	logger->debug( oss, __FILE__, __LINE__); } throw e( __FILE__,__LINE__, m1,m2,m3,oss.str(); }
#endif // TRACE_THROW3

#ifndef LOG_ASSERT
#define LOG_ASSERT( logger,assertion ) { \
	if ( logger != 0 ) {\
	StringStream oss;											\
	logger->assertLog( assertion ,oss, __FILE__, __LINE__); 	\
	}															\
	else														\
	{															\
	(void)( (!!(assertion)) || (_wassert(_CRT_WIDE(#assertion), _CRT_WIDE(__FILE__), __LINE__), 0) );\
	} }

#endif // LOG_ASSERT

#else	// _NO_LOG_

#ifndef BT_NDC
#define BT_NDC( logger, ndc , msg )				{}
#endif // BT_NDC

#ifndef LOG
#define LOG(logger, level, message)			{}
#endif // LOG

#ifndef DEBUG
#define DEBUG(logger, message)			{}
#endif // DEBUG

#ifndef INFO
#define INFO(logger, message)			{}
#endif // INFO

#ifndef WARN
#define WARN(logger, message)			{}
#endif // WARN

#ifndef ERROR
#define ERROR(logger, message)			{}
#endif // ERROR

#ifndef FATAL
#define FATAL(logger, message)			{}
#endif // FATAL

#ifndef TRACE
#define TRACE(logger, message)			{}
#endif // TRACE

#ifndef LOG_ASSERT
#define LOG_ASSERT(logger,assertion )			{}
#endif // LOG_ASSERT

#ifndef LOG_RETURN
#define LOG_RETURN(logger, level, message, ret )			return ( ret );
#endif // LOG_RETURN

#ifndef DEBUG_RETURN
#define DEBUG_RETURN(logger, message, ret )			return ( ret );
#endif // DEBUG_RETURN

#ifndef INFO_RETURN
#define INFO_RETURN(logger, message, ret )			return ( ret );
#endif // INFO_RETURN

#ifndef WARN_RETURN
#define WARN_RETURN(logger, message, ret )			return ( ret );
#endif // WARN_RETURN

#ifndef ERROR_RETURN
#define ERROR_RETURN(logger, message, ret )			return ( ret );
#endif // ERROR_RETURN

#ifndef FATAL_RETURN
#define FATAL_RETURN(logger, message, ret )			return ( ret );
#endif // FATAL_RETURN

#ifndef TRACE_RETURN
#define TRACE_RETURN(logger, message, ret )			return ( ret );
#endif // TRACE_RETURN


#ifndef LOG_THROW
#define LOG_THROW(logger, level, message ,e )			{ \
	throw e( __FILE__,__LINE__,  message );\
}
#endif // LOG_THROW

#ifndef DEBUG_THROW
#define DEBUG_THROW(logger, message, e )		{ \
	StringStream oss; oss << message;throw e( __FILE__,__LINE__, message );\
}
#endif // DEBUG_THROW

#ifndef DEBUG_THROW2
#define DEBUG_THROW2(logger, m1,m2, e )		{ \
	StringStream oss; oss << m2;throw e( __FILE__,__LINE__, m1,oss.str();\
}
#endif // DEBUG_THROW2

#ifndef DEBUG_THROW3
#define DEBUG_THROW3(logger, m1,m2,m3, e )		{ \
	StringStream oss; oss << m3;throw e( __FILE__,__LINE__, m1,m2,oss.str();\
}
#endif // DEBUG_THROW3

#ifndef DEBUG_THROW4
#define DEBUG_THROW4(logger, m1,m2,m3,m4, e )		{ \
	StringStream oss; oss << m4;throw e( __FILE__,__LINE__, m1,m2,m3,oss.str();\
}
#endif // DEBUG_THROW4

#ifndef INFO_THROW
#define INFO_THROW(logger, message, e )		{ \
	StringStream oss; oss << message;throw e( __FILE__,__LINE__, message );\
}
#endif // INFO_THROW

#ifndef INFO_THROW2
#define INFO_THROW2(logger, m1,m2, e )		{ \
	StringStream oss; oss << m2;throw e( __FILE__,__LINE__, m1,oss.str();\
}
#endif // INFO_THROW2

#ifndef INFO_THROW3
#define INFO_THROW3(logger, m1,m2,m3, e )		{ \
	StringStream oss; oss << m3;throw e( __FILE__,__LINE__, m1,m2,oss.str();\
}
#endif // INFO_THROW3

#ifndef INFO_THROW4
#define INFO_THROW4(logger, m1,m2,m3,m4, e )		{ \
	StringStream oss; oss << m4;throw e( __FILE__,__LINE__, m1,m2,m3,oss.str();\
}
#endif // INFO_THROW4

#ifndef WARN_THROW
#define WARN_THROW(logger, message, e )		{ \
	StringStream oss; oss << message;throw e( __FILE__,__LINE__, message );\
}
#endif // WARN_THROW

#ifndef WARN_THROW2
#define WARN_THROW2(logger, m1,m2, e )		{ \
	StringStream oss; oss << m2;throw e( __FILE__,__LINE__, m1,oss.str();\
}
#endif // WARN_THROW2

#ifndef WARN_THROW3
#define WARN_THROW3(logger, m1,m2,m3, e )		{ \
	StringStream oss; oss << m3;throw e( __FILE__,__LINE__, m1,m2,oss.str();\
}
#endif // WARN_THROW3

#ifndef WARN_THROW4
#define WARN_THROW4(logger, m1,m2,m3,m4, e )		{ \
	StringStream oss; oss << m4;throw e( __FILE__,__LINE__, m1,m2,m3,oss.str();\
}
#endif // WARN_THROW4

#ifndef ERROR_THROW
#define ERROR_THROW(logger, message, e )		{ \
	throw e( __FILE__,__LINE__,  message );\
}
#endif // ERROR_THROW

#ifndef FATAL_THROW
#define FATAL_THROW(logger, message, e )		{ \
	StringStream oss; oss << message;throw e( __FILE__,__LINE__, message );\
}
#endif // FATAL_THROW

#ifndef FATAL_THROW2
#define FATAL_THROW2(logger, m1,m2, e )		{ \
	StringStream oss; oss << m2;throw e( __FILE__,__LINE__, m1,oss.str();\
}
#endif // FATAL_THROW2

#ifndef FATAL_THROW3
#define FATAL_THROW3(logger, m1,m2,m3, e )		{ \
	StringStream oss; oss << m3;throw e( __FILE__,__LINE__, m1,m2,oss.str();\
}
#endif // FATAL_THROW3

#ifndef FATAL_THROW4
#define FATAL_THROW4(logger, m1,m2,m3,m4, e )		{ \
	StringStream oss; oss << m4;throw e( __FILE__,__LINE__, m1,m2,m3,oss.str();\
}
#endif // FATAL_THROW4

#ifndef TRACE_THROW
#define TRACE_THROW(logger, message, e )		{ \
	StringStream oss; oss << message;throw e( __FILE__,__LINE__, message );\
}
#endif // TRACE_THROW

#ifndef TRACE_THROW2
#define TRACE_THROW2(logger, m1,m2, e )		{ \
	StringStream oss; oss << m2;throw e( __FILE__,__LINE__, m1,oss.str();\
}
#endif // TRACE_THROW2

#ifndef TRACE_THROW3
#define TRACE_THROW3(logger, m1,m2,m3, e )		{ \
	StringStream oss; oss << m3;throw e( __FILE__,__LINE__, m1,m2,oss.str();\
}
#endif // TRACE_THROW3

#ifndef TRACE_THROW4
#define TRACE_THROW4(logger, m1,m2,m3,m4, e )		{ \
	StringStream oss; oss << m4;throw e( __FILE__,__LINE__, m1,m2,m3,oss.str();\
}
#endif // TRACE_THROW4

#endif // _NO_LOG_

#endif // _JOMOO_Log_H_