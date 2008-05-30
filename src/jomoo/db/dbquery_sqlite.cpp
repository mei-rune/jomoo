
#include "DbQuery_SQLITE.h"
#include "jomoo/codecs.h"

#ifdef _MEMORY_DEBUG 
	#undef THIS_FILE
	#define new	   DEBUG_NEW  
	#define malloc DEBUG_MALLOC  
    static char THIS_FILE[] = __FILE__;  
#endif

_jomoo_db_begin

namespace spi
{

static tchar* _typeName[] = 
{
	_T("DB_UNKOWN"),
	_T("DB_TEXT"),
	_T("DB_INTEGER_8"),
	_T("DB_INTEGER_16"),
	_T("DB_INTEGER_32"),
	_T("DB_INTEGER_64"),
	_T("DB_DOUBLE"),
	_T("DB_TIMESTAMP"),
	_T("DB_TIMESPAN"),
	_T("DB_BLOB"),
	_T("DB_NULL")
};

DbQuery_SQLITE::DbQuery_SQLITE(DbConnection_SQLITE* con, int timeout)
: _connection(con)
, _stmt(NULL)
, _pzTail(NULL)
, _columnTypesReady( false )
, _firstRow( true )
{
	if( null_ptr == con )
		ThrowException( NullException );
	_connection->incRef();

}

DbQuery_SQLITE::~DbQuery_SQLITE()
{
	if ( _stmt )
	{
		tsqlite3_finalize( _stmt );
		_stmt = null_ptr;
	}

	release();
}

bool DbQuery_SQLITE::exec(const tchar* sql, size_t len, bool reportWarningsAsErrors  )
{
	if( -1 == len )
		len = string_traits<tchar>::strlen( sql );
	_sql_string = to_utf8( sql, len );
	_pzTail = _sql_string.c_str();
	return nextSet();
}

bool DbQuery_SQLITE::nextSet()
{
	if( null_ptr == _pzTail || null_ptr == *_pzTail )
		return false;
		
	if( !prepare( ) )
			return false;

	return fetchRow( true );
}

bool DbQuery_SQLITE::prepare( )
{
	if (null_ptr != _stmt )
	{
		tsqlite3_finalize( _stmt );
		_stmt = null_ptr;
	}
	_columnTypesReady = false;
	_firstRow = true;

	if (SQLITE_OK != tsqlite3_prepare( _connection->db_,
		_pzTail,
		0,
		&_stmt,
		&_pzTail ) )
	{
		this->_connection->last_error( this->_connection->db_ );
		return false;
	}
	return true;
}

bool DbQuery_SQLITE::fetchRow( bool isFirst )
{
	if( null_ptr == _stmt )
		return false;

	int i = 0;
l:
	switch ( tsqlite3_step( _stmt ) )
	{
	case SQLITE_ROW:
		break;
	case SQLITE_DONE:
		if( isFirst )
		{
			_firstRow = false;
			return true;
		}
		else
		{
			return false;
		}
	case  SQLITE_BUSY:
		if( i > 5 )
			break;
		i ++;
		tsqlite3_busy_timeout( this->_connection->db_,1000 );
		goto l;
	default:
		{
		this->_connection->last_error( this->_connection->db_ );
		return false;
		}
	}

	fetchColumnTypes();
	return true;
}

bool DbQuery_SQLITE::nextRow()
{
	if (_firstRow) 
	{
		_firstRow = false;
		return true;
	}
	return fetchRow( false );
}

size_t DbQuery_SQLITE::columns() const
{
	return _columnItems.size();
}

void DbQuery_SQLITE::fetchColumnTypes()
{
	if (_columnTypesReady)
		return;

	int columns = tsqlite3_column_count( _stmt );;
	_columnItems.resize(columns);

	for(int i=0; i<_columnItems.size(); ++i)
	{
		const char* colname = tsqlite3_column_name( _stmt , i );
		if( colname ==  NULL )
			ThrowException1( DbException, _T("取sqlite列名失败") );

		_columnItems[ i ].columnName = toTstring( colname );

		int t = tsqlite3_column_type( _stmt, i);
		switch( t )
		{
		case SQLITE_INTEGER:
			_columnItems[i].columnType = DB_INTEGER_32;
			break;
		case SQLITE_FLOAT:
			_columnItems[i].columnType = DB_DOUBLE;
			break;
		case SQLITE_TEXT:
			_columnItems[i].columnType = DB_TEXT;
			break;
		case SQLITE_BLOB:
			_columnItems[i].columnType = DB_BLOB;
			break;
		case SQLITE_NULL:
			_columnItems[i].columnType = DB_NULL;
			break;
		default:
			ThrowException1( DbException, _T("不支持的数据类型") );
		}

	}
	_columnTypesReady = true;
}

u_int_t DbQuery_SQLITE::columnPosition(const tchar* columnName)
{
	for( int i=0; i<_columnItems.size(); ++i)
		if ( 0 == string_traits<tchar>::stricmp(_columnItems[i].columnName.c_str(), columnName) )
			return i;

	//ThrowException1( IllegalArgumentException, _T("没有找到") + tstring( columnName ) + _T("列") );
	return -1;
}

int DbQuery_SQLITE::columnType( size_t column ) const
{
	if( _columnItems.size() <= column )
		ThrowException( OutOfRangeException );

	return _columnItems[ column ].columnType;
}

const tchar* DbQuery_SQLITE::columnName( size_t column ) const
{
	if( _columnItems.size() <= column )
		ThrowException( OutOfRangeException );

	return _columnItems[ column ].columnName.c_str();
}


//const variant& DbQuery_SQLITE::get(u_int_t column)
//{
//	fetchColumnTypes();
//	
//	if( _columnItems.size() <= column )
//		ThrowException2( OutOfRangeException, column, _columnItems.size() );
//
//	switch(_columnItems[ column ].columnType )
//	{
//	case DB_INTEGER_32:
//			// Obtain an integer value for column 'i';
//			_variant = tsqlite3_column_int( _stmt, column );
//			break;
//	case DB_DOUBLE:
//			_variant = tsqlite3_column_double( _stmt, column );
//		break;
//	case DB_TEXT:
//			_variant = utf_8_to_char( ( char* ) tsqlite3_column_text( _stmt, column ) );
//		break;
//	case DB_TEXT:
//			_variant = utf_8_to_char( ( char* ) tsqlite3_column_text( _stmt, column ) );
//		break;
//	default:
//			ThrowException1( DbException, _T("不支持的数据类型") );
//	}
//	return _variant;
//}
//
//const variant& DbQuery_SQLITE::get(const tstring& name)
//{
//	return get(columnPosition(name));
//}

bool DbQuery_SQLITE::read(u_int_t column, bool& value)
{
	fetchColumnTypes();
	if( _columnItems.size() <= column )
	{
		_connection->last_error( _T("超出范围[") + toString(_columnItems.size())
			+ _T("],实际[") + toString(column) + _T("]") );
		return false;
	}

	if(DB_INTEGER_32 != _columnItems[ column ].columnType )
	{
		_connection->last_error( _T("数据类型错误,不能将")
			+ tstring(_typeName[_columnItems[ column ].columnType])
			+ _T("转换到DB_INTEGER_32") );
		return false;
	}
	value = 0 != tsqlite3_column_int( _stmt, column );
	return true;
}

bool DbQuery_SQLITE::read(const tchar* columnName, bool& value)
{
	fetchColumnTypes();
	u_int_t index = columnPosition(columnName);
	if( -1 == index )
	{
		_connection->last_error( _T("没有找到") + tstring( columnName ) + _T("列") );
		return false;
	}
	return read( index, value );
}

bool DbQuery_SQLITE::read(u_int_t column, int8_t& value)
{
	fetchColumnTypes();
	if( _columnItems.size() <= column )
	{
		_connection->last_error( _T("超出范围[") + toString(_columnItems.size())
			+ _T("],实际[") + toString(column) + _T("]") );
		return false;
	}

	if(DB_INTEGER_32 != _columnItems[ column ].columnType )
	{
		_connection->last_error( _T("数据类型错误,不能将")
			+ tstring(_typeName[_columnItems[ column ].columnType])
			+ _T("转换到DB_INTEGER_32") );
		return false;
	}
	value = (int8_t) tsqlite3_column_int( _stmt, column );
	return true;
}

bool DbQuery_SQLITE::read(const tchar* columnName, int8_t& value)
{
	fetchColumnTypes();
	u_int_t index = columnPosition(columnName);
	if( -1 == index )
	{
		_connection->last_error( _T("没有找到") + tstring( columnName ) + _T("列") );
		return false;
	}
	return read( index, value );
}


bool DbQuery_SQLITE::read(u_int_t column, int16_t& value)
{
	fetchColumnTypes();
	if( _columnItems.size() <= column )
	{
		_connection->last_error( _T("超出范围[") + toString(_columnItems.size())
			+ _T("],实际[") + toString(column) + _T("]") );
		return false;
	}

	if(DB_INTEGER_32 != _columnItems[ column ].columnType )
	{
		_connection->last_error( _T("数据类型错误,不能将")
			+ tstring(_typeName[_columnItems[ column ].columnType])
			+ _T("转换到DB_INTEGER_32") );
		return false;
	}
	value = (int16_t) tsqlite3_column_int( _stmt, column );
	return true;
}

bool DbQuery_SQLITE::read(const tchar* columnName, int16_t& value)
{
	fetchColumnTypes();
	u_int_t index = columnPosition(columnName);
	if( -1 == index )
	{
		_connection->last_error( _T("没有找到") + tstring( columnName ) + _T("列") );
		return false;
	}
	return read( index, value );
}

bool DbQuery_SQLITE::read(u_int_t column, int32_t& value)
{
	fetchColumnTypes();
	if( _columnItems.size() <= column )
	{
		_connection->last_error( _T("超出范围[") + toString(_columnItems.size())
			+ _T("],实际[") + toString(column) + _T("]") );
		return false;
	}

	if(DB_INTEGER_32 != _columnItems[ column ].columnType )
	{
		_connection->last_error( _T("数据类型错误,不能将")
			+ tstring(_typeName[_columnItems[ column ].columnType])
			+ _T("转换到DB_INTEGER_32") );
		return false;
	}
	value = tsqlite3_column_int( _stmt, column );
	return true;
}

bool DbQuery_SQLITE::read(const tchar* columnName, int32_t& value)
{
	fetchColumnTypes();
	u_int_t index = columnPosition(columnName);
	if( -1 == index )
	{
		_connection->last_error( _T("没有找到") + tstring( columnName ) + _T("列") );
		return false;
	}
	return read( index, value );
}

bool DbQuery_SQLITE::read(u_int_t column, int64_t& value)
{
	fetchColumnTypes();
	if( _columnItems.size() <= column )
	{
		_connection->last_error( _T("超出范围[") + toString(_columnItems.size())
			+ _T("],实际[") + toString(column) + _T("]") );
		return false;
	}

	if(DB_INTEGER_32 != _columnItems[ column ].columnType )
	{
		_connection->last_error( _T("数据类型错误,不能将")
			+ tstring(_typeName[_columnItems[ column ].columnType])
			+ _T("转换到DB_INTEGER_32") );
		return false;
	}
	value = tsqlite3_column_int64( _stmt, column );
	return true;
}

bool DbQuery_SQLITE::read(const tchar* columnName, int64_t& value)
{
	fetchColumnTypes();
	u_int_t index = columnPosition(columnName);
	if( -1 == index )
	{
		_connection->last_error( _T("没有找到") + tstring( columnName ) + _T("列") );
		return false;
	}
	return read( index, value );
}

bool DbQuery_SQLITE::read(u_int_t column, Timestamp& value)
{
	int64_t v = 0;
	if( read( column, v ) )
	{
		value = v;
		return true;
	}
	return false;
}

bool DbQuery_SQLITE::read(const tchar* columnName, Timestamp& value)
{
	fetchColumnTypes();
	u_int_t index = columnPosition(columnName);
	if( -1 == index )
	{
		_connection->last_error( _T("没有找到") + tstring( columnName ) + _T("列") );
		return false;
	}
	return read( index, value );
}

bool DbQuery_SQLITE::read(u_int_t column, Timespan& value)
{
	int64_t v = 0;
	if( read( column, v ) )
	{
		value = v;
		return true;
	}
	return false;
}

bool DbQuery_SQLITE::read(const tchar* columnName, Timespan& value)
{
	fetchColumnTypes();
	u_int_t index = columnPosition(columnName);
	if( -1 == index )
	{
		_connection->last_error( _T("没有找到") + tstring( columnName ) + _T("列") );
		return false;
	}
	return read( index, value );
}

bool DbQuery_SQLITE::read(u_int_t column, double& value)
{
	fetchColumnTypes();
	if( _columnItems.size() <= column )
	{
		_connection->last_error( _T("超出范围[") + toString(_columnItems.size())
			+ _T("],实际[") + toString(column) + _T("]") );
		return false;
	}

	if(DB_DOUBLE != _columnItems[ column ].columnType )
	{
		_connection->last_error( _T("数据类型错误,不能将")
			+ tstring(_typeName[_columnItems[ column ].columnType])
			+ _T("转换到DB_DOUBLE") );
		return false;
	}
	value = tsqlite3_column_double( _stmt, column );
	return true;
}

bool DbQuery_SQLITE::read(const tchar* columnName, double& value)
{
	fetchColumnTypes();
	u_int_t index = columnPosition(columnName);
	if( -1 == index )
	{
		_connection->last_error( _T("没有找到") + tstring( columnName ) + _T("列") );
		return false;
	}
	return read( index, value );
}

int DbQuery_SQLITE::read(u_int_t column, char* buf, size_t& len )
{
	fetchColumnTypes();
	if( _columnItems.size() <= column )
	{
		_connection->last_error( _T("超出范围[") + toString(_columnItems.size())
			+ _T("],实际[") + toString(column) + _T("]") );
		return DB_NOTFOUND;
	}

	if(DB_TEXT != _columnItems[ column ].columnType )
	{
		_connection->last_error( _T("数据类型错误,不能将")
			+ tstring(_typeName[_columnItems[ column ].columnType])
			+ _T("转换到DB_TEXT") );
		return DB_MISMATCH;
	}
	
	size_t bufLength = len;
	len = sqlite3_column_bytes(_stmt, column);
	const char* txt = (const char*)tsqlite3_column_text( _stmt, column);
	if( try_from_utf8( txt, len, buf, bufLength, len ) )
		return DB_OK;
	return DB_INSUFFICIENT;
}

int DbQuery_SQLITE::read(const tchar* columnName, char* buf, size_t& len )
{
	fetchColumnTypes();
	u_int_t index = columnPosition(columnName);
	if( -1 == index )
	{
		_connection->last_error( _T("没有找到") + tstring( columnName ) + _T("列") );
		return DB_NOTFOUND;
	}
	return read( index, buf, len );
}

int DbQuery_SQLITE::readBLOB(u_int_t column, void* buf, size_t& len )
{
	fetchColumnTypes();
	if( _columnItems.size() <= column )
	{
		_connection->last_error( _T("超出范围[") + toString(_columnItems.size())
			+ _T("],实际[") + toString(column) + _T("]") );
		return DB_NOTFOUND;
	}

	if(DB_BLOB != _columnItems[ column ].columnType )
	{
		_connection->last_error( _T("数据类型错误,不能将")
			+ tstring(_typeName[_columnItems[ column ].columnType])
			+ _T("转换到DB_BLOB") );
		return DB_MISMATCH;
	}
	
	size_t bufLength = len;
	len = sqlite3_column_bytes(_stmt, column);
	if( bufLength < len)
		return DB_INSUFFICIENT;

	::memcpy_s( buf,bufLength
		, tsqlite3_column_blob( _stmt, column), len );
	return DB_OK;
}

int DbQuery_SQLITE::readBLOB(const tchar* columnName, void* buf, size_t& len )
{
	fetchColumnTypes();
	u_int_t index = columnPosition(columnName);
	if( -1 == index )
	{
		_connection->last_error( _T("没有找到") + tstring( columnName ) + _T("列") );
		return DB_NOTFOUND;
	}
	return readBLOB( index, buf, len );
}

bool DbQuery_SQLITE::readLength(u_int_t column, size_t& len )
{
	fetchColumnTypes();
	if( _columnItems.size() <= column )
	{
		_connection->last_error( _T("超出范围[") + toString(_columnItems.size())
			+ _T("],实际[") + toString(column) + _T("]") );
		return false;
	}

	DBType type = _columnItems[ column ].columnType;
	if(DB_BLOB != type && DB_TEXT != type )
	{
		_connection->last_error( _T("数据类型错误,不能将")
			+ tstring(_typeName[_columnItems[ column ].columnType])
			+ _T("转换到DB_BLOB或DB_TEXT") );
		return false;
	}

	len = sqlite3_column_bytes(_stmt, column);
	return true;
}

bool DbQuery_SQLITE::readLength(const tchar* columnName, size_t& len )
{
	fetchColumnTypes();
	u_int_t index = columnPosition(columnName);
	if( -1 == index )
	{
		_connection->last_error( _T("没有找到") + tstring( columnName ) + _T("列") );
		return false;
	}
	return readLength( index, len );
}

}

_jomoo_db_end
