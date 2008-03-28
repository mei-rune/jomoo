/**
 * -*- C++ -*-
 * -------------------------------------------------------------------------------
 * - ¤╭⌒╮ ╭⌒╮			         Share_Library.h,v 1.0 2005/04/27 11:42:54
 *  ╱◥██◣ ╭╭ ⌒╮
 * ︱田︱田田| ╰------
 * -------------------------------------------------------------------------------
 */
#ifndef _Shared_Library_H_
#define _Shared_Library_H_

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
#include "config_Util.h"
#include "Base/string.hpp"

_jomoo_begin

typedef HMODULE BT_SHLIB_HANDLE;

class Share_Library
{
public:
	/**
	 * Share_Library constructor
	 * @param[ in ] close_on_destruction 指定在本类析构时是否关闭动态库
	 */
	Share_Library( int close_on_destruction = 1 );

	/**
	 * Share_Library constructor
	 * 载入指定的动态库
	 * @param[ in ] name 动态库的名称
	 * @param[ in ] close_on_destruction 指定在本类析构时是否关闭动态库
	 * @remarks 失败时会扔出异常;
	 */
	Share_Library( const tchar* name ,int close_on_destruction = 1 );

	/**
	 * Share_Library constructor
	 * 载入指定的动态库
	 * @param[ in ] name 动态库的名称
	 * @param[ in ] close_on_destruction 指定在本类析构时是否关闭动态库
	 * @remarks 失败时会扔出异常;
	 */
	Share_Library( const tstring& name ,int close_on_destruction = 1 );

	/**
	 * Share_Library destructor
	 */
	~Share_Library(void);

	/**
	 * 载入指定的动态库
	 * @param[ in ] name 动态库的名称
	 * @param[ in ] close_on_destruction 指定在本类析构时是否关闭动态库
	 * @return 成功返回0,否则返回 -1;
	 */
	int open( const tchar* name ,int close_on_destruction = 1 );

	/**
	 * 载入指定的动态库
	 * @param[ in ] name 动态库的名称
	 * @param[ in ] close_on_destruction 指定在本类析构时是否关闭动态库
	 * @return 成功返回0,否则返回 -1;
	 */
	int open( const tstring& name ,int close_on_destruction = 1 );

	/**
	 * 关闭动态库
	 * @return 成功返回0,否则返回 -1;
	 */
	int close (void);

	/**
	 * 取得指定的符号的地址
	 * param[ in ] symbol_name 符号的称
	 * param[ in ] ignore_errors 是否忽略错误
	 * @return 成功返回符号的地址,否则返回 0;
	 */
	void *symbol (const tchar *symbol_name, int ignore_errors = 0);

	/**
	 * 取得指定的符号的地址
	 * param[ in ] symbol_name 符号的称
	 * param[ in ] ignore_errors 是否忽略错误
	 * @return 成功返回符号的地址,否则返回 0;
	 */
	void *symbol (const tstring&symbol_name, int ignore_errors = 0);

	/**
	 * 取得最后一次的出错信息
	 * @return 成功返回出错信息,否则返回 0;
	 */
	const tchar *error (void) const;

	/**
	 * 取得动态库的句柄
	 * @return 成功返回出错信息,否则返回 0;
	 */
	BT_SHLIB_HANDLE get_handle ( ) const;

	void set_handle (BT_SHLIB_HANDLE handle, int close_on_destruction = 1);

private:

	BT_SHLIB_HANDLE dll_handle_;

	int close_on_destruction_;

	mutable LPVOID lpMsgBuf;
};

_jomoo_end

#include "Shared_Library.inl"

#endif  // _Shared_Library_H_