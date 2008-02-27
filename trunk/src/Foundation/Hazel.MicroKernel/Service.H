#ifndef Hazel_SEAL_Service_H
# define Hazel_SEAL_Service_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
#include "config_MicroKernel.h"
#include "ContextKey.h"

_micro_kernel_begin


class IService : public IComponent
{
public:

  virtual ~Service();

};

inline Service::Service (Context* context, ContextKey key)
  : Component (context, key),
    m_localContext (new Context(context))
{
}

inline Service::Service (Context* context, const std::string &key)
  : Component (context, key),
    m_localContext (new Context(context))
{
}

inline Service::~Service()
{
}

inline Context *
Service::localContext (void) const
{
	return m_localContext.get();
}


inline std::string 
Service::name(void) const
{
	return contextKey().label();
}

_micro_kernel_end

#include "Service.inl"

#endif // Hazel_SEAL_Service_H
