
#ifndef _ctype_traits_hpp_
#define _ctype_traits_hpp_

#include "jingxian/config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
# include <ctype.h>
# include "jingxian/string/os_string.hpp"
# include "jingxian/exception.hpp"

_jingxian_begin



template<typename charT>
class StringArray
{
public:

    struct stringData
    {
        size_t len;
        charT* ptr;
    };

    StringArray( size_t size )
    {
        ptrArray_ = (stringData*)::malloc( sizeof( stringData ) * size );
        memset( ptrArray_, 0, sizeof( stringData ) * size );
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
            ::free( ptrArray_[ i ].ptr );
        }

        ::free( ptrArray_ );
    }

    stringData& operator[]( size_t p )
    {
        if( p >= size_ )
            ThrowException1( OutOfRangeException );
        return ptrArray_[ p ];
    }

    const stringData& operator[]( size_t p ) const
    {
        if( p >= size_ )
            ThrowException1( OutOfRangeException );
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
    stringData* ptrArray_;
    size_t size_;
}

_jingxian_end

#endif /* _CASE_FUNCTIONS_HPP_ */