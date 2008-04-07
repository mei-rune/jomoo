

#if !defined(ERRORDEF_HPP)
#define ERRORDEF_HPP

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#define IllegalArgumentError	_T("��Ч����")
#define RuntimeError			_T("����ʱ����")
#define OutOfRangeError			_T("������Χ")
#define LockError				_T("������")
#define CtrlCHandlerError		_T("����Ctrl+C����")
#define NetworkError			_T("�������")
#define InvalidPointerError		_T("��Чָ��")
#define LengthError				_T("��Ч����")
#define EOFError				_T("�Ѿ�����β��")
#define PluginError				_T("�������")
#define URLError				_T("URL��������")
#define CastError				_T("ת��ʧ��")
#define NullError				_T("��ָ��")
#define NotFindError			_T("û���ҵ�")
#define _ExistError				_T("�Ѿ�����")
#define SystemError				_T("ϵͳ����")

#define  ERR_SYS  -200 //  
#define  ERR_ARG  -201
#define  ERR_LEN -202 
#define  ERR_POINT	-203
#define  ERR_UNKOWN	-204
#define  ERR_MAXMSGLEN	-205
#define  ERR_HEADERLENGTH -206
#define  ERR_HEADERTYPE -207
#define  ERR_jomoo_memory -208

#define ERR_PARAMETER -400

#define ERR_OBJECT_NOEXIST	-501	//	���󲻴���
#define ERR_INTERNAL		-502	//	�ڲ�����
#define ERR_UNKNOWN_COMMAND	-503	//  ����ʶ�������
#define ERR_AUTH			-504	//	û��Ȩ��
#define ERR_TYPE			-505	//	���ʹ�������һ��Ŀ¼
#define ERR_SEEKFILE		-506	//	�ƶ��ļ���λ�ó���
#define ERR_READFILE		-507	//	�ƶ��ļ���λ�ó���
#define ERR_LENGTH			-508	//	�ڴ�̫С

#endif // ERRORDEF_HPP