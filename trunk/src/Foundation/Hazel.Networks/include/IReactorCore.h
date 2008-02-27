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
        /// 内部发生异常时触发
        /// </summary>
        event ThrowError OnException;

        /// <summary>
        /// 开始运行直到调用Interrupt才返回
        /// </summary>
        void Run();

        /// <summary>
        /// 停止运行
        /// </summary>
        void Interrupt();

        /// <summary>
        /// 将句柄绑定到本端口
        /// </summary>
        /// <param name="systemHandler"></param>
        void Bind(ISystemHandle systemHandler);

        /// <summary>
        /// 所有监听的端口
        /// </summary>
        IAcceptor[] ListeningPorts { get; }

        /// <summary>
        /// 添加一个端口
        /// </summary>
        /// <returns>返回port</returns>
        /// <exception cref="ArgumentNullException" />
        /// <exception cref="RuntimeError" />
        IAcceptor AddListeningPort(IAcceptor port);

        /// <summary>
        /// 删除一个端口
        /// </summary>
        /// <returns>找到并删除返回true,否则返回false</returns>
        bool RemoveListeningPort(Endpoint port);

        /// <summary>
        /// 查找IListeningPort
        /// </summary>
        IAcceptor FindListeningPort(Endpoint port);

        void SendError(Exception error);
    }
}
