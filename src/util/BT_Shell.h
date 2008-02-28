
/**
* -*- C++ -*-
* BT_Shell.h,v 1.0 2004/09/14 09:15:54
*/

#ifndef _BT_Shell_H_
#define _BT_Shell_H_

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include "util/tstring.h"

/**
 * Brief 外部程序执行类
 * <p>本类封装了，执行一个程序的细节
 */
class BT_Shell
{
public:
	/**
	 * BT_Shell constructor
	 * @param[ in ] comm_line 外部程序命令行字符串
	 * @remarks comm_line的开头一定要是以程序名开头，以空白符分隔。
	 */
	BT_Shell( const tstring & comm_line );
	
	/**
	 * BT_Shell constructor
	 * @param[ in ] app_name 外部程序名字符串
	 * @param[ in ] comm_line 外部程序命令行字符串
	 */
	BT_Shell( const tstring & app_name, const tstring& comm_line );

	/**
	 * BT_Shell constructor
	 * @param[ in ] comm_line 外部程序命令行字符串
	 * @remarks comm_line的开头一定要是以程序名开头，以空白符分隔。
	 */
	BT_Shell( const tchar* comm_line );

	/**
	 * BT_Shell constructor
	 * @param[ in ] app_name 外部程序名字符串
	 * @param[ in ] comm_line 外部程序命令行字符串
	 */
	BT_Shell( const tchar* app_str, const tchar* comm_line );

	~BT_Shell(void);

	/**
	 * 执行外部程序
	 * @return 成功返回0， 不成功则返回－1;
	 */
	int svc( );

	/**
	 * 等待外部程序结束。
	 * @param[ in ] timeout 等待外部程序结束的时间
	 * @return 成功等待返回0， 超时返回－1;
	 * @remarks 如果是无限等待的话，timeout 为INFINITE ;
	 */
	int wait( DWORD timeout = INFINITE );

	/**
	 * 取得外部程序的结束码。
	 * @param[ out ] ExitCode 外部程序的结束码
	 * @return 成功返回0， 不成功则返回－1;
	 */
	int exit_code( DWORD &ExitCode );

	/**
	 * 取得外部程序的打印的字符。
	 * @param[ out ] str 外部程序的打印的字符
	 * @return 成功返回0， 不成功则返回－1;
	 * @remarks 注意如果想要要取得外部程序的打印的字符，先要调用一个
	 * screen()函数，
	 * @see screen()
	 */
	int screen_str( tstring& str );

	/**
	 * 设置取得屏幕字符。
	 * @remarks 调用本函数后，可以通过screen_str来取得屏幕字符，
	 * 注意它要在svc之前调用才有效。
	 */
	void screen( );

	/**
	 * 取得最后一次错误的描述符。
	 * @return 错误的描述符。
	 */
	const tstring& last_error( ) const;

private:

	int init( );

	STARTUPINFO si;
    PROCESS_INFORMATION pi;
	bool success_;
	tstring app_name_;
	tstring comm_line_;


	tstring last_error_;

	bool screen_;
	SECURITY_ATTRIBUTES saAttr; 
	HANDLE hChildStdout;
	tchar TempFileName[ MAX_PATH ];
};

#endif // _Monitor_Info_H_