
// Updated: 6th July 2006

#if !defined(STLSOFT_INCL_STLSOFT_STRING_HPP_CHARSET_TOKENISER)
# error This file cannot be directly included, and should only be included within stlsoft/string/charset_tokeniser.hpp
#endif /* !STLSOFT_INCL_STLSOFT_STRING_HPP_CHARSET_TOKENISER */

#if !defined(STLSOFT_UNITTEST)
# error This file cannot be included when not unit-testing STLSoft
#endif /* !STLSOFT_UNITTEST */

namespace unittest
{
#if !defined(STLSOFT_COMPILER_IS_WATCOM)

	namespace
	{
		ss_bool_t test_stlsoft_string_charset_tokeniser_1(unittest_reporter *r)
		{
			ss_bool_t				bSuccess	=	true;

			typedef charset_tokeniser<simple_string>	tokeniser_t;

			static const char	str1[]	=	";abc|:def,ghi;hjk;:|lmn;:|";

			tokeniser_t tokens(str1, ":;|,");

			if(5 != stlsoft_ns_qual_std(distance(tokens.begin(), tokens.end())))
			{
				r->report("charset_tokeniser wrong number of tokens (skipping blanks)", __LINE__);
				bSuccess = false;
			}

			return bSuccess;
		}

		ss_bool_t test_stlsoft_string_charset_tokeniser_2(unittest_reporter *r)
		{
			ss_bool_t				bSuccess	=	true;

			typedef charset_tokeniser<simple_wstring, skip_blank_tokens<false> >	tokeniser_t;

			static const wchar_t	str1[]	=	L";abc|:def,ghi;hjk;:|lmn;:|";

			tokeniser_t tokens(str1, L":;|,");

//::fprintf(stderr, "# tokens: %u\n", stlsoft_ns_qual_std(distance(tokens.begin(), tokens.end())));

			if(11 != stlsoft_ns_qual_std(distance(tokens.begin(), tokens.end())))
			{
				r->report("charset_tokeniser wrong number of tokens (preserving blanks)", __LINE__);
				bSuccess = false;
			}

			return bSuccess;
		}

		ss_bool_t test_stlsoft_string_charset_tokeniser(unittest_reporter *r)
		{
			ss_bool_t				bSuccess	=	true;

			unittest_initialiser	init(r, "STLSoft", "string/charset_tokeniser", __FILE__);

			if(!test_stlsoft_string_charset_tokeniser_1(r))
			{
				bSuccess = false;
			}

			if(!test_stlsoft_string_charset_tokeniser_2(r))
			{
				bSuccess = false;
			}

			return bSuccess;
		}

		unittest_registrar	  unittest_stlsoft_string_charset_tokeniser(test_stlsoft_string_charset_tokeniser);
	} // anonymous namespace

#endif /* compiler */

} // namespace unittest

