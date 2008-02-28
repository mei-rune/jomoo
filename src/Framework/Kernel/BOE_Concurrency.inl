



//BOE_INLINE void BOE_Concurrency_Impl::svc (void)
//{
//  BOE_Protocol_Handler *ph;
//
//  while (this->getq (ph) != -1)
//    {
//      if (ph == 0)
//        break;
//
//      if (ph->service () == -1)
//        {
//          ph->dismiss ();
//          continue;
//        }
//    }
//}
