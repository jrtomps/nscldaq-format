// Template for a test suite.

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/Asserter.h>
#include "Asserts.h"

#include <V11/DataFormat.h>

#define private public
#define protected public
#include <V11/CRingStateChangeItem.h>
#undef private
#undef protected

#include <string.h>
#include <time.h>
#include <stdexcept>

using namespace std;

using namespace DAQ::V11;

class teststate : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(teststate);
  CPPUNIT_TEST(basiccons);
  CPPUNIT_TEST(fullcons);
  CPPUNIT_TEST(castcons);
  CPPUNIT_TEST(accessors);
  CPPUNIT_TEST(copycons);
  CPPUNIT_TEST(tstampCons);
  CPPUNIT_TEST(tstampCopyCons);
  CPPUNIT_TEST(fractionalRunTime);
  CPPUNIT_TEST_SUITE_END();


private:

public:
  void setUp() {
  }
  void tearDown() {
  }
protected:
  // Tests for items without bodyheaders.
  
  void basiccons();
  void fullcons();
  void castcons();
  void accessors();
  void copycons();
 
  // Tests for items with a body header.
  
  void tstampCons();
  void tstampCopyCons();
  
  // Tests for fractional seconds in run offsets.
  
  void fractionalRunTime();
  
};

CPPUNIT_TEST_SUITE_REGISTRATION(teststate);

// Basic construction test.
// Make a state change item, and ensure it's properly initialized.
//
void teststate::basiccons() {
  CRingStateChangeItem item(END_RUN);
  pStateChangeItem pItem = reinterpret_cast<pStateChangeItem>(item.getItemPointer());
  EQ(END_RUN, item.type());
  EQ((uint32_t)0, pItem->s_body.u_noBodyHeader.s_body.s_runNumber);
  EQ((uint32_t)0, pItem->s_body.u_noBodyHeader.s_body.s_timeOffset);
  EQ((uint32_t)time(NULL), pItem->s_body.u_noBodyHeader.s_body.s_Timestamp);
  
}

//
// Do a full construction and test that out.
//
void teststate::fullcons()
{
  // One where the title fits just fine.

  CRingStateChangeItem item(PAUSE_RUN,
			    1234,
			    5678,
			    314159,
			    "This title fits");
  EQ(PAUSE_RUN, item.type());
  EQ((uint32_t)1234, item.getRunNumber());
  EQ((uint32_t)5678, item.getElapsedTime());
  EQ((time_t)(314159), item.getTimestamp());

  // The title does not fit in this one:

  string title("supercalifragalisticexpialidocious");
  while (title.size() <= V11_TITLE_MAXSIZE) {
    title += title;
  }
  

  bool threw(false);
  try {
    CRingStateChangeItem(RESUME_RUN,
			 1234, 5678, 314159,
			 title);
  }
  catch (std::out_of_range& except) {
    threw = true;
  }
  ASSERT(threw);
  
  
}
// Test construction that effectively up-casts a CRingItem.
//
void
teststate::castcons()
{
  // Successful requires that the underlying ring item have the
  // right type.

  bool threw(false);
  CRingStateChangeItem original(BEGIN_RUN, 0, 0, 0, "Testing");
  CRingItem ok(original);
  size_t okSize = original.getItemPointer()->s_header.s_size;
  
  CRingItem bad(PHYSICS_EVENT);

  try {
    CRingStateChangeItem state(ok);
    size_t itemSize = state.getBodySize() + sizeof(RingItemHeader) + sizeof(uint32_t);
    
    EQ(okSize, itemSize);
  }
  catch (bad_cast c) {
    threw = true;
  }
  ASSERT(!threw);



  threw = false;
  try {
    CRingStateChangeItem notstate(bad);
  } 
  catch (bad_cast c) {
    threw = true;
  }
  ASSERT(threw);
}


