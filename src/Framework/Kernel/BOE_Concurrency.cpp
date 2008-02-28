

#include "BOE_Concurrency.h"
//#include "BOE_TPOOL_Concurrency.h"
//#include "BOE_TPR_Concurrency.h"
//#include "BOE_THYBRID_Concurrency.h"
#include "BOE/tstring.h"

#ifdef _MEMORY_DEBUG
#undef THIS_FILE
#define new	   DEBUG_NEW  
#define malloc DEBUG_MALLOC  
static char THIS_FILE[] = __FILE__;  
#endif // _MEMORY_DEBUG


#ifndef BOE_DEFAULT_CONCURRENCY
#define BOE_DEFAULT_CONCURRENCY "TPOOL"
#endif // BOE_DEFAULT_CONCURRENCY

_kernel_begin

//BOE_Concurrency_Bridge<BOE_Concurrency_Impl>
//::BOE_Concurrency_Bridge (BOE_Concurrency_Impl *impl)
//  : impl_ (impl)
//{
//  if (this->impl_ == 0)
//    {
//      const char *concurrency;
//      concurrency = getenv ("BOE_CONCURRENCY");
//      if (concurrency == 0)
//        concurrency = BOE_DEFAULT_CONCURRENCY;
//
//      if ( tstrcasecmp (concurrency, "TPR") == 0)
//        this->impl_ = BOE_TPR_Concurrency::instance ();
//      else if ( tstrcasecmp (concurrency, "TPOOL") == 0)
//        this->impl_ = BOE_TPOOL_Concurrency::instance ();
//      else if ( tstrcasecmp (concurrency, "THYBRID") == 0)
//        this->impl_ = BOE_THYBRID_Concurrency::instance ();
//      else
//        this->impl_ = BOE_THYBRID_Concurrency::instance ();
//    }
//}
//
//
//int
//BOE_Concurrency_Bridge<BOE_Concurrency_Impl>
//::putq (BOE_Protocol_Handler *ph)
//{
//  return this->impl_->putq (ph);
//}
//  
//
//int
//BOE_Concurrency_Bridge<BOE_Concurrency_Impl>
//::getq (BOE_Protocol_Handler *&ph)
//{
//  return this->impl_->getq (ph);
//}
//
//
//void
//BOE_Concurrency_Bridge<BOE_Concurrency_Impl>::shutdown (void)
//{
//
//  BOE_Concurrency_Impl* task = BOE_THYBRID_Concurrency::instance ();
//  task->close ();
//
//  task = BOE_TPOOL_Concurrency::instance ();
//  task->close ();
//
//  task = BOE_TPR_Concurrency::instance ();
//  task->close ();
//}

_kernel_end