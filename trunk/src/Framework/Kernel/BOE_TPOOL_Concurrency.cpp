

#include "BOE_TPOOL_Concurrency.h"
#include "BOE_Protocol_Handler.h"


#ifndef BOE_DEFAULT_TPOOL_THREADS
#define BOE_DEFAULT_TPOOL_THREADS BT_TEXT("10")
#endif // BOE_DEFAULT_TPOOL_THREADS

BOE_TPOOL_Concurrency::BOE_TPOOL_Concurrency (void)
  : BOE_Concurrency_Impl( BT_TEXT("BOE_TPOOL_Concurrency"), BOE_Log( BT_TEXT("BOE_TPOOL_Concurrency") ) )
  , number_of_threads_ (5)
  , shutdown_task_ (0)
  , error_ (0)
{
	if( open( 0 ) != 0 )
		BOE_LOG_THROW( m_log_,BT_TEXT( "³õ»¯»¯Ê§°Ü" ) );
}

int BOE_TPOOL_Concurrency::open( void* )
{
  const char *value = getenv ( BT_TEXT( "BOE_TPOOL_THREADS") );
  if (value != 0)
    this->number_of_threads_ = atoi (value);
  else
    this->number_of_threads_ = atoi (BOE_DEFAULT_TPOOL_THREADS);

  if (this->number_of_threads_ <= 0)
    this->number_of_threads_ = 5;

  int r = this->activate ( this->number_of_threads_);

  if (r < 0)
    {
      this->error_ = 1;
      this->shutdown_task_ = 1;
	  return -1;
    }
	return 0;
}

int BOE_TPOOL_Concurrency::putq (BOE_Protocol_Handler *ph)
{
  if (this->error_)
    return -1;

  return m_queue_.put ( ph );
}

int BOE_TPOOL_Concurrency::getq (BOE_Protocol_Handler *&ph)
{
  ph = 0;

  if (this->shutdown_task_ && m_queue_.empty () )
    return -1;

  int result = m_queue_.get ( ph );

  if (result != -1)
  {
	  if (ph == 0)
	  {
		  this->shutdown_task_ = 1;
		  m_queue_.put ( ph );
		  result = -1;
	  }
  }
  return result;
}

int BOE_TPOOL_Concurrency::close( )
{
	putq( 0 );
	join_all();
	return 0;
}

void BOE_TPOOL_Concurrency::svc (void)
{
  BOE_Protocol_Handler *ph;

  while ( true )
  {
	  if( this->getq (ph) == -1 )
		  continue;

	  if (ph == 0)
		  break;

	  if (ph->service () == -1)
	  {
		  ph->dismiss ();
		  continue;
	  }
  }
}
