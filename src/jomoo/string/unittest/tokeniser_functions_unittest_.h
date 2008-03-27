
#if !defined(STLSOFT_INCL_STLSOFT_STRING_HPP_TOKENISER_FUNCTIONS)
# error This file cannot be directly included, and should only be included within stlsoft/string/tokeniser_functions.hpp
#endif /* !STLSOFT_INCL_STLSOFT_STRING_HPP_TOKENISER_FUNCTIONS */

#if !defined(STLSOFT_UNITTEST)
# error This file cannot be included when not unit-testing STLSoft
#endif /* !STLSOFT_UNITTEST */

namespace unittest
{
#if !defined(STLSOFT_COMPILER_IS_WATCOM)

	namespace
	{
		template <ss_typename_param_k C>
		struct tokeniser_functions_tester
		{
		public:
			typedef C												char_type;
# if defined(STLSOFT_COMPILER_IS_MWERKS) && \
	 ((__MWERKS__ & 0xff00) < 0x3000)
			typedef basic_simple_string<char_type>					string_view_type;
# else /* ? compiler */
			typedef basic_string_view<char_type>					string_view_type;
# endif /* compiler */
			typedef stlsoft_ns_qual_std(vector)<string_view_type>	results_type;

		public:
			static results_type tokenise_1(char_type const *s, char_type delim)
			{
				char_type const 		*p0 =	s;
				char_type const 		*p1 =	s;
				char_type const *const	end =	s + strlen(s); // NOTE: Obviously this is only for char at the moment!
				results_type			results;

				for(; end != find_next_token(p0, p1, end, delim); )
				{
					results.push_back(string_view_type(p0, p1));
				}

				return results;
			}

			static results_type tokenise_2(char_type const *s, char_type delim)
			{
				char_type const 		*p0 =	s;
				char_type const 		*p1 =	s;
				results_type			results;

				for(; find_next_token(p0, p1, delim); )
				{
					results.push_back(string_view_type(p0, p1));
				}

				return results;
			}
		};

		template <ss_typename_param_k C>
		bool test_tokeniser_function_(unittest_reporter *r)
		{
			typedef tokeniser_functions_tester<C>	tester_t;

			ss_bool_t	bSuccess	=	true;

			{
				ss_typename_type_k tester_t::results_type	results1	=	tester_t::tokenise_1(";;*.zip;*.html;;*.exe;;*.pdf;", ';');
				ss_typename_type_k tester_t::results_type	results2	=	tester_t::tokenise_2(";;*.zip;*.html;;*.exe;;*.pdf;", ';');

				if(results1 != results2)
				{
					r->report("find_next_token() overloads produced different results", __LINE__);
					bSuccess = false;
				}

				if(results1.size() != 7)
				{
					r->report("find_next_token() produced wrong number of results", __LINE__);
					bSuccess = false;
				}

				if(results1[0] != "")
				{
					r->report("find_next_token() produced wrong number results", __LINE__);
					bSuccess = false;
				}

				if(results1[1] != "*.zip")
				{
					r->report("find_next_token() produced wrong number results", __LINE__);
					bSuccess = false;
				}

				if(results1[2] != "*.html")
				{
					r->report("find_next_token() produced wrong number results", __LINE__);
					bSuccess = false;
				}

				if(results1[3] != "")
				{
					r->report("find_next_token() produced wrong number results", __LINE__);
					bSuccess = false;
				}

				if(results1[4] != "*.exe")
				{
					r->report("find_next_token() produced wrong number results", __LINE__);
					bSuccess = false;
				}

				if(results1[5] != "")
				{
					r->report("find_next_token() produced wrong number results", __LINE__);
					bSuccess = false;
				}

				if(results1[6] != "*.pdf")
				{
					r->report("find_next_token() produced wrong number results", __LINE__);
					bSuccess = false;
				}
			}

			{
				ss_typename_type_k tester_t::results_type	results1	=	tester_t::tokenise_1("*", ';');
				ss_typename_type_k tester_t::results_type	results2	=	tester_t::tokenise_2("*", ';');

				if(results1 != results2)
				{
					r->report("find_next_token() overloads produced different results", __LINE__);
					bSuccess = false;
				}

				if(results1.size() != 1)
				{
					r->report("find_next_token() produced wrong number of results", __LINE__);
					bSuccess = false;
				}

				if(results1[0] != "*")
				{
					r->report("find_next_token() produced wrong number results", __LINE__);
					bSuccess = false;
				}
			}

			{
				ss_typename_type_k tester_t::results_type	results1	=	tester_t::tokenise_1("", ';');
				ss_typename_type_k tester_t::results_type	results2	=	tester_t::tokenise_2("", ';');

				if(results1 != results2)
				{
					r->report("find_next_token() overloads produced different results", __LINE__);
					bSuccess = false;
				}

				if(results1.size() != 0)
				{
					r->report("find_next_token() produced wrong number of results", __LINE__);
					bSuccess = false;
				}
			}

			{
				ss_typename_type_k tester_t::results_type	results1	=	tester_t::tokenise_1(";", ';');
				ss_typename_type_k tester_t::results_type	results2	=	tester_t::tokenise_2(";", ';');

				if(results1 != results2)
				{
					r->report("find_next_token() overloads produced different results", __LINE__);
					bSuccess = false;
				}

				if(results1.size() != 0)
				{
					r->report("find_next_token() produced wrong number of results", __LINE__);
					bSuccess = false;
				}
			}

			{
				ss_typename_type_k tester_t::results_type	results1	=	tester_t::tokenise_1(";;", ';');
				ss_typename_type_k tester_t::results_type	results2	=	tester_t::tokenise_2(";;", ';');

				if(results1 != results2)
				{
					r->report("find_next_token() overloads produced different results", __LINE__);
					bSuccess = false;
				}

				if(results1.size() != 1)
				{
					r->report("find_next_token() produced wrong number of results", __LINE__);
					bSuccess = false;
				}

				if(results1[0] != "")
				{
					r->report("find_next_token() produced wrong number results", __LINE__);
					bSuccess = false;
				}
			}

			return bSuccess;
		}

		ss_bool_t test_stlsoft_string_tokeniser_functions(unittest_reporter *r)
		{
			ss_bool_t				bSuccess	=	true;

			unittest_initialiser	init(r, "STLSoft", "string/tokeniser_functions", __FILE__);

			if( bSuccess &&
				!test_tokeniser_function_<char>(r))
			{
				bSuccess = false;
			}

# if 0
			if( bSuccess &&
				!test_tokeniser_function_<wchar_t>(r))
			{
				bSuccess = false;
			}
# endif /* 0 */

			return bSuccess;
		}

		unittest_registrar	  unittest_stlsoft_string_tokeniser_functions(test_stlsoft_string_tokeniser_functions);
	} // anonymous namespace

#endif /* compiler */

} // namespace unittest

