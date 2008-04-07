
#if !defined(EXCEPTION_HPP)
#define EXCEPTION_HPP

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "error.H"
#include "jomoo/string.hpp"
#include "lastError.h"
#include <stdexcept>

_jomoo_begin


class Exception : public std::runtime_error 
{
public:
    virtual ~Exception()
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
    virtual ~theType() {}									\
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

#define ThrowException( type ) throw type(__FILE__, __LINE__ )
#define ThrowException1( type ,m1 ) throw type(__FILE__, __LINE__ , m1 )
#define ThrowException2( type ,m1 ,m2 ) throw type(__FILE__, __LINE__ , m1, m2 )
#define ThrowException3( type ,m1 ,m2 ,m3 ) throw type(__FILE__, __LINE__ , m1, m2, m3 )
#define ThrowException4( type ,m1 ,m2 ,m3 ,m4) throw type(__FILE__, __LINE__ , m1, m2, m3, m4)

_jomoo_end

#endif
