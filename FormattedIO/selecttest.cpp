// Template for a test suite.

#include <stdlib.h>

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/Asserter.h>
#include "Asserts.h"

// dirt for testing:

#define private   public
#define protected public
#include "CRingSelectionPredicate.h"
#undef private
#undef protected

#include <V12/CRawRingItem.h>

using namespace std;
using namespace DAQ::V12;

extern std::string uniqueName(std::string base);


// We need a predicate that is concrete as we're testing an ABC.
// We'll also want it to expose some of the protected members.

class TestPred : public CRingSelectionPredicate
{
private:
  uint32_t  m_myType;
public:
  TestPred(uint32_t type) :
    m_myType(type) {}

  TestPred(uint32_t type, unsigned int nType ,uint32_t* types) :
    CRingSelectionPredicate(nType, types),
    m_myType(type) {}

  TestPred(uint32_t type, unsigned int ntype, uint32_t* types, bool* sample) :
    CRingSelectionPredicate(ntype, types, sample),
    m_myType(type) {}

  ~TestPred() {}

  virtual bool selectThis(uint32_t type) {
    return type!=m_myType;
  }

};

class selecttest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(selecttest);
  CPPUNIT_TEST(swap);
  CPPUNIT_TEST(construct);
  CPPUNIT_TEST(canonicals);
  CPPUNIT_TEST(addItem);
  CPPUNIT_TEST(eval);
  CPPUNIT_TEST_SUITE_END();


private:

public:
  void setUp() {
  }
  void tearDown() {
    try {
      CRingBuffer::remove(uniqueName("pred"));
    }
    catch(...) {}
  }
protected:
  void swap();
  void construct();
  void canonicals();
  void addItem();
  void eval();
};

CPPUNIT_TEST_SUITE_REGISTRATION(selecttest);

// Make sure byte swapping works:
void selecttest::swap() {
  TestPred pred(5);
  uint32_t result = pred.longswap(0x01020304);
  EQ((uint32_t)0x04030201, result);

}
// Try the various construction modes:

void selecttest::construct()
{
  TestPred  empty(5);
  EQ((size_t)0, empty.m_selections.size());

  // list of types should put the types in there and they all should
  // be unsampled:

  uint32_t types[5] = {1,2,3,4,5};
  TestPred listofTypes(5, 5, types);
  EQ((size_t)5, listofTypes.m_selections.size());
  for (uint32_t i=1; i <=5; i++) {
    EQ(i, listofTypes.m_selections[i].s_itemType);
    EQ(false, listofTypes.m_selections[i].s_sampled);
  }

  //  We should be able to specify sampling too:

  bool sampleflags[5]={true, false, true, false, true};
  TestPred listwithsamples(5, 5, types, sampleflags);
  EQ((size_t)5, listwithsamples.m_selections.size());
  bool correctState =  true;
  for (uint32_t i= 1; i <= 5; i++) {
    EQ(i, listwithsamples.m_selections[i].s_itemType);
    EQ(correctState, listwithsamples.m_selections[i].s_sampled);
    correctState = !correctState;
  }

}
// Test assignemnt, comparison.

void selecttest::canonicals()
{
  uint32_t types[5] = {1,2,3,4,5};
  bool     flags[5] = {true, false, true, false, true};
  TestPred list1(1,5,types,flags);
  TestPred other(1,5,types);

  ASSERT(list1 != other);
  other = list1;
  ASSERT(list1 == other);
}

// Test adding an item.
void selecttest::addItem()
{
  TestPred p(42);
  p.addSelectionItem(1234, true);
  EQ((size_t)1, p.m_selections.size());
  EQ((uint32_t)1234, p.m_selections[1234].s_itemType);
  EQ(true, p.m_selections[1234].s_sampled);
}

// Test the predicate evaluation (unsampled).
// There are three distinct cases which with the possibility of swapping
// comes down to 5 sub-tests
//  - The ring does not have a header's worth of data.
//    return true
//  - The header for the item in the ring is not the right type
//    skip the item, and return true (swap case too).
//  - The header for the item in the ring is the right type.
//    return false (swap case too).
//
void selecttest::eval()
{
  TestPred p(5);
  CRingBuffer::create(uniqueName("pred"));

  try {
    CRingBuffer prod(uniqueName("pred"), CRingBuffer::producer);
    CRingBuffer cons(uniqueName("pred"), CRingBuffer::consumer);
    
    // No header:

    bool result = p(cons);
    ASSERT(result);
    
    // Wrong header:

    CRawRingItem rawItem(BEGIN_RUN, 34, 56);

    array<char,20> header;
    serializeHeader(rawItem, header.begin());

    prod.put(header.data(), header.size());
    result = p(cons);
    ASSERT(result);
    EQ((size_t)0, cons.availableData());

    // Wrong header but byteswapped:

    std::fill(header.begin(), header.end(), 0);
    header[3] = 0x14;
    header[7] = 0x01;
    prod.put(header.data(), header.size());
    result = p(cons);
    ASSERT(result);
    EQ((size_t)0, cons.availableData());

    // Right type:

    rawItem.setType(5);
    serializeHeader(rawItem, header.begin());

    prod.put(header.data(), header.size());
    result = p(cons);
    ASSERT(!result);
    EQ(sizeof(header), cons.availableData());
    cons.skip(sizeof(header));

    // Byte swapped right type:


    std::fill(header.begin(), header.end(), 0);
    header[3] = 0x14;
    header[7] = 0x05;

    prod.put(&header, sizeof(header));
    result = p(cons);
    ASSERT(!result);
    EQ(sizeof(header), cons.availableData());
    cons.skip(sizeof(header));
    
  }
  catch(...) {
    CRingBuffer::remove(uniqueName("pred"));
    throw;
  }
  CRingBuffer::remove(uniqueName("pred"));
  
  
}
