

#ifndef JOMOO_GUARD_H
#define JOMOO_GUARD_H

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "config_threading.h"
#include "../Exception.HPP"


_jomoo_begin

template <class JOMOO_LOCK>
class JOMOO_Guard
{
public:

  MakeException( LockException , LockError );

  JOMOO_Guard (JOMOO_LOCK &l, bool nothrow = true );

#if(_WIN32_WINNT >= 0x0400)

  JOMOO_Guard (JOMOO_LOCK &l, bool block, bool nothrow );

#endif // (_WIN32_WINNT >= 0x0400)

  JOMOO_Guard (JOMOO_LOCK &l, bool block, bool become_owner, bool nothrow );

  ~JOMOO_Guard (void);

  bool acquire (void);

#if(_WIN32_WINNT >= 0x0400)
  bool tryacquire (void);
#endif // (_WIN32_WINNT >= 0x0400)

  void release (void);

  void disown (void);

  bool locked (void) const;

  bool remove (void);

protected:

  JOMOO_Guard (JOMOO_LOCK *lock): lock_ (lock) {}

  JOMOO_LOCK *lock_;

  bool owner_;

private:
	
	DECLARE_NO_COPY_CLASS( JOMOO_Guard );
};

_jomoo_end

#if defined (JOMOO_TEMPLATES_REQUIRE_SOURCE)
#include "Guard.T"
#endif /* ACE_TEMPLATES_REQUIRE_SOURCE */

#if defined (JOMOO_TEMPLATES_REQUIRE_PRAGMA)
#pragma implementation ("Guard.T")
#endif /* ACE_TEMPLATES_REQUIRE_PRAGMA */

#endif //JOMOO_GUARD_H