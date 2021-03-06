// Template for a test suite.

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/Asserter.h>
#include <string>
#include "Asserts.h"

#include "V12/DataFormat.h"
#include "V12/CCompositeRingItem.h"
#include "V12/CRawRingItem.h"
#include "V12/CRingStateChangeItem.h"
#include "V12/CPhysicsEventItem.h"
#include "V12/CRingPhysicsEventCountItem.h"
#include "ContainerDeserializer.h"

#include <iostream>
#include <sstream>

// Tests for glom parameter ring item class:

using namespace DAQ;
using namespace DAQ::V12;

class CCompositeRingItemTests : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(CCompositeRingItemTests);
    CPPUNIT_TEST(constructor_0);
    CPPUNIT_TEST(size_0);
    CPPUNIT_TEST(size_1);
    CPPUNIT_TEST(appendChild_0);
    CPPUNIT_TEST(toRawRingItem_0);
    CPPUNIT_TEST(toRawRingItem_1);
    CPPUNIT_TEST(toString_0);
    CPPUNIT_TEST(toString_1);
    CPPUNIT_TEST(toString_2);
    CPPUNIT_TEST(typeName_0);
    CPPUNIT_TEST(comparison_0);
    CPPUNIT_TEST(comparison_1);
    CPPUNIT_TEST(comparison_2);
    CPPUNIT_TEST(comparison_3);
    CPPUNIT_TEST(comparison_4);
    CPPUNIT_TEST(comparison_5);
    CPPUNIT_TEST(fromRawRingItem_0);
    CPPUNIT_TEST(fromRawRingItem_1);
    CPPUNIT_TEST(fromRawRingItem_2);
    CPPUNIT_TEST(consistency_0);
    CPPUNIT_TEST(setType_0);
    CPPUNIT_TEST(access_0);
    CPPUNIT_TEST(at_0);
    CPPUNIT_TEST(at_1);
    CPPUNIT_TEST_SUITE_END();
private:

public:
  void setUp() {
  }
  void tearDown() {
  }
