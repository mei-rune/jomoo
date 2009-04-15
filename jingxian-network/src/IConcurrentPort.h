
#ifndef _COMPLETIONPORT_H_
#define _COMPLETIONPORT_H_

#include "config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files

_jingxian_begin

/**
 * 方法接口
 */
class runnable
{
public:
	virtual ~runnable() {}

	virtual void run() = 0;
};

/**
 * 线程接口
 */
class IConcurrentPort
{
public:

	virtual ~IConcurrentPort() {}

    /**
     * 将执行方法发送到线程等待队列,稍后执行
     *
     * @param[ in ] run 执行方法
	 */
    virtual void send( runnable* run ) = 0;
};

_jingxian_end

#endif // _COMPLETIONPORT_H_
