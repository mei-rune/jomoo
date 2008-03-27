
#if !defined(STLSOFT_INCL_STLSOFT_STRING_HPP_CSTRING_MAKER)
# error This file cannot be directly included, and should only be included within stlsoft/string/cstring_maker.hpp
#endif /* !STLSOFT_INCL_STLSOFT_STRING_HPP_CSTRING_MAKER */

#if !defined(STLSOFT_UNITTEST)
# error This file cannot be included when not unit-testing STLSoft
#endif /* !STLSOFT_UNITTEST */

namespace unittest
{
	namespace
	{
		ss_bool_t test_stlsoft_cstring_maker(unittest_reporter *r)
		{
			ss_bool_t				bSuccess	=	true;

			unittest_initialiser	init(r, "STLSoft", "string/cstring_maker", __FILE__);

			typedef cstring_maker<char> 	string_maker_a_t;
			typedef cstring_maker<wchar_t>	string_maker_w_t;

			char *s1	=	string_maker_a_t::dup("String #1");

			if(NULL == s1)
			{
				r->report("dup (ANSI) failed", __LINE__);
				bSuccess = false;
			}
			else
			{

				string_maker_a_t::free(s1);
			}

			return bSuccess;
		}

		unittest_registrar	  unittest_atlstl_string_access(test_stlsoft_cstring_maker);
	} // anonymous namespace

} // namespace unittest
