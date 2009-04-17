#ifndef STRINGPTR_H
# define STRINGPTR_H

#include "jingxian/config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
# include "jingxian/string/string_traits.hpp"

_jingxian_begin

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

_jingxian_end

#endif // STRINGPTR_H
