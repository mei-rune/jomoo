

#ifndef BOE_TPOOL_CONCURRENCY_H
#define BOE_TPOOL_CONCURRENCY_H

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include "BOE_Concurrency.h"
#include "framework\singleton.h"
#include "framework\BOE_Thread_Queue.H"

class BOE_TPOOL_Concurrency : public BOE_Concurrency_Impl
{
public:

  typedef BOE_Concurrency_Impl BOE_CONCURRENCY_TASK;

  BOE_TPOOL_Concurrency (void);

  int putq (BOE_Protocol_Handler *ph);

  int getq (BOE_Protocol_Handler *&ph);

  static BOE_TPOOL_Concurrency * instance (void)
  {
    return BOE_Singleton<BOE_TPOOL_Concurrency, BOE_Mutex>::instance ();
  }

  int open( void* );

  int close( );

  void svc (void);

private:

  int number_of_threads_;
  int shutdown_task_;
  int error_;

  BOE_Thread_Queue< BOE_Protocol_Handler > m_queue_;
};

#endif /* BOE_TPOOL_CONCURRENCY_H */
