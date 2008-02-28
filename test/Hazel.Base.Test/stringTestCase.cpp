#include "stdafx.h"
#include <cppunit/config/SourcePrefix.h>
#include "stringTestCase.h"
#include "Hazel.Base/string.hpp"
#include "Hazel.Base/make_null_ptr.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION( stringTestCase );

#define TEST_STRING "test_string"
#define LITERAL( X ) X

void stringTestCase::setUp()
{
}

void stringTestCase::testConstructor()
{
	//{
 //       string_view bcs( make_null_ptr<char>() );
	//	CPPUNIT_ASSERT_EQUAL( bcs.size(), (string_view::size_type)0 );
 //       CPPUNIT_ASSERT( bcs.empty() );
 //   }

    {
        string_view bcs( "" );
        CPPUNIT_ASSERT_EQUAL( bcs.size(), (string_view::size_type)0 );
        CPPUNIT_ASSERT( bcs.empty() );
    }

    {
        string_view bcs( "",0 );
        CPPUNIT_ASSERT_EQUAL( bcs.size(),(string_view::size_type)0 );
        CPPUNIT_ASSERT( bcs.empty() );
    }

	{
        string_view bcs( "1234567890",10 );
        CPPUNIT_ASSERT_EQUAL( bcs.size(), (string_view::size_type)10 );
        CPPUNIT_ASSERT( !bcs.empty() );
    }

	{
        typedef string_view::traits_type traits;

        string_view bcs( TEST_STRING );
        CPPUNIT_ASSERT_EQUAL( traits::compare( bcs.buf(), TEST_STRING, bcs.size() ), 0 );
        CPPUNIT_ASSERT_EQUAL( bcs.size(), traits::length( TEST_STRING ) );

        string_view bcs1( bcs );
        CPPUNIT_ASSERT_EQUAL( traits::compare( bcs1.buf(), TEST_STRING, bcs1.size() ), 0 );
    }

    {
        typedef string_view::traits_type traits;

        string_view bcs( TEST_STRING, 4 );
        CPPUNIT_ASSERT_EQUAL( traits::compare( bcs.buf(),  "test" , bcs.size() ), 0 );

		CPPUNIT_ASSERT_EQUAL( bcs.compare(  "test" ), 0 );
		CPPUNIT_ASSERT_EQUAL( bcs.compare(  "test" ), 0 );
    }

    {
        typedef string_view::traits_type traits;

        string_view bcs( TEST_STRING, 6 );
        CPPUNIT_ASSERT_EQUAL( traits::compare( bcs.buf(),  "test_s" , bcs.size() ), 0 );
		CPPUNIT_ASSERT_EQUAL( bcs.compare(  "test_s" ), 0 );
    }
}


void stringTestCase::testDataAccess()
{
    typedef string_view::traits_type traits_type;

    string_view bcs1( TEST_STRING );
    CPPUNIT_ASSERT_EQUAL( traits_type::compare( bcs1.buf(), TEST_STRING, bcs1.size() ), 0 );
    CPPUNIT_ASSERT_EQUAL( traits_type::compare( bcs1.buf(), bcs1.buf(), bcs1.size() ), 0 );

    CPPUNIT_ASSERT_EQUAL( bcs1[0], 't' );
    CPPUNIT_ASSERT_EQUAL( bcs1[4], '_' );
    CPPUNIT_ASSERT_EQUAL( bcs1[bcs1.size()-1], 'g' );

    CPPUNIT_ASSERT_EQUAL( bcs1[0], bcs1.at( 0 ) );
    CPPUNIT_ASSERT_EQUAL( bcs1[2], bcs1.at( 5 ) );
    CPPUNIT_ASSERT_EQUAL( bcs1.at( bcs1.size() - 1 ), 'g' );

    CPPUNIT_ASSERT_EQUAL( * bcs1.begin(), 't' );
    CPPUNIT_ASSERT_EQUAL( * (bcs1.end()-1) , 'g' );

}

//BOOST_TEST_CASE_TEMPLATE_FUNCTION( asignment_test, CharT )
//{
//    typedef typename string_view::traits_type traits_type;
//
//    string_view bcs1;
//    string_literal<CharT> l( "test", 4 );
//
//    bcs1 = l.buff;
//    CPPUNIT_ASSERT_EQUAL( traits_type::compare( bcs1.begin(), LITERAL( "test" ), bcs1.size() ), 0 );
//
//    string_view bcs2( TEST_STRING );
//    bcs1 = bcs2;
//    CPPUNIT_ASSERT_EQUAL( traits_type::compare( bcs1.begin(), TEST_STRING, bcs1.size() ), 0 );
//
//    bcs1.assign( l.buff );
//    CPPUNIT_ASSERT_EQUAL( traits_type::compare( bcs1.begin(), LITERAL( "test" ), bcs1.size() ), 0 );
//
//    bcs1.assign( l.buff+1, l.buff+3 );
//    CPPUNIT_ASSERT_EQUAL( traits_type::compare( bcs1.begin(), LITERAL( "est" ), bcs1.size() ), 0 );
//
//    bcs1.assign( bcs2, 4, 3 );
//    CPPUNIT_ASSERT_EQUAL( traits_type::compare( bcs1.begin(), LITERAL( "_st" ), bcs1.size() ), 0 );
//
//    bcs1.swap( bcs2 );
//    CPPUNIT_ASSERT_EQUAL( traits_type::compare( bcs1.begin(), TEST_STRING, bcs1.size() ), 0 );
//    CPPUNIT_ASSERT_EQUAL( traits_type::compare( bcs2.begin(), LITERAL( "_st" ), bcs2.size() ), 0 );
//}

