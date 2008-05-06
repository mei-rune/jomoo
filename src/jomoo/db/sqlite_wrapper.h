
#ifndef _QSqlite_H_
#define _QSqlite_H_

# include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_db.h"
# include "sqlite/sqlite3.h"

_jomoo_db_begin

typedef int (*sqlite3_open_t) (	const char* ,sqlite3 ** );
typedef int (*sqlite3_close_t)(sqlite3 * );
typedef int (*sqlite3_exec_t)( sqlite3* , const char *, sqlite3_callback ,void * ,char **);
typedef void (*sqlite3_free_t)(char *);
typedef const char *(*sqlite3_errmsg_t)(sqlite3* );
typedef int (*sqlite3_finalize_t)(sqlite3_stmt *);
typedef int (*sqlite3_reset_t)(sqlite3_stmt *);
typedef int (*sqlite3_prepare_t)( sqlite3 *,const char *,int ,sqlite3_stmt **,const char ** );
typedef int (*sqlite3_bind_blob_t)(sqlite3_stmt* , int , const void* , int , void(*)(void*));
typedef int (*sqlite3_bind_double_t)(sqlite3_stmt* , int , double );
typedef int (*sqlite3_bind_int_t)(sqlite3_stmt* , int , int );
typedef int (*sqlite3_bind_int64_t)(sqlite3_stmt* , int , sqlite_int64 );
typedef int (*sqlite3_bind_null_t)(sqlite3_stmt* , int  );
typedef int (*sqlite3_bind_text_t)(sqlite3_stmt* , int , const char* , int , void(*)(void*));
typedef int (*sqlite3_bind_text16_t)(sqlite3_stmt* , int , const void*  , int , void(*)(void*));
typedef int (*sqlite3_step_t)(sqlite3_stmt*);
typedef int (*sqlite3_column_int_t)(sqlite3_stmt* , int );
typedef sqlite_int64 (*sqlite3_column_int64_t)(sqlite3_stmt* , int );
typedef const unsigned char *(*sqlite3_column_text_t)(sqlite3_stmt* , int );
typedef const void *(*sqlite3_column_text16_t)(sqlite3_stmt* , int );
typedef int (*sqlite3_column_type_t)(sqlite3_stmt* , int );
typedef double (*sqlite3_column_double_t)(sqlite3_stmt* , int );
typedef const char *(*sqlite3_column_name_t)(sqlite3_stmt* ,int );
typedef int (*sqlite3_column_count_t)(sqlite3_stmt *);
typedef int (*sqlite3_bind_parameter_index_t)(sqlite3_stmt*, const char *);
typedef int (*sqlite3_value_type_t)(sqlite3_value*);
typedef void (*sqlite3_result_null_t)(sqlite3_context*);
typedef const unsigned char * (*sqlite3_value_text_t)(sqlite3_value*);
typedef void (*sqlite3_result_int_t)(sqlite3_context*, int);
typedef sqlite_int64 (*sqlite3_value_int64_t)(sqlite3_value*);
typedef int (*sqlite3_busy_timeout_t)(sqlite3*, int );

typedef int (*sqlite3_create_function_t)(
  sqlite3 *,
  const char *zFunctionName,
  int nArg,
  int eTextRep,
  void *pUserData,
  void (*xFunc)(sqlite3_context*,int,sqlite3_value**),
  void (*xStep)(sqlite3_context*,int,sqlite3_value**),
  void (*xFinal)(sqlite3_context*)
);

 typedef int (*sqlite3_changes_t)(sqlite3*);


