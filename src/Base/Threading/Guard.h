

#ifndef Hazel_GUARD_H
#define Hazel_GUARD_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

#include "config_threading.h"
#include "../Exception.HPP"


_hazel_begin

template <class Hazel_LOCK>
class Hazel_Guard
{
public:

  MakeException( LockException , LockError );

  Hazel_Guard (Hazel_LOCK &l, bool nothrow = true );

#if(_WIN32_WINNT >= 0x0400)

  Hazel_Guard (Hazel_LOCK &l, bool block, bool nothrow );

#endif // (_WIN32_WINNT >= 0x0400)

  Hazel_Guard (Hazel_LOCK &l, bool block, bool become_owner, bool nothrow );

  ~Hazel_Guard (void);

  bool acquire (void);

#if(_WIN32_WINNT >= 0x0400)
  bool tryacquire (void);
#endif // (_WIN32_WINNT >= 0x0400)

  void release (void);

  void disown (void);

  bool locked (void) const;

  bool remove (void);

protected:

  Hazel_Guard (Hazel_LOCK *lock): lock_ (lock) {}

  Hazel_LOCK *lock_;

  bool owner_;

private:
	
	DECLARE_NO_COPY_CLASS( Hazel_Guard );
};

_hazel_end

#if defined (Hazel_TEMPLATES_REQUIRE_SOURCE)
#include "Guard.T"
#endif /* ACE_TEMPLATES_REQUIRE_SOURCE */

#if defined (Hazel_TEMPLATES_REQUIRE_PRAGMA)
#pragma implementation ("Guard.T")
#endif /* ACE_TEMPLATES_REQUIRE_PRAGMA */

#endif //Hazel_GUARD_H