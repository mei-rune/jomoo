

#ifndef TimespanTest_INCLUDED
#define TimespanTest_INCLUDED


#include "CppUnit/TestCase.h"


class TimespanTest: public CppUnit::TestCase
{
public:
	TimespanTest(const std::string& name);
	~TimespanTest();

	void testConversions();
	void testComparisons();
	void testArithmetics();
	void testSwap();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

private:
};


#endif // TimespanTest_INCLUDED
