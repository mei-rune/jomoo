using System;
using System.Collections.Generic;
using System.Text;
using System.Net;

namespace Betanetworks.Commons
{
    using Betanetworks.Commons.Threading;

    public interface IReactorCore : IReactorArbitrary, ICompletionPort
    {        
        /// <summary>
        /// �ڲ������쳣ʱ����
        /// </summary>
        event ThrowError OnException;

        /// <summary>
        /// ��ʼ����ֱ������Interrupt�ŷ���
        /// </summary>
        void Run();

        /// <summary>
        /// ֹͣ����
        /// </summary>
        void Interrupt();

        /// <summary>
        /// ������󶨵����˿�
        /// </summary>
        /// <param name="systemHandler"></param>
        void Bind(ISystemHandle systemHandler);

        /// <summary>
        /// ���м����Ķ˿�
        /// </summary>
        IAcceptor[] ListeningPorts { get; }

        /// <summary>
        /// ���һ���˿�
        /// </summary>
        /// <returns>����port</returns>
        /// <exception cref="ArgumentNullException" />
        /// <exception cref="RuntimeError" />
        IAcceptor AddListeningPort(IAcceptor port);

        /// <summary>
        /// ɾ��һ���˿�
        /// </summary>
        /// <returns>�ҵ���ɾ������true,���򷵻�false</returns>
        bool RemoveListeningPort(Endpoint port);

        /// <summary>
        /// ����IListeningPort
        /// </summary>
        IAcceptor FindListeningPort(Endpoint port);

        void SendError(Exception error);
    }
}
