
#ifndef _string_token_iterator_
#define _string_token_iterator_

#include "config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
# include "os_string.hpp"

template< typename C >
struct string_token_iterator ITERATOR_BASE( input_iterator, tstring , ptrdiff_t )
{
public:

	typedef C char_type;
	typedef size_t size_type;

  string_token_iterator() : _ptr(0), start(0), end(0) {}

  template< typename S >
  string_token_iterator(const S & s, const char_type * separator_ = _T(" ")) :
    separator(separator_),
    _ptr( c_str_ptr(s) ),
    end(0)
  {
    find_next();
  }

  string_token_iterator(const string_token_iterator & rhs) :
    separator(rhs.separator),
    _ptr(rhs._ptr),
    start(rhs.start),
    end(rhs.end)
  {
  }

  string_token_iterator & operator++()
  {
    find_next();
    return *this;
  }

  string_token_iterator operator++(int)
  {
    string_token_iterator temp(*this);
    ++(*this);
    return temp;
  }

  tstring operator*() const
  {
    return tstring(*_ptr, start, end - start);
  }

  bool operator==(const string_token_iterator & rhs) const
  {
    return (rhs._ptr == _ptr && rhs.start == start && rhs.end == end);
  }

  bool operator!=(const string_token_iterator & rhs) const
  {
    return !(rhs == *this);
  }

private:

  void find_next(void)
  {
    start = _ptr->find_first_not_of(separator, end);
    if(start == tstring::npos)
    {
      start = end = 0;
      _ptr = 0;
      return;
    }

    end = _ptr->find_first_of(separator, start);
  }

  const char_type * separator;
  const char_type * const _ptr;
  size_type start;
  size_type end;
};

#endif // _string_token_iterator_
