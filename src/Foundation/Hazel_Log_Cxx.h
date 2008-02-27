

/**
 * -*- C++ -*-
 * -------------------------------------------------------------------------------
 * - ¤╭⌒╮ ╭⌒╮		                   BT_Log_Cxx.h,v 1.0 2005/04/22 10:34:54
 *  ╱◥██◣ ╭╭ ⌒╮
 * ︱田︱田田| ╰------
 * -------------------------------------------------------------------------------
 */

#ifndef _BT_Log_Cxx_H_
#define _BT_Log_Cxx_H_


#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#ifndef NOLOG4CXX

#include <list>
#include "Logger.h"
#include "log4cxx\logger.h"
#include "log4cxx\ndc.h"

_boe_begin


/**
 * @Brief BT_Log 日志接口
 * 这是BT的日志接口，每一个具体的日志都必须从它继承，每一个需要记日志的都可以得到一个这样的接，
 * 但不推荐直接使用它。有一组预定义好的宏，请使用宏
 */
class BT_Log_Cxx :
	public BOE_Log_Impl
{
public:

	BT_Log_Cxx( const tchar* name );

	~BT_Log_Cxx(void);
	
	/**
	 * assert 语句
	 * @param[ in ] assertion 条件是否为真
	 * @param[ in ] message 日志内容
	 * @param[ in ] file 日志记录的源文件名
	 * @param[ in ] line 日志记录的源文件的当前行
	 */
	void assertLog(bool assertion, const StringStream& msg, const char* file, int line );

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
	void fatal(const StringStream& message, const char* file, int line );

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
	void error(const StringStream& message, const char* file, int line );

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
	void info(const StringStream& message, const char* file, int line );

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
	void debug(const StringStream& message, const char* file, int line );

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
	void warn(const StringStream& message, const char* file, int line );

	/**
	 * level级的日志是否可以记日志
	 * @return 可以true,不可以false
	 */
	bool isEnabledFor(const LevelPtr& level) const;

	/**
	 * Trace级的日志是否可以记日志
	 * @return 可以true,不可以false
	 */
	bool isTraceEnabled() const;

	/**
	 * 记录warn级的日志
	 * @param[ in ] message 日志内容
	 * @param[ in ] file 日志记录的源文件名
	 * @param[ in ] line 日志记录的源文件的当前行
	 */
	void trace(const StringStream& message, const char* file, int line );

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

	/**
	 * 基于对象的NDC,与下面的基于线程的不一样，它是只有使用这个日志对象才有
	 * 会在日志中打印NDC
	 * 加一个NDC
	 * @param[ in ] str 描述字符串
	 */
	void pushNDC( const tchar* str );

	/**
	 * 取出一个NDC
	 */
	void popNDC( );

	/**
	 * 清空NDC
	 */
	void clearNDC();

	void createLog_i();

	LevelPtr Log4CxxLeveltoLevelPtr( int level ) const;

	int LevelPtrtoLog4CxxLevel( LevelPtr level ) const;

private:

	mutable LevelPtr level_;
	log4cxx:: LoggerPtr rootLogger_;

	std::list< tstring > m_NDCs_;
};

class BT_Log_NDC_Cxx : public BOE_Log_NDC_Base
{
public:


	void pushNDC( const tchar* str );
	void popNDC( );

};

BOE_Log_NDC_Base* make_BT_NDC_Cxx( );
BOE_Log_Impl* make_BT_Log_Cxx( const tchar* name );

int init_BT_Log_Cxx(  );
void shutdown_BT_Log_Cxx(  );




_boe_end


#endif // #ifndef NOLOG4CXX

#endif // _BT_Log_Cxx_H_
