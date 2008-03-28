

/**
* -*- C++ -*-
* -------------------------------------------------------------------------------
* - ¤╭⌒╮ ╭⌒╮					 System_Directory.H,v 1.0 2005/05/17 16:41:54
*  ╱◥██◣ ╭╭ ⌒╮
* ︱田︱田田| ╰------
* -------------------------------------------------------------------------------
*/

#ifndef _System_Directory_H_
#define _System_Directory_H_

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include <Windows.h>
#include <vector>
#include <errno.h>

#ifdef _WIN32
#   include <direct.h>
#   include <io.h>
#include <sys/stat.h>
#	include "windows.h"
#   define S_ISDIR(mode) ((mode) & _S_IFDIR)
#   define S_ISREG(mode) ((mode) & _S_IFREG)
#else
#   include <unistd.h>
#   include <dirent.h>
#endif

#include "exception.hpp"
#include "string.hpp"

_jomoo_begin

OS_INLINED
DWORD get_application_directory(tchar *szModName, DWORD Size, bool slash = true );

/**
 * 取得模块所在的目录
 * @param[ in ] slash 是否保留最后的"/"符（true 保留，false 不保留）
 */
OS_INLINED
tstring get_application_directory( bool slash = true );

/**
 * 规格化路径
 * @param[ in ] pa 需要规格化的路径
 */
OS_INLINED
tstring simplify(const tstring& path);

/**
 * 判它是不是绝对路径
 * @return 是绝对路径返回true,否则返回false
 */
OS_INLINED
bool isAbsolute(const tstring& pa);

/**
 * 判它是不是根目录
 * @return 是根目录返回true,否则返回false
 * @remarks 注意根目录是指 "c:\","x:\"这样的路径
 */
OS_INLINED
bool isRoot(const tstring& pa);

/**
 * 判它是不是目录
 */
OS_INLINED
bool isDirectory(const tstring& pa);

/**
 * 取得路径中的上一级目录
 * @remarks 注意，不论路径是一个文件还是一个目录都是删除最后一个
 * "\"后面的字符，同时保留"\",如
 * "c:\\aa\a"，返回"c:\\aa\"
 * "c:\\aa\a\"，返回"c:\\aa\"
 */
OS_INLINED
tstring getBasename(const tstring& pa);

/**
 * 取得路径中的上一级目录
 * @remarks 注意，与getBasename不同的是，不保留最后一个"\"
 * "c:\\aa\a"，返回"c:\\aa"
 * "c:\\aa\a\"，返回"c:\\aa"
 */
OS_INLINED
tstring getDirectoryName(const tstring& pa);

/**
 * 重命名文件名或目录名
 */
OS_INLINED
void rename(const tstring& fromPa, const tstring& toPa);

/**
 * 删除文件或目录（目录必须是空的）
 */
OS_INLINED
void remove(const tstring& pa);

/**
 * 删除文件或目录（目录可以不为空）
 */
OS_INLINED
void removeRecursive(const tstring& pa);

/**
 * 读目录下所有的文件或目录
 */
OS_INLINED
StringSeq readDirectory(const tstring& pa);

/**
 * 创建一个目录
 */
OS_INLINED
void createDirectory(const tstring& pa);

/**
 * 创建一个目录
 */
OS_INLINED
void createDirectoryRecursive(const tstring& pa);

/**
 * 合并一个路径
 */
OS_INLINED
tstring combinePath(const tstring& path1,const tstring& path2);

/**
 * 取得文件路径中的扩展名
 */
OS_INLINED
tstring getExtension (const tstring& path);

/**
 * 取得文件路径中的文件名(不带扩展名)
 */
OS_INLINED
tstring getFileNameWithoutExtension(const tstring& path);

/**
 * 取得文件路径中的文件名
 */
OS_INLINED
tstring getFileName(const tstring& path);

# if defined (OS_HAS_INLINED)
#   include "directory.inl"
# endif /* JOMOO_HAS_INLINED_OSCALLS */

_jomoo_end

#endif // _System_Directory_H_