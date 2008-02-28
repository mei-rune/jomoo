


BOE_INLINE BOE_Concurrency_Impl::BOE_Concurrency_Impl( const tchar* name , BOE_Log& log )
: BOE_Thread_Svc_Handler( name , log )
{
}

BOE_INLINE void BOE_Concurrency_Impl::svc (void)
{
  BOE_Protocol_Handler *ph;

  while (this->getq (ph) != -1)
    {
      if (ph == 0)
        break;

      if (ph->service () == -1)
        {
          ph->dismiss ();
          continue;
        }
    }
}
