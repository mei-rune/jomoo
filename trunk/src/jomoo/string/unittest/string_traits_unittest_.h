
#if !defined(STLSOFT_INCL_STLSOFT_STRING_HPP_STRING_TRAITS)
# error This file cannot be directly included, and should only be included within stlsoft/string/string_traits.hpp
#endif /* !STLSOFT_INCL_STLSOFT_STRING_HPP_STRING_TRAITS */

#if !defined(STLSOFT_UNITTEST)
# error This file cannot be included when not unit-testing STLSoft
#endif /* !STLSOFT_UNITTEST */

namespace unittest
{
	namespace
	{
		template <ss_typename_param_k S>
		ss_bool_t test_stlsoft_string_traits__(S const &, unittest_reporter *r, const ss_size_t cbCharType)
		{
			typedef string_traits<S>						traits_t;
			typedef ss_typename_type_k traits_t::char_type	char_t;

			ss_bool_t					bSuccess	=	true;

			if(cbCharType != sizeof(char_t))
			{
				r->report("size of discriminated char_type incorrect", __LINE__);
				bSuccess = false;
			}

			return bSuccess;
		}

#if 1
		template <ss_typename_param_k S>
		ss_bool_t test_stlsoft_string_traits_(S const &s, unittest_reporter *r, const ss_size_t cbCharType)
		{
			return test_stlsoft_string_traits__(s, r, cbCharType);
		}

		template <ss_typename_param_k C>
		ss_bool_t test_stlsoft_string_traits_(C const *s, unittest_reporter *r, const ss_size_t cbCharType)
		{
			return test_stlsoft_string_traits__(s, r, cbCharType);
		}
#else
		template <ss_typename_param_k S>
		ss_bool_t test_stlsoft_string_traits_(S const &s, unittest_reporter *r, const ss_size_t cbCharType, int_to_type<0>)
		{
			return test_stlsoft_string_traits__(s, r, cbCharType);
		}
		template <ss_typename_param_k S>
		ss_bool_t test_stlsoft_string_traits_(S const &s, unittest_reporter *r, const ss_size_t cbCharType, int_to_type<1>)
		{
			return test_stlsoft_string_traits__(&s[0], r, cbCharType);
		}
#endif /* 0 */

		template <ss_typename_param_k S>
		ss_bool_t test_stlsoft_string_traits(S const &s, unittest_reporter *r, const ss_size_t cbCharType)
		{
#if 1
			typedef string_traits<S>						traits_t;
			ss_bool_t										bSuccess	=	true;

#if !defined(STLSOFT_COMPILER_IS_BORLAND)
			typedef ss_typename_type_k traits_t::char_type	char_t;

			if(cbCharType != sizeof(char_t))
			{
				r->report("size of discriminated char_type incorrect", __LINE__);
				bSuccess = false;
			}
#endif /* compiler */

			STLSOFT_SUPPRESS_UNUSED(s);
			STLSOFT_SUPPRESS_UNUSED(r);
			STLSOFT_SUPPRESS_UNUSED(cbCharType);

			return bSuccess;
#else

# if 0
#  ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT
#  else /* ? STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT */
#  endif /* STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT */

			enum { is_array_or_pointer = 0 != base_type_traits_array_detector<S>::value };

			typedef int_to_type<is_array_or_pointer>	overload_t;

			return test_stlsoft_string_traits_(s, r, cbCharType, overload_t());
# else /* ? 0 */
			return test_stlsoft_string_traits_(s, r, cbCharType);
# endif /* 0 */

#endif /* 0 */
		}

		ss_bool_t test_stlsoft_string_traits(unittest_reporter *r)
		{
			ss_bool_t				bSuccess	=	true;

			unittest_initialiser	init(r, "STLSoft", "string/string_traits", __FILE__);

			{
				const char	*s	=	"";

				if(!test_stlsoft_string_traits(s, r, sizeof(char)))
				{
					bSuccess = false;
				}
			}

			{
				char	*s	=	"";

				if(!test_stlsoft_string_traits(s, r, sizeof(char)))
				{
					bSuccess = false;
				}
			}

#if 0
			{
				const char	s[] =	"";

				if(!test_stlsoft_string_traits(s, r, sizeof(char)))
				{
					bSuccess = false;
				}
			}
#endif /* 0 */

			{
				const wchar_t	*s	=	L"";

				if(!test_stlsoft_string_traits(s, r, sizeof(wchar_t)))
				{
					bSuccess = false;
				}
			}

			{
				wchar_t *s	=	L"";

				if(!test_stlsoft_string_traits(s, r, sizeof(wchar_t)))
				{
					bSuccess = false;
				}
			}

			{
				stlsoft_ns_qual_std(string) s	=	"";

				if(!test_stlsoft_string_traits(s, r, sizeof(char)))
				{
					bSuccess = false;
				}
			}

			{
				stlsoft_ns_qual_std(wstring)	s	=	L"";

				if(!test_stlsoft_string_traits(s, r, sizeof(wchar_t)))
				{
					bSuccess = false;
				}
			}

			return bSuccess;
		}

		unittest_registrar	  unittest_stlsoft_string_traits(test_stlsoft_string_traits);
	} // anonymous namespace

} // namespace unittest

