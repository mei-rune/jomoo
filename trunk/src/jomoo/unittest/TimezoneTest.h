

#ifndef TimezoneTest_INCLUDED
#define TimezoneTest_INCLUDED


#include "CppUnit/TestCase.h"


class TimezoneTest: public CppUnit::TestCase
{
public:
	TimezoneTest();
	~TimezoneTest();

	void testTimezone();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

private:
};


#endif // TimezoneTest_INCLUDED
