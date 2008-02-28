/* -*- c++ -*- */
// THYBRID_Concurrency.h,v 1.2 2003/11/25 21:55:11 kobica Exp

#ifndef BOE_THYBRID_CONCURRENCY_H
#define BOE_THYBRID_CONCURRENCY_H

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include "BOE_Concurrency.h"
#include "framework\singleton.h"

class BOE_THYBRID_Concurrency : public BOE_Concurrency_Impl
{
public:

  BOE_THYBRID_Concurrency (void);

  int putq (BOE_Protocol_Handler *ph);

  int getq (BOE_Protocol_Handler *&ph);

  static BOE_THYBRID_Concurrency * instance (void)
  {
    return BOE_Singleton<BOE_THYBRID_Concurrency, BOE_Mutex>::instance ();
  }

private:

  int getting_;
  int min_number_of_threads_;
  int max_number_of_threads_;
  int shutdown_task_;
  int error_;

};

#endif /* BOE_THYBRID_CONCURRENCY_H */
