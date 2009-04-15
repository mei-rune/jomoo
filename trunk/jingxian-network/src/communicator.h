
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
        /// ��ʼ����ֱ������Interrupt�ŷ���
        /// </summary>
        void runForever();

        /// <summary>
        /// ֹͣ����
        /// </summary>
        void interrupt();

        /// <summary>
        /// ����һ���쳣�¼�
        /// </summary>
        void send(const Exception& e);

        /// <summary>
        /// ����һ��ϵͳ�¼�
        /// </summary>
        void send(const SystemEvent& e);
    }


_jingxian_end
