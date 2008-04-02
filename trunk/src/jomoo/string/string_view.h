#ifndef _basic_string_view_hpp_
#define _basic_string_view_hpp_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include <xutility>
#include "stringOps.h"
#include "../random_iterator.hpp"

#if _DEBUG

#define STRING_DEBUG_POINTER(first) std::_Debug_pointer(first, __FILEW__,__LINE__)

#else

#define STRING_DEBUG_POINTER(first) 

#endif

template<class _Elem>
struct string_types
{
	typedef _Elem value_type;
	typedef value_type* pointer;
	typedef value_type & reference;
	typedef const value_type * const_pointer;
	typedef const value_type & const_reference;
};

template<class _Elem>
struct const_string_types
{
	typedef _Elem value_type;
	typedef const value_type * pointer;
	typedef const value_type & reference;
	typedef const value_type * const_pointer;
	typedef const value_type & const_reference;
};

template<class _Elem ,
	class _Types = const_string_types<_Elem> ,
	class _Traits = std::char_traits<_Elem> >
class basic_string_view
{
public:

	typedef _Traits traits_type;

	typedef typename _Types::value_type value_type;
	typedef typename _Types::pointer pointer;
	typedef typename _Types::reference reference;
	typedef typename _Types::const_pointer const_pointer;
	typedef typename _Types::const_reference const_reference;
	
	typedef _SIZT size_type;
	typedef _PDFT difference_type;
	typedef basic_string_view< _Elem, _Types,_Traits > _Myt;

	typedef random_iterator< value_type, difference_type, pointer, reference  > iterator;
	typedef random_iterator< value_type, difference_type, const_pointer, const_reference  > const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	basic_string_view(pointer _Ptr)
	: pointer_( _Ptr )
	, length_( _Traits::length(_Ptr) )
	{}

	basic_string_view(pointer str, size_type len )
	: pointer_( str )
	, length_( len )
	{}

    basic_string_view& operator = (const basic_string_view& rhs)
	{
		pointer_ = rhs.pointer_;
		length_ = rhs.length_;
	}

	basic_string_view(const basic_string_view& rhs)
	: pointer_(rhs.pointer_)
	, length_(rhs.length_) 
	{}

	basic_string_view(const basic_string_view& rhs, size_type _Off, size_type _Count = npos)
	: pointer_( rhs.pointer_ + _Off )
	, length_( _Count ) 
	{
		if (rhs.size() < _Off)
			_policy::out_of_range();
		if (rhs.length_ - _Off < _Count)
			length_ = rhs.length_ - _Off;
	}

    size_type size(void) const
	{
		return length_;
	}

    pointer buf() const
	{
		return pointer_;
	}

	iterator begin()
		{
		return iterator(pointer_, length_, 0);
		}

	const_iterator begin() const
		{
			return const_iterator(pointer_, length_, 0);
		}

	iterator end()
		{
			return iterator(pointer_, length_, length_);
		}

	const_iterator end() const
		{
			return const_iterator(pointer_, length_, length_);
		}

	reverse_iterator rbegin()
		{
		return (reverse_iterator(end()));
		}

	const_reverse_iterator rbegin() const
		{
		return (const_reverse_iterator(end()));
		}

	reverse_iterator rend()
		{
		return (reverse_iterator(begin()));
		}

	const_reverse_iterator rend() const
		{
		return (const_reverse_iterator(begin()));
		}

	reference at(size_type _Off)
		{
		if (length_ <= _Off)
			throw std::out_of_range( "" );
		return (pointer_[_Off]);
		}

	const_reference at(size_type _Off) const
		{
		if (length_ <= _Off)
			throw std::out_of_range("");
		return (pointer_[_Off]);
		}

	reference operator[](size_type _Off)
		{
		if (length_ <= _Off)
			throw std::out_of_range( "" );
		return (pointer_[_Off]);
		}

	const_reference operator[](size_type _Off) const
		{
		if (length_ <= _Off)
			throw std::out_of_range( "" );
		return (pointer_[_Off]);
		}

	bool empty() const
		{
		return (length_ == 0);
		}

	
	size_type find(const _Myt& _Right, size_type _Off = 0) const
		{	// look for _Right beginnng at or after _Off
		return (find(_Right.buf(), _Off, _Right.size()));
		}

