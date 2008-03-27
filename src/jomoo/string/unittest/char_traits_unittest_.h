
#if !defined(STLSOFT_INCL_STLSOFT_STRING_HPP_CHAR_TRAITS)
# error This file cannot be directly included, and should only be included within stlsoft/string/char_traits.hpp
#endif /* !STLSOFT_INCL_STLSOFT_STRING_HPP_CHAR_TRAITS */

#if !defined(STLSOFT_UNITTEST)
# error This file cannot be included when not unit-testing STLSoft
#endif /* !STLSOFT_UNITTEST */

namespace unittest
{
	namespace
	{
		ss_bool_t test_stlsoft_char_traits(unittest_reporter *r)
		{
			ss_bool_t				bSuccess	=	true;

			unittest_initialiser	init(r, "STLSoft", "string/char_traits", __FILE__);

	#if 0
			if(<<TODO>>)
			{
				r->report("<<TODO>> failed", __LINE__);
				bSuccess = false;
			}
	#endif /* 0 */

			return bSuccess;
		}

		unittest_registrar	  unittest_stlsoft_char_traits(test_stlsoft_char_traits);
	} // anonymous namespace

} // namespace unittest

