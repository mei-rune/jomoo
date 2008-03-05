#ifndef is_empty_H
# define is_empty_H

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files

_JOMOO_begin

#ifdef _STRING_
template<class _Elem,
	class _Traits,
	class _Alloc>
inline bool is_empty( const std::basic_string< _Elem ,_Traits , _Alloc>& string_ )
	{
		return string_.empty();
	}
#endif

#ifdef _LIST_
template<class _Ty,
	class _Alloc>
		inline bool is_empty( const std::list< _Ty, _Alloc >& list_ )
	{
		return list_.empty();
	}
#endif

#ifdef _VECTOR_
template<class _Ty,
	class _Alloc>
		inline bool is_empty( const std::vector< _Ty, _Alloc >& vector_ )
	{
		return vector_.empty();
	}
#endif

#ifdef _MAP_
template<class _Kty,
	class _Ty,
	class _Pr,
	class _Alloc >
		inline bool is_empty( const std::map< _Kty,_Ty,_Pr , _Alloc >& map_ )
	{
		return map_.empty();
	}
template<class _Kty,
	class _Ty,
	class _Pr,
	class _Alloc >
		inline bool is_empty( const std::multimap< _Kty,_Ty,_Pr , _Alloc >& map_ )
	{
		return map_.empty();
	}
#endif

#ifdef _HASH_MAP_
template<class _Kty,
	class _Ty,
	class _Pr,
	class _Alloc >
		inline bool is_empty( const _STDEXT hash_map< _Kty,_Ty,_Pr , _Alloc >& map_ )
	{
		return map_.empty();
	}
template<class _Kty,
	class _Ty,
	class _Pr,
	class _Alloc >
		inline bool is_empty( const _STDEXT hash_multimap< _Kty,_Ty,_Pr , _Alloc >& map_ )
	{
		return map_.empty();
	}
#endif

#ifdef _SET_
template<class _Kty,
	class _Pr,
	class _Alloc > 
		inline bool is_empty( const std::set< _Kty,_Pr , _Alloc >& set_ )
	{
		return set_.empty();
	}
	template<class _Kty,
	class _Pr,
	class _Alloc > 
		inline bool is_empty( const std::multiset< _Kty,_Pr , _Alloc >& set_ )
	{
		return set_.empty();
	}
#endif

#ifdef _HASH_SET_
template<class _Kty,
	class _Pr,
	class _Alloc > 
		inline bool is_empty( const _STDEXT set< _Kty,_Pr , _Alloc >& set_ )
	{
		return set_.empty();
	}
	template<class _Kty,
	class _Pr,
	class _Alloc > 
		inline bool is_empty( const _STDEXT multiset< _Kty,_Pr , _Alloc >& set_ )
	{
		return set_.empty();
	}
#endif

_JOMOO_end

#endif // is_empty_H
