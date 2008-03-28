/**
 * -*- C++ -*-
 * -------------------------------------------------------------------------------
 * - ��q�Шr �q�Шr			         Share_Library.h,v 1.0 2005/04/27 11:42:54
 *  �u�������� �q�q �Шr
 * ���������| �t------
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
	 * @param[ in ] close_on_destruction ָ���ڱ�������ʱ�Ƿ�رն�̬��
	 */
	Share_Library( int close_on_destruction = 1 );

	/**
	 * Share_Library constructor
	 * ����ָ���Ķ�̬��
	 * @param[ in ] name ��̬�������
	 * @param[ in ] close_on_destruction ָ���ڱ�������ʱ�Ƿ�رն�̬��
	 * @remarks ʧ��ʱ���ӳ��쳣;
	 */
	Share_Library( const tchar* name ,int close_on_destruction = 1 );

	/**
	 * Share_Library constructor
	 * ����ָ���Ķ�̬��
	 * @param[ in ] name ��̬�������
	 * @param[ in ] close_on_destruction ָ���ڱ�������ʱ�Ƿ�رն�̬��
	 * @remarks ʧ��ʱ���ӳ��쳣;
	 */
	Share_Library( const tstring& name ,int close_on_destruction = 1 );

	/**
	 * Share_Library destructor
	 */
	~Share_Library(void);

	/**
	 * ����ָ���Ķ�̬��
	 * @param[ in ] name ��̬�������
	 * @param[ in ] close_on_destruction ָ���ڱ�������ʱ�Ƿ�رն�̬��
	 * @return �ɹ�����0,���򷵻� -1;
	 */
	int open( const tchar* name ,int close_on_destruction = 1 );

	/**
	 * ����ָ���Ķ�̬��
	 * @param[ in ] name ��̬�������
	 * @param[ in ] close_on_destruction ָ���ڱ�������ʱ�Ƿ�رն�̬��
	 * @return �ɹ�����0,���򷵻� -1;
	 */
	int open( const tstring& name ,int close_on_destruction = 1 );

	/**
	 * �رն�̬��
	 * @return �ɹ�����0,���򷵻� -1;
	 */
	int close (void);

	/**
	 * ȡ��ָ���ķ��ŵĵ�ַ
	 * param[ in ] symbol_name ���ŵĳ�
	 * param[ in ] ignore_errors �Ƿ���Դ���
	 * @return �ɹ����ط��ŵĵ�ַ,���򷵻� 0;
	 */
	void *symbol (const tchar *symbol_name, int ignore_errors = 0);

	/**
	 * ȡ��ָ���ķ��ŵĵ�ַ
	 * param[ in ] symbol_name ���ŵĳ�
	 * param[ in ] ignore_errors �Ƿ���Դ���
	 * @return �ɹ����ط��ŵĵ�ַ,���򷵻� 0;
	 */
	void *symbol (const tstring&symbol_name, int ignore_errors = 0);

	/**
	 * ȡ�����һ�εĳ�����Ϣ
	 * @return �ɹ����س�����Ϣ,���򷵻� 0;
	 */
	const tchar *error (void) const;

	/**
	 * ȡ�ö�̬��ľ��
	 * @return �ɹ����س�����Ϣ,���򷵻� 0;
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