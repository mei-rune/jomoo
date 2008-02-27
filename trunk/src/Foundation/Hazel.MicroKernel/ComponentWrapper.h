
#ifndef SEAL_KERNEL_COMPONENT_WRAPPER_H
#define SEAL_KERNEL_COMPONENT_WRAPPER_H 1

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_MicroKernel.h"
# include "IKernel.h"

_micro_kernel_begin

  template <class I>
    class ComponentWrapper : public IComponent
    {
      public:
        //DECLARE_SEAL_COMPONENT( );

      public:
        ComponentWrapper( I* i, IKernel* c, const IKernel::key_type& key )
          : Component( c, key ), m_wrapped( i )
        {
        }

        virtual ~ComponentWrapper()
        {
        }

        operator I*()
        {
          return m_wrapped;
        }

      private:
        I* m_wrapped;
    };

_micro_kernel_end
  
#endif // SEAL_KERNEL_COMPONENT_WRAPPER_H
