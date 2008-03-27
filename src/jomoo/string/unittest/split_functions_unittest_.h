
#if !defined(STLSOFT_INCL_STLSOFT_STRING_HPP_SPLIT_FUNCTIONS)
# error This file cannot be directly included, and should only be included within stlsoft/string/split_functions.hpp
#endif /* !STLSOFT_INCL_STLSOFT_STRING_HPP_SPLIT_FUNCTIONS */

#if !defined(STLSOFT_UNITTEST)
# error This file cannot be included when not unit-testing STLSoft
#endif /* !STLSOFT_UNITTEST */

namespace unittest
{
	namespace
	{
		template <ss_typename_param_k S>
		ss_bool_t test_string_splits(unittest_reporter *r)
		{
			typedef S	string_type;

#if defined(STLSOFT_COMPILER_IS_BORLAND)
			using ::stlsoft::split;
#endif /* compiler */

			ss_bool_t			bSuccess	=	true;
			const string_type	src1("name=value");
			const string_type	src2("name-value");
			const string_type	src3("name=value=suspect");

			{
				string_type s0;
				string_type s1;

				split(src1, '=', s0, s1);

				if(s0 != "name")
				{
					r->report("split() failed to derive string-0", __LINE__);
					bSuccess = false;
				}

				if(s1 != "value")
				{
					r->report("split() failed to derive string-1", __LINE__);
					bSuccess = false;
				}
			}

			{
				string_type s0;
				string_type s1;

				split(src2, '=', s0, s1);

				if(s0 != "name-value")
				{
					r->report("split() failed to derive string-0", __LINE__);
					bSuccess = false;
				}

				if(s1 != "")
				{
					r->report("split() failed to derive string-1", __LINE__);
					bSuccess = false;
				}
			}

			{
				string_type s0;
				string_type s1;

				split(src3, '=', s0, s1);

				if(s0 != "name")
				{
					r->report("split() failed to derive string-0", __LINE__);
					bSuccess = false;
				}

				if(s1 != "value=suspect")
				{
					r->report("split() failed to derive string-1", __LINE__);
					bSuccess = false;
				}
			}

			return bSuccess;
		}

		ss_bool_t test_stlsoft_string_split_functions(unittest_reporter *r)
		{
			ss_bool_t				bSuccess	=	true;

			unittest_initialiser	init(r, "STLSoft", "string/split_functions", __FILE__);

			typedef stlsoft_ns_qual_std(string) 	std_string_t;
			typedef simple_string					simple_string_t;

			if(bSuccess)
			{
				bSuccess = test_string_splits<std_string_t>(r);
			}

			if(bSuccess)
			{
				bSuccess = test_string_splits<simple_string_t>(r);
			}

			return bSuccess;
		}

		unittest_registrar	  unittest_stlsoft_string_split_functions(test_stlsoft_string_split_functions);
	} // anonymous namespace

} // namespace unittest

