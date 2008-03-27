

#if !defined(ERRORDEF_HPP)
#define ERRORDEF_HPP

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#define IllegalArgumentError "无效参数"
#define RuntimeError "运行时错误"
#define OutOfRangeError "超出范围"
#define LockError "锁出错"
#define CtrlCHandlerError "设置Ctrl+C出错"
#define NetworkError "网络错误"
#define InvalidPointerError "无效指针"
#define LengthError  "无效长度"
#define EOFError "已经到结尾了"
#define PluginError "插件错误"
#define URLError "URL分析出错"
#define CastError "转换失败"
#define NullError "空指针"
#define NoFindError  "没有找到"
#define _ExistError  "已经存在"
#define SystemError "系统错误"

#define  ERR_SYS  -200 //  
#define  ERR_ARG  -201
#define  ERR_LEN -202 
#define  ERR_POINT	-203
#define  ERR_UNKOWN	-204
#define  ERR_MAXMSGLEN	-205
#define  ERR_HEADERLENGTH -206
#define  ERR_HEADERTYPE -207
#define  ERR_MEMORY -208

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