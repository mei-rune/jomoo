
#include <windows.h>
#include "DbQuery_ODBC.h"
#include "DbConnection_ODBC.h"

#include "include/config.h"
#ifdef _MEMORY_DEBUG 
	#undef THIS_FILE
	#define new	   DEBUG_NEW  
	#define malloc DEBUG_MALLOC  
    static char THIS_FILE[] = __FILE__;  
#endif




_jomoo_db_begin

DbQuery_ODBC::DbQuery_ODBC(DbConnection_ODBC* con, int timeout)
: con_(con)
, rowReady_(false)
, errorThrown_(false)
#ifdef _BOOST_TIME_
, Time_( invailptime )
#endif
{
	// Allocate a statement handle
	SQLRETURN r = SQLAllocHandle(
		SQL_HANDLE_STMT,             // HandleType
		con_->dbc_,                  // InputHandle
		&dbs_);                      // OutputHandlePtr
	if (SQLERROR(r))
	{
		throw std::runtime_error( "取得odbc执行句柄失败" );
	}

	// Make sure we are in Forward Only cursor
	r = SQLSetStmtAttr(
		dbs_,                                 // StatementHandle
		SQL_ATTR_CURSOR_TYPE,                 // Attribute
		(SQLPOINTER)SQL_CURSOR_FORWARD_ONLY,  // ValuePtr
		SQL_IS_UINTEGER);                     // StringLength
	if (SQLERROR(r))
	{
		reportError_("设置odbc执行句柄光标属性失败");
		SQLFreeHandle(SQL_HANDLE_STMT, dbs_);
		throw std::runtime_error( con->last_error() );
	}
	//// Make sure we are in synchronous mode
	//r = SQLSetStmtAttr(
	//	dbs_,                                 // StatementHandle
	//	SQL_ATTR_ASYNC_ENABLE,                // Attribute
	//	(SQLPOINTER)SQL_ASYNC_ENABLE_OFF,     // ValuePtr
	//	SQL_IS_UINTEGER);                     // StringLength
	//if (SQLERROR(r))
	//{
	//	SQLFreeHandle(SQL_HANDLE_STMT, dbs_);
	//	throw std::runtime_error("设置odbc执行句柄异步属性失败");
	//}
	// Change the time out
	//SQLUINTEGER sqlTimeout = timeout;
	//r = SQLSetStmtAttr(
	//	dbs_,                                 // StatementHandle
	//	SQL_ATTR_QUERY_TIMEOUT,               // Attribute
	//	(SQLPOINTER)sqlTimeout,               // ValuePtr
	//	SQL_IS_UINTEGER);                     // StringLength
	//if (SQLERROR(r))
	//{
	//	reportError_("设置odbc执行句柄超时属性失败");
	//	SQLFreeHandle(SQL_HANDLE_STMT, dbs_);
	//	throw std::runtime_error( con->last_error() );
	//}
}

DbQuery_ODBC::~DbQuery_ODBC()
{
	if (!errorThrown_)
	{
		// Browse all the result sets until no more data is available
		// !! Special case for SQL which returns only an empty result
		//    set. If there was at least one non empty result set, we 
		//    should be on it, and columns_ contains its number of columns.
		//    This if columns_==0, no non-empty result set was found at all.

		if (columns_)
		{
			for(;;)
			{
				for(;;)
				{
					if (!nextRow()) break;
				}
				if (!nextSet()) break;
			}
		}
	}
	//
	SQLFreeHandle(SQL_HANDLE_STMT, dbs_);
}

