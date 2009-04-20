#ifndef _variant_h_
# define _variant_h_

#include "jingxian/config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files


_jingxian_begin



struct stringData
{
	size_t len;
	char* ptr;
};

class variantObject
{
public:

	enum variant_type
	{
		BOOLEAN_TYPE
		INT8_TYPE,
		INT16_TYPE,
		INT32_TYPE,
		INT64_TYPE,
		STRING_TYPE,
		PTR_TYPE,
		SEQUENCE_TYPE,
		IDictionary_TYPE
	};

	virtual ~ObjectBase(){};

	virtual bool toBoolean()const = 0;

	virtual int8_t toInt8()const = 0;

	virtual int16_t toInt16()const = 0;

	virtual int32_t toInt32()const = 0;

	virtual int64_t toInt64()const = 0;

	virtual const stringData& toString()const = 0;

	virtual void* toPtr()const = 0;

	virtual bool is_null() const = 0;

	virtual int getType()const = 0;
};

struct variant
{
	int type;
	union 
	{
		bool bVal;
		int8_t i8;
		int16_t i16;
		int32_t i32;
		int64_t i64;
		stringData str;
		void* ptr;
	} record;
};

_jingxian_end

#endif // _variant_h_