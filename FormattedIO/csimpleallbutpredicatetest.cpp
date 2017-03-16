
// Template for a test suite.

#include <stdlib.h>

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/Asserter.h>
#include "Asserts.h"

#include "CSimpleAllButPredicate.h"
#include <CTestSourceSink.h>
#include <RingIOV12.h>

#include <V12/CRawRingItem.h>

using namespace DAQ;

extern std::string uniqueName(std::string base);

class CSimpleAllButPredicateTests : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(CSimpleAllButPredicateTests);
  CPPUNIT_TEST(noExclusions_0);
  CPPUNIT_TEST(oneExclusion_0);
  CPPUNIT_TEST_SUITE_END();


private:

public:
  void setUp() {
  }
  void tearDown() {
  }

  void setUpStream(CTestSourceSink& stream, const std::vector<uint32_t>& types) {

      V12::CRawRingItem item;

      for (auto type : types) {
          item.setType(type);
          writeItem(stream, item);
      }
  }

  void noExclusions_0() {
      CTestSourceSink stream;
      setUpStream(stream, {V12::BEGIN_RUN});

      CSimpleAllButPredicate pred;

      V12::CRawRingItem item;
      readItemIf(stream, item, pred);

      EQMSG("read the first item", V12::BEGIN_RUN, item.type());
  }


  void oneExclusion_0 () {
      CTestSourceSink stream;
      setUpStream(stream, {V12::BEGIN_RUN, V12::END_RUN});

      CSimpleAllButPredicate pred;
      pred.addExceptionType(V12::BEGIN_RUN);

      V12::CRawRingItem item;
      readItemIf(stream, item, pred);

      EQMSG("skipped exclusion", V12::END_RUN, item.type());
  }


};

CPPUNIT_TEST_SUITE_REGISTRATION(CSimpleAllButPredicateTests);

