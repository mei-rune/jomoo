

#ifndef BOE_NULL_CONCURRENCY_H
#define BOE_NULL_CONCURRENCY_H

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

// Include files
#include "config_Kernel.h"
#include "BOE_Concurrency.h"


class BOE_NULL_Concurrency : public BOE_Concurrency_Impl
{
public:

  typedef BOE_Concurrency_Impl BOE_CONCURRENCY_TASK;

  BOE_NULL_Concurrency ( );

  int putq (BOE_Protocol_Handler_Ptr ph);

  int getq (BOE_Protocol_Handler_Ptr &ph);

  void run (void);

};

#endif /* BOE_NULL_CONCURRENCY_H */
