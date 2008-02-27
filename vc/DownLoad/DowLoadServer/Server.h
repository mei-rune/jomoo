#pragma once
#include "BOE\IO\IO.h"


// CServer

class CDownLoadServer
{
public:
	CDownLoadServer( );
	int start( int argc, char* argv[] );
	void stop();
	void run();
private:

	_io BOE_Communicator_Ptr communicator_;
	bool stop_;
};


