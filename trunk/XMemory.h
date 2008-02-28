
#if !defined(XMEMORY_HPP)
#define XMEMORY_HPP

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include "BT_Memory_Base.H"
#include "BT_Export.H"

_bt_begin

class BT_Export XMemory
{
public :

    void* operator new(size_t size);

#if defined(BOE_VISUALCPP)

    void* operator new(size_t size, const char* file, int line);

    void operator delete(void* p, const char* file, int line);
#endif

    void* operator new(size_t size, BT_Memory_Base* memMgr);

    void operator delete(void* p);

#if !defined(BOE_BORLAND)

    void operator delete(void* p, BT_Memory_Base* memMgr);
#endif

    //@}

protected :

    XMemory()
    {
    }

    XMemory(const XMemory&)
    {
    }

#if defined(BOE_BORLAND)
    virtual ~XMemory()
    {
    }
#endif

private:
    // -----------------------------------------------------------------------
    //  Unimplemented operators
    // -----------------------------------------------------------------------
    XMemory& operator=(const XMemory&);
};

_bt_end

#endif
