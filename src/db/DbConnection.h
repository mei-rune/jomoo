

#ifndef _DbConnection_H_
#define _DbConnection_H_

#include "../../def.h"
#include "../../tstring.h"
#include "boost/shared_ptr.hpp"

_bt_begin

class DbConnection;
class DbQuery;
class DbExecute;

typedef boost::shared_ptr<DbConnection> PDbConnection;
typedef boost::shared_ptr<DbQuery>      PDbQuery;
typedef boost::shared_ptr<DbExecute>    PDbExecute;

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

_bt_end

#endif // _DbConnection_H_
