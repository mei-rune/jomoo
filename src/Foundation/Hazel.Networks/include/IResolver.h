using System;
using System.Collections.Generic;
using System.Text;
using System.Net;

namespace Betanetworks.Commons
{
    using Betanetworks.Commons.Threading;

    public delegate void ResolveHost<T>(string name, IPAddress[] addr, T context);
    public delegate void ResolveError<T>(string name, T context);

    public interface IDNSResolver
    {
        void ResolveHostByName<T>(string name, T context, ResolveHost<T> callback, ResolveError<T> onError, TimeSpan timeout);
        void ResolveHostByName<T>(string name, T context, ResolveHost<T> callback, ResolveError<T> onError);
    }
}
