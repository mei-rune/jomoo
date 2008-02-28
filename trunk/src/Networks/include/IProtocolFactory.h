
#ifndef PROTOCOLFACTORY_H
#define PROTOCOLFACTORY_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_Networks.h"
#include "ITransport.h"

_networks_begin

    /// <summary>
    /// Interface for protocol factories.
    /// </summary>
    class IProtocolFactory
    {
	public:

		virtual ~IProtocolFactory(){};

        virtual IDictionary<string, string> getMisc() = 0;

        virtual IProtocol* buildProtocol(ITransport* transport) = 0;

        void releaseProtocol(IProtocol* protocol);
    };

_networks_end

#endif
