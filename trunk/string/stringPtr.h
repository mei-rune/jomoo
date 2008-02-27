#ifndef SEAL_BASE_OPS_STRING_OPS_H
# define SEAL_BASE_OPS_STRING_OPS_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

# include <memory>
# include <string>
# include <vector>

_hazel_begin

namespace StringOps
{

	namespace detail
	{
		template< typename charT >
		class StringOp
		{
		public:
			typedef charT char_type;

			static char_type* dup( const char_type* p )
			{
				return _tcsdup( p );
			}

			static void free( char_type* p)
			{
				::free( p );
			}
		};
	}

	template< typename charT, typename OP = StringOp<charT> >
	class StringPtr
	{
	public:
			typedef charT value_type;
			typedef size_t size_type;
			enum
			{
				npos = tstring::npos;
			};
			

		explicit StringPtr(value_type *_Ptr = 0) _THROW0()
			: _Myptr(_Ptr)
			, _length( npos )
		{
		}

		StringPtr(StringPtr& _Right) _THROW0()
			: _Myptr(_Right.release())
			, _length( _Right._length )
		{
		}

		template< typename stringT >
		StringPtr(const stringT& _Right) _THROW0()
			: _Myptr( 0 )
			, _length( npos )
		{
			if( !_Right.empty() )
			{
				_Myptr = OP::dup(_Right.c_str() );
				_length = _Right.size();
			}
		}

		StringPtr& operator=(StringPtr& _Right) _THROW0()
		{
			reset(_Right.release(), _Right._length);
			return (*this);
		}

		~StringPtr()
		{
			reset();
		}

		value_type *get() const _THROW0()
		{
			return (_Myptr);
		}

		const value_type *c_str() const _THROW0()
		{
			return (_Myptr);
		}

		value_type *release() _THROW0()
		{
			value_type *_Tmp = _Myptr;
			_Myptr = 0;
			_length = npos;
			return (_Tmp);
		}

		void reset(value_type* _Ptr = 0,size_type len = npos )
		{
			if (_Ptr != _Myptr)
				OP::free( _Myptr );

			_Myptr = _Ptr;
			_length = len;
		}

		size_type size() const
		{
			if( 0 == _Myptr) return npos;
			if( npos == _length) 
				_length = string_traits<value_type>::strlen( _Myptr );
			return _length;
		}

	private:
		value_type *_Myptr;
		mutable size_t _length;
	};
}
_hazel_end

#endif // SEAL_BASE_OPS_STRING_OPS_H