extern sqlite3_close_t sqlite3_close_;
extern sqlite3_open_t sqlite3_open_;
extern sqlite3_exec_t sqlite3_exec_;
extern sqlite3_free_t sqlite3_free_;
extern sqlite3_errmsg_t sqlite3_errmsg_;
extern sqlite3_finalize_t sqlite3_finalize_;
extern sqlite3_reset_t sqlite3_reset_;
extern sqlite3_prepare_t sqlite3_prepare_;
extern sqlite3_bind_blob_t sqlite3_bind_blob_;
extern sqlite3_bind_double_t sqlite3_bind_double_;
extern sqlite3_bind_int_t sqlite3_bind_int_;
extern sqlite3_bind_int64_t sqlite3_bind_int64_;
extern sqlite3_bind_null_t sqlite3_bind_null_;
extern sqlite3_bind_text_t sqlite3_bind_text_;
extern sqlite3_bind_text16_t sqlite3_bind_text16_;
extern sqlite3_step_t sqlite3_step_;
extern sqlite3_column_int_t sqlite3_column_int_;
extern sqlite3_column_int64_t sqlite3_column_int64_;
extern sqlite3_column_text_t sqlite3_column_text_;
extern sqlite3_column_text16_t sqlite3_column_text16_;
extern sqlite3_column_type_t sqlite3_column_type_;
extern sqlite3_column_double_t sqlite3_column_double_;
extern sqlite3_column_name_t sqlite3_column_name_;
extern sqlite3_column_count_t sqlite3_column_count_;
extern sqlite3_bind_parameter_index_t sqlite3_bind_parameter_index_;

extern sqlite3_value_type_t sqlite3_value_type_;
extern sqlite3_result_null_t sqlite3_result_null_;
extern sqlite3_value_text_t sqlite3_value_text_;
extern sqlite3_value_int64_t sqlite3_value_int64_;
extern sqlite3_result_int_t sqlite3_result_int_;
extern sqlite3_create_function_t sqlite3_create_function_;
extern sqlite3_busy_timeout_t sqlite3_busy_timeout_;

extern sqlite3_changes_t sqlite3_changes_;


#define SQLITE_DLL  "sqlite3.dll"

bool ___init_sqlite(  const char* name );
void ___shutdown_sqlite( );



#define tsqlite3_open							( *sqlite3_open_ )
#define tsqlite3_close							( *sqlite3_close_ )
#define tsqlite3_exec							( *sqlite3_exec_ )
#define tsqlite3_free							( *sqlite3_free_ )
#define tsqlite3_errmsg							( *sqlite3_errmsg_ )
#define tsqlite3_finalize						( *sqlite3_finalize_ )
#define tsqlite3_reset							( *sqlite3_reset_ )
#define tsqlite3_prepare						( *sqlite3_prepare_ )
#define tsqlite3_step							( *sqlite3_step_ )
#define tsqlite3_bind_int						( *sqlite3_bind_int_ )
#define tsqlite3_bind_int64						( *sqlite3_bind_int64_ )
#define tsqlite3_bind_double					( *sqlite3_bind_double_ )
#define tsqlite3_bind_text						( *sqlite3_bind_text_ )
#define tsqlite3_bind_text16					( *sqlite3_bind_text16_ )
#define tsqlite3_bind_parameter_index			( *sqlite3_bind_parameter_index_ )
#define tsqlite3_column_int						( *sqlite3_column_int_ )
#define tsqlite3_column_int64					( *sqlite3_column_int64_ )
#define tsqlite3_column_double					( *sqlite3_column_double_ )
#define tsqlite3_column_text					( *sqlite3_column_text_ )
#define tsqlite3_column_count					( *sqlite3_column_count_ )
#define tsqlite3_column_type					( *sqlite3_column_type_ )
#define tsqlite3_column_name					( *sqlite3_column_name_ )

#define tsqlite3_value_type						( *sqlite3_value_type_)
#define tsqlite3_result_null					( *sqlite3_result_null_)
#define tsqlite3_value_text						( *sqlite3_value_text_)
#define tsqlite3_create_function				( *sqlite3_create_function_)
#define tsqlite3_result_int						( *sqlite3_result_int_)
#define tsqlite3_value_int64					( *sqlite3_value_int64_)
#define tsqlite3_busy_timeout					( *sqlite3_busy_timeout_)
#define tsqlite3_changes						( *sqlite3_changes_)


_jomoo_db_end

#endif // _QSqlite_H_