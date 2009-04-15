
#ifndef _transport_h_
#define _transport_h_

#include "config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
# include "buffer.h"
# include "endpoint.h"
# include "exception.hpp"

_jingxian_begin

    enum SystemEvent
    {
        CtrlC = 0,
        CtrlBreak = 1,
        CtrlClose = 2,
        CtrlLogoff = 5,
        CtrlShutdown = 6
    }

    //public interface ICommunicatingWalker
    //{
    //    void OnBeginWalk(ICommunicator reactorCore);
    //    void OnEndWalk(ICommunicator reactorCore);

    //    void OnBeginWalk(IReactorCore reactorCore);
    //    void OnEndWalk(IReactorCore reactorCore);

    //    void OnSession(IReactorCore reactorCore, ISession session);
    //    void OnListenPort(IReactorCore reactorCore, IAcceptor listeningPort);
    //}

    class communicator : public concurrent_port
    {
	public:

        /// <summary>
        /// 开始运行直到调用Interrupt才返回
        /// </summary>
        void runForever();

        /// <summary>
        /// 停止运行
        /// </summary>
        void interrupt();

        /// <summary>
        /// 引发一个异常事件
        /// </summary>
        void send(const Exception& e);

        /// <summary>
        /// 引发一个系统事件
        /// </summary>
        void send(const SystemEvent& e);
    }


_jingxian_end
