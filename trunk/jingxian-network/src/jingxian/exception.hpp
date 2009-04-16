
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
		: std::runtime_error( "<δ֪�쳣>" )
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
#define TimeSyntaxError         _T("ʱ���ʽ����")

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

#define ERR_OBJECT_NOEXIST	-501	//	���󲻴���
#define ERR_INTERNAL		-502	//	�ڲ�����
#define ERR_UNKNOWN_COMMAND	-503	//  ����ʶ�������
#define ERR_AUTH			-504	//	û��Ȩ��
#define ERR_TYPE			-505	//	���ʹ�������һ��Ŀ¼
#define ERR_SEEKFILE		-506	//	�ƶ��ļ���λ�ó���
#define ERR_READFILE		-507	//	�ƶ��ļ���λ�ó���
#define ERR_LENGTH			-508	//	�ڴ�̫С


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
