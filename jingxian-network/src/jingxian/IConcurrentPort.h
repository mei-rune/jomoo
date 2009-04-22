
#ifndef _IConcurrentPort_H_
#define _IConcurrentPort_H_

#include "jingxian/config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
# include "jingxian/string/string.hpp"

_jingxian_begin

/**
 * 方法接口
 */
class IRunnable
{
public:
	virtual ~IRunnable() {}

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
     * @param[ in ] runnable 执行方法
	 */
    virtual bool send( IRunnable* runnable ) = 0;

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
