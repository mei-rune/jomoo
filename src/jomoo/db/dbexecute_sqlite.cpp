
#include "DbConnection_SQLITE.h"
#include "DbExecute_SQLITE.h"
#include "../../util/codecs.h"

#include "include/config.h"
#ifdef _MEMORY_DEBUG 
	#undef THIS_FILE
	#define new	   DEBUG_NEW  
	#define malloc DEBUG_MALLOC  
    static char THIS_FILE[] = __FILE__;  
#endif





_jomoo_db_begin

DbExecute_SQLITE::DbExecute_SQLITE( DbConnection_SQLITE* con )
: con_(con)
, stmt_(NULL)
, tail_(NULL)
{
}

DbExecute_SQLITE::~DbExecute_SQLITE()
{
	if( stmt_ != NULL )
		tsqlite3_finalize( stmt_ );
}

bool DbExecute_SQLITE::prepare( const tchar* sql, size_t len, bool reportWarningsAsErrors )
{
	if( stmt_ != NULL )
	{
		tsqlite3_finalize( stmt_ );
		stmt_ = NULL;
	}
	buffer_.clear();

	std::string utf8;
	std::list< tstring >::iterator it = buffer_.insert( buffer_.begin(), utf8 );
	char_to_utf_8( sql ,*it );

	if( tsqlite3_prepare( con_->db_,
		it->c_str(), 
		( int )len, &stmt_, NULL) == SQLITE_OK )
		return true;
	con_->last_error( con_ ->db_ );
	return false;
}

bool DbExecute_SQLITE::prepare(const tstring& sql, bool reportWarningsAsErrors ) 
{
	return prepare( sql.c_str(), sql.size() , reportWarningsAsErrors );
}

bool DbExecute_SQLITE::reset( )
{
	buffer_.clear();
	if( stmt_ == NULL )
		return false;
	if( tsqlite3_reset( stmt_ )  == SQLITE_OK )
		return true;
	con_->last_error( con_ ->db_ );
	return false;
}

bool DbExecute_SQLITE::exec( )
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

bool DbExecute_SQLITE::bind( int index, int value )
{// sqlite3_bind_int
	if(tsqlite3_bind_int( stmt_ , index, value ) == SQLITE_OK )
		return true;
	con_->last_error( con_ ->db_ );
	return false;
}

bool DbExecute_SQLITE::bind( int index, __int64 value )
{ //sqlite3_bind_int64
	if( tsqlite3_bind_int64( stmt_ , index, value ) == SQLITE_OK )
		return true;
	con_->last_error( con_ ->db_ );
	return false;
}

bool DbExecute_SQLITE::bind( int index, double value )
{ // sqlite3_bind_double
	if( tsqlite3_bind_double( stmt_ , index, value ) == SQLITE_OK )
		return true;
	con_->last_error( con_ ->db_ );
	return false;
}

bool DbExecute_SQLITE::bind( int index, const char* str, size_t n )
{// sqlite3_bind_text

	//注意， sqlite3_bind_text操作并不拷贝字符串，它只是记住了字符串的地址
	std::string utf8;
	std::list< tstring >::iterator it = buffer_.insert( buffer_.begin(), utf8 );
	char_to_utf_8( str ,*it );
	if( tsqlite3_bind_text( stmt_ , index, it->c_str(), ( int )it->size() ,NULL ) == SQLITE_OK )
		return true;
	con_->last_error( con_ ->db_ );
	return false;
}



bool DbExecute_SQLITE::bind( int index, const wchar_t* str, size_t n )
{ // sqlite3_bind_text16
	if( tsqlite3_bind_text16( stmt_ , index, str, ( int )n  ,NULL ) == SQLITE_OK )
		return true;
	con_->last_error( con_ ->db_ );
	return false;
}

#ifdef _BOOST_TIME_
bool DbExecute_SQLITE::bind( int index, const ptime& time )
{
	tstring timestr = boost::posix_time::to_iso_extended_string( time );
	return bind( index,timestr.c_str(), timestr.size() );
}
#endif

bool DbExecute_SQLITE::bind( const tchar* name, size_t len, int value )
{
	int index = tsqlite3_bind_parameter_index( stmt_, name );
	if( index == 0 )
	{
		con_->last_error( "指定的列名[" + tstring( name ) + "]不存在!" );
		return false;
	}

	return bind( index, value );
}

bool DbExecute_SQLITE::bind( const tstring& name, int value )
{
	return bind( name.c_str(),name.size(), value );
}

bool DbExecute_SQLITE::bind( const tchar* name, size_t len, __int64 value )
{
	int index = tsqlite3_bind_parameter_index( stmt_, name );
	if( index == 0 )
	{
		con_->last_error( "指定的列名[" + tstring( name ) + "]不存在!" );
		return false;
	}

	return bind( index, value );
}

bool DbExecute_SQLITE::bind( const tstring& name, __int64 value )
{
	return bind( name.c_str(),name.size(), value );
}

bool DbExecute_SQLITE::bind( const tchar* name, size_t len, double value )
{
	int index = tsqlite3_bind_parameter_index( stmt_, name );
	if( index == 0 )
	{
		con_->last_error( "指定的列名[" + tstring( name ) + "]不存在!" );
		return false;
	}

	return bind( index, value );
}

bool DbExecute_SQLITE::bind( const tstring& name, double value )
{
	return bind( name.c_str(),name.size(), value );
}

bool DbExecute_SQLITE::bind( const tchar* name, size_t len, const char* str , size_t n )
{
	int index = tsqlite3_bind_parameter_index( stmt_, name );
	if( index == 0 )
	{
		con_->last_error( "指定的列名[" + tstring( name ) + "]不存在!" );
		return false;
	}

	return bind( index, str ,n );
}

bool DbExecute_SQLITE::bind( const tstring& name, const char* str , size_t n )
{
	return bind( name.c_str(),name.size(), str ,n );
}

bool DbExecute_SQLITE::bind( const tchar* name, size_t len, const wchar_t* str , size_t n )
{
	int index = tsqlite3_bind_parameter_index( stmt_, name );
	if( index == 0 )
	{
		con_->last_error( "指定的列名[" + tstring( name ) + "]不存在!" );
		return false;
	}

	return bind( index, str ,n );
}

bool DbExecute_SQLITE::bind( const tstring& name, const wchar_t* str , size_t n )
{
	return bind( name.c_str(), name.size(), str ,n );
}

#ifdef _BOOST_TIME_
bool DbExecute_SQLITE::bind( const tchar* name, size_t len, const ptime& time )
{
	int index = tsqlite3_bind_parameter_index( stmt_, name );
	if( index == 0 )
	{
		con_->last_error( "指定的列名[" + tstring( name ) + "]不存在!" );
		return false;
	}

	return bind( index, time );
}

bool DbExecute_SQLITE::bind( const tstring& name, const ptime& time )
{
	return bind( name.c_str(),name.size(), time );
}
#endif

int DbExecute_SQLITE::affected_rows( )
{
	int n = tsqlite3_changes ( con_->db_ );
	if( n < 0 )
		con_->last_error( con_ ->db_ );
	return n;
}

bool DbExecute_SQLITE::direct_exec( const tchar* sql, size_t len , bool reportWarningsAsErrors )
{
	if( !prepare( sql, len , reportWarningsAsErrors ) )
		return false;
	return this->exec( );
}

bool DbExecute_SQLITE::direct_exec( const tstring& sql, bool reportWarningsAsErrors )
{
	return direct_exec( sql.c_str(),sql.size(), reportWarningsAsErrors );
}

_jomoo_db_end

