
#if !defined(STLSOFT_INCL_STLSOFT_STRING_HPP_TRIM_FUNCTIONS)
# error This file cannot be directly included, and should only be included within stlsoft/string/trim_functions.hpp
#endif /* !STLSOFT_INCL_STLSOFT_STRING_HPP_TRIM_FUNCTIONS */

#if !defined(STLSOFT_UNITTEST)
# error This file cannot be included when not unit-testing STLSoft
#endif /* !STLSOFT_UNITTEST */

namespace unittest
{
	namespace
	{
		template <ss_typename_param_k S>
		ss_bool_t test_trim_functions(unittest_reporter *r)
		{
			ss_bool_t			bSuccess	=	true;

			typedef S			string_type;

#if defined(STLSOFT_COMPILER_IS_BORLAND)
			using ::stlsoft::trim_left;
			using ::stlsoft::trim_right;
			using ::stlsoft::trim_all;
			using ::stlsoft::remove_all;
#endif /* compiler */

			const string_type	src1("	\t\vspaces on either side \r \n ");
			const string_type	src2("no-spaces-anywhere");

			{
				string_type s1(src1);
				string_type s2(src2);

				trim_left(s1);
				trim_left(s2);

				if(s1 != "spaces on either side \r \n ")
				{
					r->report("trim_left() failed", __LINE__);
					bSuccess = false;
				}

				if(s2 != "no-spaces-anywhere")
				{
					r->report("trim_left() failed", __LINE__);
					bSuccess = false;
				}
			}

			{
				string_type s1(src1);
				string_type s2(src2);

				trim_right(s1);
				trim_right(s2);

				if(s1 != "	\t\vspaces on either side")
				{
					r->report("trim_right() failed", __LINE__);
					bSuccess = false;
				}

				if(s2 != "no-spaces-anywhere")
				{
					r->report("trim_right() failed", __LINE__);
					bSuccess = false;
				}
			}

			{
				string_type s1(src1);
				string_type s2(src2);

				trim_all(s1);
				trim_all(s2);

				if(s1 != "spaces on either side")
				{
					r->report("trim_all() failed", __LINE__);
					bSuccess = false;
				}

				if(s2 != "no-spaces-anywhere")
				{
					r->report("trim_all() failed", __LINE__);
					bSuccess = false;
				}
			}


			{
				string_type s1(src1);
				string_type s2(src2);

				remove_all(s1);
				remove_all(s2);

				if(s1 != "spacesoneitherside")
				{
					r->report("remove_all() failed", __LINE__);
					bSuccess = false;
				}

				if(s2 != "no-spaces-anywhere")
				{
					r->report("remove_all() failed", __LINE__);
					bSuccess = false;
				}
			}
			return bSuccess;
		}

		ss_bool_t test_stlsoft_string_trim_functions(unittest_reporter *r)
		{
			ss_bool_t				bSuccess	=	true;

			unittest_initialiser	init(r, "STLSoft", "string/trim_functions", __FILE__);

			typedef stlsoft_ns_qual_std(string) 	std_string_t;
			typedef simple_string					simple_string_t;

// There are bugs in some standard library string implementations that causes them to
// fail to appropriately initialise from c-strings containing \r \n \v
//
// - Intel and Dinkumware
// - Metrowerks

#if (	!defined(STLSOFT_COMPILER_IS_INTELx) || \
		!defined(STLSOFT_CF_STD_LIBRARY_IS_DINKUMWARE_VC)) && \
	!defined(STLSOFT_COMPILER_IS_MWERKS)
			if(bSuccess)
			{
				bSuccess = test_trim_functions<std_string_t>(r);
			}
#endif /* compiler */

			if(bSuccess)
			{
				bSuccess = test_trim_functions<simple_string_t>(r);
			}

			return bSuccess;
		}

		unittest_registrar	  unittest_stlsoft_string_trim_functions(test_stlsoft_string_trim_functions);
	} // anonymous namespace

} // namespace unittest

