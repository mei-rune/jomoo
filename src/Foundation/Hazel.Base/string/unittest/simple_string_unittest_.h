
// Updated: 6th June 2006

#if !defined(STLSOFT_INCL_STLSOFT_STRING_HPP_SIMPLE_STRING)
# error This file cannot be directly included, and should only be included within stlsoft/string/simple_string.hpp
#endif /* !STLSOFT_INCL_STLSOFT_STRING_HPP_SIMPLE_STRING */

#if !defined(STLSOFT_UNITTEST)
# error This file cannot be included when not unit-testing STLSoft
#endif /* !STLSOFT_UNITTEST */

//#define _STLSOFT_SIMPLE_STRING_SHOW_SECTIONS

namespace unittest
{
	namespace
	{
		ss_bool_t test_stlsoft_simple_string(unittest_reporter *r)
		{
			ss_bool_t				bSuccess	=	true;

			unittest_initialiser	init(r, "STLSoft", "string/simple_string", __FILE__);

			typedef basic_simple_string<	char
										,	stlsoft_char_traits<char>
										,	allocator_selector<char>::allocator_type
										>								string_t;
			typedef stlsoft_ns_qual_std(basic_string)<char> 			alt_string_t;

#ifdef _STLSOFT_SIMPLE_STRING_SHOW_SECTIONS
		   r->start_section("section-1");
#endif /* 0 */

			if(string_t("abc") != "abc")
			{
				r->report("construction failed", __LINE__);
				bSuccess = false;
			}

#ifdef _STLSOFT_SIMPLE_STRING_SHOW_SECTIONS
		   r->start_section("section-2");
#endif /* 0 */

			if(string_t("abc") >= "def")
			{
				r->report("comparison failed", __LINE__);
				bSuccess = false;
			}

#ifdef _STLSOFT_SIMPLE_STRING_SHOW_SECTIONS
		   r->start_section("section-3");
#endif /* 0 */

			// Self assignment
			string_t const	s3("abcdefghijklm");
			string_t		s4;

			s4 = s3;	// setup
			s4 = s4;	// action
			if(s3 != s4)
			{
				r->report("self-assignment (1) failed", __LINE__);
				bSuccess = false;
			}

#ifdef _STLSOFT_SIMPLE_STRING_SHOW_SECTIONS
		   r->start_section("section-4");
#endif /* 0 */

			s4 = s3;			// setup
			s4.assign(&s4[2]);	// action
			if("abcdefghijklm" + 2 != s4)
			{
				r->report("self-assignment (2) failed", __LINE__);
				bSuccess = false;
			}

			s4 = s3;				// setup
			s4.append(&s4[2], 4);	// action
			if("abcdefghijklmcdef" != s4)
			{
				r->report("self-append (1) failed", __LINE__);
				bSuccess = false;
			}

			s4 = s3;			// setup
			s4.append(&s4[1]);	// action
			if("abcdefghijklmbcdefghijklm" != s4)
			{
				r->report("self-append (2) failed", __LINE__);
				bSuccess = false;
			}

#ifdef STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT
			const alt_string_t	ss1(s4.begin(), s4.end());
#else /* ? STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT */
			const alt_string_t	ss1(s4.data(), s4.length());
#endif /* STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT */

#ifdef _STLSOFT_SIMPLE_STRING_SHOW_SECTIONS
		   r->start_section("section-5");
#endif /* 0 */

			if(ss1.c_str() != s4)
			{
				r->report("equality testing with std::string failed", __LINE__);
				bSuccess = false;
			}

			if(s4.c_str() != ss1)
			{
				r->report("equality testing with std::string failed", __LINE__);
				bSuccess = false;
			}

#ifdef STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT
			const string_t		s5(ss1.begin(), ss1.end());
#else /* ? STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT */
			const string_t		s5(ss1.data(), ss1.length());
#endif /* STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT */

#ifdef _STLSOFT_SIMPLE_STRING_SHOW_SECTIONS
		   r->start_section("section-6");
#endif /* 0 */

			if(ss1.c_str() != s5)
			{
				r->report("equality testing with std::string failed", __LINE__);
				bSuccess = false;
			}

			if(s5.c_str() != ss1)
			{
				r->report("equality testing with std::string failed", __LINE__);
				bSuccess = false;
			}

#ifdef _STLSOFT_SIMPLE_STRING_SHOW_SECTIONS
		   r->start_section("section-7");
#endif /* 0 */

#ifdef STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT
			string_t	  s6(s5);
			string_t	  s7(s5);

			s6.append(s3.begin(), s3.end());
			s7.append(s3.data(), s3.data() + s3.length());

			if(s6 != s7)
			{
				r->report("range append() does not work", __LINE__);
				bSuccess = false;
			}

#endif /* STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT */

#ifdef _STLSOFT_SIMPLE_STRING_SHOW_SECTIONS
		   r->start_section("section-8");
#endif /* 0 */

			/// Sub-string construction
//			s3("abcdefghijklm");
			if(string_t(s3, 0, s3.length()) != s3)
			{
				r->report("Sub-string construction failed: full contents", __LINE__);
				bSuccess = false;
			}
			if(string_t(s3, 0, s3.length() + 1) != s3)
			{
				r->report("Sub-string construction failed: excess length requested", __LINE__);
				bSuccess = false;
			}
			if(string_t(s3, 0, s3.length() + 100) != s3)
			{
				r->report("Sub-string construction failed: excess length requested", __LINE__);
				bSuccess = false;
			}

			if(string_t(s3, 1, s3.length() - 1) != "bcdefghijklm")
			{
				r->report("Sub-string construction failed: non-zero pos to end of source", __LINE__);
				bSuccess = false;
			}
			if(string_t(s3, 1, s3.length()) != "bcdefghijklm")
			{
				r->report("Sub-string construction failed: non-zero pos with excess length", __LINE__);
				bSuccess = false;
			}
			if(string_t(s3, 1, s3.length() + 100) != "bcdefghijklm")
			{
				r->report("Sub-string construction failed: non-zero pos with excess length", __LINE__);
				bSuccess = false;
			}

#ifdef _STLSOFT_SIMPLE_STRING_SHOW_SECTIONS
		   r->start_section("section-9");
#endif /* 0 */

			{
				string_t	s;

				s.assign(s3, 0, s3.length());
				if(s != s3)
				{
					r->report("Sub-string construction failed: full contents", __LINE__);
					bSuccess = false;
				}
				s.assign(s3, 0, s3.length() + 1);
				if(s != s3)
				{
					r->report("Sub-string construction failed: excess length requested", __LINE__);
					bSuccess = false;
				}
				s.assign(s3, 0, s3.length() + 100);
				if(s != s3)
				{
					r->report("Sub-string construction failed: excess length requested", __LINE__);
					bSuccess = false;
				}

				s.assign(s3, 1, s3.length() - 1);
				if(s != "bcdefghijklm")
				{
					r->report("Sub-string construction failed: non-zero pos to end of source", __LINE__);
					bSuccess = false;
				}
				s.assign(s3, 1, s3.length());
				if(s != "bcdefghijklm")
				{
					r->report("Sub-string construction failed: non-zero pos with excess length", __LINE__);
					bSuccess = false;
				}
				s.assign(s3, 1, s3.length() + 100);
				if(s != "bcdefghijklm")
				{
					r->report("Sub-string construction failed: non-zero pos with excess length", __LINE__);
					bSuccess = false;
				}
			}

#ifdef _STLSOFT_SIMPLE_STRING_SHOW_SECTIONS
		   r->start_section("section-10");
#endif /* 0 */

#if defined(STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT)
			{
				const string_t	ss_1("This is an stlsoft::simple_string instance");
				const string_t	ss_2(ss_1.rbegin(), ss_1.rend());	// Reverse form of ss_1
#if (	defined(STLSOFT_CF_STD_LIBRARY_IS_DINKUMWARE_VC) && \
		STLSOFT_CF_STD_LIBRARY_DINKUMWARE_VC_VERSION < STLSOFT_CF_DINKUMWARE_VC_VERSION_7_0) || \
	(	defined(STLSOFT_COMPILER_IS_GCC) && \
		(	__GNUC__ < 3 || \
			(	__GNUC__ == 3 && \
				__GNUC_MINOR__ < 4)))
				string_t		ss_3_(ss_1.rbegin(), ss_1.rend());	// Reverse form of as_1 === forward form of ss_1
				string_t		ss_3(ss_3_.rbegin(), ss_3_.rend()); // Reverse form of as_1 === forward form of ss_1
#else /* ? lib-ver */
				alt_string_t	as_1(ss_1.rbegin(), ss_1.rend());	// Reverse form of ss_1
				string_t		ss_3(as_1.rbegin(), as_1.rend());	// Reverse form of as_1 === forward form of ss_1
#endif /* lib-ver */

				if(ss_1 != ss_3)
				{
					r->report("Double reverse construction failed", __LINE__);
					bSuccess = false;
				}

#ifdef _STLSOFT_SIMPLE_STRING_SHOW_SECTIONS
		   r->start_section("section-11");
#endif /* 0 */

# if !defined(STLSOFT_COMPILER_IS_BORLAND)
				// Now do some forward and reverse sorting.
				string_t		ss_4(ss_3.rbegin(), ss_3.rend());

				stlsoft_ns_qual_std(sort)(ss_3.rbegin(), ss_3.rend());
				stlsoft_ns_qual_std(sort)(ss_4.rbegin(), ss_4.rend());

				if(ss_3 != ss_4)
				{
					r->report("reverse-sorted reverse-constructed === reversed source equality failed", __LINE__);
					bSuccess = false;
				}
# endif /* compiler */
			}
#endif /* STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT */

#ifdef _STLSOFT_SIMPLE_STRING_SHOW_SECTIONS
		   r->start_section("section-12");
#endif /* 0 */

