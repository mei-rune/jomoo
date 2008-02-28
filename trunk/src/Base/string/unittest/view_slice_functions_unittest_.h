
#if !defined(STLSOFT_INCL_STLSOFT_STRING_HPP_VIEW_SLICE_FUNCTIONS)
# error This file cannot be directly included, and should only be included within stlsoft/string/view_slice_functions.hpp
#endif /* !STLSOFT_INCL_STLSOFT_STRING_HPP_VIEW_SLICE_FUNCTIONS */

#if !defined(STLSOFT_UNITTEST)
# error This file cannot be included when not unit-testing STLSoft
#endif /* !STLSOFT_UNITTEST */

namespace unittest
{
	namespace
	{
		template <ss_typename_param_k S>
		ss_bool_t test_view_slices(unittest_reporter *r)
		{
			ss_bool_t				bSuccess	=	true;

			typedef S			string_type;

			const string_type	src("Hello, Natty!");

			if(left_view(src, stlsoft_ns_qual(c_str_len)(src)) != src.c_str())
			{
				r->report("left_view() slice invalid; full-length of source requested", __LINE__);
				bSuccess = false;
			}

			if(right_view(src, stlsoft_ns_qual(c_str_len)(src)) != src.c_str())
			{
				r->report("right_view() slice invalid; full-length of source requested", __LINE__);
				bSuccess = false;
			}

			if(mid_view(src, 0, stlsoft_ns_qual(c_str_len)(src)) != src.c_str())
			{
				r->report("mid_view() slice invalid; full-length of source requested", __LINE__);
				bSuccess = false;
			}

			if(left_view(src, 10 + stlsoft_ns_qual(c_str_len)(src)) != src.c_str())
			{
				r->report("left_view() slice invalid; excess-length of source requested", __LINE__);
				bSuccess = false;
			}

			if(right_view(src, 10 + stlsoft_ns_qual(c_str_len)(src)) != src.c_str())
			{
				r->report("right_view() slice invalid; excess-length of source requested", __LINE__);
				bSuccess = false;
			}

			if(mid_view(src, 0, 10 + stlsoft_ns_qual(c_str_len)(src)) != src.c_str())
			{
				r->report("mid_view() slice invalid; excess-length of source requested", __LINE__);
				bSuccess = false;
			}

			if(left_view(src, 5) != "Hello")
			{
				r->report("left_view() slice invalid; sub-length of source requested", __LINE__);
				bSuccess = false;
			}

			if(right_view(src, 6) != "Natty!")
			{
				r->report("right_view() slice invalid; sub-length of source requested", __LINE__);
				bSuccess = false;
			}

			if(mid_view(src, 7, 5) != "Natty")
			{
				r->report("mid_view() slice invalid; sub-length of source requested", __LINE__);
				bSuccess = false;
			}

			if(mid_view(src, 0, 5) != "Hello")
			{
				r->report("mid_view() slice invalid; sub-length of source requested", __LINE__);
				bSuccess = false;
			}

			if(left_view(src, 0) != "")
			{
				r->report("left_view() slice invalid; zero-length of source requested", __LINE__);
				bSuccess = false;
			}

			if(right_view(src, 0) != "")
			{
				r->report("right_view() slice invalid; zero-length of source requested", __LINE__);
				bSuccess = false;
			}

			if(mid_view(src, 0, 0) != "")
			{
				r->report("mid_view() slice invalid; zero-length of source requested", __LINE__);
				bSuccess = false;
			}

			return bSuccess;
		}

		ss_bool_t test_stlsoft_string_view_slice_functions(unittest_reporter *r)
		{
			ss_bool_t				bSuccess	=	true;

			unittest_initialiser	init(r, "STLSoft", "string/view_slice_functions", __FILE__);

			typedef stlsoft_ns_qual_std(string) 	std_string_t;
			typedef simple_string					simple_string_t;

			if(bSuccess)
			{
				bSuccess = test_view_slices<std_string_t>(r);
			}

			if(bSuccess)
			{
				bSuccess = test_view_slices<simple_string_t>(r);
			}

#if 0
# if defined(WIN32) && \
	 (	defined(STLSOFT_COMPILER_IS_INTEL) || \
		defined(STLSOFT_COMPILER_IS_MSVC))
			if(bSuccess)
			{
				bSuccess = test_view_slices<CString>(r);
			}
# endif /* WIN32 && Intel or MSVC */
#endif /* 0 */

			return bSuccess;
		}

		unittest_registrar	  unittest_stlsoft_string_view_slice_functions(test_stlsoft_string_view_slice_functions);
	} // anonymous namespace

} // namespace unittest

