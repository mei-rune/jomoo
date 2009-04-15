
#ifndef _jingxian_tracer_h_
#define _jingxian_tracer_h_

#include "config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

#include "string.hpp"
#include "buffer.h"

_jingxian_begin

namespace logging
{
    enum TransportWay
    {
        Receive,

        Send,

        Both
    };
}

class tracer 
{
public:
	/**
	 * virtual tracer destructor
	 */
	virtual ~tracer(){};

	/**
	 * 
	 */
    virtual void WriteInboundBuffer(const Buffer& buffer) = 0;
    
	/**
	 *
	 */
	virtual void WriteOutboundBuffer(const Buffer& buffer) = 0;

	/**
	 * debug级的日志是否可以记日志
	 * @return 可以true,不可以false
	 */
	virtual bool isDebugEnabled() const = 0;

	/**
	 * 记录debug级的日志
	 * @param[ in ] way 流传输的方向
	 * @param[ in ] message 日志内容
	 * @param[ in ] file 日志记录的源文件名
	 * @param[ in ] line 日志记录的源文件的当前行
	 */
	virtual void debug(logging::TransportWay way, const StringStream& message, const char* file=0, int line=-1);
	
	/**
	 * error级的日志是否可以记日志
	 * @return 可以true,不可以false
	 */
	virtual bool isErrorEnabled() const = 0;

	/**
	 * 记录error级的日志
	 * @param[ in ] way 流传输的方向
	 * @param[ in ] message 日志内容
	 * @param[ in ] file 日志记录的源文件名
	 * @param[ in ] line 日志记录的源文件的当前行
	 */
    virtual void error(logging::TransportWay way, const StringStream& message, const char* file=0, int line=-1);
	
	/**
	 * fatal级的日志是否可以记日志
	 * @return 可以true,不可以false
	 */
	virtual bool isFatalEnabled() const = 0;

	/**
	 * 记录fatal级的日志
	 * @param[ in ] way 流传输的方向
	 * @param[ in ] message 日志内容
	 * @param[ in ] file 日志记录的源文件名
	 * @param[ in ] line 日志记录的源文件的当前行
	 */
    virtual void fatal(logging::TransportWay way, const StringStream& message, const char* file=0, int line=-1);

	/**
	 * info级的日志是否可以记日志
	 * @return 可以true,不可以false
	 */
	virtual bool isInfoEnabled() const = 0;

	/**
	 * 记录info级的日志
	 * @param[ in ] way 流传输的方向
	 * @param[ in ] message 日志内容
	 * @param[ in ] file 日志记录的源文件名
	 * @param[ in ] line 日志记录的源文件的当前行
	 */
    virtual void info(logging::TransportWay way, const StringStream& message, const char* file=0, int line=-1);
	
	/**
	 * warn级的日志是否可以记日志
	 * @return 可以true,不可以false
	 */
	virtual bool isWarnEnabled() const = 0;

	/**
	 * 记录warn级的日志
	 * @param[ in ] way 流传输的方向
	 * @param[ in ] message 日志内容
	 * @param[ in ] file 日志记录的源文件名
	 * @param[ in ] line 日志记录的源文件的当前行
	 */
    virtual void warn(logging::TransportWay way, const StringStream& message, const char* file=0, int line=-1);

	
	/**
	 * Trace级的日志是否可以记日志
	 * @return 可以true,不可以false
	 */
	virtual bool isTraceEnabled() const = 0;

	/**
	 * 记录trace级的日志
	 * @param[ in ] way 流传输的方向
	 * @param[ in ] message 日志内容
	 * @param[ in ] file 日志记录的源文件名
	 * @param[ in ] line 日志记录的源文件的当前行
	 */
    virtual void trace(logging::TransportWay way, const StringStream& message, const char* file=0, int line=-1);
};

_jingxian_end

#endif // _JOMOO_Log_H_