	size_type find(const _Elem *_Ptr,
		size_type _Off, size_type _Count) const
		{
		STRING_DEBUG_POINTER(_Ptr);
		if (_Count == 0 && _Off <= length_ )
			return (_Off);

		size_type _Nm;
		if (_Off < length_ && _Count <= (_Nm = length_ - _Off))
			{
			// 先找到_Ptr第一个字符的位置，再比较整个_Ptr字符串
			// _Vptr 为字符串的偏移位置
			// _Uptr为_Ptr第一个字符在_Vptr指向的字符串的中的位置
			const _Elem *_Uptr, *_Vptr;
			for (_Nm -= _Count - 1, _Vptr = buf() + _Off;
				(_Uptr = _Traits::find(_Vptr, _Nm, *_Ptr)) != 0;
				_Nm -= _Uptr - _Vptr + 1, _Vptr = _Uptr + 1)
				if (_Traits::compare(_Uptr, _Ptr, _Count) == 0)
					return (_Uptr - buf());	// found a match
			}

		return (npos);	// no match
		}

	size_type find(const _Elem *_Ptr, size_type _Off = 0) const
		{
		return (find(_Ptr, _Off, _Traits::length(_Ptr)));
		}

	size_type find(_Elem _Ch, size_type _Off = 0) const
		{
		return (find((const _Elem *)&_Ch, _Off, 1));
		}

	size_type rfind(const _Myt& _Right, size_type _Off = npos) const
		{
		return (rfind(_Right.buf(), _Off, _Right.size()));
		}

	size_type rfind(const _Elem *_Ptr,
		size_type _Off, size_type _Count) const
		{
		STRING_DEBUG_POINTER(_Ptr);
		if (_Count == 0)
			return (_Off < length_ ? _Off : length_);	// null always matches
		if (_Count <= length_)
			{
			const _Elem *_Uptr = buf() +
				(_Off < length_ - _Count ? _Off : length_ - _Count);
			for (; ; --_Uptr)
				if (_Traits::eq(*_Uptr, *_Ptr)
					&& _Traits::compare(_Uptr, _Ptr, _Count) == 0)
					return (_Uptr - buf());	// found a match
				else if (_Uptr == buf())
					break;
			}

		return (npos);	// no match
		}

	size_type rfind(const _Elem *_Ptr, size_type _Off = npos) const
		{
		return (rfind(_Ptr, _Off, _Traits::length(_Ptr)));
		}

	size_type rfind(_Elem _Ch, size_type _Off = npos) const
		{
		return (rfind((const _Elem *)&_Ch, _Off, 1));
		}

	size_type find_first_of(const _Myt& _Right,
		size_type _Off = 0) const
		{
		return (find_first_of(_Right.buf(), _Off, _Right.size()));
		}

	size_type find_first_of(const _Elem *_Ptr,
		size_type _Off, size_type _Count) const
		{
		STRING_DEBUG_POINTER(_Ptr);
		if (0 < _Count && _Off < length_)
			{
			const _Elem *const _Vptr = buf() + length_;
			for (const _Elem *_Uptr = buf() + _Off; _Uptr < _Vptr; ++_Uptr)
				if (_Traits::find(_Ptr, _Count, *_Uptr) != 0)
					return (_Uptr - buf());
			}
		return (npos);
		}

	size_type find_first_of(const _Elem *_Ptr, size_type _Off = 0) const
		{
		return (find_first_of(_Ptr, _Off, _Traits::length(_Ptr)));
		}

	size_type find_first_of(_Elem _Ch, size_type _Off = 0) const
		{
		return (find((const _Elem *)&_Ch, _Off, 1));
		}

	size_type find_last_of(const _Myt& _Right,
		size_type _Off = npos) const
		{
		return (find_last_of(_Right.buf(), _Off, _Right.size()));
		}

	size_type find_last_of(const _Elem *_Ptr,
		size_type _Off, size_type _Count) const
		{
		STRING_DEBUG_POINTER(_Ptr);
		if (0 < _Count && 0 < length_)
			for (const _Elem *_Uptr = buf()
				+ (_Off < length_ ? _Off : length_ - 1); ; --_Uptr)
				if (_Traits::find(_Ptr, _Count, *_Uptr) != 0)
					return (_Uptr - buf());	// found a match
				else if (_Uptr == buf())
					break;

		return (npos);
		}

	size_type find_last_of(const _Elem *_Ptr,
		size_type _Off = npos) const
		{
		return (find_last_of(_Ptr, _Off, _Traits::length(_Ptr)));
		}