			// substr
#ifdef STLSOFT_CF_EXCEPTION_SUPPORT
			{
				const string_t	s0;
				const string_t	s1("abcdefghijklm");
				const string_t	s2	=	s0.substr();
				const string_t	s3	=	s1.substr();

				if(s2 != s0)
				{
					r->report("substr() (0 argument form) failed", __LINE__);
					bSuccess = false;
				}
				if(s3 != s1)
				{
					r->report("substr() (0 argument form) failed", __LINE__);
					bSuccess = false;
				}

				const string_t	s4	=	s0.substr(0);
				const string_t	s5	=	s1.substr(4);

				if(s4 != s0)
				{
					r->report("substr() (1 argument form) failed", __LINE__);
					bSuccess = false;
				}
				if(s5 != "efghijklm")
				{
					r->report("substr() (1 argument form) failed", __LINE__);
					bSuccess = false;
				}

				const string_t	s6	=	s0.substr(0, 0);
				const string_t	s7	=	s1.substr(4, 4);

				if(s6 != s0)
				{
					r->report("substr() (2 argument form) failed", __LINE__);
					bSuccess = false;
				}
				if(s7 != "efgh")
				{
					r->report("substr() (2 argument form) failed", __LINE__);
					bSuccess = false;
				}
			}
#endif /* !STLSOFT_CF_EXCEPTION_SUPPORT */

			return bSuccess;
		}

		unittest_registrar	  unittest_stlsoft_simple_string(test_stlsoft_simple_string);

	} // anonymous namespace

} // namespace unittest
