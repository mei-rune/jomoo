
#include "Guard.H"

#ifndef JOMOO_GUARD_CPP
#define JOMOO_GUARD_CPP

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */


_jomoo_begin

template <class LOCK>  bool
guard<LOCK>::lock (void)
{
  return this->owner_ = this->lock_->acquire ();
}

#if(_WIN32_WINNT >= 0x0400)

template <class LOCK>  bool
guard<LOCK>::try_lock ( )
{
  return this->owner_ = this->lock_->tryacquire ();
}

#endif // (_WIN32_WINNT >= 0x0400)

template <class LOCK>  void guard<LOCK>::unlock (void)
{
  if ( !this->owner_ )
    return ;
    
  this->owner_ = false;
  this->lock_->release ();
}

template <class LOCK> 
guard<LOCK>::guard (LOCK &l, bool nothrow )
  : lock_ (&l),
    owner_ ( false )
{
  if( !this->lock () && !nothrow )
	  ThrowException1( LockException , "进入锁失败" );
}

#if(_WIN32_WINNT >= 0x0400)

template <class LOCK> 
guard<LOCK>::guard (LOCK &l, bool block, bool nothrow )
  : lock_ (&l),
    owner_ ( false )
{
  if (block)
    this->lock ();
  else
    if( ! this->try_lock () && !nothrow )
	  ThrowException1( LockException , "进入锁失败" );
}

#endif // (_WIN32_WINNT >= 0x0400)

template <class LOCK> 
guard<LOCK>::guard (LOCK &l, bool block, bool become_owner, bool nothrow )
  : lock_ (&l),
    owner_ (become_owner == 0 ? false : true )
{
  //JOMOO_UNUSED_ARG (block);
}


template <class LOCK> 
guard<LOCK>::~guard (void)
{
  this->unlock ();
}

template <class LOCK>  bool
guard<LOCK>::locked (void) const
{
  return this->owner_ ;
}

template <class LOCK>  bool
guard<LOCK>::remove (void)
{
  return this->lock_->remove ();
}

template <class LOCK>  void
guard<LOCK>::disown (void)
{
  this->owner_ = false;
}

_jomoo_end

#endif //JOMOO_GUARD_CPP