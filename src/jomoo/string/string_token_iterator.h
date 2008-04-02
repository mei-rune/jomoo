
#ifndef _string_token_iterator_
#define _string_token_iterator_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

template< typename C >
struct string_token_iterator ITERATOR_BASE( input_iterator, tstring , ptrdiff_t )
{
public:

	typedef C char_type;
	typedef size_t size_type;

  string_token_iterator() : str(0), start(0), end(0) {}

  template< typename S >
  string_token_iterator(const S & str_, const char_type * separator_ = " ") :
    separator(separator_),
    str( c_str_ptr(str_) ),
    end(0)
  {
    find_next();
  }

  string_token_iterator(const string_token_iterator & rhs) :
    separator(rhs.separator),
    str(rhs.str),
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
    return tstring(*str, start, end - start);
  }

  bool operator==(const string_token_iterator & rhs) const
  {
    return (rhs.str == str && rhs.start == start && rhs.end == end);
  }

  bool operator!=(const string_token_iterator & rhs) const
  {
    return !(rhs == *this);
  }

private:

  void find_next(void)
  {
    start = str->find_first_not_of(separator, end);
    if(start == tstring::npos)
    {
      start = end = 0;
      str = 0;
      return;
    }

    end = str->find_first_of(separator, start);
  }

  const char_type * separator;
  const char_type * const str_;
  size_type start;
  size_type end;
};

#endif // _string_token_iterator_
