
#include "DbQuery_SQLITE.h"
#include "DbConnection_SQLITE.h"
#include "../../util/codecs.h"

#include "include/config.h"
#ifdef _MEMORY_DEBUG 
	#undef THIS_FILE
	#define new	   DEBUG_NEW  
	#define malloc DEBUG_MALLOC  
    static char THIS_FILE[] = __FILE__;  
#endif




_jomoo_db_begin

DbQuery_SQLITE::DbQuery_SQLITE(DbConnection_SQLITE* con, int timeout)
: con_(con)
, stmt_(NULL)
, tail_(NULL)
#ifdef _BOOST_TIME_
, Time_( invailptime )
#endif
, columnTypesReady_( false )
, firstRow_( true )
{
}

DbQuery_SQLITE::~DbQuery_SQLITE()
{
	if ( stmt_ )
	{
		tsqlite3_finalize( stmt_ );
	}
}

bool DbQuery_SQLITE::exec(const char* sql, size_t len, bool reportWarningsAsErrors  )
{
	sql_str_.clear();
	char_to_utf_8( sql ,sql_str_ );
	tail_ = sql_str_.c_str();
	return nextSet();
}

bool DbQuery_SQLITE::exec(const tstring& sql_str, bool reportWarningsAsErrors)
{
	return exec( sql_str.c_str() , sql_str.size() , reportWarningsAsErrors );
}

bool DbQuery_SQLITE::execOne_( )
{
	if (stmt_ != NULL ) tsqlite3_finalize( stmt_ );

	columnTypesReady_ = false;

	if ( tsqlite3_prepare( con_->db_,
		tail_,
		0,
		&stmt_,
		&tail_ ) != SQLITE_OK)
	{
		this->con_->last_error( this->con_->db_ );
		return false;
	}
	return true;
}

bool DbQuery_SQLITE::fetchRow_()
{
	if( stmt_ == NULL ) return false;
	int i = 0;
l:
	switch ( tsqlite3_step( stmt_ ) )
	{
	case SQLITE_ROW:
		break;
	case  SQLITE_BUSY:
		if( i > 5 )
			break;
		i ++;
		tsqlite3_busy_timeout( this->con_->db_,1000 );
		goto l;

	case SQLITE_DONE:
	default:
		{
		this->con_->last_error( this->con_->db_ );
		return false;
		}
	}
	
	return true;
}

bool DbQuery_SQLITE::fetchRow_2()
{
	if( stmt_ == NULL ) return false;
	int i = 0;
l:
	switch ( tsqlite3_step( stmt_ ) )
	{
	case SQLITE_ROW:
		break;
	case  SQLITE_BUSY:
		if( i > 5 )
			break;
		i ++;
		tsqlite3_busy_timeout( this->con_->db_,1000 );
		goto l;

	case SQLITE_DONE:
		firstRow_ = false;
		break;
	default:
		{
		this->con_->last_error( this->con_->db_ );
		return false;
		}
	}
	
	return true;
}

bool DbQuery_SQLITE::nextRow()
{
	if (firstRow_) 
	{
		firstRow_ = false;
		return true;
	}
	return fetchRow_();
}

bool DbQuery_SQLITE::nextSet()
{
	firstRow_ = true;
	if( tail_ && *tail_ )
	{
		if( !execOne_( ) )
			return false;

		if (fetchRow_2()) 
			return true;
	}
	return false;
}

int DbQuery_SQLITE::columns()
{
	fetchColumnTypes_();
	return columns_;
}

bool DbQuery_SQLITE::getBoolean(u_int column)
{
	return (tsqlite3_column_int( stmt_, column ) >= 1);
}

bool DbQuery_SQLITE::getBoolean(const tstring& column)
{
	fetchColumnTypes_();
	return getBoolean(columnPosition_( column ));
}

int DbQuery_SQLITE::getInt(u_int column)
{
	return tsqlite3_column_int( stmt_, column );
}

int DbQuery_SQLITE::getInt(const tstring& column)
{
	fetchColumnTypes_();
	return getInt(columnPosition_( column ));
}

__int64 DbQuery_SQLITE::getInt64(u_int column)
{
	return tsqlite3_column_int64( stmt_, column );
}

