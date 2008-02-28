

#ifndef BOE_CONCURRENCY_H
#define BOE_CONCURRENCY_H

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include "BOE_Protocol_Handler.h"
#include "framework/singleton.h"
#include "synch/BOE_Thread_Svc_Handler.H"

class BOE_Concurrency_Impl : public BOE_Thread_Svc_Handler
{
public:

  BOE_Concurrency_Impl( const tchar* name , BOE_Log& log );

  virtual ~BOE_Concurrency_Impl (void) {};

  virtual int putq (BOE_Protocol_Handler *ph) = 0;

  virtual int getq (BOE_Protocol_Handler *&ph) = 0;

  virtual void svc (void) ;

};

# if defined (BOE_HAS_INLINED_OSCALLS)
#   if defined (BOE_INLINE)
#     undef BOE_INLINE
#   endif /* BOE_INLINE */
#   define BOE_INLINE inline
#   include "BOE_Concurrency.inl"
# endif /* BOE_HAS_INLINED_OSCALLS */

// Include the templates here.
#include "BOE_Concurrency_T.h"


BOE_TEMPLATE_SPECIALIZATION
class BOE_Concurrency_Bridge<BOE_Concurrency_Impl>
{
public:

  BOE_Concurrency_Bridge (BOE_Concurrency_Impl *impl = 0);

  int putq (BOE_Protocol_Handler *ph);
  int getq (BOE_Protocol_Handler *&ph);

  void shutdown (void);

protected:

  BOE_Concurrency_Impl *impl_;

};


#ifndef BOE_CONCURRENCY_CONCRETE_IMPL
#define BOE_CONCURRENCY_CONCRETE_IMPL BOE_Concurrency_Impl
#endif /* BOE_CONCURRENCY_CONCRETE_IMPL */


class BOE_Concurrency
  : public BOE_Concurrency_Bridge<BOE_CONCURRENCY_CONCRETE_IMPL>
{
public:

  BOE_Concurrency( BOE_CONCURRENCY_CONCRETE_IMPL *impl )
	  : BOE_Concurrency_Bridge<BOE_CONCURRENCY_CONCRETE_IMPL>( impl )
  {
  }

  static BOE_Concurrency * get ( BOE_CONCURRENCY_CONCRETE_IMPL *impl = 0 )
  {
	  return BT_Singleton< BOE_Concurrency,BOE_CONCURRENCY_CONCRETE_IMPL*, BOE_Mutex >::instance( impl );
  }

};


#endif /* BOE_CONCURRENCY_H */
