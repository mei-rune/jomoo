\
// Updated: 6th June 2006

#if !defined(STLSOFT_INCL_STLSOFT_STRING_HPP_FUNCTIONALS)
# error This file cannot be directly included, and should only be included within stlsoft/string/functionals.hpp
#endif /* !STLSOFT_INCL_STLSOFT_STRING_HPP_FUNCTIONALS */

#if !defined(STLSOFT_UNITTEST)
# error This file cannot be included when not unit-testing STLSoft
#endif /* !STLSOFT_UNITTEST */

namespace unittest
{
	namespace
	{
		ss_bool_t test_stlsoft_string_functionals(unittest_reporter *r)
		{
			ss_bool_t				bSuccess	=	true;

			unittest_initialiser	init(r, "STLSoft", "string/functionals", __FILE__);

			return bSuccess;
		}

		unittest_registrar	  unittest_stlsoft_string_functionals(test_stlsoft_string_functionals);
	} // anonymous namespace

} // namespace unittest
