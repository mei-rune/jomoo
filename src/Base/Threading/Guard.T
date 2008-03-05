
#include "Guard.H"

#ifndef JOMOO_GUARD_CPP
#define JOMOO_GUARD_CPP

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */


_JOMOO_begin

template <class JOMOO_LOCK>  bool
JOMOO_Guard<JOMOO_LOCK>::acquire (void)
{
  return this->owner_ = this->lock_->acquire ();
}

#if(_WIN32_WINNT >= 0x0400)

template <class JOMOO_LOCK>  bool
JOMOO_Guard<JOMOO_LOCK>::tryacquire ( )
{
  return this->owner_ = this->lock_->tryacquire ();
}

#endif // (_WIN32_WINNT >= 0x0400)

template <class JOMOO_LOCK>  void
JOMOO_Guard<JOMOO_LOCK>::release (void)
{
  if ( !this->owner_ )
    return ;
  else
    {
      this->owner_ = false;
      this->lock_->release ();
    }
}

template <class JOMOO_LOCK> 
JOMOO_Guard<JOMOO_LOCK>::JOMOO_Guard (JOMOO_LOCK &l, bool nothrow )
  : lock_ (&l),
    owner_ ( false )
{
  if( !this->acquire () && !nothrow )
	  ThrowException1( LockException , "进入锁失败" );
}

#if(_WIN32_WINNT >= 0x0400)

template <class JOMOO_LOCK> 
JOMOO_Guard<JOMOO_LOCK>::JOMOO_Guard (JOMOO_LOCK &l, bool block, bool nothrow )
  : lock_ (&l),
    owner_ ( false )
{
  if (block)
    this->acquire ();
  else
    if( ! this->tryacquire () && !nothrow )
	  ThrowException1( LockException , "进入锁失败" );
}

#endif // (_WIN32_WINNT >= 0x0400)

template <class JOMOO_LOCK> 
JOMOO_Guard<JOMOO_LOCK>::JOMOO_Guard (JOMOO_LOCK &l, bool block, bool become_owner, bool nothrow )
  : lock_ (&l),
    owner_ (become_owner == 0 ? false : true )
{
  //JOMOO_UNUSED_ARG (block);
}


template <class JOMOO_LOCK> 
JOMOO_Guard<JOMOO_LOCK>::~JOMOO_Guard (void)
{
  this->release ();
}

template <class JOMOO_LOCK>  bool
JOMOO_Guard<JOMOO_LOCK>::locked (void) const
{
  return this->owner_ ;
}

template <class JOMOO_LOCK>  bool
JOMOO_Guard<JOMOO_LOCK>::remove (void)
{
  return this->lock_->remove ();
}

template <class JOMOO_LOCK>  void
JOMOO_Guard<JOMOO_LOCK>::disown (void)
{
  this->owner_ = false;
}

_JOMOO_end

#endif //JOMOO_GUARD_CPP