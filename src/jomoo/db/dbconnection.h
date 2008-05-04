

#ifndef _DbConnection_H_
#define _DbConnection_H_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_db.h"
# include "jomoo/counter_ptr.hpp"
# include "jomoo/exception.hpp"

_jomoo_db_begin

enum DBType
{
	UNKOWN,
	STRING,
	INTEGER_8,
	INTEGER_16,
	INTEGER_32,
	INTEGER_64,
	DOUBLE,
	TIME
};

class DbConnection;
class DbQuery;
class DbExecute;

typedef intrusive_ptr<DbConnection> PDbConnection;
typedef intrusive_ptr<DbQuery>      PDbQuery;
typedef intrusive_ptr<DbExecute>    PDbExecute;

MakeException( DbException , _T("数据库操作发生错误!") );

class DbConnection
{
public:
	virtual ~DbConnection() {}

	// connects
	virtual bool open(const tstring& parameters) = 0;
	virtual void close() = 0;
	virtual bool uses(const tstring& database) = 0;

	// query creation
	virtual PDbQuery query() = 0;

	// execute creation
	virtual PDbExecute execute() = 0;

	// transactions
	virtual bool begin()    = 0;
	virtual bool commit()   = 0;
	virtual bool rollback() = 0;

	virtual const tstring& last_error() const = 0;
	virtual const tstring& name() const = 0;

	virtual void incRef() = 0;
    virtual void decRef() = 0;
};


_jomoo_db_end

#endif // _DbConnection_H_
