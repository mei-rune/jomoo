
#ifndef _DbExecute_h_
#define _DbExecute_h_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_db.h"
# include "jomoo/datetime.h"
# include "jomoo/timespan.h"
# include "jomoo/Timestamp.h"

_jomoo_db_begin

class DbExecute {
public:
	virtual ~DbExecute() {}

	virtual bool direct_exec( const tchar* sql, size_t len , bool reportWarningsAsErrors = true ) = 0;
	virtual bool direct_exec( const tstring& sql, bool reportWarningsAsErrors = true ) = 0;

	virtual bool prepare( const tchar* sql, size_t len, bool reportWarningsAsErrors = true ) = 0;
	virtual bool prepare( const tstring& sql, bool reportWarningsAsErrors = true ) = 0;
	virtual bool exec( ) = 0;
	virtual bool reset( ) = 0;
	virtual int affected_rows( ) = 0;

	virtual bool bind( int index, int value ) = 0;
	virtual bool bind( int index, __int64 value ) = 0;
	virtual bool bind( int index, double value ) = 0;
	virtual bool bind( int index, const char* str , size_t n ) = 0;
	virtual bool bind( int index, const wchar_t* str , size_t n ) = 0;

	virtual bool bind( int index, const Timestamp& time ) = 0;

	virtual bool bind( const tstring& name, int value ) = 0;
	virtual bool bind( const tstring& name, __int64 value ) = 0;
	virtual bool bind( const tstring& name, double value ) = 0;
	virtual bool bind( const tstring& name, const char* str , size_t n ) = 0;
	virtual bool bind( const tstring& name, const wchar_t* str , size_t n ) = 0;
	virtual bool bind( const tstring& name, const Timestamp& time ) = 0;

	virtual bool bind( const tchar* name, size_t len, int value ) = 0;
	virtual bool bind( const tchar* name, size_t len, __int64 value ) = 0;
	virtual bool bind( const tchar* name, size_t len, double value ) = 0;
	virtual bool bind( const tchar* name, size_t len, const char* str , size_t n ) = 0;
	virtual bool bind( const tchar* name, size_t len, const wchar_t* str , size_t n ) = 0;
	virtual bool bind( const tchar* name, size_t len, const Timestamp& time ) = 0;

	
	virtual void incRef() = 0;
    virtual void decRef() = 0;
};


_jomoo_db_end

#endif // _DbExecute_h_
