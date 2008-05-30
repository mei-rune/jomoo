
#include "DbConnection_SQLITE.h"
#include "DbCommand_SQLITE.h"
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

DbCommand_SQLITE::DbCommand_SQLITE( DbConnection_SQLITE* con )
: con_(con)
, stmt_(NULL)
, tail_(NULL)
{
}

DbCommand_SQLITE::~DbCommand_SQLITE()
{
	if( stmt_ != NULL )
		tsqlite3_finalize( stmt_ );
}

bool DbCommand_SQLITE::prepare( const tchar* sql, size_t len, bool reportWarningsAsErrors )
{
	if( stmt_ != NULL )
	{
		tsqlite3_finalize( stmt_ );
		stmt_ = NULL;
	}
	buffer_.clear();

	std::string utf8 = to_utf8( sql , len );
	std::list< tstring >::iterator it = buffer_.insert( buffer_.begin(), utf8 );

	if( tsqlite3_prepare( con_->db_,
		it->c_str(), 
		( int )len, &stmt_, NULL) == SQLITE_OK )
		return true;
	con_->last_error( con_ ->db_ );
	return false;
}

bool DbCommand_SQLITE::reset( )
{
	buffer_.clear();
	if( stmt_ == NULL )
		return false;
	if( tsqlite3_reset( stmt_ )  == SQLITE_OK )
		return true;
	con_->last_error( con_ ->db_ );
	return false;
}

bool DbCommand_SQLITE::exec( )
{
	int i = 0;
l:
	switch ( tsqlite3_step( stmt_ ) )
	{
	case SQLITE_ROW:
	case SQLITE_DONE:
		return true;
		break;
	case  SQLITE_BUSY:
		if( i > 5 )
			break;
		i ++;
		tsqlite3_busy_timeout( this->con_->db_,1000 );
		goto l;

	default:
		;
	}

	con_->last_error( con_ ->db_ );
	return false;
}

int DbCommand_SQLITE::affected_rows( )
{
	int n = tsqlite3_changes ( con_->db_ );
	if( n < 0 )
		con_->last_error( con_ ->db_ );
	return n;
}

bool DbCommand_SQLITE::direct_exec( const tchar* sql, size_t len , bool reportWarningsAsErrors )
{
	if( !prepare( sql, len , reportWarningsAsErrors ) )
		return false;
	return this->exec( );
}

bool DbCommand_SQLITE::bind( int index, bool value )
{// sqlite3_bind_int
	if(tsqlite3_bind_int( stmt_ , index, value?1:0 ) == SQLITE_OK )
		return true;
	con_->last_error( con_ ->db_ );
	return false;
}

bool DbCommand_SQLITE::bind( int index, int8_t value )
{ //sqlite3_bind_int64
	if( tsqlite3_bind_int( stmt_ , index, value ) == SQLITE_OK )
		return true;
	con_->last_error( con_ ->db_ );
	return false;
}

bool DbCommand_SQLITE::bind( int index, int16_t value )
{ //sqlite3_bind_int64
	if( tsqlite3_bind_int( stmt_ , index, value ) == SQLITE_OK )
		return true;
	con_->last_error( con_ ->db_ );
	return false;
}

bool DbCommand_SQLITE::bind( int index, int32_t value )
{ //sqlite3_bind_int64
	if( tsqlite3_bind_int( stmt_ , index, value ) == SQLITE_OK )
		return true;
	con_->last_error( con_ ->db_ );
	return false;
}

bool DbCommand_SQLITE::bind( int index, int64_t value )
{ //sqlite3_bind_int64
	if( tsqlite3_bind_int64( stmt_ , index, value ) == SQLITE_OK )
		return true;
	con_->last_error( con_ ->db_ );
	return false;
}

bool DbCommand_SQLITE::bind( int index, double value )
{ // sqlite3_bind_double
	if( tsqlite3_bind_double( stmt_ , index, value ) == SQLITE_OK )
		return true;
	con_->last_error( con_ ->db_ );
	return false;
}

bool DbCommand_SQLITE::bind( int index, const char* str, size_t n )
{// sqlite3_bind_text

	//注意， sqlite3_bind_text操作并不拷贝字符串，它只是记住了字符串的地址
	std::list< tstring >::iterator it = buffer_.insert( buffer_.begin(), to_utf8( str, n) );
	if( tsqlite3_bind_text( stmt_ , index, it->c_str(), ( int )it->size() ,NULL ) == SQLITE_OK )
		return true;
	con_->last_error( con_ ->db_ );
	return false;
}

bool DbCommand_SQLITE::bind( int index, const Timestamp& time )
{
	return bind( index, time.epochMicroseconds() );
}

bool DbCommand_SQLITE::bind( int index, const Timespan& time )
{
	return bind( index, time.totalMicroseconds() );
}

bool DbCommand_SQLITE::bind( const tchar* columnName, bool value )
{
		con_->last_error( _T("指定的列名[") + tstring( columnName ) + _T("]不存在!") );
		return false;
}

bool DbCommand_SQLITE::bind( const tchar* columnName, int8_t value )
{
		con_->last_error( _T("指定的列名[") + tstring( columnName ) + _T("]不存在!") );
		return false;
}

bool DbCommand_SQLITE::bind( const tchar* columnName, int16_t value )
{
		con_->last_error( _T("指定的列名[") + tstring( columnName ) + _T("]不存在!") );
		return false;
}

bool DbCommand_SQLITE::bind( const tchar* columnName, int32_t value )
{
		con_->last_error( _T("指定的列名[") + tstring( columnName ) + _T("]不存在!") );
		return false;
}

bool DbCommand_SQLITE::bind( const tchar* columnName, int64_t value )
{
		con_->last_error( _T("指定的列名[") + tstring( columnName ) + _T("]不存在!") );
		return false;
}

bool DbCommand_SQLITE::bind( const tchar* columnName, double value )
{
		con_->last_error( _T("指定的列名[") + tstring( columnName ) + _T("]不存在!") );
		return false;
}

bool DbCommand_SQLITE::bind( const tchar* columnName, const char* str, size_t n )
{
		con_->last_error( _T("指定的列名[") + tstring( columnName ) + _T("]不存在!") );
		return false;
}

bool DbCommand_SQLITE::bind( const tchar* columnName, const Timestamp& time )
{
		con_->last_error( _T("指定的列名[") + tstring( columnName ) + _T("]不存在!") );
		return false;
}

bool DbCommand_SQLITE::bind( const tchar* columnName, const Timespan& time )
{
		con_->last_error( _T("指定的列名[") + tstring( columnName ) + _T("]不存在!") );
		return false;
}

DEFINE_SHARED( DbCommand_SQLITE );

}

_jomoo_db_end

