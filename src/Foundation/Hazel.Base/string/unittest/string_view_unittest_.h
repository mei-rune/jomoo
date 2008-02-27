
// Updated: 6th June 2006

#if !defined(STLSOFT_INCL_STLSOFT_STRING_HPP_STRING_VIEW)
# error This file cannot be directly included, and should only be included within stlsoft/string/string_view.hpp
#endif /* !STLSOFT_INCL_STLSOFT_STRING_HPP_STRING_VIEW */

#if !defined(STLSOFT_UNITTEST)
# error This file cannot be included when not unit-testing STLSoft
#endif /* !STLSOFT_UNITTEST */

namespace unittest
{
# if !defined(STLSOFT_COMPILER_IS_MWERKS) || \
	 (__MWERKS__ & 0xFF00) >= 0x3000
	namespace
	{
		ss_bool_t test_stlsoft_string_view_1(unittest_reporter *r)
		{
			ss_bool_t				bSuccess	=	true;

			basic_string_view<char> sv_a;

			if(NULL == sv_a.data())
			{
				r->report("data() returned a NULL pointer", __LINE__);
				bSuccess = false;
			}

			if(NULL == sv_a.c_str())
			{
				r->report("c_str() returned a NULL pointer", __LINE__);
				bSuccess = false;
			}

			if(!sv_a.empty())
			{
				r->report("empty() returns invalid value for empty instance", __LINE__);
				bSuccess = false;
			}

			if(0 != sv_a.size())
			{
				r->report("size() returns invalid value for empty instance", __LINE__);
				bSuccess = false;
			}

			if(0 != sv_a.length())
			{
				r->report("length() returns invalid value for empty instance", __LINE__);
				bSuccess = false;
			}

			if(0 != sv_a.capacity())
			{
				r->report("capacity() returns invalid value for empty instance", __LINE__);
				bSuccess = false;
			}

			sv_a.clear();

			sv_a.max_size();

			basic_string_view<char> sv_a_2;

			if(!sv_a.equal(sv_a_2))
			{
				r->report("Empty instances do not compare equal", __LINE__);
				bSuccess = false;
			}
			if(!sv_a.equal(sv_a_2.base(), sv_a_2.size()))
			{
				r->report("Empty instances do not compare equal", __LINE__);
				bSuccess = false;
			}

#ifdef STLSOFT_CF_EXCEPTION_SUPPORT
			try
			{
				char const	&ch =	sv_a.at(0);

				STLSOFT_SUPPRESS_UNUSED(ch);

				r->report("Failed to detect invalid subscript in at() for empty instance", __LINE__);
				bSuccess = false;
			}
			catch(std::out_of_range &)
			{}
#endif /* !STLSOFT_CF_EXCEPTION_SUPPORT */


			return bSuccess;
		}

		ss_bool_t test_stlsoft_string_view_2(unittest_reporter *r)
		{
			ss_bool_t				bSuccess	=	true;

			basic_string_view<char> sv_a("Paninaro");

			if(NULL == sv_a.data())
			{
				r->report("data() returned a NULL pointer", __LINE__);
				bSuccess = false;
			}

			if(NULL == sv_a.c_str())
			{
				r->report("c_str() returned a NULL pointer", __LINE__);
				bSuccess = false;
			}

			if(sv_a.empty())
			{
				r->report("empty() returns invalid value for non-empty instance", __LINE__);
				bSuccess = false;
			}

			if(8 != sv_a.size())
			{
				r->report("size() returns invalid value for non-empty instance", __LINE__);
				bSuccess = false;
			}

			if(8 != sv_a.length())
			{
				r->report("length() returns invalid value for non-empty instance", __LINE__);
				bSuccess = false;
			}

			if(8 != sv_a.capacity())
			{
				r->report("capacity() returns invalid value for non-empty instance", __LINE__);
				bSuccess = false;
			}

			sv_a.max_size();

			basic_string_view<char> sv_a_2(sv_a);

			if(!sv_a.equal(sv_a_2))
			{
				r->report("Empty instances do not compare equal", __LINE__);
				bSuccess = false;
			}
			if(!sv_a.equal(sv_a_2.base(), sv_a_2.size()))
			{
				r->report("Empty instances do not compare equal", __LINE__);
				bSuccess = false;
			}

#ifdef STLSOFT_CF_EXCEPTION_SUPPORT
			try
			{
				{ for(size_t i = 0; i < sv_a.size(); ++i)
				{
					char const	&ch =	sv_a.at(i);

					STLSOFT_SUPPRESS_UNUSED(ch);
				}}
			}
			catch(std::out_of_range &)
			{
				r->report("Erroneously detected valid subscript in at() for non-empty instance", __LINE__);
				bSuccess = false;
			}
#endif /* !STLSOFT_CF_EXCEPTION_SUPPORT */


			return bSuccess;
		}

		ss_bool_t test_stlsoft_string_view(unittest_reporter *r)
		{
			ss_bool_t				bSuccess	=	true;

			unittest_initialiser	init(r, "STLSoft", "string/string_view", __FILE__);

			typedef stlsoft_ns_qual(basic_string_view)< char
													,	char_traits<char>
													,	allocator_selector<char>::allocator_type
													>		seg_string_t;

			if(!test_stlsoft_string_view_1(r))
			{
				bSuccess = false;
			}
			if(!test_stlsoft_string_view_2(r))
			{
				bSuccess = false;
			}

			char const		s[] = "Hello Natty!";

			if(!seg_string_t().empty())
			{
				r->report("Default construction and/or != comparison failed", __LINE__);
				bSuccess = false;
			}

			if(seg_string_t() != seg_string_t())
			{
				r->report("Default construction and/or != comparison failed", __LINE__);
				bSuccess = false;
			}
			seg_string_t	ss(s, STLSOFT_NUM_ELEMENTS(s) - 1);
			seg_string_t	ss1(&s[6], 6);
			seg_string_t	ss2(&s[0], 5);

			if(ss.data() != &s[0])
			{
				r->report("data() returns invalid value", __LINE__);
				bSuccess = false;
			}

			if(ss1 <= ss2)
			{
				r->report("<= comparison failed", __LINE__);
				bSuccess = false;
			}
			if(ss2 > ss1)
			{
				r->report("> comparison failed", __LINE__);
				bSuccess = false;
			}

			if(0 != seg_string_t("abc", 3).compare("abc"))
			{
				r->report("compare(s) failed", __LINE__);
				bSuccess = false;
			}

			if(0 != seg_string_t("abcdef", 3).compare(0, 3, "abc"))
			{
				r->report("compare(p, cch, s) failed", __LINE__);
				bSuccess = false;
			}

			if(0 != seg_string_t("Well done Matty!", 16).compare(11, 5, ss, 7, 5))
			{
				r->report("compare(p, cch, r, rp, rn) failed", __LINE__);
				bSuccess = false;
			}

#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT
			seg_string_t	ss3(s);

			if(ss3 != s)
			{
				r->report("array[] constructor failed", __LINE__);
				bSuccess = false;
			}
#endif /* STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT */

			return bSuccess;
		}

		unittest_registrar	  unittest_stlsoft_string_view(test_stlsoft_string_view);
	} // anonymous namespace
# endif /* compiler */

} // namespace unittest
