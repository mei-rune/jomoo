
#ifdef TEST
#ifndef TEST_MEMORY_H
#define TEST_MEMORY_H

#include "SystemPoolTest.H"
#include "FixedPoolTest.H"
#include "ObjectPoolTest.H"


void Test()
{
	_memory TestPool_T();
	_memory TestFixed_Pool_T();
	//_memory TestObjectPool();
	_memory TestFixedPool();
	_memory TestSystemPool();
	_memory TestFixedPool();
	_memory TestSystemPool();
}

#endif //SYSTEM_POOL_H
#endif //TEST