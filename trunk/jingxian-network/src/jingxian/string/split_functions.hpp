
#ifndef _split_functions_hpp_
#define _split_functions_hpp_

#include "jingxian/config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
# include <functional>
# include <list>
# include "jingxian/string/string_traits.hpp"
# include "jingxian/string/stringArray.hpp"


_jingxian_begin


template<typename charT, typename OP >
inline StringArray<charT,OP> split( const charT* str, const charT* seps )
{
   charT* ptr = OP::dup( str );
   charT* next_token = NULL;

   std::list<charT*> tmpList;
   charT* token = string_traits<charT>::strtok( ptr, seps, &next_token);
   while( token != NULL )
   {
	   tmpList.push_back( OP::dup( token ) );
       token = string_traits<charT>::strtok( NULL, seps , &next_token );
   }

   StringArray<charT,OP> result( tmpList.size() );
   int i = 0;
   for( std::list<charT*>::iterator it = tmpList.begin(); it != tmpList.end(); it ++ )
   {
		result[ i ].ptr = *it;
		++i;
   }
   return result;
}

template<typename charT >
inline StringArray<charT,detail::StringOp<charT> > split( const  charT* str, const charT* seps )
{
   return split<charT, detail::StringOp<charT> >( str, seps );
}

template<typename stringT, typename OP >
inline StringArray<typename stringT::value_type,OP> split( const  stringT& str, const typename stringT::value_type* seps )
{
   return split<typename stringT::value_type, OP>( str.c_str(), seps );
}

template<typename stringT >
inline StringArray<typename stringT::value_type,detail::StringOp<typename stringT::value_type> > split( const stringT& str, const typename stringT::value_type* seps )
{
   return split<typename stringT::value_type, detail::StringOp<typename stringT::value_type> >( str.c_str(), seps );
}

_jingxian_end

#endif // _split_functions_hpp_