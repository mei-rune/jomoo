
/**
* -*- C++ -*-
* -------------------------------------------------------------------------------
* - ��q�Шr �q�Шr						_utf8encoding.h,v 1.0 2008/05/15 21:11:54
*  �u�������� �q�q �Шr
* ���������| �t------
* -------------------------------------------------------------------------------
*/

# ifndef _utf8encoding_h_
# define _utf8encoding_h_


# include "jomoo/config.h"

# if !defined (JOMOO_LACKS_PRAGMA_ONCE)
#  pragma once
# endif /* JOMOO_LACKS_PRAGMA_ONCE */

# include "jomoo/exception.hpp"

_jomoo_begin

MakeException( EncodingException , _T("�������:") );

void to_unicode( const char* from, size_t len, std::wstring& to )
{
	to.resize( 2 * len + 100 );
	int wLen = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, from,len, ( wchar_t* )to.c_str(), to.size() );
	if( 0 != wLen )
	{
		to.resize( wLen );
		return;
	}

	DWORD err = ::GetLastError();
	if( ERROR_INSUFFICIENT_BUFFER != err )
		ThrowException1( EncodingException, lastError( err ) );

	// ���㳤��
	wLen = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, from,len, NULL, 0 );
	if( 0 == wLen )
		ThrowException1( EncodingException, lastError( ) );

	to.resize( wLen + 10 );
	wLen = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, from,len, ( wchar_t* )to.c_str(), to.size() );
	if( 0 == wLen )
		ThrowException1( EncodingException, lastError( ) );

	to.resize( wLen );
}

void encode( int code, const wchar_t* from, size_t len, std::string& to )
{
	to.resize( 3 * len + 100 );
	int wLen = WideCharToMultiByte(code, MB_PRECOMPOSED, from,len, ( char* )to.c_str(), to.size() );
	if( 0 != wLen )
	{
		to.resize( wLen );
		return;
	}

	DWORD err = ::GetLastError();
	if( ERROR_INSUFFICIENT_BUFFER != err )
		ThrowException1( EncodingException, lastError( err ) );

	// ���㳤��
	wLen = WideCharToMultiByte(code, MB_PRECOMPOSED, from,len, NULL, 0 );
	if( 0 == wLen )
		ThrowException1( EncodingException, lastError( ) );

	to.resize( wLen + 100 );
	wLen = WideCharToMultiByte(code, MB_PRECOMPOSED, from,len, ( char* )to.c_str(), to.size() );
	if( 0 == wLen )
		ThrowException1( EncodingException, lastError( ) );

	to.resize( wLen );
}



_jomoo_end

#endif /* _utf8encoding_h_ */
