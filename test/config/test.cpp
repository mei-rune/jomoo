#include "stdafx.h"

#include <iostream>
#include "../bt_configure_xml.cpp"
#include "../bt_log_cxx.cpp"
#include "../../../xml/xml.cpp"
#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <boost/shared_ptr.hpp>

const tchar cfg[] = "<?xml version=\"1.0\"?>\n"  \
"<config>\n" \
"<af>1f</af>" \
"<bf>2f</bf>" \
"<cf><af>3f1f</af></cf>\n" \
"<df>" \
	"<af><af>4f1f1f</af><bf>4f1f2f</bf></af>" \
	"<bf>aa</bf>" \
	"<cf>aa</cf>" \
	"<df><af>4f4f1f</af><bf>4f4f2f</bf></df>" \
"</df>" \
"</config>";

use_bt

#define ASSERT( K,R ) 	{	BT_Configure_Base* ddf = config.findChild( K );		\
		assert( ddf != 0 );											\
		assert( tstrcmp( ddf->getValue( ) , R ) == 0  );}

void dumpConfig( const BT_Configure_Base& node , std::string str )
{
	
	if( node.getValue() == 0 )
	{
		
		std::cout << str << node.getName() << std::endl;
		for( BT_Configure_Base::const_iterator it = node.begin(); it != node.end(); it ++ )
		{
			dumpConfig( *it, str + "\t" );
		}
	}
	else
	{
		std::cout << str << node.getName() << " : " << node.getValue() << std::endl;
	}

}

void assertConfig( BT_Configure_Base& config )
{
		assert( tstrcmp( config.findValue( "af" ) , "1f" ) == 0 );
		assert( tstrcmp( config.findValue( "bf" ) , "2f" ) == 0  );
		BT_Configure_Base* cf = config.findChild( "cf" );
		assert( cf != 0 );
		assert( tstrcmp( cf->findValue( "af" ) , "3f1f" ) == 0  );

		BT_Configure_Base* df = config.findChild( "df" );
		assert( df != 0 );
		assert( tstrcmp( df->findValue( "bf" ) , "aa" ) == 0  );
		assert( tstrcmp( df->findValue( "cf" ) , "aa" )  == 0 );

		ASSERT( "df.af.af","4f1f1f");
		ASSERT( "df.af.bf","4f1f2f");


		ASSERT( "df.df.af","4f4f1f");
		ASSERT( "df.df.bf","4f4f2f");

		BT_Configure_Base* af = df->findChild( "af" );
		assert( af != 0 );
		assert( tstrcmp( af->findValue( "af" ) , "4f1f1f" ) == 0  );
		assert( tstrcmp( af->findValue( "bf" ) , "4f1f2f" ) == 0  );


		BT_Configure_Base* ddf = df->findChild( "df" );
		assert( ddf != 0 );
		assert( tstrcmp( ddf->findValue( "af" ) , "4f4f1f" ) == 0  );
		assert( tstrcmp( ddf->findValue( "bf" ) , "4f4f2f" ) == 0  );



		assert( tstrcmp( config.findValue( ".af" ) , "1f" ) == 0 );
		assert( tstrcmp( config.findValue( ".bf" ) , "2f" ) == 0  );
		assert( tstrcmp( config.findValue( "cf.af" ) , "3f1f" ) == 0  );
		assert( tstrcmp( config.findValue( "df.bf" ) , "aa" ) == 0  );
		assert( tstrcmp( config.findValue( "df.cf" ) , "aa" )  == 0 );
		assert( tstrcmp( config.findValue( "df.af.af" ) , "4f1f1f" ) == 0  );
		assert( tstrcmp( config.findValue( "df.af.bf" ) , "4f1f2f" ) == 0  );
		assert( tstrcmp( config.findValue( "df.df.af" ) , "4f4f1f" ) == 0  );
		assert( tstrcmp( config.findValue( "df.df.bf" ) , "4f4f2f" ) == 0  );



		assert( tstrcmp( config.findValue( ".af" ) , "1f" ) == 0 );
		assert( tstrcmp( config.findValue( ".bf" ) , "2f" ) == 0  );
		assert( tstrcmp( config.findValue( ".cf.af" ) , "3f1f" ) == 0  );
		assert( tstrcmp( config.findValue( ".df.bf" ) , "aa" ) == 0  );
		assert( tstrcmp( config.findValue( ".df.cf" ) , "aa" )  == 0 );
		assert( tstrcmp( config.findValue( ".df.af.af" ) , "4f1f1f" ) == 0  );
		assert( tstrcmp( config.findValue( ".df.af.bf" ) , "4f1f2f" ) == 0  );
		assert( tstrcmp( config.findValue( ".df.df.af" ) , "4f4f1f" ) == 0  );
		assert( tstrcmp( config.findValue( ".df.df.bf" ) , "4f4f2f" ) == 0  );



		assert( tstrcmp( config.findValue( ".Af" ) , "1f" ) == 0 );
		assert( tstrcmp( config.findValue( ".bF" ) , "2f" ) == 0  );
		assert( tstrcmp( config.findValue( "cf.Af" ) , "3f1f" ) == 0  );
		assert( tstrcmp( config.findValue( "df.Bf" ) , "aa" ) == 0  );
		assert( tstrcmp( config.findValue( "df.Cf" ) , "aa" )  == 0 );
		assert( tstrcmp( config.findValue( "df.Af.af" ) , "4f1f1f" ) == 0  );
		assert( tstrcmp( config.findValue( "df.Af.bf" ) , "4f1f2f" ) == 0  );
		assert( tstrcmp( config.findValue( "df.Df.af" ) , "4f4f1f" ) == 0  );
		assert( tstrcmp( config.findValue( "df.Df.bf" ) , "4f4f2f" ) == 0  );



		assert( tstrcmp( config.findValue( ".aF" ) , "1f" ) == 0 );
		assert( tstrcmp( config.findValue( ".bF" ) , "2f" ) == 0  );
		assert( tstrcmp( config.findValue( ".cF.af" ) , "3f1f" ) == 0  );
		assert( tstrcmp( config.findValue( ".dF.bf" ) , "aa" ) == 0  );
		assert( tstrcmp( config.findValue( ".dF.cf" ) , "aa" )  == 0 );
		assert( tstrcmp( config.findValue( ".dF.af.af" ) , "4f1f1f" ) == 0  );
		assert( tstrcmp( config.findValue( ".dF.af.bf" ) , "4f1f2f" ) == 0  );
		assert( tstrcmp( config.findValue( ".dF.df.af" ) , "4f4f1f" ) == 0  );
		assert( tstrcmp( config.findValue( ".dF.df.bf" ) , "4f4f2f" ) == 0  );
}

