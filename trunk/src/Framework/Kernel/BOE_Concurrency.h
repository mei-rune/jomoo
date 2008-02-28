

#ifndef BOE_CONCURRENCY_H
#define BOE_CONCURRENCY_H

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

// Include files
#include "config_Kernel.h"
#include "BOE_Protocol_Handler.h"
#include "BOE/Threading/threading.h"

_kernel_begin

class BOE_Concurrency_Impl 
#ifdef BOE_MT
	: public _thread Runnable 
#endif
{
public:

  virtual ~BOE_Concurrency_Impl (void) {};

  virtual int putq (BOE_Protocol_Handler_Ptr ph) = 0;

  virtual int getq (BOE_Protocol_Handler_Ptr &ph) = 0;

#ifndef BOE_MT

  virtual void run( ) = 0;

#endif

};

# if defined (BOE_HAS_INLINED_OSCALLS)
#   if defined (BOE_INLINE)
#     undef BOE_INLINE
#   endif /* BOE_INLINE */
#   define BOE_INLINE inline
#   include "BOE_Concurrency.inl"
# endif /* BOE_HAS_INLINED_OSCALLS */

_kernel_end

// Include the templates here.
#include "BOE_Concurrency_T.h"

_kernel_begin

//BOE_TEMPLATE_SPECIALIZATION
//class BOE_Concurrency_Bridge<BOE_Concurrency_Impl>
//{
//public:
//
//  BOE_Concurrency_Bridge (BOE_Concurrency_Impl *impl = 0);
//
//  int putq (BOE_Protocol_Handler *ph);
//  int getq (BOE_Protocol_Handler *&ph);
//
//  void shutdown (void);
//
//protected:
//
//  BOE_Concurrency_Impl *impl_;
//
//};


#ifndef BOE_CONCURRENCY_CONCRETE_IMPL
#define BOE_CONCURRENCY_CONCRETE_IMPL BOE_Concurrency_Impl
#endif /* BOE_CONCURRENCY_CONCRETE_IMPL */


//class BOE_Concurrency
//  : public BOE_Concurrency_Bridge<BOE_CONCURRENCY_CONCRETE_IMPL>
//{
//public:
//
//  BOE_Concurrency( BOE_CONCURRENCY_CONCRETE_IMPL *impl )
//	  : BOE_Concurrency_Bridge<BOE_CONCURRENCY_CONCRETE_IMPL>( impl )
//  {
//  }
//
//  static BOE_Concurrency * get ( BOE_CONCURRENCY_CONCRETE_IMPL *impl = 0 )
//  {
//	  return BT_Singleton< BOE_Concurrency,BOE_CONCURRENCY_CONCRETE_IMPL*, BOE_Mutex >::instance( impl );
//  }
//
//};

_kernel_end

#endif /* BOE_CONCURRENCY_H */
