
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
 * Brief �ⲿ����ִ����
 * <p>�����װ�ˣ�ִ��һ�������ϸ��
 */
class BT_Shell
{
public:
	/**
	 * BT_Shell constructor
	 * @param[ in ] comm_line �ⲿ�����������ַ���
	 * @remarks comm_line�Ŀ�ͷһ��Ҫ���Գ�������ͷ���Կհ׷��ָ���
	 */
	BT_Shell( const tstring & comm_line );
	
	/**
	 * BT_Shell constructor
	 * @param[ in ] app_name �ⲿ�������ַ���
	 * @param[ in ] comm_line �ⲿ�����������ַ���
	 */
	BT_Shell( const tstring & app_name, const tstring& comm_line );

	/**
	 * BT_Shell constructor
	 * @param[ in ] comm_line �ⲿ�����������ַ���
	 * @remarks comm_line�Ŀ�ͷһ��Ҫ���Գ�������ͷ���Կհ׷��ָ���
	 */
	BT_Shell( const tchar* comm_line );

	/**
	 * BT_Shell constructor
	 * @param[ in ] app_name �ⲿ�������ַ���
	 * @param[ in ] comm_line �ⲿ�����������ַ���
	 */
	BT_Shell( const tchar* app_str, const tchar* comm_line );

	~BT_Shell(void);

	/**
	 * ִ���ⲿ����
	 * @return �ɹ�����0�� ���ɹ��򷵻أ�1;
	 */
	int svc( );

	/**
	 * �ȴ��ⲿ���������
	 * @param[ in ] timeout �ȴ��ⲿ���������ʱ��
	 * @return �ɹ��ȴ�����0�� ��ʱ���أ�1;
	 * @remarks ��������޵ȴ��Ļ���timeout ΪINFINITE ;
	 */
	int wait( DWORD timeout = INFINITE );

	/**
	 * ȡ���ⲿ����Ľ����롣
	 * @param[ out ] ExitCode �ⲿ����Ľ�����
	 * @return �ɹ�����0�� ���ɹ��򷵻أ�1;
	 */
	int exit_code( DWORD &ExitCode );

	/**
	 * ȡ���ⲿ����Ĵ�ӡ���ַ���
	 * @param[ out ] str �ⲿ����Ĵ�ӡ���ַ�
	 * @return �ɹ�����0�� ���ɹ��򷵻أ�1;
	 * @remarks ע�������ҪҪȡ���ⲿ����Ĵ�ӡ���ַ�����Ҫ����һ��
	 * screen()������
	 * @see screen()
	 */
	int screen_str( tstring& str );

	/**
	 * ����ȡ����Ļ�ַ���
	 * @remarks ���ñ������󣬿���ͨ��screen_str��ȡ����Ļ�ַ���
	 * ע����Ҫ��svc֮ǰ���ò���Ч��
	 */
	void screen( );

	/**
	 * ȡ�����һ�δ������������
	 * @return �������������
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