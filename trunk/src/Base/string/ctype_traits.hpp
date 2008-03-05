
#ifndef _ctype_traits_hpp_
#define _ctype_traits_hpp_

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

# include "Platform/os_string.h"

template <typename C>
struct ctype_traits;

template<>
struct ctype_traits<char_t>
{
    typedef char_t     char_type;

    static bool    is_alpha(char_type ch)      {   return 0 != ::isalpha(ch);      }
    static bool    is_upper(char_type ch)      {   return 0 != ::isupper(ch);      }
    static bool    is_lower(char_type ch)      {   return 0 != ::islower(ch);      }
    static bool    is_digit(char_type ch)      {   return 0 != ::isdigit(ch);      }
    static bool    is_xdigit(char_type ch)     {   return 0 != ::isxdigit(ch);     }
    static bool    is_space(char_type ch)      {   return 0 != ::isspace(ch);      }
    static bool    is_punct(char_type ch)      {   return 0 != ::ispunct(ch);      }
    static bool    is_alnum(char_type ch)      {   return 0 != ::isalnum(ch);      }
    static bool    is_print(char_type ch)      {   return 0 != ::isprint(ch);      }
    static bool    is_graph(char_type ch)      {   return 0 != ::isgraph(ch);      }
    static bool    is_cntrl(char_type ch)      {   return 0 != ::iscntrl(ch);      }

};

template<>
struct ctype_traits<wchar_t>
{
    typedef wchar_t     char_type;

    static bool    is_alpha(char_type ch)      {   return 0 != ::iswalpha(ch);     }
    static bool    is_upper(char_type ch)      {   return 0 != ::iswupper(ch);     }
    static bool    is_lower(char_type ch)      {   return 0 != ::iswlower(ch);     }
    static bool    is_digit(char_type ch)      {   return 0 != ::iswdigit(ch);     }
    static bool    is_xdigit(char_type ch)     {   return 0 != ::iswxdigit(ch);    }
    static bool    is_space(char_type ch)      {   return 0 != ::iswspace(ch);     }
    static bool    is_punct(char_type ch)      {   return 0 != ::iswpunct(ch);     }
    static bool    is_alnum(char_type ch)      {   return 0 != ::iswalnum(ch);     }
    static bool    is_print(char_type ch)      {   return 0 != ::iswprint(ch);     }
    static bool    is_graph(char_type ch)      {   return 0 != ::iswgraph(ch);     }
    static bool    is_cntrl(char_type ch)      {   return 0 != ::iswcntrl(ch);     }
};

#endif /* _ctype_traits_hpp_ */
