// Template for a test suite.

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/Asserter.h>
#include "Asserts.h"

#include <V12/DataFormat.h>
#include <V12/StringsToIntegers.h>

#include <string>

using namespace std;

using namespace DAQ::V12;

class StringsToIntegersTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(StringsToIntegersTest);
  CPPUNIT_TEST(parse_0);
  CPPUNIT_TEST(parse_1);
  CPPUNIT_TEST(parse_2);
  CPPUNIT_TEST(parse_4);
  CPPUNIT_TEST(parse_5);
  CPPUNIT_TEST_SUITE_END();

private:

public:
  void setUp() {
  }
  void tearDown() {
  }
protected:
  


  void parse_0() {
    auto ints = stringListToIntegers("PHYSICS_EVENT,BEGIN_RUN");
    CPPUNIT_ASSERT_MESSAGE("parse", std::vector<int>({PHYSICS_EVENT,BEGIN_RUN}) == ints);
  }

  void parse_1() {
    // spaces are NOT tolerated
    CPPUNIT_ASSERT_THROW_MESSAGE("parsing spaces causes failures",
                                 stringListToIntegers("COMP_PHYSICS_EVENT, MONITORED_VARIABLES"),
                                 std::invalid_argument);
  }

  void parse_2() {
    
    CPPUNIT_ASSERT_THROW_MESSAGE("failure occurs when non-type encountered", 
                    stringListToIntegers("NOT_A_TYPE, COMP_PHYSICS_EVENT, BEGIN_RUN"),
                    std::invalid_argument);
  }

  void parse_4() {
    // integer arguments ARE supported
    CPPUNIT_ASSERT_NO_THROW_MESSAGE("integers are supported",
                    stringListToIntegers("1,2"));
  }

  void parse_5() {
    auto ints = stringListToIntegers("1,2,3,30");
    CPPUNIT_ASSERT_MESSAGE("parse", std::vector<int>({1,2,3,30}) == ints);
  }

};

CPPUNIT_TEST_SUITE_REGISTRATION(StringsToIntegersTest);
