
#ifndef SAXPARSEEXCEPTION_HPP
#define SAXPARSEEXCEPTION_HPP

# include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_MicroKernel.h"
# include "ILocator.hpp"

_micro_kernel_xml_begin

class SAXParseException : public SAXException
{
public:

    SAXParseException( const   char* const         srcFile
            , size_t        srcLine
			, const ILocator& locator
			, const tstring& message )
			: _hazel Exception( srcFile, srcLine ,message )
			, publicId_( is_null( locator.getPublicId()) ? "":locator.getPublicId() )
			, systemId_(  is_null( locator.getSystemId()) ? "":locator.getSystemId() )
			, lineNumber_( locator.getLineNumber() )
			, column_number_( locator.getColumnNumber() )
	{
	}

    SAXParseException( const   char* const         srcFile
            , size_t			srcLine
			, const tstring&    publicId
			, const tstring&    systemId
			, size_t			lineNumber
			, size_t			columnNumber
			, const tstring& message)
			: _hazel Exception( srcFile, srcLine ,message )
			, publicId_( publicId )
			, systemId_( systemId )
			, lineNumber_( lineNumber )
			, column_number_( columnNumber )
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
			Target << "[ line_number=" << line_number();
			Target << ",column_number=" << column_number();
			Target << ",public_id=" << public_id();
			Target << ",system_id=" << system_id();
			Target << "]";
		}

    size_t column_number() const
	{
		return columnNumber_;
	}

    size_t line_number() const
	{
		return lineNumber_;
	}

    const tstring& public_id() const
	{
		return publicId_;
	}

    const tstring system_id() const
	{
		return systemId_;
	}

private:
	tstring    publicId_;
	tstring    systemId_;
	size_t			lineNumber_;
	size_t			column_number_;
};

_micro_kernel_xml_end

#endif
