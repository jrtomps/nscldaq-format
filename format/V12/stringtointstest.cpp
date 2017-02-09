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
  CPPUNIT_TEST_SUITE_END();

private:

public:
  void setUp() {
  }
  void tearDown() {
  }
protected:
  // Tests for items without bodyheaders.
  
  void parse_0();
  
};

CPPUNIT_TEST_SUITE_REGISTRATION(StringsToIntegersTest);

// Basic construction test.
// Make a state change item, and ensure it's properly initialized.
//
void StringsToIntegersTest::parse_0() {
  auto ints = stringListToIntegers("PHYSICS_EVENT,BEGIN_RUN");
  ASSERTMSG("parse", std::vector<int>({PHYSICS_EVENT,BEGIN_RUN}) == ints);
}

