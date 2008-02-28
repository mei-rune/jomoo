#ifndef SAXEXCEPTION_HPP
#define SAXEXCEPTION_HPP

# include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_MicroKernel.h"

_micro_kernel_xml_begin

class SAXException : public _hazel Exception
{
public:
		SAXException( const   char* const         srcFile
            , size_t        srcLine
			, const tstring& message )
			: _hazel Exception( srcFile, srcLine ,message )
		{
		}

		virtual ~SAXException()
		{
		}

		virtual Exception* clone()
		{
			return new SAXNotSupportedException( *this );
		}

		virtual void rethrow()
		{
			Raise( *this );
		}

		virtual void print(std::ostream& Target ) const
		{
			Target << "SAXException[file:" <<  fSrcFile << " line:" << ( int ) fSrcLine << "] " << what() << std::endl;
		}
};

class SAXNotSupportedException : public SAXException
{
public:
		SAXNotSupportedException( const   char* const         srcFile
            , size_t        srcLine
			, const tstring& message )
			: _hazel Exception( srcFile, srcLine ,message )
		{
		}

		virtual Exception* clone()
		{
			return new SAXNotSupportedException( *this );
		}

		virtual void rethrow()
		{
			Raise( *this );
		}

		virtual void print(std::ostream& Target ) const
		{
			Target << "SAXNotSupportedException[file:" <<  fSrcFile << " line:" << ( int ) fSrcLine << "] " << what() << std::endl;
		}
};

class SAXNotRecognizedException : public SAXException
{
public:
		SAXNotRecognizedException( const   char* const         srcFile
            , size_t        srcLine
			, const tstring& message )
			: _hazel Exception( srcFile, srcLine ,message )
		{
		}

		virtual Exception* clone()
		{
			return new SAXNotRecognizedException( *this );
		}

		virtual void rethrow()
		{
			Raise( *this );
		}

		virtual void print(std::ostream& Target ) const
		{
			Target << "SAXNotRecognizedException[file:" <<  fSrcFile << " line:" << ( int ) fSrcLine << "] " << what() << std::endl;
		}
};

_micro_kernel_xml_end

#endif
