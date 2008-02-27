
#if !defined(STLSOFT_INCL_STLSOFT_STRING_HPP_CSTRING_FUNCTIONS)
# error This file cannot be directly included, and should only be included within stlsoft/string/cstring_functions.hpp
#endif /* !STLSOFT_INCL_STLSOFT_STRING_HPP_CSTRING_FUNCTIONS */

#if !defined(STLSOFT_UNITTEST)
# error This file cannot be included when not unit-testing STLSoft
#endif /* !STLSOFT_UNITTEST */

namespace unittest
{
	namespace
	{
		ss_bool_t test_stlsoft_cstring_functions(unittest_reporter *r)
		{
			ss_bool_t				bSuccess	=	true;

			unittest_initialiser	init(r, "STLSoft", "string/cstring_functions", __FILE__);

			static const char		sz1[]		=	"";
			static const char		sz2[]		=	"string 1";

			char					*ds1;
			char					*ds2;

# ifdef STLSOFT_CF_THROW_BAD_ALLOC
			try
			{
# endif /* STLSOFT_CF_THROW_BAD_ALLOC */
				{
					malloc_allocator<char>	ator;

					ds1 = string_dup(sz1, ator);
				}
# ifdef STLSOFT_CF_THROW_BAD_ALLOC
			}
			catch(stlsoft_ns_qual_std(bad_alloc) &)
			{
				ds1 = NULL;
			}
# endif /* STLSOFT_CF_THROW_BAD_ALLOC */

# ifdef STLSOFT_CF_THROW_BAD_ALLOC
			try
			{
# endif /* STLSOFT_CF_THROW_BAD_ALLOC */
				{
					new_allocator<char> 	ator;

					ds2 = string_dup(sz2, ator);
				}
# ifdef STLSOFT_CF_THROW_BAD_ALLOC
			}
			catch(stlsoft_ns_qual_std(bad_alloc) &)
			{
				ds2 = NULL;
			}
# endif /* STLSOFT_CF_THROW_BAD_ALLOC */

			if( NULL != ds1 &&
				0 != ::strcmp(sz1, ds1))
			{
				r->report("string_dup() (with non-empty string) failed", __LINE__);
				bSuccess = false;
			}

			if( NULL != ds2 &&
				0 != ::strcmp(sz2, ds2))
			{
				r->report("string_dup() (with empty string) failed", __LINE__);
				bSuccess = false;
			}

			return bSuccess;
		}

		unittest_registrar	  unittest_stlsoft_cstring_functions(test_stlsoft_cstring_functions);
	} // anonymous namespace

} // namespace unittest

