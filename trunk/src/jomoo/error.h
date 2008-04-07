

#if !defined(ERRORDEF_HPP)
#define ERRORDEF_HPP

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#define IllegalArgumentError	_T("无效参数")
#define RuntimeError			_T("运行时错误")
#define OutOfRangeError			_T("超出范围")
#define LockError				_T("锁出错")
#define CtrlCHandlerError		_T("设置Ctrl+C出错")
#define NetworkError			_T("网络错误")
#define InvalidPointerError		_T("无效指针")
#define LengthError				_T("无效长度")
#define EOFError				_T("已经到结尾了")
#define PluginError				_T("插件错误")
#define URLError				_T("URL分析出错")
#define CastError				_T("转换失败")
#define NullError				_T("空指针")
#define NotFindError			_T("没有找到")
#define _ExistError				_T("已经存在")
#define SystemError				_T("系统错误")

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

#define ERR_OBJECT_NOEXIST	-501	//	对象不存在
#define ERR_INTERNAL		-502	//	内部错误
#define ERR_UNKNOWN_COMMAND	-503	//  不可识别的命令
#define ERR_AUTH			-504	//	没有权限
#define ERR_TYPE			-505	//	类型错误，它是一个目录
#define ERR_SEEKFILE		-506	//	移动文件读位置出错
#define ERR_READFILE		-507	//	移动文件读位置出错
#define ERR_LENGTH			-508	//	内存太小

#endif // ERRORDEF_HPP