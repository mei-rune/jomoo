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

/** @Brief CtrlCHandler 提供了一个可移植的处理 CTRL+C 和类似于CTRL+C 信号的方法
 * <p>在 Unix/POSIX上, 它处理 SIGHUP, SIGINT 和 SIGTERM. 
 * 在 Windows上, 它本质上是一个SetConsoleCtrlHandler的包装类
 * 在一个进程中，同一时刻仅有一个CtrlCHandler实例存在，如果你企图生成第二个
 * CtrlCHandler时，会发生一个 CtrlCHandlerException 异常。
 * 在Unix/POSIX上, 它必须在创建任何线程之前创建，CtrlCHandler 构造器函数据会设置
 * SIGHUP, SIGINT 和 SIGTERM; 缺省情况下, 以后创建的线程将继承它。
 * 当一个CTRL+C 和类似于CTRL+C 信号发生，用户注册的回调函数将在一个单独的线程中
 * 被调用。回调函数据必须不能引发异常。
 * 在 CtrCHandler 析构时，会注销回调函数据，可是在Unix/POSIX上，它用不会恢复老的
 * 信号掩码(mask),所以 SIGHUP, SIGINT 和 SIGTERM 会被忽略，在Windows上可能也会如
 * 止。<p>
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
