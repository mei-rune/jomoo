

#ifndef TimestampTest_INCLUDED
#define TimestampTest_INCLUDED


#include "CppUnit/TestCase.h"


class TimestampTest: public CppUnit::TestCase
{
public:
	TimestampTest(const std::string& name);
	~TimestampTest();

	void testTimestamp();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

private:
};


#endif // TimestampTest_INCLUDED
