// BOE

#include "BOE_Dispatcher.h"
#include "BOE_Concurrency.H"

_kernel_begin

int BOE_Dispatcher::putq( BOE_Protocol_Handler* ph )
{
	return 0;
//	return BOE_Concurrency::get()->putq( ph );
}

int BOE_Dispatcher::getq( BOE_Protocol_Handler*& ph )
{
	return 0;
	//return BOE_Concurrency::get()->getq( ph );
}

_kernel_end