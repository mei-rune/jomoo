
// Updated: 21st March 2006

#if !defined(STLSOFT_INCL_STLSOFT_STRING_HPP_STRING_TOKENISER)
# error This file cannot be directly included, and should only be included within stlsoft/string/string_tokeniser.hpp
#endif /* !STLSOFT_INCL_STLSOFT_STRING_HPP_STRING_TOKENISER */

#if !defined(STLSOFT_UNITTEST)
# error This file cannot be included when not unit-testing STLSoft
#endif /* !STLSOFT_UNITTEST */

namespace unittest
{
	namespace
	{
		ss_bool_t test_stlsoft_string_tokeniser_1(unittest_reporter *r)
		{
			ss_bool_t				bSuccess	=	true;
#if 0
			typedef basic_simple_string<char>							string_t;
			typedef basic_simple_string<char>							str_delim_t;
#else /* ? 0 */
			typedef std::basic_string<char> 							string_t;
			typedef std::basic_string<char> 							str_delim_t;
#endif /* 0 */
			typedef string_tokeniser_type_traits<string_t, string_t>	tt_traits_t;

			typedef string_tokeniser<	string_t
									,	char
									,	string_tokeniser_ignore_blanks<true>
									,	string_t
									,	tt_traits_t
									,	string_tokeniser_comparator<char, string_t, tt_traits_t >
									>		tokeniser_char_T;
			typedef string_tokeniser<	string_t
									,	char
									,	string_tokeniser_ignore_blanks<false>
									,	string_t
									,	tt_traits_t
									,	string_tokeniser_comparator<char, string_t, tt_traits_t >
									>		tokeniser_char_F;
			typedef string_tokeniser<	string_t
									,	str_delim_t
									,	string_tokeniser_ignore_blanks<true>
									,	string_t
									,	tt_traits_t
									,	string_tokeniser_comparator<str_delim_t, string_t, tt_traits_t >
									>		tokeniser_string_T;
			typedef string_tokeniser<	string_t
									,	str_delim_t
									,	string_tokeniser_ignore_blanks<false>
									,	string_t
									,	tt_traits_t
									,	string_tokeniser_comparator<str_delim_t, string_t, tt_traits_t >
									>	tokeniser_string_F;

			struct test_sequence
			{
				char const	*sequence;
				ss_size_t	count_char_T;
				ss_size_t	count_char_F;
				ss_size_t	count_string_T;
				ss_size_t	count_string_F;
			};
			char const		delim_c 			=	';';
			char const		*delim_s			=	"<>";
			test_sequence	test_sequences[]	=
			{
					{	";x;"											,	1,	2,	1,	1	}
				,	{	"<>x<>" 										,	1,	1,	1,	2	}
				,	{	""												,	0,	0,	0,	0	}
				,	{	";" 											,	0,	1,	1,	1	}
				,	{	";;;;;;;;;;"									,	0,	10, 1,	1	}
				,	{	";a;b"											,	2,	3,	1,	1	}
				,	{	"a;b;"											,	2,	2,	1,	1	}
				,	{	"a;b"											,	2,	2,	1,	1	}
				,	{	";a;b;" 										,	2,	3,	1,	1	}
				,	{	"x" 											,	1,	1,	1,	1	}
				,	{	";x"											,	1,	2,	1,	1	}
				,	{	"x;"											,	1,	1,	1,	1	}
				,	{	";x;"											,	1,	2,	1,	1	}
				,	{	"x;;"											,	1,	2,	1,	1	}
				,	{	";;x"											,	1,	3,	1,	1	}
				,	{	";;x;;" 										,	1,	4,	1,	1	}
				,	{	";%BIN%;b2;;;WBEM;blah;;;bfg"					,	5,	10, 1,	1	}
				,	{	"<<><>abc<sdfsdf<>sdfs><><><><>sdfsdf<>s<><><>" ,	1,	1,	5,	11	}
				,	{	"<>"											,	1,	1,	0,	1	}
				,	{	"<><>"											,	1,	1,	0,	2	}
				,	{	"x<><>" 										,	1,	1,	1,	2	}
				,	{	"<>x<>" 										,	1,	1,	1,	2	}
				,	{	"<><>x" 										,	1,	1,	1,	3	}
				,	{	"x;;;;;"										,	1,	5,	1,	1	}
#if 0
				,	{	"x<>;;;;<>;"									,	0,	0,	0,	0	}
#endif /* 0 */
			};

			test_sequence	*b;
			test_sequence	*const e  =   &test_sequences[sizeof(test_sequences) / sizeof(test_sequences[0])];

			for(b = &test_sequences[0]; b != e; ++b)
			{
				ss_size_t	n;

#ifdef STLSOFT_OBSOLETE
				n = tokeniser_char_T((*b).sequence, delim_c).size();
#else /* ? STLSOFT_OBSOLETE */
				{
					tokeniser_char_T tokens((*b).sequence, delim_c);
					n = static_cast<ss_size_t>(stlsoft_ns_qual_std(distance)(tokens.begin(), tokens.end()));
				}
#endif /* STLSOFT_OBSOLETE */
				if((*b).count_char_T != n)
				{
					r->report("tokeniser<, char, <true>, ...>  failed", __LINE__);
					bSuccess = false;
				}

#ifdef STLSOFT_OBSOLETE
				n = tokeniser_char_F((*b).sequence, delim_c).size();
#else /* ? STLSOFT_OBSOLETE */
				{
					tokeniser_char_F tokens((*b).sequence, delim_c);
					n = static_cast<ss_size_t>(stlsoft_ns_qual_std(distance)(tokens.begin(), tokens.end()));
				}
#endif /* STLSOFT_OBSOLETE */
				if((*b).count_char_F != n)
				{
					r->report("tokeniser<, char, <false>, ...>	failed", __LINE__);
					bSuccess = false;
				}

#ifdef STLSOFT_OBSOLETE
				n = tokeniser_string_T((*b).sequence, delim_s).size();
#else /* ? STLSOFT_OBSOLETE */
				{
					tokeniser_string_T tokens((*b).sequence, delim_s);
					n = static_cast<ss_size_t>(stlsoft_ns_qual_std(distance)(tokens.begin(), tokens.end()));
				}
#endif /* STLSOFT_OBSOLETE */
				if((*b).count_string_T != n)
				{
					r->report("tokeniser<, string, <true>, ...>  failed", __LINE__);
					bSuccess = false;
				}

#ifdef STLSOFT_OBSOLETE
				n = tokeniser_string_F((*b).sequence, delim_s).size();
#else /* ? STLSOFT_OBSOLETE */
				{
					tokeniser_string_F tokens((*b).sequence, delim_s);
					n = static_cast<ss_size_t>(stlsoft_ns_qual_std(distance)(tokens.begin(), tokens.end()));
				}
#endif /* STLSOFT_OBSOLETE */
				if((*b).count_string_F != n)
				{
					r->report("tokeniser<, string, <false>, ...>  failed", __LINE__);
					bSuccess = false;
				}
			}

			for(b = &test_sequences[0]; b != e; ++b)
			{
				ss_size_t	n;

#ifdef STLSOFT_OBSOLETE
				n = tokeniser_char_T((*b).sequence, delim_c).size();
#else /* ? STLSOFT_OBSOLETE */
				{
					tokeniser_char_T tokens(simple_string((*b).sequence), delim_c);
					n = static_cast<ss_size_t>(stlsoft_ns_qual_std(distance)(tokens.begin(), tokens.end()));
				}
#endif /* STLSOFT_OBSOLETE */
				if((*b).count_char_T != n)
				{
					r->report("tokeniser<, char, <true>, ...>  failed", __LINE__);
					bSuccess = false;
				}

#ifdef STLSOFT_OBSOLETE
				n = tokeniser_char_F((*b).sequence, delim_c).size();
#else /* ? STLSOFT_OBSOLETE */
				{
					tokeniser_char_F tokens(simple_string((*b).sequence), delim_c);
					n = static_cast<ss_size_t>(stlsoft_ns_qual_std(distance)(tokens.begin(), tokens.end()));
				}
#endif /* STLSOFT_OBSOLETE */
				if((*b).count_char_F != n)
				{
					r->report("tokeniser<, char, <false>, ...>	failed", __LINE__);
					bSuccess = false;
				}

#ifdef STLSOFT_OBSOLETE
				n = tokeniser_string_T((*b).sequence, delim_s).size();
#else /* ? STLSOFT_OBSOLETE */
				{
					tokeniser_string_T tokens(simple_string((*b).sequence), delim_s);
					n = static_cast<ss_size_t>(stlsoft_ns_qual_std(distance)(tokens.begin(), tokens.end()));
				}
#endif /* STLSOFT_OBSOLETE */
				if((*b).count_string_T != n)
				{
					r->report("tokeniser<, string, <true>, ...>  failed", __LINE__);
					bSuccess = false;
				}

#ifdef STLSOFT_OBSOLETE
				n = tokeniser_string_F((*b).sequence, delim_s).size();
#else /* ? STLSOFT_OBSOLETE */
				{
					tokeniser_string_F tokens(simple_string((*b).sequence), delim_s);
					n = static_cast<ss_size_t>(stlsoft_ns_qual_std(distance)(tokens.begin(), tokens.end()));
				}
#endif /* STLSOFT_OBSOLETE */
				if((*b).count_string_F != n)
				{
					r->report("tokeniser<, string, <false>, ...>  failed", __LINE__);
					bSuccess = false;
				}
			}

			return bSuccess;
		}