bool DbQuery_ODBC::exec( const char* sql, size_t len, bool reportWarningsAsErrors)
{
	rowReady_         = false;
	columnTypesReady_ = false;
	//
	SQLCHAR    *sqlText = (SQLCHAR*)sql;
	SQLSMALLINT sqlTextSize = (SQLSMALLINT)len;
	SQLRETURN r = SQLExecDirect(
		dbs_,                        // StatementHandle
		sqlText,                     // StatementText
		sqlTextSize);                // TextLength

	switch(r) {
	case SQL_SUCCESS:
	case SQL_NO_DATA:
		return firstRow_();

	case SQL_SUCCESS_WITH_INFO:
		if (reportWarningsAsErrors)
		{
			reportError_("在执行语句 '"+tstring( sql )+"'时");
		}
		else
		{
			return firstRow_();
		}
		break;

	default:
		reportError_("在执行语句 '"+tstring(sql)+"'时");
	}
	return false;

	// Note: Even when SQLExecDirect returns SQL_NO_DATA we
	// must try to get some data with firstRow_() because the
	// behaviour of the "NO DATA" flag is erratic :
	// - sometimes it means "no data at all"
	// - sometimes it means "no data on the first result set"
	//   (but maybe some data in further sets)
}

bool DbQuery_ODBC::exec( const tstring& sql,bool reportWarningsAsErrors  )
{
	return exec( sql.c_str(), sql.size(), reportWarningsAsErrors );
}

void DbQuery_ODBC::reportError_(const tstring& message)
{
	errorThrown_ = true;
	con_->reportError_(message, SQL_HANDLE_STMT, dbs_);
}

bool DbQuery_ODBC::firstRow_()
{
	SQLSMALLINT count;
	SQLRETURN   r;

	for(;;)
	{
		// Obtain size of result set
		r = SQLNumResultCols(dbs_, &count);
		if (SQLERROR(r)) return false;

		columns_ = count;

		// If no columns, we shall skip this empty data set
		// Otherwise we're done
		if (columns_) break;

		if (!nextSet_())
			return false;
	}

	return true;
}

bool DbQuery_ODBC::nextRow()
{
	rowReady_ = false;
	//
	SQLRETURN r = SQLFetch(dbs_);
	switch(r) {
	case SQL_SUCCESS:
	case SQL_SUCCESS_WITH_INFO:
		return true;

	case SQL_NO_DATA:
		return false;

	default:
		reportError_("在取一新行时");
	};
	return false;
}

bool DbQuery_ODBC::nextSet()
{
	if (nextSet_())
	{
		return firstRow_();
	}
	return false;
}

bool DbQuery_ODBC::nextSet_()
{
	columnTypesReady_ = false;
	//
	SQLRETURN r = SQLMoreResults(dbs_);
	switch(r) {
	case SQL_SUCCESS:
	case SQL_SUCCESS_WITH_INFO:
		return true;

	case SQL_NO_DATA:
		return false;

	default:
		reportError_("当取一新记录集时");
	};
	return false;
}

int DbQuery_ODBC::columns()
{
	return columns_;
}

const Variant& DbQuery_ODBC::get(u_int_t column)
{
	fetchRow_();
	if (column >= row_.size())
	{
		throw std::range_error("表的最大列为" + convertIntegerToString( row_.size() ) );
	}
	return row_[column];
}

const Variant& DbQuery_ODBC::get(const tstring& name)
{
	return get(columnPosition_(name));
}

