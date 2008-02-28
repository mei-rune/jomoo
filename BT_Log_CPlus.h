

/**
 * -*- C++ -*-
 * -------------------------------------------------------------------------------
 * - ¤╭⌒╮ ╭⌒╮		              BT_Log_CPlus.h,v 1.0 2005/04/22 10:34:54
 *  ╱◥██◣ ╭╭ ⌒╮
 * ︱田︱田田| ╰------
 * -------------------------------------------------------------------------------
 */

#ifndef _BT_Log_CPlus_H_
#define _BT_Log_CPlus_H_


#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#ifndef _NO_LOGCPLUS_

#include "BOE_Log_Base.h"
#include "log4\log4.hpp"

_bt_begin


/**
 * @Brief BT_Log 日志接口
 * 这是BT的日志接口，每一个具体的日志都必须从它继承，每一个需要记日志的都可以得到一个这样的接，
 * 但不推荐直接使用它。有一组预定义好的宏，请使用宏
 */
class BT_Log_CPlus :
	public BOE_Log_Impl
{
public:

	BT_Log_CPlus(void);

	~BT_Log_CPlus(void);
	
	/**
	 * assert 语句
	 * @param[ in ] assertion 条件是否为真
	 * @param[ in ] message 日志内容
	 * @param[ in ] file 日志记录的源文件名
	 * @param[ in ] line 日志记录的源文件的当前行
	 */
	void assertLog(bool assertion, const StringStream& msg, const char* file=0, int line=-1);

	/**
	 * fatal级的日志是否可以记日志
	 * @return 可以true,不可以false
	 */
	bool isFatalEnabled() const;
	
	/**
	 * 记录fatal级的日志
	 * @param[ in ] message 日志内容
	 * @param[ in ] file 日志记录的源文件名
	 * @param[ in ] line 日志记录的源文件的当前行
	 */
	void fatal(const StringStream& message, const char* file=0, int line=-1);

	/**
	 * error级的日志是否可以记日志
	 * @return 可以true,不可以false
	 */
	bool isErrorEnabled() const;

	/**
	 * 记录error级的日志
	 * @param[ in ] message 日志内容
	 * @param[ in ] file 日志记录的源文件名
	 * @param[ in ] line 日志记录的源文件的当前行
	 */
	void error(const StringStream& message, const char* file=0, int line=-1);

	/**
	 * info级的日志是否可以记日志
	 * @return 可以true,不可以false
	 */
	bool isInfoEnabled() const;

	/**
	 * 记录info级的日志
	 * @param[ in ] message 日志内容
	 * @param[ in ] file 日志记录的源文件名
	 * @param[ in ] line 日志记录的源文件的当前行
	 */
	void info(const StringStream& message, const char* file=NULL, int line=-1);

	/**
	 * debug级的日志是否可以记日志
	 * @return 可以true,不可以false
	 */
	bool isDebugEnabled() const;

	/**
	 * 记录debug级的日志
	 * @param[ in ] message 日志内容
	 * @param[ in ] file 日志记录的源文件名
	 * @param[ in ] line 日志记录的源文件的当前行
	 */
	void debug(const StringStream& message, const char* file=0, int line=-1);

	/**
	 * warn级的日志是否可以记日志
	 * @return 可以true,不可以false
	 */
	bool isWarnEnabled() const;

	/**
	 * 记录warn级的日志
	 * @param[ in ] message 日志内容
	 * @param[ in ] file 日志记录的源文件名
	 * @param[ in ] line 日志记录的源文件的当前行
	 */
	void warn(const StringStream& message, const char* file=NULL, int line=-1);

	/**
	 * level级的日志是否可以记日志
	 * @return 可以true,不可以false
	 */
	bool isEnabledFor(const LevelPtr& level) const;

	/**
	 * 记录level级的日志
	 * @param[ in ] message 日志内容
	 * @param[ in ] file 日志记录的源文件名
	 * @param[ in ] line 日志记录的源文件的当前行
	 */
	void log(const LevelPtr& level, const StringStream& message,
		const char* file=0, int line=-1);

	/**
	 * 取得当前的日志的级别
	 * @return 日志的级别
	 */
	const LevelPtr& getLevel() const;


	LevelPtr Log4CxxLeveltoLevelPtr( int level ) const;

	int LevelPtrtoLog4CxxLevel( LevelPtr level ) const;

private:

	mutable log4cplus::LogLevel level_;
	log4cplus:: Logger rootLogger_;
};

class BT_Log_NDC_CPlus : public BOE_Log_NDC_Base
{
public:

	BT_Log_NDC_CPlus( );


	~BT_Log_NDC_CPlus() ;

	void pushNDC( const tchar* str );
	void popNDC( );

};

BOE_Log_NDC_Base* make_BT_NDC_CPlus( const tchar* name );


int init_BT_Log_CPlus(  );
int shutdown_BT_Log_CPlus( name );
BOE_Log_Impl* make_BT_Log_CPlus( const tchar* name );


_bt_end



#endif // _NO_LOGCPLUS_

#endif // _BT_Log_CPlus_H_

