


#ifndef _SQLite_Fun_H_
#define _SQLite_Fun_H_

#include "QSqlite.h"

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