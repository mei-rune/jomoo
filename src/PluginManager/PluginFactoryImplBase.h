#ifndef PLUGIN_MANAGER_FACTORY_IMPL_BASE_H
# define PLUGIN_MANAGER_FACTORY_IMPL_BASE_H

# include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_PluginManager.h"
# include "base/counter_ptr.hpp"
# include "base/string.hpp"
# include "base/exception.hpp"

_seal_begin
	class PluginInfoExistDefaultInfo : public _hazel Exception
	{
	public:

		PluginInfoExistDefaultInfo( const   char* const         srcFile
            , size_t        srcLine
			, const tstring& category
			, const tstring& old_name
			, const tstring& new_name
			, const tstring& message )
			: _hazel Exception( srcFile, srcLine ,message )
			, category_( category )
			, old_name_( old_name )
			, new_name_( new_name )
		{
		}

		const tstring& category() const
		{
			return category_;
		}

		const tstring& old_info() const
		{
			return old_name_;
		}

		const tstring& new_info() const
		{
			return new_name_;
		}

		virtual Exception* clone()
		{
			return new PluginInfoExistDefaultInfo( *this );
		}

		virtual void rethrow()
		{
			Raise( *this );
		}

		virtual void print(std::ostream& Target ) const
		{
			Target << "PluginInfoExistError[file:" <<  fSrcFile << " line:" << ( int ) fSrcLine << "] " << what() << std::endl;
			Target << "[ category=" << category_;
			Target << ",old_name=" << old_name_;
			Target << ",new_name=" << new_name_;
			Target << "]";
		}

	private:
		tstring category_;
		tstring new_name_;
		tstring old_name_;
	};	
	class PluginInfoExistError : public _hazel Exception
	{
	public:

		PluginInfoExistError( const   char* const         srcFile
            , size_t        srcLine
			, const tstring& category
			, const tstring& name
			, const tstring& message )
			: _hazel Exception( srcFile, srcLine ,message )
			, category_( category )
			, name_( name )
		{
		}

		const tstring& category() const
		{
			return category_;
		}

		const tstring& name() const
		{
			return name_;
		}
		virtual Exception* clone()
		{
			return new PluginInfoExistError( *this );
		}

		virtual void rethrow()
		{
			Raise( *this );
		}

		virtual void print(std::ostream& Target ) const
		{
			Target << "PluginInfoExistError[file:" <<  fSrcFile << " line:" << ( int ) fSrcLine << "] " << what() << std::endl;
			Target << "[ category=" << category_ << ",name=" << name_ << "]";
		}

	private:
		tstring category_;
		tstring name_;
	};	
	class PluginInfoNoExistError : public _hazel Exception
	{
	public:

		PluginInfoNoExistError(  const   char* const         srcFile
            , size_t        srcLine
			, const tstring& category
			, const tstring& name
			, const tstring& message )
			: _hazel Exception( srcFile, srcLine ,message )
			, category_( category )
			, name_( name )
		{
		}

		const tstring& category() const
		{
			return category_;
		}

		const tstring& name() const
		{
			return name_;
		}
		virtual Exception* clone()
		{
			return new PluginInfoNoExistError( *this );
		}

		virtual void rethrow()
		{
			Raise( *this );
		}

		virtual void print(std::ostream& Target ) const
		{
			Target << "PluginInfoNoExistError[file:" <<  fSrcFile << " line:" << ( int )fSrcLine << "] " << what() << std::endl;
			Target << "[ category=" << category_ << ",name=" << name_ << "]";
		}

	private:
		tstring category_;
		tstring name_;
	};

	class FacetoryRegisterError : public _hazel Exception
	{
	public:

		FacetoryRegisterError( const   char* const         srcFile
            , size_t        srcLine
			, const tstring& category
			, const tstring& name
			, const tstring& message )
			: _hazel Exception( srcFile, srcLine ,message )
			, category_( category )
			, name_( name )
		{
		}

		const tstring& category() const
		{
			return category_;
		}

		const tstring& name() const
		{
			return name_;
		}

		virtual Exception* clone()
		{
			return new FacetoryRegisterError( *this );
		}

		virtual void rethrow()
		{
			Raise( *this );
		}

		virtual void print(std::ostream& Target ) const
		{
			Target << "FacetoryRegisterError[file:" <<  fSrcFile << " line:" << ( int ) fSrcLine << "] " << what() << std::endl;
			Target << "[ category=" << category_ << ",name=" << name_ << "]";
		}

	private:
		tstring category_;
		tstring name_;
	};

	class FacetoryNoRegisterError : public _hazel Exception
	{
	public:

		FacetoryNoRegisterError(  const   char* const         srcFile
            , size_t        srcLine
			, const tstring& category
			, const tstring& name
			, const tstring& message )
			: _hazel Exception( srcFile, srcLine ,message )
			, category_( category )
			, name_( name )
		{
		}

		const tstring& category() const
		{
			return category_;
		}

		const tstring& name() const
		{
			return name_;
		}
		virtual Exception* clone()
		{
			return new FacetoryNoRegisterError( *this );
		}

		virtual void rethrow()
		{
			Raise( *this );
		}

		virtual void print(std::ostream& Target ) const
		{
			Target << "FacetoryNoRegisterError[file:" <<  fSrcFile << " line:" << ( int )fSrcLine << "] " << what() << std::endl;
			Target << "[ category=" << category_ << ",name=" << name_ << "]";
		}

	private:
		tstring category_;
		tstring name_;
	};

	class NoFactoryError : public _hazel Exception
	{
	public:

		NoFactoryError(  const   char* const         srcFile
            , size_t        srcLine
			, const tstring& category
			, const tstring& name
			, const tstring& message )
			: _hazel Exception( srcFile, srcLine ,message )
			, category_( category )
			, name_( name )
		{
		}

		const tstring& category() const
		{
			return category_;
		}

		const tstring& name() const
		{
			return name_;
		}
		virtual Exception* clone()
		{
			return new NoFactoryError( *this );
		}

		virtual void rethrow()
		{
			Raise( *this );
		}

		virtual void print(std::ostream& Target ) const
		{
			Target << "NoFactoryError[file:" <<  fSrcFile << " line:" << ( int ) fSrcLine << "] " << what() << std::endl;
			Target << "[ category=" << category_ << ",name=" << name_ << "]";
		}

	private:
		tstring category_;
		tstring name_;
	};


	class PluginInterfaceVersonException : public _hazel Exception
	{
	public:

		PluginInterfaceVersonException(  const   char* const         srcFile
            , size_t        srcLine
			, const tstring& category
			, const tstring& version )
			: _hazel Exception( srcFile, srcLine ,"°æ±¾´íÎó" )
			, category_( category )
			, version_( version )
		{
		}

		const tstring& category() const
		{
			return category_;
		}

		const tstring& version() const
		{
			return version_;
		}

		virtual Exception* clone()
		{
			return new PluginInterfaceVersonException( *this );
		}

		virtual void rethrow()
		{
			Raise( *this );
		}

		virtual void print(std::ostream& Target ) const
		{
			Target << "PluginInterfaceVersonException[file:" <<  fSrcFile << " line:" << ( int ) fSrcLine << "] " << what() << std::endl;
			Target << "[ category=" << category_ << ",version=" << version_ << "]";
		}

	private:
		tstring category_;
		tstring version_;
	};




