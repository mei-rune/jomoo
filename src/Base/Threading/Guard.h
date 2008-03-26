

#ifndef _GUARD_H_
#define _GUARD_H_

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "config_threading.h"
#include "../Exception.HPP"


_jomoo_begin

template <class LOCK>
class guard
{
public:

  MakeException( LockException , LockError );

  guard (LOCK &l, bool nothrow = true );

#if(_WIN32_WINNT >= 0x0400)

  guard (LOCK &l, bool block, bool nothrow );

#endif // (_WIN32_WINNT >= 0x0400)

  guard (LOCK &l, bool block, bool become_owner, bool nothrow );

  ~guard (void);

  bool lock (void);

#if(_WIN32_WINNT >= 0x0400)
  bool try_lock (void);
#endif // (_WIN32_WINNT >= 0x0400)

  void unlock (void);

  void disown (void);

  bool locked (void) const;

  bool remove (void);

protected:

  guard (LOCK *lock): lock_ (lock) {}

  LOCK *lock_;

  bool owner_;

private:
	
	DECLARE_NO_COPY_CLASS( guard );
};

_jomoo_end

#if defined (JOMOO_TEMPLATES_REQUIRE_SOURCE)
#include "Guard.T"
#endif /* ACE_TEMPLATES_REQUIRE_SOURCE */

#if defined (JOMOO_TEMPLATES_REQUIRE_PRAGMA)
#pragma implementation ("Guard.T")
#endif /* ACE_TEMPLATES_REQUIRE_PRAGMA */

#endif //_GUARD_H_