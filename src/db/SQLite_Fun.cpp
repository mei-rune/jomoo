#include "StdAfx.h"
#include "sqlite_fun.h"
#include <boost/regex.hpp>

use_bt;

static void regex_match(sqlite3_context *context, int argc, sqlite3_value **argv)
{
	switch( tsqlite3_value_type(argv[0]) )
	{
	case SQLITE_NULL:
		tsqlite3_result_int( context, -1 );break;
	case SQLITE_INTEGER:
		tsqlite3_result_int( context, -1 );break;
	case SQLITE_TEXT: 
		{
			const unsigned char *zA = tsqlite3_value_text(argv[0]);
			const unsigned char *zB = tsqlite3_value_text(argv[1]);
			boost::regex expression( ( const char* ) zB ); 
			const char* start = ( const char* )zA, * end = ( const char* )zA + tstrlen( ( const char* )zA );
			boost::match_results< const char* > what;
			boost::match_flag_type flags = boost::match_default;
			if( boost::regex_search( start, end, what, expression, flags) )
				tsqlite3_result_int ( context, 0 );
			else
				tsqlite3_result_int( context, -1 );
			break;
		}
	case SQLITE_FLOAT:
		tsqlite3_result_int( context, -1 );break;
	case SQLITE_BLOB:
		tsqlite3_result_int( context, -1 );break;
	default:
		tsqlite3_result_int( context, -1 );
	}
}

static void Time_Match(sqlite3_context *context, int argc, sqlite3_value **argv)
{
	if( argc != 3 )
	{
		tsqlite3_result_int( context, -1 );
		return ;
	}

			time_t t =  ( time_t ) tsqlite3_value_int64(argv[0]);
			time_t begin =  ( time_t ) tsqlite3_value_int64(argv[1] );
			time_t end =( time_t ) tsqlite3_value_int64(argv[2]);

	if( t > begin && t < end )
		tsqlite3_result_int( context, 0 );
	else
		tsqlite3_result_int( context, -1 );
}


/*
** A structure defining how to do GLOB-style comparisons.
*/
struct compareInfo {
  u_char_t matchAll;
  u_char_t matchOne;
  u_char_t matchSet;
  u_char_t noCase;
};
static const struct compareInfo globInfo = { '*', '?', '[', 0 };
static const struct compareInfo likeInfo = { '%', '_',   0, 1 };

/*
** X is a pointer to the first byte of a UTF-8 character.  Increment
** X so that it points to the next character.  This only works right
** if X points to a well-formed UTF-8 string.
*/
#define sqliteNextChar(X)  while( (0xc0&*++(X))==0x80 ){}
#define sqliteCharVal(X)   sqlite3ReadUtf8(X)


