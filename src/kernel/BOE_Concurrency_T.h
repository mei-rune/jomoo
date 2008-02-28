

#ifndef BOE_CONCURRENCY_T_H
#define BOE_CONCURRENCY_T_H

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

class BOE_Protocol_Handler;

template <class CONCURRENCY_IMPL>
class BOE_Concurrency_Bridge
{
public:

  BOE_Concurrency_Bridge (CONCURRENCY_IMPL *impl = 0);

  int putq (BOE_Protocol_Handler *ph);
  int getq (BOE_Protocol_Handler *&ph);

  void shutdown (void);

protected:

  CONCURRENCY_IMPL *impl_;

};

#if defined (BOE_TEMPLATES_REQUIRE_SOURCE)
#include "BOE_Concurrency_T.cpp"
#endif /* BOE_TEMPLATES_REQUIRE_SOURCE */

#if defined (BOE_TEMPLATES_REQUIRE_PRAGMA)
#pragma implementation ("BOE_Concurrency_T.cpp")
#endif /* BOE_TEMPLATES_REQUIRE_PRAGMA */


#endif /* BOE_CONCURRENCY_T_H */