		ss_bool_t test_stlsoft_string_tokeniser_2(unittest_reporter *r)
		{
			ss_bool_t				bSuccess	=	true;

			{ //
				typedef basic_string_view<char> 	string_view_t;
				typedef string_tokeniser<	string_view_t
										,	string_view_t
										>			tokeniser_t;

				static const char		token[] 	=	"%%";
				static const char		str[]		=	"%%abc%%%%def%%ghi%%%%%%%%jkl%%mno%%mno";
				const tokeniser_t		tokens(str, token);
				ss_ptrdiff_t			n1			=	stlsoft_ns_qual_std(distance)(tokens.begin(), tokens.end());
				ss_ptrdiff_t			n2			=	stlsoft_ns_qual_std(count)(tokens.begin(), tokens.end(), "mno");

				if(6 != n1)
				{
					r->report("tokeniser<string_view, string_view, <true>, ...>  failed", __LINE__);
					bSuccess = false;
				}
				if(2 != n2)
				{
					r->report("tokeniser<string_view, string_view, <true>, ...>  failed", __LINE__);
					bSuccess = false;
				}
			}

			{ //
				typedef basic_string_view<char> 	string_view_t;
				typedef string_tokeniser<	string_view_t
										,	string_view_t
										,	string_tokeniser_ignore_blanks<false>
										>			tokeniser_t;

				static const char		token[] 	=	"%%";
				static const char		str[]		=	"%%abc%%%%def%%ghi%%%%%%%%jkl%%mno%%mno";
				const tokeniser_t		tokens(str, token);
				ss_ptrdiff_t			n1			=	stlsoft_ns_qual_std(distance)(tokens.begin(), tokens.end());
				ss_ptrdiff_t			n2			=	stlsoft_ns_qual_std(count)(tokens.begin(), tokens.end(), "mno");

				if(11 != n1)
				{
					r->report("tokeniser<string_view, string_view, <true>, ...>  failed", __LINE__);
					bSuccess = false;
				}
				if(2 != n2)
				{
					r->report("tokeniser<string_view, string_view, <true>, ...>  failed", __LINE__);
					bSuccess = false;
				}
			}

			return bSuccess;
		}

		ss_bool_t test_stlsoft_string_tokeniser_3(unittest_reporter *r)
		{
			ss_bool_t				bSuccess	=	true;

			((void)r);

			return bSuccess;
		}

		ss_bool_t test_stlsoft_string_tokeniser(unittest_reporter *r)
		{
			ss_bool_t				bSuccess	=	true;
			unittest_initialiser	init(r, "STLSoft", "string/basic_string_tokeniser", __FILE__);

			if(!test_stlsoft_string_tokeniser_1(r))
			{
				bSuccess = false;
			}
			if(!test_stlsoft_string_tokeniser_2(r))
			{
				bSuccess = false;
			}
			if(!test_stlsoft_string_tokeniser_3(r))
			{
				bSuccess = false;
			}

			return bSuccess;
		}

		unittest_registrar	  unittest_stlsoft_string_tokeniser(test_stlsoft_string_tokeniser);
	} // anonymous namespace

} // namespace unittest