void DbQuery_ODBC::fetchRow_()
{
	if (rowReady_) return;
	fetchColumnTypes_();

	// The row was not already fetched. Get the values now.
	row_.resize(columns_);
	for(int i=0; i<columns_; ++i)
	{
		Variant& result = row_[i];

		switch(columnTypes_[i]) {
	  case Variant_Type::INTEGER:
		  {
			  // Obtain an integer value for column 'i'
			  SQLINTEGER value;
			  SQLINTEGER indicator;

			  SQLRETURN r = SQLGetData(
				  dbs_,             // StatementHandle
				  i+1,              // ColumnNumber
				  SQL_C_SLONG,      // TargetType
				  &value,           // TargetValuePtr
				  sizeof(value),    // BufferLength
				  &indicator);      // StrLen_or_IndPtr

			  switch(r) {
	  case SQL_SUCCESS:
	  case SQL_SUCCESS_WITH_INFO:
		  if (indicator == SQL_NULL_DATA)
			  result = 0;
		  else
			  result = value;
		  break;

	  default:
		  reportError_("while fetching an integer column value");
			  };
		  }
		  break;

	  case Variant_Type::DOUBLE:
		  {
			  // Obtain a double value for column 'i'
			  SQLDOUBLE  value;
			  SQLINTEGER indicator;

			  SQLRETURN r = SQLGetData(
				  dbs_,             // StatementHandle
				  i+1,              // ColumnNumber
				  SQL_C_DOUBLE,     // TargetType
				  &value,           // TargetValuePtr
				  sizeof(value),    // BufferLength
				  &indicator);      // StrLen_or_IndPtr

			  switch(r) {
	  case SQL_SUCCESS:
	  case SQL_SUCCESS_WITH_INFO:
		  if (indicator == SQL_NULL_DATA)
			  result = 0.0;
		  else
			  result = value;
		  break;

	  default:
		  reportError_("while fetching a double column value");
			  };
		  }
		  break;

	  case Variant_Type::STRING:
		  {
			  SQLCHAR    value[256];
			  SQLINTEGER indicator;

			  SQLRETURN r = SQLGetData(
				  dbs_,             // StatementHandle
				  i+1,              // ColumnNumber
				  SQL_C_CHAR,       // TargetType
				  value,            // TargetValuePtr
				  255,              // BufferLength
				  &indicator);      // StrLen_or_IndPtr

			  switch(r) {
	  case SQL_SUCCESS:
	  case SQL_SUCCESS_WITH_INFO:
		  if (indicator == SQL_NULL_DATA)
			  result = tstring("");
		  else
			  result = tstring((char*)value);
		  break;

	  default:
		  reportError_("while fetching an string column value");
			  };
		  }
		  break;

	  case Variant_Type::TIME:
		  {
#ifdef _BOOST_TIME_
			  SQLCHAR    value[256];
			  SQLINTEGER indicator;

			  SQLRETURN r = SQLGetData(
				  dbs_,             // StatementHandle
				  i+1,              // ColumnNumber
				  SQL_C_CHAR,       // TargetType
				  value,            // TargetValuePtr
				  255,              // BufferLength
				  &indicator);      // StrLen_or_IndPtr

			  switch(r)
			  {
				case SQL_SUCCESS:
				case SQL_SUCCESS_WITH_INFO:
					if (indicator == SQL_NULL_DATA)
						result = invailptime;
					else
						result = boost::posix_time::time_from_string( (char*)value );
					break;
				default:
					reportError_("while fetching an string column value");
			  };
#endif
		  }
		  break;

	  default:
		  throw std::runtime_error( "不支持的数据类型" );
		}
	}

	rowReady_ = true;
}

void DbQuery_ODBC::fetchColumnTypes_()
{
	if (columnTypesReady_) return;

	// the collumn data types was not already fetched. Get them now.
	columnTypes_.resize(columns_);
	columnNames_.resize(columns_);
	columnPositions_.clear();
	for(int i=0; i<columns_; ++i)
	{
		// Obtain data type for column 'i'
		SQLCHAR     columnName[50];
		SQLSMALLINT columnNameLength;
		SQLSMALLINT dataType;
		SQLUINTEGER columnSize;
		SQLSMALLINT decimalDigit;
		SQLSMALLINT nullable;

		SQLRETURN r = SQLDescribeCol(
			dbs_,                 // StatementHandle
			i+1,                  // ColumnNumber
			columnName,           // ColumnName
			50,                   // BufferLength
			&columnNameLength,    // NameLengthPtr
			&dataType,            // DataTypePtr
			&columnSize,          // ColumnSizePtr
			&decimalDigit,        // DecimalDigitsPtr
			&nullable);           // NullablePtr

		switch(r) {
	  case SQL_SUCCESS:
	  case SQL_SUCCESS_WITH_INFO:
		  // Ok, continue
		  break;

	  default:
		  reportError_("while fetching an string column value");
		};
		columnNames_[i] = tstring((const char*)columnName, columnNameLength);

		switch(dataType) {
	  case SQL_CHAR:
	  case SQL_VARCHAR:
	  case -1:
	  case -9:
		  columnTypes_[i] = Variant_Type::STRING;
		  break;
	  case SQL_SMALLINT:
	  case SQL_INTEGER:
	  case SQL_TINYINT:
		  columnTypes_[i] = Variant_Type::INTEGER;
		  break;
	  case SQL_NUMERIC:
	  case SQL_DECIMAL:
	  case SQL_REAL:
	  case SQL_FLOAT:
	  case SQL_DOUBLE:
		  columnTypes_[i] = Variant_Type::DOUBLE;
		  break;
	  case SQL_TYPE_TIMESTAMP:
		  columnTypes_[i] = Variant_Type::TIME;
		  break;

	  default:
		  throw std::runtime_error("[" + columnNames_[i] + "]不支持的数据类型[" + convertIntegerToString( dataType ) + "]");
		};
	}

	columnTypesReady_ = true;
}

