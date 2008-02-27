// **********************************************************************
//
// Copyright (c) 2003-2005 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef UTIL_CTRL_C_HANDLER_H
#define UTIL_CTRL_C_HANDLER_H

#include <config.h>

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
#include "config_Util.h"
#include <stdexcept>


_util_begin

/** @Brief CtrlCHandler �ṩ��һ������ֲ�Ĵ��� CTRL+C ��������CTRL+C �źŵķ���
 * <p>�� Unix/POSIX��, ������ SIGHUP, SIGINT �� SIGTERM. 
 * �� Windows��, ����������һ��SetConsoleCtrlHandler�İ�װ��
 * ��һ�������У�ͬһʱ�̽���һ��CtrlCHandlerʵ�����ڣ��������ͼ���ɵڶ���
 * CtrlCHandlerʱ���ᷢ��һ�� CtrlCHandlerException �쳣��
 * ��Unix/POSIX��, �������ڴ����κ��߳�֮ǰ������CtrlCHandler �����������ݻ�����
 * SIGHUP, SIGINT �� SIGTERM; ȱʡ�����, �Ժ󴴽����߳̽��̳�����
 * ��һ��CTRL+C ��������CTRL+C �źŷ������û�ע��Ļص���������һ���������߳���
 * �����á��ص������ݱ��벻�������쳣��
 * �� CtrCHandler ����ʱ����ע���ص������ݣ�������Unix/POSIX�ϣ����ò���ָ��ϵ�
 * �ź�����(mask),���� SIGHUP, SIGINT �� SIGTERM �ᱻ���ԣ���Windows�Ͽ���Ҳ����
 * ֹ��<p>
 */

typedef void (*CtrlCHandlerCallback)(int);

class CtrlCHandler
{
public:

    CtrlCHandler( CtrlCHandlerCallback = 0);
    ~CtrlCHandler();

    void setCallback(CtrlCHandlerCallback);
    CtrlCHandlerCallback getCallback() const;

	static CtrlCHandler* get( );
};


class CtrlCHandlerException : public std::runtime_error
{ 
public:

	CtrlCHandlerException(const std::string& s ) 
		:  std::runtime_error( s )
	  {
	  }
};

_util_end

#endif
