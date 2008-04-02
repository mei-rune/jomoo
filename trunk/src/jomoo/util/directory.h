

/**
* -*- C++ -*-
* -------------------------------------------------------------------------------
* - ��q�Шr �q�Шr					 System_Directory.H,v 1.0 2005/05/17 16:41:54
*  �u�������� �q�q �Шr
* ���������| �t------
* -------------------------------------------------------------------------------
*/

#ifndef _System_Directory_H_
#define _System_Directory_H_

#include "jomoo/config.h"

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

# include "jomoo/exception.hpp"
#include "jomoo/string.hpp"

_jomoo_begin

OS_INLINE
DWORD get_application_directory(tchar *szModName, DWORD Size, bool slash = true );

/**
 * ȡ��ģ�����ڵ�Ŀ¼
 * @param[ in ] slash �Ƿ�������"/"����true ������false ��������
 */
OS_INLINE
tstring get_application_directory( bool slash = true );

/**
 * ���·��
 * @param[ in ] pa ��Ҫ��񻯵�·��
 */
OS_INLINE
tstring simplify(const tstring& path);

/**
 * �����ǲ��Ǿ���·��
 * @return �Ǿ���·������true,���򷵻�false
 */
OS_INLINE
bool isAbsolute(const tstring& pa);

/**
 * �����ǲ��Ǹ�Ŀ¼
 * @return �Ǹ�Ŀ¼����true,���򷵻�false
 * @remarks ע���Ŀ¼��ָ "c:\","x:\"������·��
 */
OS_INLINE
bool isRoot(const tstring& pa);

/**
 * �����ǲ���Ŀ¼
 */
OS_INLINE
bool isDirectory(const tstring& pa);

/**
 * ȡ��·���е���һ��Ŀ¼
 * @remarks ע�⣬����·����һ���ļ�����һ��Ŀ¼����ɾ�����һ��
 * "\"������ַ���ͬʱ����"\",��
 * "c:\\aa\a"������"c:\\aa\"
 * "c:\\aa\a\"������"c:\\aa\"
 */
OS_INLINE
tstring getBasename(const tstring& pa);

/**
 * ȡ��·���е���һ��Ŀ¼
 * @remarks ע�⣬��getBasename��ͬ���ǣ����������һ��"\"
 * "c:\\aa\a"������"c:\\aa"
 * "c:\\aa\a\"������"c:\\aa"
 */
OS_INLINE
tstring getDirectoryName(const tstring& pa);

/**
 * �������ļ�����Ŀ¼��
 */
OS_INLINE
void rename(const tstring& fromPa, const tstring& toPa);

/**
 * ɾ���ļ���Ŀ¼��Ŀ¼�����ǿյģ�
 */
OS_INLINE
void remove(const tstring& pa);

/**
 * ɾ���ļ���Ŀ¼��Ŀ¼���Բ�Ϊ�գ�
 */
OS_INLINE
void removeRecursive(const tstring& pa);

/**
 * ��Ŀ¼�����е��ļ���Ŀ¼
 */
OS_INLINE
StringSeq readDirectory(const tstring& pa);

/**
 * ����һ��Ŀ¼
 */
OS_INLINE
void createDirectory(const tstring& pa);

/**
 * ����һ��Ŀ¼
 */
OS_INLINE
void createDirectoryRecursive(const tstring& pa);

/**
 * �ϲ�һ��·��
 */
OS_INLINE
tstring combinePath(const tstring& path1,const tstring& path2);

/**
 * ȡ���ļ�·���е���չ��
 */
OS_INLINE
tstring getExtension (const tstring& path);

/**
 * ȡ���ļ�·���е��ļ���(������չ��)
 */
OS_INLINE
tstring getFileNameWithoutExtension(const tstring& path);

/**
 * ȡ���ļ�·���е��ļ���
 */
OS_INLINE
tstring getFileName(const tstring& path);

# if defined (OS_HAS_INLINED)
#   include "directory.inl"
# endif /* JOMOO_HAS_INLINED_OSCALLS */

_jomoo_end

#endif // _System_Directory_H_