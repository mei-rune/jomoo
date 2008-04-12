

#ifndef _DbConnection_H_
#define _DbConnection_H_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_db.h"

_jomoo_db_begin

class DbConnection;
class DbQuery;
class DbExecute;
class DbConnection2;
class DbQuery2;
class DbExecute2;

typedef boost::shared_ptr<DbConnection> PDbConnection;
typedef boost::shared_ptr<DbQuery>      PDbQuery;
typedef boost::shared_ptr<DbExecute>    PDbExecute;

typedef boost::shared_ptr<DbConnection2> PDbConnection2;
typedef boost::shared_ptr<DbQuery2>      PDbQuery2;
typedef boost::shared_ptr<DbExecute2>    PDbExecute2;

class DbException : public std::runtime_error{};

// Abstract DbConnection class
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
	//
	virtual const tstring& name() const = 0;

};

class DbConnection2 : public DbConnection
{
public:
	virtual ~DbConnection2() {}
		
	// query creation
	virtual PDbQuery2 query2() = 0;

	// execute creation
	virtual PDbExecute2 execute2() = 0;
};

_jomoo_db_end

#endif // _DbConnection_H_