///*
//** Compare two UTF-8 strings for equality where the first string can
//** potentially be a "glob" expression.  Return true (1) if they
//** are the same and false (0) if they are different.
//**
//** Globbing rules:
//**
//**      '*'       Matches any sequence of zero or more characters.
//**
//**      '?'       Matches exactly one character.
//**
//**     [...]      Matches one character from the enclosed list of
//**                characters.
//**
//**     [^...]     Matches one character not in the enclosed list.
//**
//** With the [...] and [^...] matching, a ']' character can be included
//** in the list by making it the first character after '[' or '^'.  A
//** range of characters can be specified using '-'.  Example:
//** "[a-z]" matches any single lower-case letter.  To match a '-', make
//** it the last character in the list.
//**
//** This routine is usually quick, but can be N**2 in the worst case.
//**
//** Hints: to match '*' or '?', put them in "[]".  Like this:
//**
//**         abc[*]xyz        Matches "abc*xyz" only
//*/
//int patternCompare(
//  const u_char_t *zPattern,              /* The glob pattern */
//  const u_char_t *zString,               /* The string to compare against the glob */
//  const struct compareInfo *pInfo  /* Information about how to do the compare */
//){
//  register int c;
//  int invert;
//  int seen;
//  int c2;
//  u_char_t matchOne = pInfo->matchOne;
//  u_char_t matchAll = pInfo->matchAll;
//  u_char_t matchSet = pInfo->matchSet;
//  u_char_t noCase = pInfo->noCase; 
//
//  while( (c = *zPattern)!=0 ){
//    if( c==matchAll ){
//      while( (c=zPattern[1]) == matchAll || c == matchOne ){
//        if( c==matchOne ){
//          if( *zString==0 ) return 0;
//          sqliteNextChar(zString);
//        }
//        zPattern++;
//      }
//      if( c==0 ) return 1;
//      if( c==matchSet ){
//        while( *zString && patternCompare(&zPattern[1],zString,pInfo)==0 ){
//          sqliteNextChar(zString);
//        }
//        return *zString!=0;
//      }else{
//        while( (c2 = *zString)!=0 ){
//          if( noCase ){
//            c2 = sqlite3UpperToLower[c2];
//            c = sqlite3UpperToLower[c];
//            while( c2 != 0 && c2 != c ){ c2 = sqlite3UpperToLower[*++zString]; }
//          }else{
//            while( c2 != 0 && c2 != c ){ c2 = *++zString; }
//          }
//          if( c2==0 ) return 0;
//          if( patternCompare(&zPattern[1],zString,pInfo) ) return 1;
//          sqliteNextChar(zString);
//        }
//        return 0;
//      }
//    }else if( c==matchOne ){
//      if( *zString==0 ) return 0;
//      sqliteNextChar(zString);
//      zPattern++;
//    }else if( c==matchSet ){
//      int prior_c = 0;
//      seen = 0;
//      invert = 0;
//      c = sqliteCharVal(zString);
//      if( c==0 ) return 0;
//      c2 = *++zPattern;
//      if( c2=='^' ){ invert = 1; c2 = *++zPattern; }
//      if( c2==']' ){
//        if( c==']' ) seen = 1;
//        c2 = *++zPattern;
//      }
//      while( (c2 = sqliteCharVal(zPattern))!=0 && c2!=']' ){
//        if( c2=='-' && zPattern[1]!=']' && zPattern[1]!=0 && prior_c>0 ){
//          zPattern++;
//          c2 = sqliteCharVal(zPattern);
//          if( c>=prior_c && c<=c2 ) seen = 1;
//          prior_c = 0;
//        }else if( c==c2 ){
//          seen = 1;
//          prior_c = c2;
//        }else{
//          prior_c = c2;
//        }
//        sqliteNextChar(zPattern);
//      }
//      if( c2==0 || (seen ^ invert)==0 ) return 0;
//      sqliteNextChar(zString);
//      zPattern++;
//    }else{
//      if( noCase ){
//        if( sqlite3UpperToLower[c] != sqlite3UpperToLower[*zString] ) return 0;
//      }else{
//        if( c != *zString ) return 0;
//      }
//      zPattern++;
//      zString++;
//    }
//  }
//  return *zString==0;
//}
//
//
///*
//** Implementation of the like() SQL function.  This function implements
//** the build-in LIKE operator.  The first argument to the function is the
//** pattern and the second argument is the string.  So, the SQL statements:
//**
//**       A LIKE B
//**
//** is implemented as like(B,A).
//**
//** If the pointer retrieved by via a call to sqlite3_user_data() is
//** not NULL, then this function uses UTF-16. Otherwise UTF-8.
//*/
//static void likeFunc(
//  sqlite3_context *context, 
//  int argc, 
//  sqlite3_value **argv
//){
//  const unsigned char *zA = sqlite3_value_text(argv[0]);
//  const unsigned char *zB = sqlite3_value_text(argv[1]);
//  if( zA && zB ){
//    sqlite3_result_int(context, patternCompare(zA, zB, &likeInfo));
//  }
//}
//
SQLite_Fun sqlite_funs[]={ { "regex_match", 2, SQLITE_UTF8,    0, regex_match, 0, 0   }
	,  { "time_match", 3, SQLITE_UTF8,    0, Time_Match, 0, 0   } };

SQLite_Fun* g_sqlite_fun = sqlite_funs;
int g_sqlite_fun_count = 2;