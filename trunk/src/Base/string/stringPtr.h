#ifndef SEAL_BASE_OPS_STRING_OPS_H
# define SEAL_BASE_OPS_STRING_OPS_H

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

# include <memory>
# include <string>
# include <vector>

_JOMOO_begin

namespace StringOps
{

	namespace detail
	{
		class StringOp
		{
		public:
			static tchar* dup( const tchar* p )
			{
				return _tcsdup( p );
			}

			static void free( tchar* p)
			{
				::free( p );
			}
		};
	}

	template< typename OP = StringOp >
	class StringPtr
	{
	public:
		explicit StringPtr(tchar *_Ptr = 0) _THROW0()
			: _Myptr(_Ptr)
		{
		}

		StringPtr(StringPtr& _Right) _THROW0()
			: _Myptr(_Right.release())
		{
		}

		StringPtr(const tstring& _Right) _THROW0()
			: _Myptr( 0 )
		{
			if( !_Right.empty() )
				_Myptr = OP::dup(_Right.c_str() );
		}

		StringPtr& operator=(StringPtr& _Right) _THROW0()
		{
			reset(_Right.release());
			return (*this);
		}

		~StringPtr()
		{
			reset();
		}

		tchar *get() const _THROW0()
		{
			return (_Myptr);
		}

		tchar *c_str() const _THROW0()
		{
			return (_Myptr);
		}

		tchar *release() _THROW0()
		{
			tchar *_Tmp = _Myptr;
			_Myptr = 0;
			return (_Tmp);
		}

		void reset(tchar* _Ptr = 0)
		{
			if (_Ptr != _Myptr)
				OP::free( _Myptr );
			_Myptr = _Ptr;
		}

	private:
		tchar *_Myptr;
	};
}
_JOMOO_end

#endif // SEAL_BASE_OPS_STRING_OPS_H
