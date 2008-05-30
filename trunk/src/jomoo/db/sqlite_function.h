


#ifndef _SQLite_Fun_H_
#define _SQLite_Fun_H_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_db.h"
# include "sqlite_wrapper.h"

struct SQLite_Fun
{
  const char *zFunctionName;
  int nArg;
  int eTextRep;
  void *pUserData;
  void (*xFunc)(sqlite3_context*,int,sqlite3_value**);
  void (*xStep)(sqlite3_context*,int,sqlite3_value**);
  void (*xFinal)(sqlite3_context*);
};

extern SQLite_Fun* g_sqlite_fun;
extern int g_sqlite_fun_count;
//void regex_match(sqlite3_context *context, int argc, sqlite3_value **argv);

#endif // _SQLite_Fun_H_