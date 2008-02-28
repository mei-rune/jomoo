

#include "BOE_Concurrency.h"
#include "BOE_TPR_Concurrency.h"
#include "BOE_Protocol_Handler.h"


BOE_TPR_Concurrency::BOE_TPR_Concurrency (void)
  : BOE_Concurrency_Impl( BT_TEXT("BOE_TPR_Concurrency") , BOE_Log( BT_TEXT("BOE_TPR_Concurrency") ) )
  , getting_ (0)
  , shutdown_task_ (0)
  , error_ (0)
{
  int r;
  r = this->activate ( 1 );
  if (r < 0)
    {
      this->error_ = 1;
      this->shutdown_task_ = 1;
    }
}

int
BOE_TPR_Concurrency::putq (BOE_Protocol_Handler *ph)
{
  if (this->error_)
    return -1;

  if (result != -1)
    {
      int r;
      r = this->activate ( 1 );
      if (r < 0)
        {
          return -1;
        }
    }

  return result;
}

int
BOE_TPR_Concurrency::getq (BOE_Protocol_Handler *&ph)
{

}
