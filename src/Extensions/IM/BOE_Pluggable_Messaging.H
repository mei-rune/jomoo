#ifndef BOE_PLUGGABLE_MESSAGING_H
#define BOE_PLUGGABLE_MESSAGING_H

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

// Include files
#include "config_IM.h"
#include "BOE/IO/IO.H"
#include "BOE/counter_ptr.hpp"

_im_begin

class BOE_Pluggable_Messaging
{
public:
	typedef counter_ptr< BOE_Pluggable_Messaging > ptr_type;

	virtual ~BOE_Pluggable_Messaging(){}

	virtual int open( ) = 0;
	virtual void close( ) = 0;

	virtual void finalize() = 0;

	virtual void* wd_ptr( ) = 0;
	virtual void wd_ptr( size_t ) = 0;
	virtual size_t wd_space() = 0;
	virtual int parse( ) = 0;
	virtual int parse( void* data, size_t length ) = 0;


	virtual bool hasData() = 0;
	virtual int rd_type() = 0;

	// 1
	virtual const void* rd_ptr( ) = 0;
	virtual void rd_ptr( size_t ) = 0;
	virtual size_t rd_length() = 0;

	// 2
	virtual iovec* rd_vec() = 0;
	virtual size_t rd_size() = 0;
	virtual void rd_vec( size_t ) = 0;

	// 3
	virtual iopack* rd_f_vec() = 0;
	virtual size_t  rd_f_size() = 0;
	virtual void rd_f_vec( size_t ) = 0;

};

typedef BOE_Pluggable_Messaging::ptr_type BOE_Pluggable_Messaging_Ptr;

class BOE_Pluggable_Messaging_Factory
{
public:
	virtual ~BOE_Pluggable_Messaging_Factory(){}
	virtual BOE_Pluggable_Messaging_Ptr create( ) = 0;
	virtual const tstring& getName();
};

_im_end

#endif /*BOE_PLUGGABLE_MESSAGING_H*/
