// -*- C++ -*-
// Cleanup.cpp,v 1.2 2003/11/01 11:15:12 dhinton Exp

#include "Cleanup.h"


#if !defined (BOE_HAS_INLINED_OSCALLS)
# include "Cleanup.inl"
#endif /* ACE_HAS_INLINED_OS_CALLS */



_bt_begin
//
//BOE_Mutex* gBOECleanupListMutex;
//
//BOERegisterCleanup* gBOECleanupList;

void BOERegisterCleanup::doCleanup()
{
    if (m_cleanup)
        m_cleanup->cleanup ( 0 );

    unregisterCleanup();
}

void BOERegisterCleanup::registerCleanup( BOE_Cleanup* cleanup )
{

	BOE_GUARD( BOE_Thraad_Mutex , guard, *gBOECleanupListMutex );
    m_cleanup = cleanup;

    if (!m_nextCleanup && !m_prevCleanup) 
    {
        m_nextCleanup = gBOECleanupList;
        gBOECleanupList = this;

        if (m_nextCleanup)
            m_nextCleanup->m_prevCleanup = this;
    }
}

void BOERegisterCleanup::unregisterCleanup()
{
    BOERegisterCleanup *tmpThis = (BOERegisterCleanup*) this;
	{
    BOE_GUARD( BOE_Thraad_Mutex , guard, *gBOECleanupListMutex );


    if (m_nextCleanup) 
        m_nextCleanup->m_prevCleanup = m_prevCleanup;
		
    if (!m_prevCleanup) 
        gBOECleanupList = m_nextCleanup;
    else 
        m_prevCleanup->m_nextCleanup = m_nextCleanup;

    }	

	tmpThis->resetCleanup();

}


BOERegisterCleanup::BOERegisterCleanup()
{
	resetCleanup();
}


void BOERegisterCleanup::resetCleanup() 
{
	m_nextCleanup = 0;
	m_prevCleanup = 0;
	m_cleanup = 0;
}

BOERegisterCleanup_Implementation *BOERegisterCleanup_Implementation::get()
{
	static BOERegisterCleanup_Implementation impl_;
	return &impl_;
}

BOE_Mutex* BOERegisterCleanup_Implementation::get_singleton_lock()
{

#ifdef BOE_MT
	return &m_mutex_;
#else
	return 0;
#endif //
}

BOERegisterCleanup_Implementation::	BOERegisterCleanup_Implementation()
{
}

_bt_end
