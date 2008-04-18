#ifndef _variant_h_
# define _variant_h_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files


_jomoo_begin


enum jomoo_type
{
	boolean_type
	int8_type,
	int16_type,
	int32_type,
	int64_type,
	string_type,
	object_type,
	sequence_type,
	dictionary_type
};

class variant
{
public:

	virtual ~variant(){};

	virtual void incRef() = 0;
    
	virtual void decRef() = 0;

	virtual const tstring& toString() = 0;

	virtual bool toBoolean() = 0;

	virtual int8_t toInt8() = 0;

	virtual int16_t toInt16() = 0;

	virtual int32_t toInt32() = 0;

	virtual int64_t toInt64() = 0;

	virtual void* toPtr() = 0;

	virtual bool is_null() const = 0;
};

template<T>
class variant
{
public:

	virtual ~variant(){};

	virtual const tstring& toString() = 0;

	virtual bool toBoolean() = 0;

	virtual int8_t toInt8() = 0;

	virtual int16_t toInt16() = 0;

	virtual int32_t toInt32() = 0;

	virtual int64_t toInt64() = 0;

	virtual void* toPtr() = 0;

	virtual bool is_null() const = 0;

private:

};

_jomoo_end

#endif // _variant_h_