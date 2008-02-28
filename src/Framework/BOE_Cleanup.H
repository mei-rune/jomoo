

#ifndef BOE_CLEANUP_H
# define BOE_CLEANUP_H


# include "config.h"

# if !defined (BOE_LACKS_PRAGMA_ONCE)
#  pragma once
# endif /* BOE_LACKS_PRAGMA_ONCE */

#include "BT_export.h"
#include "synch/synch_traits.h"

_bt_begin

class BT_Export BOE_Cleanup
{
public:

	virtual ~BOE_Cleanup (void);

	virtual void cleanup (void *param = 0);
};

class BT_Export BOERegisterCleanup
{
public :
	
	void doCleanup(); 

	void registerCleanup( BOE_Cleanup* cleanup );

	void unregisterCleanup();

	BOERegisterCleanup();

private:

	BOERegisterCleanup(const BOERegisterCleanup&);
    BOERegisterCleanup& operator=(const BOERegisterCleanup&);


	BOE_Cleanup* m_cleanup;


	BOERegisterCleanup *m_nextCleanup, *m_prevCleanup;

	void resetCleanup();
};

#ifdef BOE_MT
extern BOE_Mutex* gBOECleanupListMutex;
#endif 

extern BOERegisterCleanup* gBOECleanupList;

class BOERegisterCleanup_Implementation
{
public:
	static BOERegisterCleanup_Implementation *get();
	BOE_Mutex* get_singleton_lock();
private:
	BOERegisterCleanup_Implementation();
	BOE_MUTEX( m_mutex_ );
};



# if defined (BOE_HAS_INLINED_OSCALLS)
#   if defined (BOE_INLINE)
#     undef BOE_INLINE
#   endif /* BOE_INLINE */
#   define BOE_INLINE inline
#   include "Cleanup.inl"
# endif /* BOE_HAS_INLINED_OSCALLS */
_bt_end

#endif /* ACE_CLEANUP_H */