class PluginFactoryImplBase
{
public:

	typedef counter_ptr< PluginFactoryImplBase > ptr_type;

	virtual ~PluginFactoryImplBase (void){};
	virtual const tstring &	category (void) const = 0;
	virtual const tstring &	version (void) const = 0;
	virtual const tstring& toString() const = 0;
};

typedef PluginFactoryImplBase::ptr_type PluginFactoryImplBasePtr;

//
//inline bool operator<( const PluginFactoryImplBase& A, const PluginFactoryImplBase& B )
//{
//	return A.category() < B.category();
//}
//
//inline bool operator>( const PluginFactoryImplBase& A, const PluginFactoryImplBase& B )
//{
//	return A.category() > B.category();
//}
//
//inline bool operator==( const PluginFactoryImplBase& A, const PluginFactoryImplBase& B )
//{
//	return A.category() == B.category();
//}
//
//inline bool operator!=( const PluginFactoryImplBase& A, const PluginFactoryImplBase& B )
//{
//	return A.category() != B.category();
//}
//
//inline bool operator<( PluginFactoryImplBasePtr A, PluginFactoryImplBasePtr B )
//{
//	if( is_null( A ) ) return true;
//	if( is_null( B ) ) return false;
//	return A->category() < B->category();
//}
//
//inline bool operator>( PluginFactoryImplBasePtr A, PluginFactoryImplBasePtr B )
//{
//	return !( B < A );
//}
//
//inline bool operator==( PluginFactoryImplBasePtr A, PluginFactoryImplBasePtr B )
//{
//	if( is_null( A ) )
//	{
//		if( is_null( B ) ) return true;
//		return false;
//	}
//	if( is_null( B ) ) return false;
//	return A->category() == B->category();
//}
//
//inline bool operator!=( PluginFactoryImplBasePtr A, PluginFactoryImplBasePtr B )
//{
//	return !( A->category() == B->category() );
//}

_seal_end

#endif // PLUGIN_MANAGER_FACTORY_IMPL_BASE_H
