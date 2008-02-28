// Concurrency_T.cpp,v 1.2 2003/11/09 04:12:07 dhinton Exp



#include "BOE_Concurrency_T.h"

#ifndef _BOE_Concurrency_T_CPP_
#define _BOE_Concurrency_T_CPP_

_kernel_begin

template <class CONCURRENCY_IMPL>
BOE_Concurrency_Bridge<CONCURRENCY_IMPL>
::BOE_Concurrency_Bridge (CONCURRENCY_IMPL *impl)
  : impl_ (impl)
{
  if (this->impl_ == 0)
    this->impl_ = CONCURRENCY_IMPL::instance ();
}


template <class CONCURRENCY_IMPL> int
BOE_Concurrency_Bridge<CONCURRENCY_IMPL>::putq (BOE_Protocol_Handler_Ptr ph)
{
  return this->impl_->putq (ph);
}
  

template <class CONCURRENCY_IMPL> int
BOE_Concurrency_Bridge<CONCURRENCY_IMPL>::getq (BOE_Protocol_Handler_Ptr& ph)
{
  return this->impl_->getq (ph);
}


template <class CONCURRENCY_IMPL> void
BOE_Concurrency_Bridge<CONCURRENCY_IMPL>::shutdown (void)
{

  task = this->impl_;
  task->putq ( 0 );
  task->wait ();
}

_kernel_end

#endif // _BOE_Concurrency_T_CPP_
