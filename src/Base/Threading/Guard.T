
#include "Guard.H"

#ifndef Hazel_GUARD_CPP
#define Hazel_GUARD_CPP

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */


_hazel_begin

template <class Hazel_LOCK>  bool
Hazel_Guard<Hazel_LOCK>::acquire (void)
{
  return this->owner_ = this->lock_->acquire ();
}

#if(_WIN32_WINNT >= 0x0400)

template <class Hazel_LOCK>  bool
Hazel_Guard<Hazel_LOCK>::tryacquire ( )
{
  return this->owner_ = this->lock_->tryacquire ();
}

#endif // (_WIN32_WINNT >= 0x0400)

template <class Hazel_LOCK>  void
Hazel_Guard<Hazel_LOCK>::release (void)
{
  if ( !this->owner_ )
    return ;
  else
    {
      this->owner_ = false;
      this->lock_->release ();
    }
}

template <class Hazel_LOCK> 
Hazel_Guard<Hazel_LOCK>::Hazel_Guard (Hazel_LOCK &l, bool nothrow )
  : lock_ (&l),
    owner_ ( false )
{
  if( !this->acquire () && !nothrow )
	  ThrowException1( LockException , "进入锁失败" );
}

#if(_WIN32_WINNT >= 0x0400)

template <class Hazel_LOCK> 
Hazel_Guard<Hazel_LOCK>::Hazel_Guard (Hazel_LOCK &l, bool block, bool nothrow )
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

template <class Hazel_LOCK> 
Hazel_Guard<Hazel_LOCK>::Hazel_Guard (Hazel_LOCK &l, bool block, bool become_owner, bool nothrow )
  : lock_ (&l),
    owner_ (become_owner == 0 ? false : true )
{
  //HAZEL_UNUSED_ARG (block);
}


template <class Hazel_LOCK> 
Hazel_Guard<Hazel_LOCK>::~Hazel_Guard (void)
{
  this->release ();
}

template <class Hazel_LOCK>  bool
Hazel_Guard<Hazel_LOCK>::locked (void) const
{
  return this->owner_ ;
}

template <class Hazel_LOCK>  bool
Hazel_Guard<Hazel_LOCK>::remove (void)
{
  return this->lock_->remove ();
}

template <class Hazel_LOCK>  void
Hazel_Guard<Hazel_LOCK>::disown (void)
{
  this->owner_ = false;
}

_hazel_end

#endif //Hazel_GUARD_CPP