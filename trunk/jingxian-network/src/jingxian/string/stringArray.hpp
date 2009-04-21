
#ifndef _string_array_hpp_
#define _string_array_hpp_

#include "jingxian/config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
# include <ctype.h>
# include "jingxian/exception.hpp"
# include "jingxian/string/os_string.hpp"
# include "jingxian/string/stringOps.hpp"

_jingxian_begin



template<typename charT, typename OP = detail::StringOp<charT> >
class StringArray
{
public:

    StringArray( size_t size )
    {
        ptrArray_ = (stringData<charT>*)OP::malloc( sizeof( stringData<charT> ) * size );
        memset( ptrArray_, 0, sizeof( stringData<charT> ) * size );
        size_ = size;
    }

    StringArray( StringArray& sa )
    {
        ptrArray_ = sa.ptrArray_;
        size_ = sa.size_;

        sa.ptrArray_ = 0;
        sa.size_ = 0;
    }

    
    StringArray& operator=( StringArray& sa )
    {
        ptrArray_ = sa.ptrArray_;
        size_ = sa.size_;

        sa.ptrArray_ = 0;
        sa.size_ = 0;

        return *this;
    }
  
    ~StringArray()
    {
        if( is_null( ptrArray_ ) )
            return;

        for( size_t i = 0; i < size_ ; i ++ )
        {
            OP::free( ptrArray_[ i ].ptr );
        }

        OP::free( ptrArray_ );
    }

    stringData<charT>& operator[]( size_t p )
    {
        if( p >= size_ )
            ThrowException( OutOfRangeException );
        return ptrArray_[ p ];
    }

    const stringData<charT>& operator[]( size_t p ) const
    {
        if( p >= size_ )
            ThrowException( OutOfRangeException );
        return ptrArray_[ p ];
    }

    charT* ptr( size_t p )
    {
        if( p >= size_ )
            return NULL;
        return ptrArray_[ p ].ptr;
    }

    const charT* ptr( size_t p ) const
    {
        if( p >= size_ )
            return NULL;
        return ptrArray_[ p ].ptr;
    }

    size_t len( size_t p ) const
    {
        if( p >= size_ )
            return 0;
        return ptrArray_[ p ].len;
    }

    size_t size() const
    {
        return size_;
    }

    void swap( StringArray& sa )
    {
        std::swap( ptrArray_, sa.ptrArray_ );
        std::swap( size_, sa.size_ );
    }
    
private:
    stringData<charT>* ptrArray_;
    size_t size_;
};

_jingxian_end

#endif /* _string_array_hpp_ */