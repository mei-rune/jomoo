
#ifndef _string_traits_hpp_
#define _string_traits_hpp_

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

# include "Platform/os_string.h"

template <typename C>
struct string_traits;

template<>
struct string_traits<char_t>
{
    typedef char_t     char_type;
	typedef size_t     size_type;

	inline static   double strtod( const char_type *nptr,
			char_type **endptr )
	{
		return ::strtod( nptr, endptr );
	}

	inline static   long strtol( const char_type *nptr,
				char_type **endptr,
				int base )
	{
		return ::strtol( nptr, endptr , base );
	}

	inline static   unsigned long strtoul( const char_type *nptr,
				char_type **endptr,
				int base )
	{
		return ::strtoul( nptr, endptr , base );
	}

	inline static   __int64 _strtoi64( const char_type *nptr,
				char_type **endptr,
				int base )
	{
		return ::_strtoi64( nptr, endptr , base );
	}

	inline static   unsigned __int64 strtoui64( const char_type *nptr,
				char_type **endptr,
				int base )
	{
		return ::_strtoui64( nptr, endptr , base );
	}

	inline static   double atof(  const char_type *str )
	{
		return ::atof( str );
	}

	inline static   long atol(  const char_type *str )
	{
		return ::atol( str );
	}

	inline static   int atoi(  const char_type *str )
	{
		return ::atoi( str );
	}

	inline static   __int64 atoi64(  const char_type *str )
	{
		return ::_atoi64( str );
	}

	inline static   char_type *itoa( int value,
				 char_type *str,
				 size_t len,
				 int radix )
	{
		return ( 0 == ::_itoa_s( value, str,len, radix ) )? str : 0;
	}

	inline static   char_type *ltoa( long value,
				 char_type *str,
				 size_t len,
				 int radix )
	{
		return ( 0 == ::_ltoa_s( value, str, len, radix ))? str : 0;
	}

	inline static   char_type *ultoa( unsigned long value,
				 char_type *str,
				 size_t len,
				 int radix )
	{
		return ( 0 == ::_ultoa_s( value, str, len, radix ))? str : 0;
	}

	inline static   char_type *i64toa( __int64 value,
				 char_type *str,
				 size_t len,
				 int radix )
	{
		return ( 0 == ::_i64toa_s( value, str, len, radix ))? str : 0;
	}

	inline static   char_type *ui64toa( unsigned __int64 value,
				 char_type *str,
				 size_t len,
				 int radix )
	{
		return ( 0 == ::_ui64toa_s( value, str, len, radix ))? str : 0;
	}

	/* String functions */
 
	inline static   errno_t strcat(char_type *strDestination, size_t length,
				const char_type *strSource )
	{
		return ::strcat_s( strDestination, length, strSource );
	}

	inline static   errno_t strcpy(char_type *strDestination, size_t length,
				const char_type *strSource )
	{
		return ::strcpy_s( strDestination, length, strSource );
	}

	//寻找strCharSet字符集中任意一个字符在str字符串中第一次出现的位置
	inline static   size_type strcspn( const char_type *str,
				const char_type *strCharSet )
	{
		return ::strcspn( str, strCharSet );
	}


	//寻找str字符串第一个没有在strCharSet字符集中出现的位置
	inline static   size_type strspn( const char_type *str,
				const char_type *strCharSet )
	{
		return ::strspn( str, strCharSet );
	}

	inline static   size_type strlen(const char_type *str )
	{
		return ::strlen( str );
	}

	inline static  const char_type *strpbrk( const char_type * str,
				const char_type *strCharSet )
	{
		return ::strpbrk( str ,strCharSet);
	}

	inline static  char_type *strpbrk( char_type * str,
				const char_type *strCharSet )
	{
		return ::strpbrk( str ,strCharSet);
	}

	inline static  char_type *strchr( char_type *str,
		int c )
	{
		return ::strchr( str, c );
	}

	inline static  const char_type *strchr( const char_type *str,
		int c )
	{
		return ::strchr( str, c );
	}

	inline static  char_type *strrchr( char_type *str,
				int c )
	{
		return ::strrchr( str, c );
	}

	inline static  const char_type *strrchr( const char_type *str,
				int c )
	{
		return ::strrchr( str, c );
	}

	inline static  char_type *strstr( char_type *str,
			const char_type *strSearch )
	{
		return ::strstr( str, strSearch );
	}

	inline static  const char_type *strstr( const char_type *str,
			const char_type *strSearch )
	{
		return ::strstr( str, strSearch );
	}

	inline static char_type *strtok( char_type *strToken
		, const char_type *strDelimit )
	{
		return ::strtok( strToken, strDelimit );
	}

	inline static char_type *strdup( const char_type *strSource )
	{
		return ::_strdup( strSource );
	}

	///反转字符串
	inline static char_type *strrev( char_type *str )
	{
		return ::_strrev( str );
	}

	inline static char_type *strset( char_type *str
		, int c )
	{
		return ::_strset( str , c );
	}

	inline static int strcmp(  const char_type *string1,
		const char_type *string2 )
	{
		return ::strcmp( string1 , string2 );
	}

	inline static int stricmp(  const char_type *string1,
		const char_type *string2 )
	{
		return ::_stricmp( string1 , string2 );
	}

	inline static int strncmp( const char_type *string1,
			const char_type *string2,
			size_type count  )
	{
		return ::strncmp( string1 , string2 , count );
	}

	inline static int strnicmp( const char_type *string1,
			const char_type *string2,
			size_type count  )
	{
		return ::_strnicmp( string1 , string2 , count );
	}
};

