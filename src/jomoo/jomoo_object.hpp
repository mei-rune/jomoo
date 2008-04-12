#ifndef is_empty_H
# define is_empty_H

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

class object
{
public:
	virtual ~object() {}

	virtual jomoo_type type() const = 0;

	virtual void print( tostream& target ) const = 0;
};

tostream& operator<<(tostream& target, const object& obj)
{
	obj.print( target ); 
	return target;
}

class sequence : public jomoo_object
{
public:
	virtual ~sequence() {}
	virtual jomoo_type item_type() const = 0;
};

class dictionary : public sequence
{
	virtual ~sequence() {}
	virtual jomoo_type key_type() const = 0;
	virtual jomoo_type value_type() const = 0;
};

class value
{
public:


	virtual ~jomoo_object(){};

	virtual const tstring& toString() = 0;

	virtual bool toBoolean() = 0;

	virtual int8_t toInt8() = 0;

	virtual int16_t toInt16() = 0;

	virtual int32_t toInt32() = 0;

	virtual int64_t toInt64() = 0;

	virtual bool is_null() const = 0;
};



_jomoo_end

#endif // is_empty_H