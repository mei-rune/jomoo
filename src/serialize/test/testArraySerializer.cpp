
#include "../StdAfx.h"
#include "../../btnm_snmp.hpp"
#include "../Array_Accessor.H"
#include "../BT_Serialize_Stream.H"
#include "../../../BTNM_HostInfo/BTNM_HostInfo.h"

int main( int argc, char * argv[] )
{

	if( argc < 3 )
		return -1;
	char ipstr[ 100 ] = "";
	char comm[ 100 ] = "";

	strcpy( ipstr , argv[ 1 ] );
	strcpy( comm  , argv[ 2 ] );

	char *pProcess = ".1.3.6.1.2.1.25.4.2.1";
	char *pProcess_col = "1,2,4,5,6,7";


	char **ppvalue = NULL;
	char **ppindex = NULL;
	int32 R = 0, C = 0;

	HOST_PROCESS_TABLE hpis;

	int32 pid = 0;

	if ( getMIBTable((char*)ipstr, (char*)comm, pProcess, pProcess_col, &ppvalue, &ppindex, R, C) == BTNM_SUCCESS )
	{
		std::vector< int > v( 16,-1 );
		v[ 0 ] = 1;
		v[ 1 ] = 0;
		v[ 11 ] = 2;
		v[ 12 ] = 3;
		v[ 9 ] = 4;
		v[ 10 ] = 5;

		VArray_Reader_Accessor ar( ppvalue, R,C ,v );

		_bt_serialize BT_Input_Stream is( ar , _bt_serialize array_stream );
		is >> hpis;
	}

	for( HOST_PROCESS_TABLE::const_iterator it = hpis.begin();
		it != hpis.end(); it ++ )
		{
			std::cout << it->second.pid << "\t"
				<< it->second.name << "\t"
				<< it->second.path << "\t"
				<< it->second.parameters << "\t"
				<< it->second.type << "\t"
				<< it->second.status << std::endl;

		}
	FreeCharssBuffer(&ppvalue, R*C);
	FreeCharssBuffer(&ppindex, R);

	return 0;
}