	size_type find_last_of(_Elem _Ch, size_type _Off = npos) const
		{
		return (rfind((const _Elem *)&_Ch, _Off, 1));
		}

	size_type find_first_not_of(const _Myt& _Right,
		size_type _Off = 0) const
		{
		return (find_first_not_of(_Right.buf(), _Off,
			_Right.size()));
		}

	size_type find_first_not_of(const _Elem *_Ptr,
		size_type _Off, size_type _Count) const
		{	// look for none of [_Ptr, _Ptr + _Count) at or after _Off
		STRING_DEBUG_POINTER(_Ptr);
		if (_Off < length_)
			{	// room for match, look for it
			const _Elem *const _Vptr = buf() + length_;
			for (const _Elem *_Uptr = buf() + _Off; _Uptr < _Vptr; ++_Uptr)
				if (_Traits::find(_Ptr, _Count, *_Uptr) == 0)
					return (_Uptr - buf());
			}
		return (npos);
		}

	size_type find_first_not_of(const _Elem *_Ptr,
		size_type _Off = 0) const
		{	// look for one of [_Ptr, <null>) at or after _Off
		return (find_first_not_of(_Ptr, _Off, _Traits::length(_Ptr)));
		}

	size_type find_first_not_of(_Elem _Ch, size_type _Off = 0) const
		{	// look for non _Ch at or after _Off
		return (find_first_not_of((const _Elem *)&_Ch, _Off, 1));
		}

	size_type find_last_not_of(const _Myt& _Right,
		size_type _Off = npos) const
		{	// look for none of _Right before _Off
		return (find_last_not_of(_Right.buf(), _Off, _Right.size()));
		}

	size_type find_last_not_of(const _Elem *_Ptr,
		size_type _Off, size_type _Count) const
		{	// look for none of [_Ptr, _Ptr + _Count) before _Off
		STRING_DEBUG_POINTER(_Ptr);
		if (0 < length_)
			for (const _Elem *_Uptr = buf()
				+ (_Off < length_ ? _Off : length_ - 1); ; --_Uptr)
				if (_Traits::find(_Ptr, _Count, *_Uptr) == 0)
					return (_Uptr - buf());
				else if (_Uptr == buf())
					break;
		return (npos);
		}

	size_type find_last_not_of(const _Elem *_Ptr,
		size_type _Off = npos) const
		{	// look for none of [_Ptr, <null>) before _Off
		return (find_last_not_of(_Ptr, _Off, _Traits::length(_Ptr)));
		}

	size_type find_last_not_of(_Elem _Ch, size_type _Off = npos) const
		{	// look for non _Ch before _Off
		return (find_last_not_of((const _Elem *)&_Ch, _Off, 1));
		}

	_Myt substr(size_type _Off = 0, size_type _Count = npos) const
		{
		return (_Myt(*this, _Off, _Count));
		}

	int compare(const _Myt& _Right) const
		{
		return (compare(0, length_, _Right.buf(), _Right.size()));
		}

	int compare(size_type _Off, size_type _N0,
		const _Myt& _Right) const
		{
		return (compare(_Off, _N0, _Right, 0, npos));
		}

	int compare(size_type _Off,
		size_type _N0, const _Myt& _Right,
		size_type _Roff, size_type _Count) const
		{
		if (_Right.size() < _Roff)
			_policy::out_of_range();
		if (_Right.length_ - _Roff < _Count)
			_Count = _Right.length_ - _Roff;	// trim _Count to size
		return (compare(_Off, _N0, _Right.buf() + _Roff, _Count));
		}

	int compare(const _Elem *_Ptr) const
		{	// compare [0, length_) with [_Ptr, <null>)
		return (compare(0, length_, _Ptr, _Traits::length(_Ptr)));
		}

	int compare(size_type _Off, size_type _N0, const _Elem *_Ptr) const
		{	// compare [_Off, _Off + _N0) with [_Ptr, <null>)
		return (compare(_Off, _N0, _Ptr, _Traits::length(_Ptr)));
		}

