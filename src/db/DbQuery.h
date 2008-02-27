
#ifndef _DbQuery_H_
#define _DbQuery_H_

#include "../../util/Variant.h"
#include "../../util/pTime.h"

_bt_begin

class DbQuery {
public:
	virtual ~DbQuery() {}

	virtual bool exec(const char* sql, size_t len, bool reportWarningsAsErrors = true ) = 0;

	virtual bool exec(const tstring& sql, bool reportWarningsAsErrors = true ) = 0;

	virtual bool nextRow() = 0;

	virtual bool nextSet() = 0;

	virtual int columns() = 0;

	virtual bool getBoolean(u_int_t column) = 0;

	virtual bool getBoolean(const tstring& column) = 0;

	virtual int getInt(u_int_t column) = 0;

	virtual int getInt(const tstring& column) = 0;

	virtual __int64 getInt64(u_int_t column) = 0;

	virtual __int64 getInt64(const tstring& column) = 0;

	virtual double getDouble(u_int_t column) = 0;

	virtual double getDouble(const tstring& column) = 0;

	virtual const tstring& getString(u_int_t column) = 0;

	virtual const tstring& getString(const tstring& column) = 0;

	virtual const ptime& getTime(u_int_t column) = 0;

	virtual const ptime& getTime(const tstring& column) = 0;

	virtual const Variant& get(u_int_t column) = 0;

	virtual const Variant& get(const tstring& column) = 0;

	virtual int getColumnType( size_t pos ) = 0;

	virtual const tstring& getColumnName( size_t pos ) = 0;
};

inline bool getQueryCol( DbQuery& q, u_int_t index, bool& i )
{
	i = q.getBoolean( index );
	return true;
}

inline bool getQueryCol( DbQuery& q, u_int_t index, int& i )
{
	i = q.getInt( index );
	return true;
}

inline bool getQueryCol( DbQuery& q, u_int_t index, __int64& i )
{
	i = q.getInt64( index );
	return true;
}

inline bool getQueryCol( DbQuery& q, u_int_t index, double& d )
{
	d = q.getDouble( index );
	return true;
}

inline bool getQueryCol( DbQuery& q, u_int_t index, tstring& s )
{
	s = q.getString( index );
	return true;
}

inline bool getQueryCol( DbQuery& q, u_int_t index, ptime& t )
{
	t = q.getTime( index );
	return true;
}

_bt_end

#endif // _DbQuery_H_
