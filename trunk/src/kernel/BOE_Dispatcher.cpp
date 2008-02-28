// BOE

#include "BOE_Dispatcher.h"
#include "BOE_Concurrency.H"

int BOE_Dispatcher::putq( BOE_Protocol_Handler* ph )
{
	return BOE_Concurrency::get()->putq( ph );
}

int BOE_Dispatcher::getq( BOE_Protocol_Handler*& ph )
{
	return BOE_Concurrency::get()->getq( ph );
}