u_int_t DbQuery_ODBC::columnPosition_(const tstring& columnName)
{
	fetchColumnTypes_();

	ColumnPositions::iterator i=columnPositions_.find(columnName);
	if (i == columnPositions_.end())
	{
		throw std::invalid_argument( "没有找到" + columnName + "列" );
	}
	return i->second;
}

bool DbQuery_ODBC::getBoolean(u_int_t column)
{
	bool value = 0;
	boost::apply_visitor( Variant_Bool_Visitor( value ), get( column ) );
	return value;
}

bool DbQuery_ODBC::getBoolean(const tstring& column)
{
	return getBoolean(columnPosition_( column ));
}


int DbQuery_ODBC::getInt(u_int_t column)
{
	int value = 0;
	boost::apply_visitor( Variant_Int_Visitor( value ), get( column ) );
	return value;
}

int DbQuery_ODBC::getInt(const tstring& column)
{
	return getInt(columnPosition_( column ));
}

__int64 DbQuery_ODBC::getInt64(u_int_t column)
{
	__int64 value = 0;
	boost::apply_visitor( Variant_Int64_Visitor( value ), get( column ) );
	return value;
}

__int64 DbQuery_ODBC::getInt64(const tstring& column)
{
	return getInt64(columnPosition_( column ));
}

double DbQuery_ODBC::getDouble(u_int_t column)
{
	double value = 0;
	boost::apply_visitor( Variant_Double_Visitor( value ), get( column ) );
	return value;
}

double DbQuery_ODBC::getDouble(const tstring& column)
{
	return getDouble(columnPosition_( column ));
}

const tstring& DbQuery_ODBC::getString(u_int_t column)
{
	boost::apply_visitor( Variant_String_Visitor( String_ ), get( column ) );
	return String_;
}

const tstring& DbQuery_ODBC::getString(const tstring& column)
{
	return getString(columnPosition_( column ));
}

#ifdef _BOOST_TIME_
const ptime& DbQuery_ODBC::getTime(u_int_t column)
{
	boost::apply_visitor( Variant_Time_Visitor( Time_ ), get( column ) );
	return Time_;
}

const ptime& DbQuery_ODBC::getTime(const tstring& column)
{
	return getTime(columnPosition_( column ));
}
#endif

int DbQuery_ODBC::getColumnType( size_t pos )
{
	fetchColumnTypes_();
	if ( pos == columnTypes_.size())
	{
		throw std::invalid_argument( "没有找到" + convertIntegerToString( pos ) + "列" );
	}
	return columnTypes_[ pos ];

}

const tstring& DbQuery_ODBC::getColumnName( size_t pos )
{
	fetchColumnTypes_();
	if ( pos == columnNames_.size())
	{
		throw std::invalid_argument( "没有找到" + convertIntegerToString( pos ) + "列"  );
	}
	return columnNames_[ pos ];
}
_jomoo_db_end
