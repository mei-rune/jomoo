#ifndef SEAL_BASE_OPS_STRING_OPS_H
# define SEAL_BASE_OPS_STRING_OPS_H

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

# include <memory>
# include <string>
# include <vector>
# include "string_traits.hpp"

_jomoo_begin

namespace StringOps
{
	namespace detail
	{
		template< typename charT >
		class StringOp
		{
		public:
			static charT* dup( const charT* p )
			{
				return string_traits< charT>::strdup( p );
			}

			static void free( charT* p)
			{
				string_traits< charT>::free( p );
			}
		};
	};

	template< typename charT , typename OP = detail::StringOp<charT> >
	class StringPtr
	{
	public:
		StringPtr(charT * ptr = 0, size_t len = -1) _THROW0()
			: _ptr(ptr)
			, _length( (-1 == len)?string_traits< charT>::strlen( ptr): len )
		{
		}

		StringPtr(StringPtr& right) _THROW0()
			: _ptr( 0 )
			, _length( 0 )
		{
			_length = right.size();
			_ptr = right.release();
		}

		template< typename STRING >
		StringPtr(const STRING& right) _THROW0()
			: _ptr( 0 )
			, _length( 0 )
		{
			if( !right.empty() )
			{
				_ptr = OP::dup( right.c_str() );
				_length = right.size();
			}
		}

		StringPtr& operator=(StringPtr& right) _THROW0()
		{
			size_t l = right.size();
			reset(right.release(), l );
			return (*this);
		}

		~StringPtr()
		{
			reset();
		}

		charT *get() const _THROW0()
		{
			return (_ptr);
		}

		charT *c_str() const _THROW0()
		{
			return (_ptr);
		}

		size_t size() const
		{
			return _length;
		}

		charT *release() _THROW0()
		{
			charT *_Tmp = _ptr;
			_ptr = 0;
			//_length = 0;
			return (_Tmp);
		}

		void reset(charT* ptr = 0, size_t l = -1)
		{
			if (ptr != _ptr)
			{
				OP::free( _ptr );
				_length = 0;
			}
			_ptr = ptr;
			_length = (-1 == l)?string_traits<charT>::strlen( _ptr ): l ;
		}

	private:
		charT *_ptr;
		size_t _length;
	};
}
_jomoo_end

#endif // SEAL_BASE_OPS_STRING_OPS_H
