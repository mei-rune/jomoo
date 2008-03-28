
#if !defined(EXCEPTION_HPP)
#define EXCEPTION_HPP

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "error.H"
#include "string.hpp"
#include "lastError.h"
#include <stdexcept>

_jomoo_begin


class Exception : public std::runtime_error 
{
public:
    virtual ~Exception();
    const tchar* getFile() const;
    size_t getLine() const;

    void setPosition(const tchar* const file, size_t line);

    Exception();
	Exception( const tstring& _Message );
    Exception(const tchar* const srcFile, size_t srcLine , const tstring& _Message );
	Exception(const tchar* const srcFile, size_t srcLine , const tstring& _Message , const Exception& e );

	template< typename E >
	void Raise( E& e )
	{
		throw e;
	}

	void dumpFile( std::ostream& Target ) const
	{
			Target << _T( "[ file:" )
			<< getFile()
			<< _T( " line:" )
			<< ( int ) getLine()
			<< _T(" ] ");
	}

	virtual Exception* clone() = 0;
	virtual void rethrow() = 0;
	virtual void print(std::ostream&) const = 0;

 #if !_HAS_EXCEPTIONS
protected:
	virtual void _Doraise() const
		{	// perform class-specific exception handling
		_RAISE(*this);
		}
 #endif /* _HAS_EXCEPTIONS */

protected :
    const tchar*     fSrcFile;
    size_t    fSrcLine;
};


inline Exception::~Exception()
{
}


inline void Exception::setPosition(const tchar* const file, size_t line)
{
    fSrcLine = line;
    fSrcFile = file;
}


// ---------------------------------------------------------------------------
inline Exception::Exception() 
	: std::runtime_error( "<δ֪�쳣>" )
	, fSrcFile( 0 )
    , fSrcLine( 0 )
{

}

inline Exception::Exception( const tstring& _Message )
	: std::runtime_error( _Message )
	, fSrcFile( 0 )
    , fSrcLine( 0 )
{
}

inline Exception::Exception( const   tchar* const     srcFile
                            , size_t    srcLine
							, const std::string& _Message )
	: std::runtime_error( _Message )
	, fSrcFile( srcFile )
    , fSrcLine(srcLine)
{
}

inline Exception::Exception(const tchar* const srcFile, size_t srcLine , const tstring& _Message , const Exception& e )
	: std::runtime_error( _Message + tstring( ",") + e.what() )
	, fSrcFile( srcFile )
    , fSrcLine(srcLine)
{
}

inline const tchar* Exception::getFile() const
{
    if (!fSrcFile)
        return "";
    return fSrcFile;
}

inline size_t Exception::getLine() const
{
    return fSrcLine;
}

#define MakeException(theType , msg ) \
class theType : public Exception \
{ \
public: \
 \
    theType(const   char* const         srcFile \
            , size_t        srcLine \
			, const std::string & m				\
			, const Exception& e				\
            ) : \
        Exception(srcFile, srcLine, msg + m ,e ) \
    { \
         \
    } \
	theType(const   char* const         srcFile \
            , size_t        srcLine \
			, const std::string & m				\
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
	theType( const std::string & m	) : \
        Exception( msg + m ) \
    { \
         \
    } \
 \
    virtual ~theType() {}									\
	virtual Exception* clone()								\
	{														\
		return new theType( *this );						\
	}														\
	virtual void rethrow()									\
	{														\
		Raise( *this );										\
	}														\
	virtual void print(std::ostream& Target ) const 		\
	{														\
			Target << MAKE_STRING( theType )				\
			<< what()										\
			<< std::endl;									\
			dumpFile( Target );								\
	}														\
};

MakeException( NullException , NullError );
MakeException( RuntimeException , RuntimeError );
MakeException( IllegalArgumentException, IllegalArgumentError );
MakeException( OutOfRangeException, OutOfRangeError );
MakeException( InvalidPointerException, InvalidPointerError );
MakeException( LengthException, LengthError );
MakeException( CastException, CastError );
MakeException( EOFException , EOFError );
MakeException( URLException, URLError );
MakeException( NoFindException, NoFindError );
MakeException( SystemException, SystemError );
MakeException( LockException , LockError );

#define ThrowException( type ) throw type(__FILE__, __LINE__ )
#define ThrowException1( type ,m1 ) throw type(__FILE__, __LINE__ , m1 )
#define ThrowException2( type ,m1 ,m2 ) throw type(__FILE__, __LINE__ , m1, m2 )
#define ThrowException3( type ,m1 ,m2 ,m3 ) throw type(__FILE__, __LINE__ , m1, m2, m3 )
#define ThrowException4( type ,m1 ,m2 ,m3 ,m4) throw type(__FILE__, __LINE__ , m1, m2, m3, m4)

_jomoo_end

#endif
