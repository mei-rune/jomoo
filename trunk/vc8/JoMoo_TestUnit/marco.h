
#define CppUnit_addTest(suite, cls, mth) \
	suite->addTest(new CppUnit::TestCaller<cls>(#mth, &cls::mth))

//#define assert(condition) \
//	(this->assertImplementation((condition), (#condition), __LINE__, __FILE__))

#define loop_1_assert(data1line, condition)									 \
do { std::stringstream ss ;                                                  \
	  ss << "在第" << data1line << "行出错!";	                             \
      CPPUNIT_NS::Asserter::failIf( !(condition),                            \
                                  CPPUNIT_NS::Message( "assertion failed",   \
                                                       "Expression: "        \
                                                       #condition,           \
                                                       ss.str() ),           \
    CPPUNIT_SOURCELINE() ); }while( 0 )

#define loop_2_assert(data1line, data2line, condition)                       \
do { std::stringstream ss ;                                                  \
	  ss << "在第" << data1line << "行"<< "第"<< data2line << "列出错!";	 \
      CPPUNIT_NS::Asserter::failIf( !(condition),                            \
                                  CPPUNIT_NS::Message( "assertion failed",   \
                                                       "Expression: "        \
                                                       #condition,           \
                                                       ss.str() ),           \
    CPPUNIT_SOURCELINE() ); }while( 0 )
//
//#define assertEqualDelta(expected, actual, delta) \
//	(this->assertEquals((expected), (actual), (delta), __LINE__, __FILE__))
//
//#define assertEqual(expected, actual) \
//	(this->assertEquals((expected), (actual), __LINE__, __FILE__))
//
//#define assertNullPtr(ptr) \
//	(this->assertNull((ptr), #ptr, __LINE__, __FILE__))
//	
//#define assertNotNullPtr(ptr) \
//	(this->assertNotNull((ptr), #ptr, __LINE__, __FILE__))
//
//#define failmsg(msg) \
//	(this->fail(msg, __LINE__, __FILE__))