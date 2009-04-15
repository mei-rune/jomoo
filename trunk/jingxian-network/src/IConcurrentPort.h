
#ifndef _COMPLETIONPORT_H_
#define _COMPLETIONPORT_H_

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
};

_jingxian_end

#endif // _COMPLETIONPORT_H_
