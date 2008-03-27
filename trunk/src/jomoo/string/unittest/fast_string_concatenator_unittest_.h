
#if !defined(STLSOFT_INCL_STLSOFT_STRING_HPP_FAST_STRING_CONCATENATOR)
# error This file cannot be directly included, and should only be included within stlsoft/string/fast_string_concatenator.hpp
#endif /* !STLSOFT_INCL_STLSOFT_STRING_HPP_FAST_STRING_CONCATENATOR */

#if !defined(STLSOFT_UNITTEST)
# error This file cannot be included when not unit-testing STLSoft
#endif /* !STLSOFT_UNITTEST */

namespace unittest
{
	namespace
	{
		ss_bool_t test_stlsoft_fast_string_concatenator(unittest_reporter *r)
		{
			ss_bool_t				bSuccess	=	true;

			unittest_initialiser	init(r, "STLSoft", "string/fast_string_concatenator", __FILE__);

#if 0
			if(<<TODO>>)
			{
				r->report("<<TODO>> failed", __LINE__);
				bSuccess = false;
			}
#endif /* 0 */

			return bSuccess;
		}

		unittest_registrar	  unittest_stlsoft_fast_string_concatenator(test_stlsoft_fast_string_concatenator);
	} // anonymous namespace

} // namespace unittest

