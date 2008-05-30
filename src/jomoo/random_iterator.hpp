#ifndef _random_iterator_hpp_
#define _random_iterator_hpp_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include <stdexcept>
#include <iterator>
#include "make_null_ptr.hpp"

#define ITERATOR_DEBUG( X ) check( X )


template<class _Ty,
	class _Diff,
	class _Pointer,
	class _Reference  >
class random_iterator : std::iterator<std::random_access_iterator_tag, _Ty, _Diff, _Pointer, _Reference >
{
public:
	typedef std::iterator<std::random_access_iterator_tag, _Ty, _Diff, _Pointer, _Reference >
            base;
    typedef random_iterator self;
	typedef size_t size_type;

	typedef typename base::value_type value_type;
    typedef typename base::difference_type difference_type;
	typedef typename base::distance_type distance_type;	// retained
    typedef typename base::pointer pointer;
    typedef typename base::reference reference;


    random_iterator():pointer_( make_null_ptr<value_type>() ),length_(0), idx_(0) {}

    random_iterator(const random_iterator& it)
        : pointer_(it.pointer_),length_(it.length_), idx_(it.idx_) {}

    random_iterator( pointer _p, size_type l, size_type idx )
        : pointer_(_p),length_( l ), idx_(idx) { ITERATOR_DEBUG( idx_ ); }

    bool operator==(const self& x) const { ITERATOR_DEBUG( x ); return ( idx_==x.idx_) ; }
    bool operator!=(const self& x) const { ITERATOR_DEBUG( x ); return ( idx_!=x.idx_) ; }
    bool operator<(const self& x) const { ITERATOR_DEBUG( x ); return ( idx_ < x.idx_) ; }

    reference operator*() { ITERATOR_DEBUG( pointer_ ); return pointer_[idx_]; }
    self& operator++()
	{
		if( length_ > idx_ )
			idx_++;
		return *this;
	}
    self operator++(int)
	{
		if( length_ <= idx_ )
		{
			idx_ = length_;
			return *this;
		}
		self tmp = *this;
		idx_++;
		return tmp;
	}
    self& operator--()
	{
		if( idx_ > 0 )
			idx_--;
		return *this;
	}
    self operator--(int)
	{
		if( idx_ <= 0 )
		{
			idx_ = 0;
			return *this;
		}
		self tmp = *this;
		idx_--;
		return tmp;
	}

    self operator+(difference_type n) const
	{ return self(pointer_ , length_, idx_ + n ); }
    self operator-(difference_type n) const
	{ return self(pointer_ , length_, idx_ - n); }

    difference_type operator-(const self& rhs) const
	{  ITERATOR_DEBUG( rhs ); return idx_ - rhs.idx_; }
    self& operator+=(difference_type n)
	{
		idx_ += n;
		if( idx_ > length_ )
			idx_ = length_;
		return *this;
	}
    self& operator-=(difference_type n)
	{
		idx_ -= n;
		if( idx_ < 0 )
			idx_ = 0;
		return *this;
	}
    reference operator[](difference_type n)
	{
		ITERATOR_DEBUG( pointer_ );
		ITERATOR_DEBUG( idx_ + n );
		return pointer_[ idx_ + n ];
	}

	void check( const random_iterator& it)
	{
		if( pointer_ != it.pointer_
			||  length_ != it.length_ )
			throw std::invalid_argument( "pointer_" );
	}

	void check( pointer pt )
	{
		if( is_null( pt ) )
			throw std::invalid_argument( "pointer_" );
	}

	void check( size_type idx )
	{
		if( 0 > idx || idx > length_ )
			throw std::out_of_range( "" );
	}

  protected:
    pointer pointer_;
	size_type length_;
    size_type idx_;
};

#endif /* _random_iterator_hpp_ */
