// Template for a test suite.

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/Asserter.h>
#include "Asserts.h"


#include <V11/CRingPhysicsEventCountItem.h>
#include <V11/CRingStateChangeItem.h>

#include <string.h>
#include <time.h>
#include <chrono>

using namespace DAQ::V11;

class physcounttests : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(physcounttests);
  CPPUNIT_TEST(simplecons);
  CPPUNIT_TEST(partialcons);
  CPPUNIT_TEST(fullcons);
  CPPUNIT_TEST(castcons);
  CPPUNIT_TEST(castcons_1);
  CPPUNIT_TEST(accessors);
  CPPUNIT_TEST(copycons);
  CPPUNIT_TEST(tscons);
  CPPUNIT_TEST(fractionalTime);
  CPPUNIT_TEST_SUITE_END();


private:

public:
  void setUp() {
  }
  void tearDown() {
  }
protected:
  void simplecons();
  void partialcons();
  void fullcons();
  void castcons();
  void castcons_1();
  void accessors();
  void copycons();
  void tscons();
  void fractionalTime();
};

CPPUNIT_TEST_SUITE_REGISTRATION(physcounttests);

// Test construction with default constructor.

void physcounttests::simplecons() {
  CRingPhysicsEventCountItem instance;

  EQ(PHYSICS_EVENT_COUNT, instance.type());
  EQ((uint32_t)0, instance.getTimeOffset());
  EQ((uint64_t)0, instance.getEventCount());
  
}
// Test construction given count and offset.

void physcounttests::partialcons()
{
  CRingPhysicsEventCountItem i(12345678, 100);
  EQ((uint64_t)12345678, i.getEventCount());
  EQ((uint32_t)100, i.getTimeOffset());

}

// Test full construction.
//
void physcounttests::fullcons()
{
  time_t t;
  time(&t);

  CRingPhysicsEventCountItem i(12345678, 100, t);

  EQ((uint64_t)12345678, i.getEventCount());
  EQ((uint32_t)100, i.getTimeOffset());
  EQ(t, i.getTimestamp());
}


// Construct from ring item.. good and bad.
//
void physcounttests::castcons()
{
    CRingItem            good(PHYSICS_EVENT_COUNT);
    CRingStateChangeItem bad;

    time_t now;
    time(&now);

    PhysicsEventCountItem body = {sizeof(PhysicsEventCountItem),
                                  PHYSICS_EVENT_COUNT,
                                  1234, static_cast<uint32_t>(now), 1234568};
    memcpy(good.getItemPointer(), &body, sizeof(body));
    uint8_t* p = reinterpret_cast<uint8_t*>(good.getBodyCursor());
    p          += sizeof(PhysicsEventCountItem) - sizeof(RingItemHeader);
    good.setBodyCursor(p);

    bool thrown(false);
    try {
        CRingPhysicsEventCountItem i(good);
    }
    catch(...) {
        thrown = true;
    }
    ASSERT(!thrown);

    // Bad construction should throw a bad cast:

    bool rightexception(false);
    thrown = false;
    try {
        CRingPhysicsEventCountItem i(bad);
    }
    catch (std::bad_cast c) {
        thrown = true;
        rightexception = true;
    }
    catch(...) {
        thrown = true;
        rightexception = false;
    }
    ASSERT(thrown);
    ASSERT(rightexception);
}

void physcounttests::castcons_1()
{
    using namespace std::chrono;
    // good constructor should cause identical body layout

    auto time_now = system_clock::to_time_t( system_clock::now() );

    CRingPhysicsEventCountItem orig(123, 345, time_now);
    CRingItem base(orig);
    CRingPhysicsEventCountItem item = base;

    EQ( uint64_t(123), item.getEventCount());
    EQ( uint32_t(345), item.getTimeOffset());
    EQ( uint32_t(1), item.getTimeDivisor());
    EQ( time_now, item.getTimestamp());

}

// Test write accessors (reads have already been tested.
//

void physcounttests::accessors()
{
  CRingPhysicsEventCountItem i(0,0,0);

  i.setTimeOffset(1234);
  time_t now = time(NULL);
  i.setTimestamp(now);
  i.setEventCount(12345678);

  EQ((uint32_t)1234, i.getTimeOffset());
  EQ(now, i.getTimestamp());
  EQ((uint64_t)12345678, i.getEventCount());
}
// Test copy construction

void physcounttests::copycons()
{
  CRingPhysicsEventCountItem original(1234, 10, 5678);
  CRingPhysicsEventCountItem copy(original);

  EQ(original.getBodySize(), copy.getBodySize());
  _RingItem* porig = original.getItemPointer();
  _RingItem* pcopy = copy.getItemPointer();

  // headers must match 

  EQ(porig->s_header.s_size, pcopy->s_header.s_size);
  EQ(porig->s_header.s_type, pcopy->s_header.s_type);

  // Contents must match:

  EQ(original.getTimeOffset(),    copy.getTimeOffset());
  EQ(original.getTimestamp(),     copy.getTimestamp());
  EQ(original.getEventCount(),    copy.getEventCount());
}
// test construction with timestamps>

void
physcounttests::tscons()
{
  time_t stamp = time(NULL);
  CRingPhysicsEventCountItem item(
      static_cast<uint64_t>(0x112233445567788ll), 1, 2, 
      static_cast<uint64_t>(54321), 100, stamp, 1 
  );

  pPhysicsEventCountItem pItem = 
    reinterpret_cast<pPhysicsEventCountItem>(item.getItemPointer());
  pBodyHeader pB = &(pItem->s_body.u_hasBodyHeader.s_bodyHeader);
  pPhysicsEventCountItemBody pBody = &(pItem->s_body.u_hasBodyHeader.s_body);

  // Check the header

  EQ(PHYSICS_EVENT_COUNT, pItem->s_header.s_type);
  EQ(
     static_cast<uint32_t>(
	sizeof(RingItemHeader) +  sizeof(BodyHeader) + sizeof(PhysicsEventCountItemBody)
     ), pItem->s_header.s_size
  );

  // check the body header.

  EQ(static_cast<uint32_t>(sizeof(BodyHeader)), pB->s_size);
  EQ(static_cast<uint64_t>(0x112233445567788ll), pB->s_timestamp);
  EQ(static_cast<uint32_t>(1), pB->s_sourceId);
  EQ(static_cast<uint32_t>(2), pB->s_barrier);

  // make sure getBodyPointer is correct.

  EQ(reinterpret_cast<void*>(pBody), item.getBodyPointer());

  // Make sure the body contents are correct.

  EQ(static_cast<uint32_t>(100), pBody->s_timeOffset);
  EQ(static_cast<uint32_t>(1),     pBody->s_offsetDivisor);
  EQ(static_cast<uint32_t>(stamp), pBody->s_timestamp);
  EQ(static_cast<uint64_t>(54321), pBody->s_eventCount);
}

// fractionalTime
//   Test of computeElapsedTime method.

void
physcounttests::fractionalTime()
{
  time_t stamp = time(NULL);
  CRingPhysicsEventCountItem item(
      static_cast<uint64_t>(0x112233445567788ll), 1, 2, 
      static_cast<uint64_t>(54321), 100, stamp, 3
  );
  
  EQ(static_cast<float>(100.0/3.0), item.computeElapsedTime());
}