	int compare(size_type _Off,
		size_type _N0, const _Elem *_Ptr, size_type _Count) const
		{	// compare [_Off, _Off + _N0) with [_Ptr, _Ptr + _Count)
		STRING_DEBUG_POINTER(_Ptr);
		if (length_ < _Off)
			throw std::out_of_range( "" );
		if (length_ - _Off < _N0)
			_N0 = length_ - _Off;	// trim _N0 to size

		size_type _Ans = _Traits::compare(buf() + _Off, _Ptr,
			_N0 < _Count ? _N0 : _Count);
		return (_Ans != 0 ? (int)_Ans : _N0 < _Count ? -1
			: _N0 == _Count ? 0 : +1);
		}

	void swap(_Myt& _Right)
		{
			_Myt _Tmp = *this;
			*this = _Right;
			_Right = _Tmp;
		}
		
public:

	static const size_type npos = -1 ;
	//enum
	//{
	//	npos = (size_type)(-1)
	//};
private:
	pointer pointer_;
	size_type length_;
};



// basic_string TEMPLATE OPERATORS
//template<class _Elem,
//	class _Types ,
//	class _Traits > inline
//	class _Alloc ,
//	
//	basic_string<_Elem, _Traits, _Alloc> operator+(
//		const std::basic_string<_Elem, _Traits, _Alloc>& _Left,
//		const basic_string_view<_Elem,_Types, _Traits>& _Right)
//	{	// return string + string
//	return (basic_string<_Elem, _Traits, _Alloc>(_Left).append( _Right.buf(), _Right.size() ));
//	}
//template<class _Elem,
//	class _Types ,
//	class _Traits > inline
//	class _Alloc ,
//	
//	basic_string<_Elem, _Traits, _Alloc> operator+(
//		const basic_string_view<_Elem,_Types, _Traits>& _Left,
//		const std::basic_string<_Elem, _Traits, _Alloc>& _Right)
//	{	// return string + string
//	return (basic_string<_Elem, _Traits, _Alloc>( _Right.buf(), _Right.size()) += _Right);
//	}
//
//template<class _Elem,
//	class _Types ,
//	class _Traits > inline
//	
//	basic_string<_Elem, _Traits > operator+(
//		const _Elem *_Left,
//		const basic_string_view<_Elem,_Types, _Traits>& _Right)
//	{	// return NTCS + string
//	return (basic_string<_Elem, _Traits>(_Left).append( _Right.buf(), _Right.size() ) );
//	}
//
//template<class _Elem,
//	class _Types ,
//	class _Traits > inline
//	
//	basic_string<_Elem, _Traits, _Alloc> operator+(
//		const _Elem _Left,
//		const basic_string_view<_Elem,_Types, _Traits>& _Right)
//	{	// return character + string
//	return (basic_string<_Elem, _Traits>(1, _Left).append( _Right.buf(), _Right.size() ) );
//	}
//
//template<class _Elem,
//	class _Types ,
//	class _Traits > inline
//	
//	basic_string<_Elem, _Traits, _Alloc> operator+(
//		const basic_string_view<_Elem,_Types, _Traits>& _Left,
//		const _Elem *_Right)
//	{	// return string + NTCS
//	return (basic_string<_Elem, _Traits>(_Left.buf(), _Left.size()) += _Right);
//	}
//
//template<class _Elem,
//	class _Types ,
//	class _Traits > inline
//	
//	basic_string<_Elem, _Traits, _Alloc> operator+(
//		const basic_string_view<_Elem,_Types, _Traits>& _Left,
//		const _Elem _Right)
//	{	// return string + character
//	return (basic_string<_Elem, _Traits>(_Left.buf(), _Left.size()) += _Right);
//	}

template<class _Elem,
	class _Types ,
	class _Traits > inline
	
	bool operator==(
		const basic_string_view<_Elem,_Types, _Traits>& _Left,
		const basic_string_view<_Elem,_Types, _Traits>& _Right)
	{	// test for string equality
	return (_Left.compare(_Right) == 0);
	}

template<class _Elem,
	class _Types ,
	class _Traits ,
	class _Alloc  > inline
	
	bool operator==(
		const std::basic_string<_Elem, _Traits, _Alloc>& _Left,
		const basic_string_view<_Elem,_Types, _Traits>& _Right)
	{	// test for string equality
	return (_Left.compare(_Right.buf(), _Right.size() ) == 0);
	}

template<class _Elem,
	class _Types ,
	class _Traits ,
	class _Alloc  > inline
	
	bool operator==(
		const basic_string_view<_Elem,_Types, _Traits>& _Left,
		const std::basic_string<_Elem, _Traits, _Alloc>& _Right)
	{	// test for string equality
	return (_Left.compare(_Right.buf(), _Right.size()) == 0);
	}

