#ifndef __JOMOO_CollectionBase__
#define __JOMOO_CollectionBase__

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */


template <typename T>
public IEnumerator
{
public :
	virtual ~IEnumerator(){}
	virtual T current() = 0;
	virtual bool next() = 0;
	virtual void reset() = 0;

private:
	DECLARE_NO_COPY_CLASS( Context );
};

template <typename T>
class IComparable
{
    virtual int compare( ) = 0;
};

#endif // #ifndef __AcfCollectionBase__
