
#ifndef _IConcurrentPort_H_
#define _IConcurrentPort_H_

#include "config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files

_jingxian_begin

/**
 * �����ӿ�
 */
class runnable
{
public:
	virtual ~runnable() {}

	virtual void run() = 0;
};

/**
 * �߳̽ӿ�
 */
class IConcurrentPort
{
public:

	virtual ~IConcurrentPort() {}

    /**
     * ��ִ�з������͵��̵߳ȴ�����,�Ժ�ִ��
     *
     * @param[ in ] run ִ�з���
	 */
    virtual void send( runnable* run ) = 0;

	/**
	* ȡ�õ�ַ������
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
