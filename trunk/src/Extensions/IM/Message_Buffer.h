
#ifndef Message_Buffer_H
#define Message_Buffer_H

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

// Include files
#include "config_IM.h"
#include "Instance_IM.H"


_im_begin

class Simple_Data_Block : public Data_Block
{
public:
	Simple_Data_Block( Instance_IM& instance,Data_Block_Ptr ptr ,size_t begin , size_t end );
	Simple_Data_Block( Instance_IM& instance,Data_Block_Ptr ptr ,size_t begin );

	const char* rd_ptr( ) const;
	size_t length( ) const;
private:
	Data_Block_Ptr ptr_;
	size_t begin_;
	size_t end_;
	Instance_IM& instance_;
};

class Simple_Data_Buffer : public Data_Buffer
{
public:
	Simple_Data_Buffer( Instance_IM& instance );
	~Simple_Data_Buffer( );

	const char* rd_ptr( ) const;
	void rd_ptr( size_t t );
	size_t length( ) const;

	char* wd_ptr();
	void wd_ptr( size_t t );
	size_t space( ) const;
private:

	DECLARE_NO_COPY_CLASS( Simple_Data_Buffer );
	
	char* buf_;
	size_t len_;
	size_t begin_;
	size_t end_;
	Instance_IM& instance_;
};

class Message_Buffer
{
public:
	Message_Buffer( );
	~Message_Buffer( );

	const iovec* rd_vec( ) const;
	size_t rd_size( ) const;
	size_t length( ) const;

	void push( Data_Block_Ptr data );
	void pop( );
	void clear( );
	Data_Block_Ptr operator[ ]( size_t n );

private:
	std::vector< Data_Block_Ptr > raw_vec_;
	std::vector< iovec > data_vec_;
	size_t length_;
};

_im_end

#endif // Message_Buffer_H

