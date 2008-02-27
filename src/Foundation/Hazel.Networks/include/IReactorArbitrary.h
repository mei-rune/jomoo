using System;
using System.Collections.Generic;
using System.Text;

namespace Betanetworks.Commons
{
    public interface IReactorArbitrary : IServiceProvider
    {
        IConnector ConnectWith(Endpoint endPoint);

        IConnector ConnectWith(Endpoint endPoint
            , IDictionary<string, object> kw);

        IAcceptor ListenWith(Endpoint endPoint
            , IProtocolFactory protocolFactory);
    }
}
