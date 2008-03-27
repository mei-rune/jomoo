
#if !defined(STLSOFT_INCL_STLSOFT_STRING_HPP_CONTAINER_SLICE_FUNCTIONS)
# error This file cannot be directly included, and should only be included within stlsoft/string/container_slice_functions.hpp
#endif /* !STLSOFT_INCL_STLSOFT_STRING_HPP_CONTAINER_SLICE_FUNCTIONS */

#if !defined(STLSOFT_UNITTEST)
# error This file cannot be included when not unit-testing STLSoft
#endif /* !STLSOFT_UNITTEST */

namespace unittest
{
	namespace
	{
		template <ss_typename_param_k S>
		ss_bool_t test_container_slices(unittest_reporter *r)
		{
			ss_bool_t				bSuccess	=	true;

			typedef S			string_type;

#if defined(STLSOFT_COMPILER_IS_BORLAND)
			using ::stlsoft::left;
			using ::stlsoft::right;
#endif /* compiler */

			const string_type	src("Hello, Natty!");

			if(left(src, stlsoft_ns_qual(c_str_len)(src)) != src)
			{
				r->report("left() slice invalid; full-length of source requested", __LINE__);
				bSuccess = false;
			}

			if(right(src, stlsoft_ns_qual(c_str_len)(src)) != src)
			{
				r->report("right() slice invalid; full-length of source requested", __LINE__);
				bSuccess = false;
			}

			if(mid(src, 0, stlsoft_ns_qual(c_str_len)(src)) != src)
			{
				r->report("mid() slice invalid; full-length of source requested", __LINE__);
				bSuccess = false;
			}

			if(left(src, 10 + stlsoft_ns_qual(c_str_len)(src)) != src)
			{
				r->report("left() slice invalid; excess-length of source requested", __LINE__);
				bSuccess = false;
			}

			if(right(src, 10 + stlsoft_ns_qual(c_str_len)(src)) != src)
			{
				r->report("right() slice invalid; excess-length of source requested", __LINE__);
				bSuccess = false;
			}

			if(mid(src, 0, 10 + stlsoft_ns_qual(c_str_len)(src)) != src)
			{
				r->report("mid() slice invalid; excess-length of source requested", __LINE__);
				bSuccess = false;
			}

			if(left(src, 5) != "Hello")
			{
				r->report("left() slice invalid; sub-length of source requested", __LINE__);
				bSuccess = false;
			}

			if(right(src, 6) != "Natty!")
			{
				r->report("right() slice invalid; sub-length of source requested", __LINE__);
				bSuccess = false;
			}

			if(mid(src, 7, 5) != "Natty")
			{
				r->report("mid() slice invalid; sub-length of source requested", __LINE__);
				bSuccess = false;
			}

			if(mid(src, 0, 5) != "Hello")
			{
				r->report("mid() slice invalid; sub-length of source requested", __LINE__);
				bSuccess = false;
			}

			if(left(src, 0) != "")
			{
				r->report("left() slice invalid; zero-length of source requested", __LINE__);
				bSuccess = false;
			}

			if(right(src, 0) != "")
			{
				r->report("right() slice invalid; zero-length of source requested", __LINE__);
				bSuccess = false;
			}

			if(mid(src, 0, 0) != "")
			{
				r->report("mid() slice invalid; zero-length of source requested", __LINE__);
				bSuccess = false;
			}

			return bSuccess;
		}

		ss_bool_t test_stlsoft_string_container_slice_functions(unittest_reporter *r)
		{
			ss_bool_t				bSuccess	=	true;

			unittest_initialiser	init(r, "STLSoft", "string/container_slice_functions", __FILE__);

			typedef stlsoft_ns_qual_std(string) 	std_string_t;
			typedef simple_string					simple_string_t;

			if(bSuccess)
			{
				bSuccess = test_container_slices<std_string_t>(r);
			}

			if(bSuccess)
			{
				bSuccess = test_container_slices<simple_string_t>(r);
			}

#if 0
# if defined(WIN32) && \
	 (	defined(STLSOFT_COMPILER_IS_INTEL) || \
		defined(STLSOFT_COMPILER_IS_MSVC))
			if(bSuccess)
			{
				bSuccess = test_slices<CString>(r);
			}
# endif /* WIN32 && Intel or MSVC */
#endif /* 0 */

			return bSuccess;
		}

		unittest_registrar	  unittest_stlsoft_string_container_slice_functions(test_stlsoft_string_container_slice_functions);
	} // anonymous namespace

} // namespace unittest

