
// Updated: 18th June 2006

#if !defined(STLSOFT_INCL_STLSOFT_STRING_HPP_COPY_FUNCTIONS)
# error This file cannot be directly included, and should only be included within stlsoft/string/copy_functions.hpp
#endif /* !STLSOFT_INCL_STLSOFT_STRING_HPP_COPY_FUNCTIONS */

#if !defined(STLSOFT_UNITTEST)
# error This file cannot be included when not unit-testing STLSoft
#endif /* !STLSOFT_UNITTEST */

namespace unittest
{
	namespace
	{
		ss_bool_t test_stlsoft_copy_functions(unittest_reporter *r)
		{
			ss_bool_t				bSuccess	=	true;

			unittest_initialiser	init(r, "STLSoft", "string/copy_functions", __FILE__);

			{
				static const char	source[]	=	"A source string";
				const size_t		SRC_LEN 	=	STLSOFT_NUM_ELEMENTS(source) - 1;
				char				dest[SRC_LEN + 10];
				size_t				cch;

#if defined(STLSOFT_COMPILER_IS_BORLAND)
				STLSOFT_SUPPRESS_UNUSED(&SRC_LEN);
#endif /* compiler */

				cch = copy_contents(static_cast<char*>(NULL), 0, source, SRC_LEN);
				if(SRC_LEN != cch)
				{
					r->report("copy_contents(NULL, , , ) failed", __LINE__);
					bSuccess = false;
				}

				dest[0] = '~';
				cch = copy_contents(&dest[0], STLSOFT_NUM_ELEMENTS(dest), source, 0);
				if( 0 != cch ||
					'\0' != dest[0])
				{
					r->report("copy_contents(, , , 0) failed", __LINE__);
					bSuccess = false;
				}

				dest[0] = '~';
				cch = copy_contents(&dest[0], 0, source, SRC_LEN);
				if( 0 != cch ||
					'~' != dest[0])
				{
					r->report("copy_contents(, 0, , SRC_LEN) failed", __LINE__);
					bSuccess = false;
				}

				dest[0] = '~';
				dest[1] = '~';
				cch = copy_contents(&dest[0], 1, source, SRC_LEN);
				if( 1 != cch ||
					'A' != dest[0] ||
					'~' != dest[1])
				{
					r->report("copy_contents(, 1, , SRC_LEN) failed", __LINE__);
					bSuccess = false;
				}

				dest[SRC_LEN] = '~';
				cch = copy_contents(dest, SRC_LEN, source, SRC_LEN);
				if( SRC_LEN != cch ||
					0 != ::strncmp(dest, source, SRC_LEN) ||
					'~' != dest[SRC_LEN])
				{
					r->report("copy_contents(, SRC_LEN, , SRC_LEN) failed", __LINE__);
					bSuccess = false;
				}

				dest[SRC_LEN] = '~';
				cch = copy_contents(dest, STLSOFT_NUM_ELEMENTS(dest), source, SRC_LEN);
				if( SRC_LEN != cch ||
					0 != ::strcmp(dest, source))
				{
					r->report("copy_contents(, >SRC_LEN, , SRC_LEN) failed", __LINE__);
					bSuccess = false;
				}
			}

			return bSuccess;
		}

		unittest_registrar	  unittest_stlsoft_copy_functions(test_stlsoft_copy_functions);
	} // anonymous namespace

} // namespace unittest

