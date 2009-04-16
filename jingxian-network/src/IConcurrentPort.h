
#ifndef _IConcurrentPort_H_
#define _IConcurrentPort_H_

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

	/**
	* 取得地址的描述
	*/
	virtual const tstring& toString() const = 0;
};

inline tostream& operator<<( tostream& target, const IConcurrentPort& concurrentPort )
{
	target << concurrentPort.toString();
	return target;
}

_jingxian_end

#endif // _IConcurrentPort_H_