template<class _Elem,
	class _Types ,
	class _Traits > inline
	
	bool operator==(
		const _Elem * _Left,
		const basic_string_view<_Elem,_Types, _Traits>& _Right)
	{	// test for NTCS vs. string equality
	return (_Right.compare(_Left) == 0);
	}

template<class _Elem,
	class _Types ,
	class _Traits > inline
	
	bool operator==(
		const basic_string_view<_Elem,_Types, _Traits>& _Left,
		const _Elem *_Right)
	{	// test for string vs. NTCS equality
	return (_Left.compare(_Right) == 0);
	}

template<class _Elem,
	class _Types ,
	class _Traits > inline
	
	bool operator!=(
		const basic_string_view<_Elem,_Types, _Traits>& _Left,
		const basic_string_view<_Elem,_Types, _Traits>& _Right)
	{	// test for string inequality
	return (!(_Left == _Right));
	}

template<class _Elem,
	class _Types ,
	class _Traits ,
	class _Alloc > inline
	
	bool operator!=(
		const basic_string_view<_Elem,_Types, _Traits>& _Left,
		const std::basic_string<_Elem, _Traits, _Alloc>& _Right)
	{	// test for string inequality
	return (!(_Left == _Right));
	}

	template<class _Elem,
	class _Types ,
	class _Traits ,
	class _Alloc  > inline
	
	bool operator!=(
		const std::basic_string<_Elem, _Traits, _Alloc>& _Left,
		const basic_string_view<_Elem,_Types, _Traits>& _Right)
	{	// test for string inequality
	return (!(_Left == _Right));
	}

template<class _Elem,
	class _Types ,
	class _Traits > inline
	
	bool operator!=(
		const _Elem *_Left,
		const basic_string_view<_Elem,_Types, _Traits>& _Right)
	{	// test for NTCS vs. string inequality
	return (!(_Left == _Right));
	}

template<class _Elem,
	class _Types ,
	class _Traits > inline
	
	bool operator!=(
		const basic_string_view<_Elem,_Types, _Traits>& _Left,
		const _Elem *_Right)
	{	// test for string vs. NTCS inequality
	return (!(_Left == _Right));
	}

template<class _Elem,
	class _Types ,
	class _Traits > inline
	
	bool operator<(
		const basic_string_view<_Elem,_Types, _Traits>& _Left,
		const basic_string_view<_Elem,_Types, _Traits>& _Right)
	{	// test if string < string
	return (_Left.compare(_Right) < 0);
	}

template<class _Elem,
	class _Types ,
	class _Traits ,
	class _Alloc   > inline
	
	bool operator<(
		const basic_string_view<_Elem,_Types, _Traits>& _Left,
		const std::basic_string<_Elem, _Traits, _Alloc>& _Right)
	{	// test if string < string
	return (_Left.compare(_Right.c_str(), _Right.size() ) < 0);
	}

template<class _Elem,
	class _Types ,
	class _Traits ,
	class _Alloc   > inline
	
	bool operator<(
		const std::basic_string<_Elem, _Traits, _Alloc>& _Left,
		const basic_string_view<_Elem,_Types, _Traits>& _Right)
	{	// test if string < string
	return (_Left.compare(_Right.buf(), _Right.size() ) < 0);
	}

template<class _Elem,
	class _Types ,
	class _Traits > inline
	
	bool operator<(
		const _Elem * _Left,
		const basic_string_view<_Elem,_Types, _Traits>& _Right)
	{	// test if NTCS < string
	return (_Right.compare(_Left) > 0);
	}

template<class _Elem,
	class _Types ,
	class _Traits > inline
	
	bool operator<(
		const basic_string_view<_Elem,_Types, _Traits>& _Left,
		const _Elem *_Right)
	{	// test if string < NTCS
	return (_Left.compare(_Right) < 0);
	}

template<class _Elem,
	class _Types ,
	class _Traits > inline
	
	bool operator>(
		const basic_string_view<_Elem,_Types, _Traits>& _Left,
		const basic_string_view<_Elem,_Types, _Traits>& _Right)
	{	// test if string > string
	return (_Right < _Left);
	}

template<class _Elem,
	class _Types ,
	class _Traits ,
	class _Alloc   > inline
	
	bool operator>(
		const basic_string_view<_Elem,_Types, _Traits>& _Left,
		const std::basic_string<_Elem, _Traits, _Alloc>& _Right)
	{	// test if string > string
	return (_Right < _Left);
	}

