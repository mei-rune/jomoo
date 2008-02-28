

/**
* -*- C++ -*-
* -------------------------------------------------------------------------------
* - ¡è¨q¡Ð¨r ¨q¡Ð¨r					   BT_Memory_Base.H,v 1.0 2005/03/25 10:52:54
*  ¨u¨¨€¨€¨Ž ¨q¨q ¡Ð¨r
* ¦òÌï¦òÌïÌï| ¨t------
* -------------------------------------------------------------------------------
*/

#ifndef _BT_Memory_Base_H_
#define _BT_Memory_Base_H_


#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */


_bt_begin

class BT_Memory_Base
{
public:
	virtual ~BT_Memory_Base(){};

	virtual void *malloc (size_t nbytes , const char* file=0, int line=-1 ) = 0;

	virtual void *calloc (size_t nbytes,char initial_value = '\0', const char* file=0, int line=-1 ) = 0;

	virtual void *calloc (size_t n_elem, size_t elem_size,char initial_value = '\0', const char* file=0, int line=-1 ) = 0;

	virtual void free (void *) = 0;

};

class Memory_Guard
{
public:
	Memory_Guard( BT_Memory_Base* memory , void * ptr )
		: memory_( memory )
		, ptr_( ptr )
	{
	}
	~Memory_Guard()
	{
		if( memory_ != 0 && ptr_ != 0 )
			memory_->free( ptr_ );
	}

	void* get()
	{
		return ptr_;
	}

	bool empty()
	{
		return ( ptr_ == 0 );
	}

	void *release()
	{
		void * ptr = ptr_;
		ptr_  = 0;
		return ptr;
	}
private:
	
	DECLARE_NO_COPY_CLASS( Memory_Guard );

	BT_Memory_Base* memory_;
	void *ptr_;
	
};

_bt_end

#endif // _BT_Memory_Base_H_