protected:

  void constructor_0() {
      CPPUNIT_ASSERT_THROW_MESSAGE("type must have composite bit set",
                                   CCompositeRingItem item(UNDEFINED, 0, 0, {}),
                                   std::invalid_argument);
  }

  void size_0() {
      CCompositeRingItem item;
      EQMSG("empty size", uint32_t(20), item.size());
  }

  void size_1() {
      CCompositeRingItem item;
      item.appendChild(CRingItemPtr(new CPhysicsEventItem(23, 34, {2,3,4,5})));

      EQMSG("size", uint32_t(44), item.size());
  }


  void appendChild_0() {
      CCompositeRingItem item;
      item.appendChild(CRingItemPtr(new CRingStateChangeItem(BEGIN_RUN)));

      EQMSG("n children", size_t(1), item.getChildren().size());
  }

  void toRawRingItem_0() {
      CCompositeRingItem item(COMP_BEGIN_RUN, 12,23);
      CRawRingItem raw;

      item.toRawRingItem(raw);

      EQMSG("size", item.size(), raw.size());
      EQMSG("type", item.type() | 0x8000, raw.type());
      EQMSG("evt timestamp", item.getEventTimestamp(), raw.getEventTimestamp());
      EQMSG("source id", item.getSourceId(), raw.getSourceId());
      EQMSG("composite", true, raw.isComposite());
  }

  void toRawRingItem_1() {
      CCompositeRingItem item(COMP_BEGIN_RUN, 12,34);
      CRingItemPtr pChild(new CRingStateChangeItem(BEGIN_RUN, 2, 3, 4, "testing"));
      item.appendChild(pChild);
      CRawRingItem raw;

      item.toRawRingItem(raw);

      EQMSG("size", uint32_t(20) + pChild->size(), raw.size());
      EQMSG("type", item.type() | 0x8000, raw.type());
      EQMSG("evt timestamp", item.getEventTimestamp(), raw.getEventTimestamp());
      EQMSG("source id", item.getSourceId(), raw.getSourceId());
      EQMSG("composite", true, raw.isComposite());
  }

  void toString_0() {
      CCompositeRingItem item(COMP_BEGIN_RUN, 12, 23);
      std::stringstream asString;
      asString << "Composite Item" << std::endl;
      asString << "Size (bytes) : 20" << std::endl;
      asString << "Type         : Composite Begin Run" << std::endl;
      asString << "Timestamp    : 12" << std::endl;
      asString << "Source Id    : 23" << std::endl;
      asString << "# subitems   : 0" << std::endl;

      EQMSG("empty compound item", asString.str(), item.toString());

  }

  void toString_1() {
      CCompositeRingItem item(COMP_BEGIN_RUN, 12, 23);
      CRingItemPtr pChild(new CRingStateChangeItem(34, 12, BEGIN_RUN, 3452,
                                                     0, 1485797295, "Testing"));
      item.appendChild(pChild);
      std::stringstream asString;
      asString << "Composite Item" << std::endl;
      asString << "Size (bytes) : 67" << std::endl;
      asString << "Type         : Composite Begin Run" << std::endl;
      asString << "Timestamp    : 12" << std::endl;
      asString << "Source Id    : 23" << std::endl;
      asString << "# subitems   : 1" << std::endl;
      asString << "+-- Subitem #0" << std::endl;
      asString << "    Size (bytes) : 47" << std::endl;
      asString << "    Type         : Begin Run" << std::endl;
      asString << "    Timestamp    : 34" << std::endl;
      asString << "    Source Id    : 12" << std::endl;
      asString << "    Run Number   : 3452" << std::endl;
      asString << "    Unix Tstamp  : Mon Jan 30 12:28:15 2017" << std::endl;
      asString << "    Elapsed Time : 0.0 seconds" << std::endl;
      asString << "    Title        : Testing" << std::endl;

      EQMSG("empty Composite item", asString.str(), item.toString());
  }

  void toString_2() {
      CCompositeRingItem item(COMP_PHYSICS_EVENT, 12, 23);
      std::shared_ptr<CCompositeRingItem> pChild(new CCompositeRingItem(COMP_PHYSICS_EVENT, 12, 23));
      pChild->appendChild(CRingItemPtr(new CPhysicsEventItem(12, 23, {1, 2})));
      item.appendChild(pChild);
      item.appendChild(CRingItemPtr(new CPhysicsEventItem(12, 23, {1, 2})));

      std::stringstream asString;
      asString << "Composite Item" << std::endl;
      asString << "Size (bytes) : 84" << std::endl;
      asString << "Type         : Composite Event" << std::endl;
      asString << "Timestamp    : 12" << std::endl;
      asString << "Source Id    : 23" << std::endl;
      asString << "# subitems   : 2" << std::endl;
      asString << "+-- Subitem #0" << std::endl;
      asString << "    Composite Item" << std::endl;
      asString << "    Size (bytes) : 42" << std::endl;
      asString << "    Type         : Composite Event" << std::endl;
      asString << "    Timestamp    : 12" << std::endl;
      asString << "    Source Id    : 23" << std::endl;
      asString << "    # subitems   : 1" << std::endl;
      asString << "    +-- Subitem #0" << std::endl;
      asString << "        Size (bytes) : 22" << std::endl;
      asString << "        Type         : Event" << std::endl;
      asString << "        Timestamp    : 12" << std::endl;
      asString << "        Source Id    : 23" << std::endl;
      asString << "        0201 " << std::endl;
      asString << "+-- Subitem #1" << std::endl;
      asString << "    Size (bytes) : 22" << std::endl;
      asString << "    Type         : Event" << std::endl;
      asString << "    Timestamp    : 12" << std::endl;
      asString << "    Source Id    : 23" << std::endl;
      asString << "    0201 " << std::endl;

      EQMSG("empty Composite item", asString.str(), item.toString());
  }


  void typeName_0() {

      CCompositeRingItem item(COMP_PHYSICS_EVENT, 12, 34);

      EQMSG("typename", std::string("Composite Event"), item.typeName());
  }


  void comparison_0() {
    CCompositeRingItem item(COMP_PHYSICS_EVENT, 12, 34);
    item.appendChild(CRingItemPtr(new CPhysicsEventItem(22, 33)));

    CPPUNIT_ASSERT_MESSAGE("identity comparison",  item == item);
  }

  void comparison_1() {
    CCompositeRingItem item1(COMP_PHYSICS_EVENT, 12, 34);
    item1.appendChild(CRingItemPtr(new CPhysicsEventItem(22, 33)));

    CCompositeRingItem item2(COMP_PHYSICS_EVENT_COUNT, 12, 34);
    item2.appendChild(CRingItemPtr(new CRingPhysicsEventCountItem(22, 33)));

    CPPUNIT_ASSERT_MESSAGE("different types",  item1 != item2);
  }

  void comparison_2() {
    CCompositeRingItem item1(COMP_PHYSICS_EVENT, 12, 34);
    item1.appendChild(CRingItemPtr(new CPhysicsEventItem(22, 33)));

    CCompositeRingItem item2(COMP_PHYSICS_EVENT, 22, 34);
    item2.appendChild(CRingItemPtr(new CPhysicsEventItem(22, 33)));

    CPPUNIT_ASSERT_MESSAGE("different evt timestamp",  item1 != item2);
  }

  void comparison_3() {
    CCompositeRingItem item1(COMP_PHYSICS_EVENT, 12, 34);
    item1.appendChild(CRingItemPtr(new CPhysicsEventItem(22, 33)));

    CCompositeRingItem item2(COMP_PHYSICS_EVENT, 12, 44);
    item2.appendChild(CRingItemPtr(new CPhysicsEventItem(22, 33)));

    CPPUNIT_ASSERT_MESSAGE("different source id",  item1 != item2);
  }

  void comparison_4() {
    CCompositeRingItem item1(COMP_PHYSICS_EVENT, 12, 34);
    item1.appendChild(CRingItemPtr(new CPhysicsEventItem(22, 33)));

    CCompositeRingItem item2(COMP_PHYSICS_EVENT, 12, 34);

    CPPUNIT_ASSERT_MESSAGE("different number of children",  item1 != item2);
  }

  void comparison_5() {
    CCompositeRingItem item1(COMP_PHYSICS_EVENT, 12, 34);
    item1.appendChild(CRingItemPtr(new CPhysicsEventItem(22, 33)));

    CCompositeRingItem item2(COMP_PHYSICS_EVENT, 12, 34);
    item2.appendChild(CRingItemPtr(new CPhysicsEventItem(23, 33)));

    CPPUNIT_ASSERT_MESSAGE("different children",  item1 != item2);
  }


  void fromRawRingItem_0() {
    CRawRingItem rawItem(COMP_PHYSICS_EVENT, 12, 23);
    auto& body = rawItem.getBody();
    body << uint32_t(21) << PHYSICS_EVENT << uint64_t(12) << uint32_t(23);
    body << uint8_t(1);

    CCompositeRingItem item(rawItem);
    EQMSG("size", uint32_t(41), item.size());
    EQMSG("type", COMP_PHYSICS_EVENT, item.type());
    EQMSG("tstamp", uint64_t(12), item.getEventTimestamp());
    EQMSG("source id", uint32_t(23), item.getSourceId());
    EQMSG("n children", size_t(1), item.getChildren().size());
    EQMSG("child size", uint32_t(21), item.getChildren()[0]->size());
    EQMSG("child type", PHYSICS_EVENT, item.getChildren()[0]->type());
    EQMSG("child evt tstamp", uint64_t(12), item.getChildren()[0]->getEventTimestamp());
    EQMSG("child source id", uint32_t(23), item.getChildren()[0]->getSourceId());

    auto& physEvent = dynamic_cast<CPhysicsEventItem&>(*item.getChildren()[0]);
    CPPUNIT_ASSERT_MESSAGE("child body", Buffer::ByteBuffer({1}) == physEvent.getBody());
  }



  void fromRawRingItem_1() {
      CRawRingItem rawItem(COMP_PHYSICS_EVENT, 12, 23);
      auto& body = rawItem.getBody();
      body << uint32_t(41) << COMP_PHYSICS_EVENT << uint64_t(12) << uint32_t(23);
      body << uint32_t(21) << PHYSICS_EVENT << uint64_t(12) << uint32_t(23);
      body << uint8_t(1);
      body << uint32_t(22) << PHYSICS_EVENT << uint64_t(21) << uint32_t(32);
      body << uint8_t(1) << uint8_t(2);

      CCompositeRingItem item(rawItem);
      EQMSG("size", uint32_t(83), item.size());
      EQMSG("type", COMP_PHYSICS_EVENT, item.type());
      EQMSG("tstamp", uint64_t(12), item.getEventTimestamp());
      EQMSG("source id", uint32_t(23), item.getSourceId());
      EQMSG("n children", size_t(2), item.getChildren().size());

      CPPUNIT_ASSERT_NO_THROW(dynamic_cast<CCompositeRingItem&>(*item.getChildren()[0]));
      CPPUNIT_ASSERT_NO_THROW(dynamic_cast<CPhysicsEventItem&>(*item.getChildren()[1]));


      auto& Composite = dynamic_cast<CCompositeRingItem&>(*item.getChildren()[0]);
      EQMSG("nchildren of subitem", size_t(1), Composite.getChildren().size());
      CPPUNIT_ASSERT_NO_THROW(dynamic_cast<CPhysicsEventItem&>(*Composite.getChildren()[0]));

      auto pItem = Composite.getChildren()[0];
      EQMSG("size of child", uint32_t(21), pItem->size());
  }

  void fromRawRingItem_2() {
      CRawRingItem rawItem(COMP_PHYSICS_EVENT, 12, 23);
      auto& body = rawItem.getBody();
      body << uint32_t(20) << COMP_PHYSICS_EVENT << uint64_t(12) << uint32_t(23);

      CPPUNIT_ASSERT_NO_THROW_MESSAGE("leaf items cannot be composite items",
                                        CCompositeRingItem item(rawItem));

      CCompositeRingItem item(rawItem);
      auto& child = dynamic_cast<CCompositeRingItem&>(*item.getChildren().at(0));
      EQMSG("empty composite", size_t(0), child.getChildren().size());
  }

  void fromSwappedRawRingItem_2() {

      Buffer::ByteBuffer body;
      body << uint32_t(0x29000000) << uint32_t(0x1e800000) << uint64_t(0x0c00000000000000)
           << uint32_t(0x17000000);
      body << uint32_t(0x15000000) << uint32_t(0x1e000000) << uint64_t(0x0c00000000000000)
           << uint32_t(0x17000000);
      body << uint8_t(1);

      CRawRingItem rawItem(body);
    CCompositeRingItem item(rawItem);
    EQMSG("size", uint32_t(41), item.size());
    EQMSG("type", COMP_PHYSICS_EVENT, item.type());
    EQMSG("tstamp", uint64_t(12), item.getEventTimestamp());
    EQMSG("source id", uint32_t(23), item.getSourceId());
    EQMSG("n children", size_t(1), item.getChildren().size());
    EQMSG("child size", uint32_t(21), item.getChildren()[0]->size());
    EQMSG("child type", PHYSICS_EVENT, item.getChildren()[0]->type());
    EQMSG("child evt tstamp", uint64_t(12), item.getChildren()[0]->getEventTimestamp());
    EQMSG("child source id", uint32_t(23), item.getChildren()[0]->getSourceId());

    auto& physEvent = dynamic_cast<CPhysicsEventItem&>(*item.getChildren()[0]);
    CPPUNIT_ASSERT_MESSAGE("child body", Buffer::ByteBuffer({1}) == physEvent.getBody());
  }


  void consistency_0() {
      CRawRingItem rawItem(COMP_PHYSICS_EVENT, 12, 23);
      auto& body = rawItem.getBody();
      body << uint32_t(41) << COMP_PHYSICS_EVENT << uint64_t(12) << uint32_t(23);
      body << uint32_t(21) << PHYSICS_EVENT << uint64_t(12) << uint32_t(23);
      body << uint8_t(1);
      body << uint32_t(24) << RING_FORMAT << uint64_t(21) << uint32_t(32);
      body << uint16_t(1) << uint16_t(2);

      CPPUNIT_ASSERT_THROW_MESSAGE("inconsistent data types should fail",
                                   CCompositeRingItem item(rawItem),
                                   std::runtime_error);
  }


  void setType_0() {
      CCompositeRingItem item;
      CPPUNIT_ASSERT_THROW_MESSAGE("type must have composite bit set",
                                   item.setType(UNDEFINED),
                                   std::invalid_argument);
  }

  void access_0() {
      CCompositeRingItem item(COMP_PHYSICS_EVENT, 22, 33);

      CRingItemPtr ptr0(new CPhysicsEventItem(22, 33));

      // another way to make a shared ptr
      auto ptr1 = std::make_shared<CPhysicsEventItem>(22, 33);

      // append children
      item.appendChild(ptr0);
      item.appendChild(ptr1);

      ASSERTMSG("array indexing returns correct value for first element",
                ptr0 == item[0]);
      ASSERTMSG("array indexing returns correct value for second element",
                ptr1 == item[1]);

  }


  void at_0() {
      CCompositeRingItem item(COMP_PHYSICS_EVENT, 22, 33);

      CRingItemPtr ptr0(new CPhysicsEventItem(22, 33));

      // another way to make a shared ptr
      auto ptr1 = std::make_shared<CPhysicsEventItem>(22, 33);

      // append children
      item.appendChild(ptr0);
      item.appendChild(ptr1);

      ASSERTMSG("at(0) returns correct value for first element",
                ptr0 == item.at(0));
      ASSERTMSG("at(1) returns correct value for second element",
                ptr1 == item.at(1));

  }

  void at_1() {
      CCompositeRingItem item(COMP_PHYSICS_EVENT, 22, 33);

      CPPUNIT_ASSERT_THROW_MESSAGE("at() throws out of range error if necessary",
                                   item.at(0),
                                   std::out_of_range);

  }

};

CPPUNIT_TEST_SUITE_REGISTRATION(CCompositeRingItemTests);

// Test parameters if not building:

