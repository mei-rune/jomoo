
#ifndef BOE_TPR_CONCURRENCY_H
#define BOE_TPR_CONCURRENCY_H

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

// Include files
#include "config_Kernal.h"
#include "BOE_Concurrency.h"
#include "framework\singleton.h"

class BOE_TPR_Concurrency : public BOE_Concurrency_Impl
{
public:

  BOE_TPR_Concurrency (void);

  int putq (BOE_Protocol_Handler *ph);

  int getq (BOE_Protocol_Handler *&ph);

  static BOE_TPR_Concurrency * instance (void)
  {
     return BOE_Singleton<BOE_TPR_Concurrency, BOE_Mutex>::instance ();
  }

private:

  int getting_;
  int min_number_of_threads_;
  int shutdown_task_;
  int error_;

};

#endif /* BOE_TPR_CONCURRENCY_H */
