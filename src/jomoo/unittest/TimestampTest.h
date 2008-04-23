

#ifndef TimestampTest_INCLUDED
#define TimestampTest_INCLUDED


#include "CppUnit/TestCase.h"


class TimestampTest: public CppUnit::TestCase
{
public:
	TimestampTest();
	~TimestampTest();

	void testTimestamp();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

private:
};


#endif // TimestampTest_INCLUDED