void stringTestCase::testFind()
{
    string_view bcs1( TEST_STRING );

   // CPPUNIT_ASSERT_EQUAL( bcs1.find( string_view() ), string_view::npos );
	CPPUNIT_ASSERT_EQUAL( bcs1.find( LITERAL( "test" ) ), (string_view::size_type)0 );
    CPPUNIT_ASSERT_EQUAL( bcs1.find( TEST_STRING ), (string_view::size_type)0 );
    CPPUNIT_ASSERT_EQUAL( bcs1.find( LITERAL( "test_string " ) ), string_view::npos );
    CPPUNIT_ASSERT_EQUAL( bcs1.find( LITERAL( " test_string" ) ), string_view::npos );
    CPPUNIT_ASSERT_EQUAL( bcs1.find( LITERAL( "est" ) ), (string_view::size_type)1 );
    CPPUNIT_ASSERT_EQUAL( bcs1.find( LITERAL( "t_st" ) ), (string_view::size_type)3 );
    CPPUNIT_ASSERT_EQUAL( bcs1.find( LITERAL( "ing" ) ),(string_view::size_type) 8 );
    CPPUNIT_ASSERT_EQUAL( bcs1.find( LITERAL( "tst" ) ), string_view::npos );

   // CPPUNIT_ASSERT_EQUAL( bcs1.rfind( string_view() ), string_view::npos );
    CPPUNIT_ASSERT_EQUAL( bcs1.rfind( LITERAL( "test" ) ), (string_view::size_type)0 );
    CPPUNIT_ASSERT_EQUAL( bcs1.rfind( TEST_STRING ), (string_view::size_type)0 );
    CPPUNIT_ASSERT_EQUAL( bcs1.rfind( LITERAL( "test_string " ) ), string_view::npos );
    CPPUNIT_ASSERT_EQUAL( bcs1.rfind( LITERAL( " test_string" ) ), string_view::npos );
    CPPUNIT_ASSERT_EQUAL( bcs1.rfind( LITERAL( "est" ) ), (string_view::size_type)1 );
    CPPUNIT_ASSERT_EQUAL( bcs1.rfind( LITERAL( "t_st" ) ), (string_view::size_type)3 );
    CPPUNIT_ASSERT_EQUAL( bcs1.rfind( LITERAL( "ing" ) ), (string_view::size_type)8 );
    CPPUNIT_ASSERT_EQUAL( bcs1.rfind( LITERAL( "tst" ) ), string_view::npos );
}

void stringTestCase::testFind_First_Of()
{
    string_view bcs1( TEST_STRING );
	std::string s1( TEST_STRING );

   // CPPUNIT_ASSERT_EQUAL( bcs1.find( string_view() ), string_view::npos );
	CPPUNIT_ASSERT_EQUAL( bcs1.find_first_of( "tes" , 0  ), (string_view::size_type)0 );
    CPPUNIT_ASSERT_EQUAL( bcs1.find_first_of( "s" ), (string_view::size_type)2 );

    CPPUNIT_ASSERT_EQUAL( bcs1.find_first_of( "ing" ),(string_view::size_type) 8 );
    CPPUNIT_ASSERT_EQUAL( bcs1.find_first_of( "r" ), (string_view::size_type)7  );
	CPPUNIT_ASSERT_EQUAL( bcs1.find_first_of( "tr",1 ), (string_view::size_type)3  );
	CPPUNIT_ASSERT_EQUAL( bcs1.find_first_of( "tg",4 ), (string_view::size_type)6  );


	CPPUNIT_ASSERT_EQUAL( bcs1.find_last_of( "ing" ),(string_view::size_type) 10 );
    CPPUNIT_ASSERT_EQUAL( bcs1.find_last_of( "r" ), (string_view::size_type)7  );
	CPPUNIT_ASSERT_EQUAL( bcs1.find_last_of( "tr",1 ), s1.find_last_of( "tr",1 )  );
	CPPUNIT_ASSERT_EQUAL( bcs1.find_last_of( "tg" ), (string_view::size_type)10  );
	CPPUNIT_ASSERT_EQUAL( bcs1.find_last_of( "t" ), (string_view::size_type)6  );

}