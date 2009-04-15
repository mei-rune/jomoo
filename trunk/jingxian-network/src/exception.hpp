
#ifndef _Exception_H_
#define _Exception_H_

#include "config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

#include "error.h"
#include "string.hpp"
#include "lastError.h"
#include <stdexcept>

_jingxian_begin

 #define _RAISE(x)	throw (x)

class Exception : public std::runtime_error
{
public:
    virtual ~Exception() throw()
	{
	}

    const char* getFile() const
	{
		if (!fSrcFile)
			return "";
		return fSrcFile;
	}

    size_t getLine() const
	{
		return fSrcLine;
	}

    void setPosition(const char* const file, size_t line)
	{
		fSrcFile = file;
		fSrcLine = line;
	}

    Exception()
		: std::runtime_error( "<未知异常>" )
		, fSrcFile( 0 )
		, fSrcLine( 0 )
	{
	}

	Exception( const tstring& message )
		: std::runtime_error( toNarrowString(message) )
		, fSrcFile( 0 )
	    , fSrcLine( 0 )
	{
	}

	Exception(const char* const srcFile, size_t srcLine , const tstring& message )
		: std::runtime_error( toNarrowString(message) )
		, fSrcFile( srcFile )
	    , fSrcLine(srcLine)
	{
	}

	Exception(const char* const srcFile, size_t srcLine , const tstring& message , const Exception& e )
		: std::runtime_error(  toNarrowString(message) + "," + e.what() )
		, fSrcFile( srcFile )
		, fSrcLine(srcLine)
	{
	}

	template< typename E >
	void Raise( E& e )
	{
		throw e;
	}

	void dumpFile( tostream& target ) const
	{
			target << _T( "[ file:" )
			<< toTstring( getFile() )
			<< _T( " line:" )
			<< ( int ) getLine()
			<< _T(" ] ");
	}

	virtual Exception* clone() = 0;
	virtual void rethrow() = 0;
	virtual void print(tostream&) const = 0;

 #if !_HAS_EXCEPTIONS
protected:
	virtual void _Doraise() const
		{	// perform class-specific exception handling
		_RAISE(*this);
		}
 #endif /* _HAS_EXCEPTIONS */

protected :
    const char*     fSrcFile;
    size_t    fSrcLine;
};


#define MakeException(theType , msg ) \
class theType : public Exception \
{ \
public: \
 \
    theType(const   char* const         srcFile \
            , size_t        srcLine \
			, const tstring & m				\
			, const Exception& e				\
            ) : \
        Exception(srcFile, srcLine, msg + m ,e ) \
    { \
         \
    } \
	theType(const   char* const         srcFile \
            , size_t        srcLine \
			, const tstring & m				\
            ) : \
        Exception(srcFile, srcLine, msg + m ) \
    { \
         \
    } \
	theType(const   char* const         srcFile \
            , size_t        srcLine \
            ) : \
        Exception(srcFile, srcLine, msg ) \
    { \
         \
    } \
	theType( ) : \
        Exception( msg ) \
    { \
         \
    } \
	theType( const tstring & m	) : \
        Exception( msg + m ) \
    { \
         \
    } \
 \
    virtual ~theType() throw() {}									\
	virtual Exception* clone()								\
	{														\
		return new theType( *this );						\
	}														\
	virtual void rethrow()									\
	{														\
		Raise( *this );										\
	}														\
	virtual void print(tostream& Target ) const 		\
	{														\
			Target << MAKE_STRING( theType )				\
			<< what()										\
			<< std::endl;									\
			dumpFile( Target );								\
	}														\
};



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
#define TimeSyntaxError         _T("时间格式错误")

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


MakeException( NullException , NullError );
MakeException( RuntimeException , RuntimeError );
MakeException( IllegalArgumentException, IllegalArgumentError );
MakeException( OutOfRangeException, OutOfRangeError );
MakeException( InvalidPointerException, InvalidPointerError );
MakeException( LengthException, LengthError );
MakeException( CastException, CastError );
MakeException( EOFException , EOFError );
MakeException( URLException, URLError );
MakeException( NotFindException, NotFindError );
MakeException( SystemException, SystemError );
MakeException( LockException , LockError );
MakeException( TimeSyntaxException , TimeSyntaxError );

#define ThrowException( type ) throw type(__FILE__, __LINE__ )
#define ThrowException1( type ,m1 ) throw type(__FILE__, __LINE__ , m1 )
#define ThrowException2( type ,m1 ,m2 ) throw type(__FILE__, __LINE__ , m1, m2 )
#define ThrowException3( type ,m1 ,m2 ,m3 ) throw type(__FILE__, __LINE__ , m1, m2, m3 )
#define ThrowException4( type ,m1 ,m2 ,m3 ,m4) throw type(__FILE__, __LINE__ , m1, m2, m3, m4)

_jingxian_end

#endif //_Exception_H_
