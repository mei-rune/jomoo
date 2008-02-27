
#ifndef _DbExecute_h_
#define _DbExecute_h_

#include "../../util/Variant.h"
#include "../../util/pTime.h"

_bt_begin

class DbExecute {
public:
	virtual ~DbExecute() {}

	virtual bool prepare( const tchar* sql, size_t len, bool reportWarningsAsErrors = true ) = 0;
	virtual bool prepare( const tstring& sql, bool reportWarningsAsErrors = true ) = 0;
	virtual bool exec( ) = 0;
	virtual bool reset( ) = 0;

	virtual bool bind( int index, int value ) = 0;
	virtual bool bind( int index, __int64 value ) = 0;
	virtual bool bind( int index, double value ) = 0;
	virtual bool bind( int index, const char* str , size_t n ) = 0;
	virtual bool bind( int index, const wchar_t* str , size_t n ) = 0;
	virtual bool bind( int index, const ptime& time ) = 0;

	virtual bool bind( const tstring& name, int value ) = 0;
	virtual bool bind( const tstring& name, __int64 value ) = 0;
	virtual bool bind( const tstring& name, double value ) = 0;
	virtual bool bind( const tstring& name, const char* str , size_t n ) = 0;
	virtual bool bind( const tstring& name, const wchar_t* str , size_t n ) = 0;
	virtual bool bind( const tstring& name, const ptime& time ) = 0;

	virtual bool bind( const tchar* name, size_t len, int value ) = 0;
	virtual bool bind( const tchar* name, size_t len, __int64 value ) = 0;
	virtual bool bind( const tchar* name, size_t len, double value ) = 0;
	virtual bool bind( const tchar* name, size_t len, const char* str , size_t n ) = 0;
	virtual bool bind( const tchar* name, size_t len, const wchar_t* str , size_t n ) = 0;
	virtual bool bind( const tchar* name, size_t len, const ptime& time ) = 0;
	virtual int affected_rows( ) = 0;
	virtual bool direct_exec( const tchar* sql, size_t len , bool reportWarningsAsErrors = true ) = 0;
	virtual bool direct_exec( const tstring& sql, bool reportWarningsAsErrors = true ) = 0;
};

_bt_end

#endif // _DbExecute_h_