// Test the accessor functions.
void
teststate::accessors()
{
  CRingStateChangeItem empty(BEGIN_RUN);
  empty.setRunNumber(1234);
  EQ((uint32_t)1234, empty.getRunNumber());
  

  empty.setElapsedTime(45);
  EQ((uint32_t)45, empty.getElapsedTime());

  string title("this is my title");
  empty.setTitle(title);
  EQ(title, empty.getTitle());

  empty.setTimestamp(314159);
  EQ((time_t)(314159), empty.getTimestamp());

  empty.setOffsetDivisor(2345);
  EQ(uint32_t(2345),empty.getOffsetDivisor());
  
}
/**
 ** test copy construction.. need to wind up with the same sizes and contents as before.
 */
void teststate::copycons()
{
  std::string title("This is a test title");

  CRingStateChangeItem original(BEGIN_RUN,
				1234, 0, (time_t)(56789),
				title);
  CRingStateChangeItem copy(original); // Copy construction.

  EQ(original.getBodySize(), copy.getBodySize());
  _RingItem* porig = original.getItemPointer();
  _RingItem* pcopy = copy.getItemPointer();

  // headers must match 

  EQ(porig->s_header.s_size, pcopy->s_header.s_size);
  EQ(porig->s_header.s_type, pcopy->s_header.s_type);

  // Contents must match:

  EQ(original.getRunNumber(),   copy.getRunNumber());
  EQ(original.getElapsedTime(), copy.getElapsedTime());
  EQ(original.getTitle(),         copy.getTitle());
  EQ(original.getTimestamp(),   copy.getTimestamp());
  EQ(original.getOffsetDivisor(),   copy.getOffsetDivisor());
}
/*
  Test constructors of items with timestamps:
*/
void teststate::tstampCons()
{
    CRingStateChangeItem item(
        0x1234567890123456ll, 1, 0, BEGIN_RUN, 1234, 0, (time_t)666, "This is a test"
    );
    
    // Ensure there's a body header and tht we can get the bits and pieces from it.
    
    EQ(true, item.hasBodyHeader());
    EQ(static_cast<uint64_t>(0x1234567890123456ll), item.getEventTimestamp());
    EQ(static_cast<uint32_t>(1), item.getSourceId());
    EQ(static_cast<uint32_t>(0), item.getBarrierType());
    
    // Ensure we cfan still get the other goodies:
    
    EQ(BEGIN_RUN, item.type());
    EQ(static_cast<uint32_t>(1234), item.getRunNumber());
    EQ(static_cast<uint32_t>(0), item.getElapsedTime());
    EQ(std::string("This is a test"), item.getTitle());
    EQ(static_cast<time_t>(666), item.getTimestamp());
    
    // Check the legnth:
    
    uint32_t properLength = sizeof(RingItemHeader) + sizeof(BodyHeader) +
        sizeof(StateChangeItemBody);
}
/*
   Ensure copy constructors work for these items too:
*/
void
teststate::tstampCopyCons()
{
    CRingStateChangeItem orig(
        0x1234567890123456ll, 1, 0, BEGIN_RUN, 1234, 0, (time_t)666, "This is a test"
    );
    CRingStateChangeItem item(orig);
    
    // Ensure there's a body header and tht we can get the bits and pieces from it.
    
    EQ(true, item.hasBodyHeader());
    EQ(static_cast<uint64_t>(0x1234567890123456ll), item.getEventTimestamp());
    EQ(static_cast<uint32_t>(1), item.getSourceId());
    EQ(static_cast<uint32_t>(0), item.getBarrierType());
    
    // Ensure we cfan still get the other goodies:
    
    EQ(BEGIN_RUN, item.type());
    EQ(static_cast<uint32_t>(1234), item.getRunNumber());
    EQ(static_cast<uint32_t>(0), item.getElapsedTime());
    EQ(std::string("This is a test"), item.getTitle());
    EQ(static_cast<time_t>(666), item.getTimestamp());
    
    // Check the legnth:
    
    uint32_t properLength = sizeof(RingItemHeader) + sizeof(BodyHeader) +
        sizeof(StateChangeItemBody);
}
/*
  Ensure fractional run time offsets work.
*/
void
teststate::fractionalRunTime()
{
        CRingStateChangeItem orig(
        0x1234567890123456ll, 1, 0, END_RUN, 1234, 5, (time_t)666, "This is a test",
        2
    );
    float offset = orig.computeElapsedTime();
    EQ(static_cast<float>(5.0/2.0), offset);
}