template<class _Elem,
	class _Types ,
	class _Traits ,
	class _Alloc  > inline
	
	bool operator>(
		const std::basic_string<_Elem, _Traits, _Alloc>& _Left,
		const basic_string_view<_Elem,_Types, _Traits>& _Right)
	{	// test if string > string
	return (_Right < _Left);
	}

template<class _Elem,
	class _Types ,
	class _Traits > inline
	
	bool operator>(
		const _Elem * _Left,
		const basic_string_view<_Elem,_Types, _Traits>& _Right)
	{	// test if NTCS > string
	return (_Right < _Left);
	}

template<class _Elem,
	class _Types ,
	class _Traits > inline
	
	bool operator>(
		const basic_string_view<_Elem,_Types, _Traits>& _Left,
		const _Elem *_Right)
	{	// test if string > NTCS
	return (_Right < _Left);
	}

template<class _Elem,
	class _Types ,
	class _Traits > inline
	
	bool operator<=(
		const basic_string_view<_Elem,_Types, _Traits>& _Left,
		const basic_string_view<_Elem,_Types, _Traits>& _Right)
	{	// test if string <= string
	return (!(_Right < _Left));
	}

template<class _Elem,
	class _Types ,
	class _Traits ,
	class _Alloc > inline
	
	bool operator<=(
		const basic_string_view<_Elem,_Types, _Traits>& _Left,
		const std::basic_string<_Elem, _Traits, _Alloc>& _Right)
	{	// test if string <= string
	return (!(_Right < _Left));
	}

template<class _Elem,
	class _Types ,
	class _Traits ,
	class _Alloc > inline
	
	bool operator<=(
		const std::basic_string<_Elem, _Traits, _Alloc>& _Left,
		const basic_string_view<_Elem,_Types, _Traits>& _Right)
	{	// test if string <= string
	return (!(_Right < _Left));
	}

template<class _Elem,
	class _Types ,
	class _Traits > inline
	
	bool operator<=(
		const _Elem * _Left,
		const basic_string_view<_Elem,_Types, _Traits>& _Right)
	{	// test if NTCS <= string
	return (!(_Right < _Left));
	}

template<class _Elem,
	class _Types ,
	class _Traits > inline
	
	bool operator<=(
		const basic_string_view<_Elem,_Types, _Traits>& _Left,
		const _Elem *_Right)
	{	// test if string <= NTCS
	return (!(_Right < _Left));
	}

template<class _Elem,
	class _Types ,
	class _Traits > inline
	
	bool operator>=(
		const basic_string_view<_Elem,_Types, _Traits>& _Left,
		const basic_string_view<_Elem,_Types, _Traits>& _Right)
	{	// test if string >= string
	return (!(_Left < _Right));
	}

template<class _Elem,
	class _Types ,
	class _Traits ,
	class _Alloc > inline
	
	bool operator>=(
		const basic_string_view<_Elem,_Types, _Traits>& _Left,
		const std::basic_string<_Elem, _Traits, _Alloc>& _Right)
	{	// test if string >= string
	return (!(_Left < _Right));
	}

template<class _Elem,
	class _Types ,
	class _Traits ,
	class _Alloc > inline
	
	bool operator>=(
		const std::basic_string<_Elem, _Traits, _Alloc>& _Left,
		const basic_string_view<_Elem,_Types, _Traits>& _Right)
	{	// test if string >= string
	return (!(_Left < _Right));
	}

template<class _Elem,
	class _Types ,
	class _Traits > inline
	
	bool operator>=(
		const _Elem * _Left,
		const basic_string_view<_Elem,_Types, _Traits>& _Right)
	{	// test if NTCS >= string
	return (!(_Left < _Right));
	}

template<class _Elem,
	class _Types ,
	class _Traits > inline
	
	bool operator>=(
		const basic_string_view<_Elem,_Types, _Traits>& _Left,
		const _Elem *_Right)
	{	// test if string >= NTCS
	return (!(_Left < _Right));
	}



	typedef basic_string_view< char_t > string_view;
	typedef basic_string_view< wchar_t > wstring_view;

	//typedef basic_string_view< char_t > string_view;
	//typedef basic_string_view< wchar_t > wstring_view;

#endif /* _basic_string_view_hpp_ */