template<>
struct string_traits<wchar_t>
{
    typedef wchar_t     char_type;
	typedef size_t     size_type;

	inline static  double strtod( const char_type *nptr,
			char_type **endptr )
	{
		return ::wcstod( nptr, endptr );
	}

	inline static  long strtol( const char_type *nptr,
				char_type **endptr,
				int base )
	{
		return ::wcstol( nptr, endptr , base );
	}

	inline static  unsigned long strtoul( const char_type *nptr,
				char_type **endptr,
				int base )
	{
		return ::wcstoul( nptr, endptr , base );
	}

	inline static  __int64 _strtoi64( const char_type *nptr,
				char_type **endptr,
				int base )
	{
		return ::_wcstoi64( nptr, endptr , base );
	}

	inline static  unsigned __int64 strtoui64( const char_type *nptr,
				char_type **endptr,
				int base )
	{
		return ::_wcstoui64( nptr, endptr , base );
	}

	inline static  double atof(  const char_type *str )
	{
		return ::_wtof( str );
	}

	inline static  long atol(  const char_type *str )
	{
		return ::_wtol( str );
	}

	inline static  int atoi(  const char_type *str )
	{
		return ::_wtoi( str );
	}

	inline static  __int64 atoi64(  const char_type *str )
	{
		return ::_wtoi64( str );
	}

	inline static  char_type *itoa( int value,
				 char_type *str,
				 size_t len,
				 int radix )
	{
		return ( 0 == ::_itow_s( value, str, len, radix ))? str : 0;
	}

	inline static  char_type *ltoa( long value,
				 char_type *str,
				 size_t len,
				 int radix )
	{
		return ( 0 == ::_ltow_s( value, str, len, radix ))? str : 0;
	}

	inline static  char_type *ultoa( unsigned long value,
				 char_type *str,
				 size_t len,
				 int radix )
	{
		return ( 0 == ::_ultow_s( value, str, len, radix ))? str : 0;
	}

	inline static  char_type *i64toa( __int64 value,
				 char_type *str,
				 size_t len,
				 int radix )
	{
		return ( 0 == ::_i64tow_s( value, str, len, radix ))? str : 0;
	}

	inline static  char_type *ui64toa( unsigned __int64 value,
				 char_type *str,
				 size_t len,
				 int radix )
	{
		return ( 0 == ::_ui64tow_s( value, str, len, radix ))? str : 0;
	}

	/* String functions */
 
	inline static  errno_t strcat(char_type *strDestination, size_t length,
				const char_type *strSource )
	{
		return ::wcscat_s( strDestination,length, strSource );
	}
	
	inline static  errno_t strcpy(char_type *strDestination, size_t length,
				const char_type *strSource )
	{
		return ::wcscpy_s( strDestination,length, strSource );
	}

	//寻找strCharSet字符集中任意一个字符在str字符串中第一次出现的位置
	inline static  size_type strcspn( const char_type *str,
				const char_type *strCharSet )
	{
		return ::wcscspn( str, strCharSet );
	}


	//寻找str字符串第一个没有在strCharSet字符集中出现的位置
	inline static  size_type strspn( const char_type *str,
				const char_type *strCharSet )
	{
		return ::wcsspn( str, strCharSet );
	}

	inline static  size_type strlen(const char_type *str )
	{
		return ::wcslen( str );
	}

	inline static  const char_type *strpbrk( const char_type * str,
				const char_type *strCharSet )
	{
		return ::wcspbrk( str ,strCharSet);
	}

	inline static  char_type *strpbrk( char_type * str,
				const char_type *strCharSet )
	{
		return ::wcspbrk( str ,strCharSet);
	}

	inline static  char_type *strchr( char_type *str,
		int c )
	{
		return ::wcschr( str, c );
	}

	inline static  const char_type *strchr( const char_type *str,
		int c )
	{
		return ::wcschr( str, c );
	}

	inline static  char_type *strrchr( char_type *str,
				int c )
	{
		return ::wcsrchr( str, c );
	}

	inline static  const char_type *strrchr( const char_type *str,
				int c )
	{
		return ::wcsrchr( str, c );
	}

	inline static  char_type *strstr( char_type *str,
			const char_type *strSearch )
	{
		return ::wcsstr( str, strSearch );
	}

	inline static  const char_type *strstr( const char_type *str,
			const char_type *strSearch )
	{
		return ::wcsstr( str, strSearch );
	}

	inline static  char_type *strtok( char_type *strToken
		, const char_type *strDelimit )
	{
		return ::wcstok( strToken, strDelimit );
	}

	inline static  char_type *strdup( const char_type *strSource )
	{
		return ::_wcsdup( strSource );
	}

	///反转字符串
	inline static  char_type *strrev( char_type *str )
	{
		return ::_wcsrev( str );
	}

	inline static  char_type *strset( char_type *str
		, int c )
	{
		return ::_wcsset( str , c );
	}

	inline static  int strcmp(  const char_type *string1,
		const char_type *string2 )
	{
		return ::wcscmp( string1 , string2 );
	}

	inline static  int stricmp(  const char_type *string1,
		const char_type *string2 )
	{
		return ::_wcsicmp( string1 , string2 );
	}

	inline static  int strncmp( const char_type *string1,
			const char_type *string2,
			size_type count  )
	{
		return ::wcsncmp( string1 , string2 , count );
	}

	inline static  int strnicmp( const char_type *string1,
			const char_type *string2,
			size_type count  )
	{
		return ::_wcsnicmp( string1 , string2 , count );
	}
};


#endif /* _string_traits_hpp_ */
