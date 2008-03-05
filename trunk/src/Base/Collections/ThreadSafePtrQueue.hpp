

#ifndef ThreadSafePtrQueue_H
#define ThreadSafePtrQueue_H

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */


#ifdef JOMOO_MT

#include "Platform/OS.H"

#define LIST_INTERFACE( X ) : public SLIST_ENTRY
#define LIST_DEFINE( X )

template< typename T >
class ThreadSafePtrQueue
{
public:

	typedef T value_type;
	typedef value_type* value_ptr_type;

	ThreadSafePtrQueue()
	{
		InitializeSListHead(&head_);
	}

	value_ptr_type pop()
	{
		return ( value_ptr_type ) InterlockedPopEntrySList( &head_ );
	}

	void push( value_ptr_type p )
	{
		InterlockedPushEntrySList(&head_, p ); 
	}

private:
	DECLARE_NO_COPY_CLASS( ThreadSafePtrQueue );
	SLIST_HEADER head_;
};
#else

#include "link.h"

#define LIST_INTERFACE( X )
#define LIST_DEFINE( X ) public: X* _next

template< typename T >
class ThreadSafePtrQueue
{
public:
	typedef T value_type;
	typedef value_type* value_ptr_type;

	struct head_type
	{
		value_ptr_type _next;
	};

	typedef head_type* head_ptr_type;

	ThreadSafePtrQueue()
	{
		SLINK_Initialize( &head_ );
	}

	value_ptr_type pop()
	{
		if( SLINK_IsEmpty( &head_ ) )
			return 0;
		return SLINK_Pop< head_ptr_type, value_ptr_type > ( &head_ );
	}

	void push( value_ptr_type v )
	{
		SLINK_Push< head_ptr_type, value_ptr_type > ( &head_,v );
	}

private:
	DECLARE_NO_COPY_CLASS( ThreadSafePtrQueue );

	head_type head_;
};

#endif JOMOO_MT


#endif //ThreadSafePtrQueue_H