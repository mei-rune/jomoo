
// Updated: 6th June 2006

#if !defined(STLSOFT_INCL_STLSOFT_STRING_HPP_STATIC_STRING)
# error This file cannot be directly included, and should only be included within stlsoft/string/static_string.hpp
#endif /* !STLSOFT_INCL_STLSOFT_STRING_HPP_STATIC_STRING */

#if !defined(STLSOFT_UNITTEST)
# error This file cannot be included when not unit-testing STLSoft
#endif /* !STLSOFT_UNITTEST */

namespace unittest
{
	namespace
	{
		ss_bool_t test_stlsoft_static_string(unittest_reporter *r)
		{
			ss_bool_t				bSuccess	=	true;

			unittest_initialiser	init(r, "STLSoft", "string/static_string", __FILE__);

			typedef basic_static_string<char, 32>	 string_t;

			{
				string_t	s1("Hello, Pussycat!");
				string_t	s2("Hello, Pussycat!");

#if !defined(STLSOFT_COMPILER_IS_DMC) || \
	__DMC__ >= 0x0844
				if(s1 != s2)
				{
					r->report("Equivalent strings comparison failed", __LINE__);
					bSuccess = false;
				}

				string_t	s3(s1);

				if(s1 != s3)
				{
					r->report("Copy construction failed", __LINE__);
					bSuccess = false;
				}

				string_t	s4;

				s4 = s1;

				if(s1 != s4)
				{
					r->report("Copy assignment failed", __LINE__);
					bSuccess = false;
				}
#endif /* compiler */
			}

			typedef stlsoft_ns_qual_std(basic_string)<char> 			alt_string_t;

			if(string_t("abc") != "abc")
			{
				r->report("construction failed", __LINE__);
				bSuccess = false;
			}

			if(string_t("abc") >= "def")
			{
				r->report("comparison failed", __LINE__);
				bSuccess = false;
			}

			// Self assignment
			string_t const	s3("abcdefghijklm");
			string_t		s4;

//printf("s3=%s; s4=%s\n", s3.c_str(), s4.c_str());
			s4 = s3;	// setup
//printf("s3=%s; s4=%s\n", s3.c_str(), s4.c_str());
			s4 = s4;	// action
//printf("s3=%s; s4=%s\n", s3.c_str(), s4.c_str());
			if(s3 != s4)
			{
				r->report("self-assignment (1) failed", __LINE__);
				bSuccess = false;
			}

//printf("s3=%s; s4=%s\n", s3.c_str(), s4.c_str());
			s4 = s3;			// setup
//printf("s3=%s; s4=%s\n", s3.c_str(), s4.c_str());
			s4.assign(&s4[2]);	// action
//printf("s3=%s; s4=%s\n", s3.c_str(), s4.c_str());
			if("abcdefghijklm" + 2 != s4)
			{
				r->report("self-assignment (2) failed", __LINE__);
				bSuccess = false;
			}

//printf("s3=%s; s4=%s\n", s3.c_str(), s4.c_str());
			s4 = s3;				// setup
//printf("s3=%s; s4=%s\n", s3.c_str(), s4.c_str());
//printf("s4: size=%d; max_size=%d\n", s4.size(), s4.max_size());
			s4.append(&s4[2], 4);	// action
//printf("s3=%s; s4=%s\n", s3.c_str(), s4.c_str());
			if("abcdefghijklmcdef" != s4)
			{
				r->report("self-append (1) failed", __LINE__);
				bSuccess = false;
			}

//printf("s3=%s; s4=%s\n", s3.c_str(), s4.c_str());
			s4 = s3;			// setup
//printf("s3=%s; s4=%s\n", s3.c_str(), s4.c_str());
			s4.append(&s4[1]);	// action
//printf("s3=%s; s4=%s\n", s3.c_str(), s4.c_str());
			if("abcdefghijklmbcdefghijklm" != s4)
			{
				r->report("self-append (2) failed", __LINE__);
				bSuccess = false;
			}
//printf("s3=%s; s4=%s\n", s3.c_str(), s4.c_str());

#ifdef STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT
			const alt_string_t	ss1(s4.begin(), s4.end());
#else /* ? STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT */
			const alt_string_t	ss1(s4.data(), s4.length());
#endif /* STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT */

//printf("1\n");
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

//printf("2\n");
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

//printf("3\n");
#ifdef STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT
			string_t	  s6(s5.begin(), s5.end());
			string_t	  s7(s5);

#if 0
//printf("4\n");
			s6.assign(s6.begin() + 1, s6.end());
			s6.append(s3.begin(), s3.end());
//printf("5\n");
			s7.erase(s7.begin() + 1, s7.end());
			s7.append(s3.data(), s3.data() + s3.length());
//printf("6\n");
#endif /* 0 */

			if(s6 != s7)
			{
				r->report("range append() does not work", __LINE__);
				bSuccess = false;
			}

#endif /* STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT */

//printf("7\n");
			/// Sub-string construction
//			s3("abcdefghijklm");
			if(string_t(s3, 0, s3.length()) != s3)
			{
				r->report("Sub-string construction failed: full contents", __LINE__);
				bSuccess = false;
			}
//printf("8\n");
#if 0 // basic_static_string allows embedded nuls
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
#endif /* 0 */
//printf("9\n");

//printf("10\n");
			if(string_t(s3, 1, s3.length() - 1) != "bcdefghijklm")
			{
				r->report("Sub-string construction failed: non-zero pos to end of source", __LINE__);
				bSuccess = false;
			}
//printf("11\n");
#if 0 // basic_static_string allows embedded nuls
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
#endif /* 0 */

//printf("12\n");
			{
				string_t	s;

				s.assign(s3, 0, s3.length());
//printf("13\n");
				if(s != s3)
				{
					r->report("Sub-string construction failed: full contents", __LINE__);
					bSuccess = false;
				}
//printf("14\n");
#if 0
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
#endif /* 0 */
//printf("15\n");

				s.assign(s3, 1, s3.length() - 1);
//printf("16\n");
				if(s != "bcdefghijklm")
				{
					r->report("Sub-string construction failed: non-zero pos to end of source", __LINE__);
					bSuccess = false;
				}
#if 0
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
#endif /* 0 */
			}
//printf("17\n");

			{
				typedef basic_static_string<char, 10>	 string_t;

//printf("18\n");
				string_t	s1(5, '~');
//printf("s1: l=%u;s=%s\n", s1.length(), s1.c_str());
//printf("19\n");
				string_t	s2(s1);
//printf("s1: l=%u;s=%s\n", s1.length(), s1.c_str());
//printf("20\n");
				string_t	s3;
//printf("s1: l=%u;s=%s\n", s1.length(), s1.c_str());
//printf("21\n");
				string_t	s4;
//printf("s1: l=%u;s=%s\n", s1.length(), s1.c_str());
//printf("21\n");

				for(size_t i = 0; i < s1.size(); s4.push_back('~'), ++i)
				{
//printf("Appending %d\n", i);
				}

				s3.assign(5, '~');
//printf("22\n");

				if(s1 != s3)
				{
					r->report("construction/assignment of n chars failed", __LINE__);
					bSuccess = false;
				}
			}
//printf("23\n");

//printf("here 1.0\n");

#if defined(STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT)
			{
				typedef basic_static_string<char, 48>	 string_t;

//printf("here 1.1\n");
				const string_t	ss_1("An stlsoft::basic_static_string instance");
//printf("here 1.2\n");
				const string_t	ss_2(ss_1.rbegin(), ss_1.rend());	// Reverse form of ss_1
//printf("here 1.3\n");
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
//printf("here 1.4\n");
				string_t		ss_3(as_1.rbegin(), as_1.rend());	// Reverse form of as_1 === forward form of ss_1
//printf("here 1.5\n");
#endif /* lib-ver */

				if(ss_1 != ss_3)
				{
					r->report("Double reverse construction failed", __LINE__);
					bSuccess = false;
				}
//printf("here 1.6\n");

# if !defined(STLSOFT_COMPILER_IS_BORLAND)
				// Now do some forward and reverse sorting.
				string_t		ss_4(ss_3.rbegin(), ss_3.rend());
//printf("here 1.7\n");

				stlsoft_ns_qual_std(sort)(ss_3.rbegin(), ss_3.rend());
//printf("here 1.8\n");
				stlsoft_ns_qual_std(sort)(ss_4.rbegin(), ss_4.rend());
//printf("here 1.9\n");

				if(ss_3 != ss_4)
				{
					r->report("reverse-sorted reverse-constructed === reversed source equality failed", __LINE__);
					bSuccess = false;
				}
# endif /* compiler */
			}
#endif /* STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT */

//printf("here 2.0\n");

			return bSuccess;
		}

		unittest_registrar	  unittest_stlsoft_static_string(test_stlsoft_static_string);

	} // anonymous namespace

} // namespace unittest
