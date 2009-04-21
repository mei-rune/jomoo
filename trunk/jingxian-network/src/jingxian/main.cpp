// Jingxian_Network.cpp : 定义控制台应用程序的入口点。

#include "pro_config.h"
#include "jingxian/string/string.hpp"
#include <iostream>


int main(int argc, char* argv[])
{
#ifdef TEST

	{
	StringArray<char, detail::StringOp<char> > sa( split<char, detail::StringOp<char> >( "ad,adf,ff,d,,.d.f",",." ) );
	StringArray<char, detail::StringOp<char> > sa1 = split<std::string, detail::StringOp<char> >( std::string("ad,adf,ff,d,,.d.f"),",." );

	StringArray<char > sa2 = split( "ad,adf,ff,d,,.d.f",",." );
	
	StringArray<char> sa3 = split(std::string( "ad,adf,ff,d,,.d.f" ),",." );
	if( sa.size() != 6)
		std::cout << "ERROR split!" << std::endl;
	if(    0 != strcmp( "ad", sa.ptr( 0 ) )
		&& 0 != strcmp( "adf", sa.ptr( 1 ) )
		&& 0 != strcmp( "ff", sa.ptr( 2 ) )
		&& 0 != strcmp( "d", sa.ptr( 3 ) )
		&& 0 != strcmp( "d", sa.ptr( 4 ) )
		&& 0 != strcmp( "f", sa.ptr( 5 ) ) )
		std::cout << "ERROR split!" << std::endl;

	try
	{
		char* p = sa[ 8 ].ptr;
		std::cout << "ERROR split!" << std::endl;
	}
	catch( OutOfRangeException& e)
	{
	}
	}



	std::string str1( "asdfasdfas" );
	std::string str2( "as" );

	if( !begin_with( str1, "asd" ) )
		std::cout << "ERROR begin_with!" << std::endl;
	
	if( begin_with( str2, "asd" ) )
		std::cout << "ERROR begin_with!" << std::endl;

	if( begin_with( str1, "as1d" ) )
		std::cout << "ERROR begin_with!" << std::endl;

	if( !end_with( str1, "fas" ) )
		std::cout << "ERROR end_with!" << std::endl;
	if( end_with( str1, "f1as" ) )
		std::cout << "ERROR end_with!" << std::endl;

	std::string str3( "       asdkdfasdf");
	std::string str4( "asdkdfasdf         ");
	std::string str5( "       asdkdfasdf         ");

	if( trim_left( str3 ) != "asdkdfasdf" )
		std::cout << "ERROR trim_left!" << std::endl;

	if( trim_right( str4 ) != "asdkdfasdf" )
		std::cout << "ERROR trim_right!" << std::endl;

	if( trim_all( str5 ) != "asdkdfasdf" )
		std::cout << "ERROR trim_all!" << std::endl;

	
	std::string str6( "asdkdfasdf");
	std::string str7( "asdkdfasdf");
	std::string str8( "asdkdfasdf");
	
	if( trim_left( str6, "af" ) != "sdkdfasdf" )
		std::cout << "ERROR trim_left!" << std::endl;
	
	if( trim_right( str7, "af" ) != "asdkdfasd" )
		std::cout << "ERROR trim_right!" << std::endl;

	if( trim_all( str8, "af" ) != "sdkdfasd" )
		std::cout << "ERROR trim_all!" << std::endl;

	std::string str9( "asdkdfasdf");
	std::string str10( "asdddkdfasdf");
	std::string str11( "asdkdfasdf");

	if( replace_all( str9, "a", "c" ) != "csdkdfcsdf" )
		std::cout << "ERROR replace_all!" << std::endl;
	
	if( replace_all( str10, "a", "cc" ) != "ccsdddkdfccsdf" )
		std::cout << "ERROR replace_all!" << std::endl;

	if( replace_all( str11, "a", "aaa" ) != "aaasdkdfaaasdf" )
		std::cout << "ERROR replace_all!" << std::endl;

	std::string str12( "aAsDFddSdkdfasdf");
	std::string str13( "asdSkdfaFAsSDdf");

	if( transform_upper( str12 ) != "AASDFDDSDKDFASDF" )
		std::cout << "ERROR transform_upper!" << std::endl;

	if( transform_lower( str13 ) != "asdskdfafassddf" )
		std::cout << "ERROR transform_lower!" << std::endl;

#endif //



	int i ; 
	std::cin  >> i;
	return 0;
}