void assertConfig_const( const BT_Configure_Base& config )
{
		assert( tstrcmp( config.findValue( "af" ) , "1f" ) == 0 );
		assert( tstrcmp( config.findValue( "bf" ) , "2f" ) == 0  );
		const BT_Configure_Base* cf = config.findChild( "cf" );
		assert( cf != 0 );
		assert( tstrcmp( cf->findValue( "af" ) , "3f1f" ) == 0  );

		const BT_Configure_Base* df = config.findChild( "df" );
		assert( df != 0 );
		assert( tstrcmp( df->findValue( "bf" ) , "aa" ) == 0  );
		assert( tstrcmp( df->findValue( "cf" ) , "aa" )  == 0 );

		const BT_Configure_Base* af = df->findChild( "af" );
		assert( af != 0 );
		assert( tstrcmp( af->findValue( "af" ) , "4f1f1f" ) == 0  );
		assert( tstrcmp( af->findValue( "bf" ) , "4f1f2f" ) == 0  );


		const BT_Configure_Base* ddf = df->findChild( "df" );
		assert( ddf != 0 );
		assert( tstrcmp( ddf->findValue( "af" ) , "4f4f1f" ) == 0  );
		assert( tstrcmp( ddf->findValue( "bf" ) , "4f4f2f" ) == 0  );



		assert( tstrcmp( config.findValue( ".af" ) , "1f" ) == 0 );
		assert( tstrcmp( config.findValue( ".bf" ) , "2f" ) == 0  );
		assert( tstrcmp( config.findValue( "cf.af" ) , "3f1f" ) == 0  );
		assert( tstrcmp( config.findValue( "df.bf" ) , "aa" ) == 0  );
		assert( tstrcmp( config.findValue( "df.cf" ) , "aa" )  == 0 );
		assert( tstrcmp( config.findValue( "df.af.af" ) , "4f1f1f" ) == 0  );
		assert( tstrcmp( config.findValue( "df.af.bf" ) , "4f1f2f" ) == 0  );
		assert( tstrcmp( config.findValue( "df.df.af" ) , "4f4f1f" ) == 0  );
		assert( tstrcmp( config.findValue( "df.df.bf" ) , "4f4f2f" ) == 0  );



		assert( tstrcmp( config.findValue( ".af" ) , "1f" ) == 0 );
		assert( tstrcmp( config.findValue( ".bf" ) , "2f" ) == 0  );
		assert( tstrcmp( config.findValue( ".cf.af" ) , "3f1f" ) == 0  );
		assert( tstrcmp( config.findValue( ".df.bf" ) , "aa" ) == 0  );
		assert( tstrcmp( config.findValue( ".df.cf" ) , "aa" )  == 0 );
		assert( tstrcmp( config.findValue( ".df.af.af" ) , "4f1f1f" ) == 0  );
		assert( tstrcmp( config.findValue( ".df.af.bf" ) , "4f1f2f" ) == 0  );
		assert( tstrcmp( config.findValue( ".df.df.af" ) , "4f4f1f" ) == 0  );
		assert( tstrcmp( config.findValue( ".df.df.bf" ) , "4f4f2f" ) == 0  );



		assert( tstrcmp( config.findValue( ".Af" ) , "1f" ) == 0 );
		assert( tstrcmp( config.findValue( ".bF" ) , "2f" ) == 0  );
		assert( tstrcmp( config.findValue( "cf.Af" ) , "3f1f" ) == 0  );
		assert( tstrcmp( config.findValue( "df.Bf" ) , "aa" ) == 0  );
		assert( tstrcmp( config.findValue( "df.Cf" ) , "aa" )  == 0 );
		assert( tstrcmp( config.findValue( "df.Af.af" ) , "4f1f1f" ) == 0  );
		assert( tstrcmp( config.findValue( "df.Af.bf" ) , "4f1f2f" ) == 0  );
		assert( tstrcmp( config.findValue( "df.Df.af" ) , "4f4f1f" ) == 0  );
		assert( tstrcmp( config.findValue( "df.Df.bf" ) , "4f4f2f" ) == 0  );



		assert( tstrcmp( config.findValue( ".aF" ) , "1f" ) == 0 );
		assert( tstrcmp( config.findValue( ".bF" ) , "2f" ) == 0  );
		assert( tstrcmp( config.findValue( ".cF.af" ) , "3f1f" ) == 0  );
		assert( tstrcmp( config.findValue( ".dF.bf" ) , "aa" ) == 0  );
		assert( tstrcmp( config.findValue( ".dF.cf" ) , "aa" )  == 0 );
		assert( tstrcmp( config.findValue( ".dF.af.af" ) , "4f1f1f" ) == 0  );
		assert( tstrcmp( config.findValue( ".dF.af.bf" ) , "4f1f2f" ) == 0  );
		assert( tstrcmp( config.findValue( ".dF.df.af" ) , "4f4f1f" ) == 0  );
		assert( tstrcmp( config.findValue( ".dF.df.bf" ) , "4f4f2f" ) == 0  );
}

int _tmain(int argc, _TCHAR* argv[])
{

	boost::shared_ptr< int > ptr;
	try {
		XERCES_CPP_NAMESPACE_QUALIFIER XMLPlatformUtils::Initialize();
	}
	catch (const XERCES_CPP_NAMESPACE_QUALIFIER XMLException& toCatch) {
		// Do your failure processing here
		return 1;
	}

	{
		BT_Configure_XML_Node config( cfg, sizeof( cfg ) );

		dumpConfig( config ," ");
		assertConfig_const( config );
		assertConfig( config );


	}
	// Do your actual work with Xerces-C++ here.
	XERCES_CPP_NAMESPACE_QUALIFIER XMLPlatformUtils::Terminate();
}