

#include "BOE_Concurrency.h"
#include "BOE_THYBRID_Concurrency.h"
#include "BOE_Protocol_Handler.h"
#include "BOE_Options.h"


BOE_THYBRID_Concurrency::BOE_THYBRID_Concurrency (void)
  : getting_ (0)
  , min_number_of_threads_ (1)
  , max_number_of_threads_ (-1)
  , shutdown_task_ (0)
  , error_ (0)
{
  const char *value;

  value = getenv ("BOE_MIN_THYBRID_THREADS");
  if (value != 0)
    this->min_number_of_threads_ = ACE_OS::atoi (value);
  else
    this->min_number_of_threads_ =
      atoi (BOE_DEFAULT_MIN_THYBRID_THREADS);

  if (this->min_number_of_threads_ <= 0)
    this->min_number_of_threads_ = 1;

  value = getenv ("BOE_MAX_THYBRID_THREADS");
  if (value != 0)
    this->max_number_of_threads_ = ACE_OS::atoi (value);
  else
    this->max_number_of_threads_ =
      ACE_OS::atoi (BOE_DEFAULT_MAX_THYBRID_THREADS);

  if (this->max_number_of_threads_ <= 0)
    this->max_number_of_threads_ = -1;
  else if (this->max_number_of_threads_ < this->min_number_of_threads_)
    this->max_number_of_threads_ = this->min_number_of_threads_;

  int r;
  r = this->activate (THR_BOUND | THR_JOINABLE, this->min_number_of_threads_);
  if (r < 0)
    {
      this->shutdown_task_ = 1;
      this->error_ = 1;
    }
}

int
BOE_THYBRID_Concurrency::putq (BOE_Protocol_Handler *ph)
{
  if (this->error_)
    return -1;

  BOE_CONCURRENCY_TASK *task = this;
  int result = task->putq (& ph );

  if (result != -1)
    {
      if (this->getting_ < this->min_number_of_threads_
          && (this->max_number_of_threads_ < 0
              || this->thr_count () < (size_t) this->max_number_of_threads_))
        {
          int r;
          r = this->activate ( THR_BOUND | THR_JOINABLE
                             , 1 // number of threads
                             , 1 // force active
                             );
          if (r < 0)
            {
              // ACE_ERROR
              return -1;
            }
        }
    }

  return result;
}

int
BOE_THYBRID_Concurrency::getq (BOE_Protocol_Handler *&ph)
{
  ph = 0;

  BOE_CONCURRENCY_TASK *task = this;

  if (this->shutdown_task_ && task->msg_queue ()->message_count () == 0)
    return -1;

  int getting = InterlockedIncrement(this->getting_);

  if (getting > this->min_number_of_threads_)
    {
      if (task->msg_queue ()->message_count () == 0)
        {
          InterlockedDecrement(this->getting_);
          return -1;
        }
    }

  BOE_Protocol_Handler *ph = 0;
  int result = task->getq ( ph );

  if (result != -1)
    {

      if (ph == 0)
        {
          // Shutdown this task;
          this->shutdown_task_ = 1;
          if (this->getting_ > 1)
            {
              task->putq (mb);
              result = -1;
            }
 
        }
    }

  InterlockedDecrement(this->getting_);
  return result;
}
