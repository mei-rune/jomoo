
#ifndef _IDictionary_H_
#define _IDictionary_H_

#include "jingxian/config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files

_jingxian_begin

class IDictionary
{
public:
	virtual ~IDictionary(void) {}

	virtual bool getBoolean(const tchar* key) const = 0;

	virtual int8_t getInt8(const tchar* key) const = 0;

	virtual int16_t getInt16(const tchar* key) const = 0;
	
	virtual int32_t getInt32(const tchar* key) const = 0;

	virtual int64_t getInt64(const tchar* key) const = 0;

	virtual const tstring& getString(const tchar* key) const = 0;

	virtual void setBoolean(const tchar* key, bool value) = 0;

	virtual void setInt8(const tchar* key, int8_t value) = 0;

	virtual void setInt16(const tchar* key, int16_t value) = 0;

	virtual void setInt32(const tchar* key, int32_t value) = 0;

	virtual void setInt64(const tchar* key, int64_t value) = 0;

	virtual void setString(const tchar* key, const tchar* value) = 0;

	virtual void dump( tostream& target ) const = 0;
};

inline tostream& operator<<( tostream& target, const IDictionary& dict )
{
	dict.dump( target );
	return target;
}

_jingxian_end

#endif //_IDictionary_H_