__int64 DbQuery_SQLITE::getInt64(const tstring& column)
{
	fetchColumnTypes_();
	return getInt64(columnPosition_( column ));
}

double DbQuery_SQLITE::getDouble(u_int column)
{
	return tsqlite3_column_double( stmt_, column );
}

double DbQuery_SQLITE::getDouble(const tstring& column)
{
	fetchColumnTypes_();
	return getDouble(columnPosition_( column ));
}

const tstring& DbQuery_SQLITE::getString(u_int column)
{
	utf_8_to_char( ( const char* )tsqlite3_column_text( stmt_, column ) , String_ );
	return String_;
}

const tstring& DbQuery_SQLITE::getString(const tstring& column)
{
	fetchColumnTypes_();
	return getString(columnPosition_( column ));
}

#ifdef _BOOST_TIME_
const ptime& DbQuery_SQLITE::getTime(u_int column)
{
	Time_ = boost::posix_time::time_from_string( tstring( ( const char*)tsqlite3_column_text( stmt_, column ) ) );
	return Time_;
}

const ptime& DbQuery_SQLITE::getTime(const tstring& column)
{
	fetchColumnTypes_();
	return getTime(columnPosition_( column ));
}
#endif

const Variant& DbQuery_SQLITE::get(u_int_t column)
{
	fetchColumnTypes_();
	if( column >= columnTypes_.size() )
		throw std::range_error("表的最大列为" + convertIntegerToString( columnTypes_.size() ) );

	switch(columnTypes_[ column ])
	{
	case Variant_Type::INTEGER:
		{
			// Obtain an integer value for column 'i'
			result_ = tsqlite3_column_int( stmt_, column );
			break;
		}

	case Variant_Type::DOUBLE:
		{
			result_ = tsqlite3_column_double( stmt_, column );
		}
		break;

	case Variant_Type::STRING:
		{
			result_ = utf_8_to_char( ( char* ) tsqlite3_column_text( stmt_, column ) );
		}
		break;
#ifdef _BOOST_TIME_
	case Variant_Type::TIME:
		{
			result_ = boost::posix_time::time_from_string( tstring( ( const char*)tsqlite3_column_text( stmt_, column ) ) );
		}
		break;
#endif
	default:
		throw std::runtime_error( "不支持的数据类型" );
	}
	return result_;
}

const Variant& DbQuery_SQLITE::get(const tstring& name)
{
	return get(columnPosition_(name));
}

void DbQuery_SQLITE::fetchColumnTypes_()
{
	if (columnTypesReady_) return;
	columns_ = tsqlite3_column_count( stmt_ );;
	columnTypes_.resize(columns_);
	columnNames_.resize(columns_);
	for(int i=0; i<columns_; ++i)
	{
		const char* colname = tsqlite3_column_name( stmt_ , i );
		if( colname ==  NULL )
			throw std::runtime_error( "取sqlite列名失败" );
		columnNames_[ i ] = colname;
		int t = tsqlite3_column_type( stmt_, i);
		switch( t )
		{
		case SQLITE_INTEGER:
			columnTypes_[i] = Variant_Type::INTEGER;
			break;
		case SQLITE_FLOAT:
			columnTypes_[i] = Variant_Type::DOUBLE;
			break;
		case SQLITE_TEXT:
			columnTypes_[i] = Variant_Type::STRING;
			break;
		case SQLITE_BLOB:
		case SQLITE_NULL:
		default:
			throw std::runtime_error("不支持的数据类型");
		}

	}
	columnTypesReady_ = true;
}

u_int_t DbQuery_SQLITE::columnPosition_(const tstring& columnName)
{
	for( int i=0; i<columns_; ++i)
		if (!tstrcasecmp(columnNames_[i].c_str(), columnName.c_str()))
			return i;
	throw std::invalid_argument( "没有找到" + columnName + "列" );
	return -1;

}

int DbQuery_SQLITE::getColumnType( size_t pos )
{
	return columnTypes_[ pos ];
}

const tstring& DbQuery_SQLITE::getColumnName( size_t pos )
{
	return columnNames_[ pos ];
}

_jomoo_db_end
