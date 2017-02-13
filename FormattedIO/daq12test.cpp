
/*
    This software is Copyright by the Board of Trustees of Michigan
    State University (c) Copyright 2015.

    You may use this software under the terms of the GNU public license
    (GPL).  The terms of this license are described at:

     http://www.gnu.org/licenses/gpl.txt

     Author:
             Jeromy Tompkins
         NSCL
         Michigan State University
         East Lansing, MI 48824-1321
*/


static const char* Copyright = "(C) Copyright Michigan State University 2014, All rights reserved";
#include <fstream>
#include <cppunit/extensions/HelperMacros.h>

#include <RingIOV12.h>
#include <V12/CRawRingItem.h>
#include <Deserializer2.h>

#ifdef NSCLDAQ_BUILD
#include <CTestSourceSink.h>
#endif

#include <cstdint>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;
using namespace DAQ;

// A test suite
class CFormattedIOV12Test : public CppUnit::TestFixture
{
    public:
    CFormattedIOV12Test();

    CPPUNIT_TEST_SUITE( CFormattedIOV12Test );
    CPPUNIT_TEST ( input_0 );
    CPPUNIT_TEST ( input_1 );
    CPPUNIT_TEST ( output_0 );
#ifdef NSCLDAQ_BUILD
    CPPUNIT_TEST ( sourceInput_0 );
    CPPUNIT_TEST ( sourceInput_1 );
    CPPUNIT_TEST ( sinkOutput_0 );
#endif
    CPPUNIT_TEST_SUITE_END();

    public:
    void setUp();
    void tearDown();

    void input_0();
    void input_1();
    void output_0();

#ifdef NSCLDAQ_BUILD
    void sourceInput_0();
    void sourceInput_1();
    void sinkOutput_0();
#endif

};


// Register it with the test factory
CPPUNIT_TEST_SUITE_REGISTRATION( CFormattedIOV12Test );

CFormattedIOV12Test::CFormattedIOV12Test()
{}


void CFormattedIOV12Test::setUp()
{}

void CFormattedIOV12Test::tearDown()
{}

void CFormattedIOV12Test::input_0()
{
  std::stringstream ss;
  // Load the source/sink with data
  const uint32_t data[] = {28, 30, 1, 0, 0, 2, 3};
  ss.write(reinterpret_cast<const char*>(data), sizeof(data));

  // extract a complete ring item
  V12::CRawRingItem item;
  ss >> item;

  CPPUNIT_ASSERT_EQUAL_MESSAGE("Size after extraction should be correct",
                               uint32_t(28), item.size());

  CPPUNIT_ASSERT_EQUAL_MESSAGE("Extracted type should be correct",
                               uint32_t(30), item.type());

  CPPUNIT_ASSERT_EQUAL_MESSAGE("Extracted evt tstamp should be correct",
                               uint64_t(1), item.getEventTimestamp());

  CPPUNIT_ASSERT_EQUAL_MESSAGE("Extracted source id should be correct",
                               uint32_t(0), item.getSourceId());

  auto body = item.getBody();

  CPPUNIT_ASSERT_MESSAGE("Body of extracted should be correct",
                          equal(body.begin(), body.end(), reinterpret_cast<const unsigned char*>(data+5)));
}

void CFormattedIOV12Test::input_1()
{
  std::stringstream ss;
  // Load the source/sink with data
  const uint32_t data[] = {36, 30, 20, 1, 0, 2, 3, 0, 0};
  ss.write(reinterpret_cast<const char*>(data), sizeof(data));

  // extract a complete ring item
  V12::CRawRingItem item;
  ss >> item;

  CPPUNIT_ASSERT_EQUAL_MESSAGE("Size after extraction should be correct",
                               uint32_t(36), item.size());

  CPPUNIT_ASSERT_EQUAL_MESSAGE("Extracted type should be correct",
                               uint32_t(30), item.type());

  CPPUNIT_ASSERT_EQUAL_MESSAGE("Extracted evt tstamp should be correct",
                               uint64_t(0x0100000014), item.getEventTimestamp());

  CPPUNIT_ASSERT_EQUAL_MESSAGE("Extracted source id should be correct",
                               uint32_t(0), item.getSourceId());


  auto body = item.getBody();

  CPPUNIT_ASSERT_MESSAGE("Body of extracted should be correct",
                          equal(body.begin(), body.end(), reinterpret_cast<const unsigned char*>(data+5)));

  CPPUNIT_ASSERT_EQUAL_MESSAGE("Body size should be correct",
                               uint32_t(16), item.getBodySize());
}

void CFormattedIOV12Test::output_0()
{
  std::stringstream sink;
  Buffer::ByteBuffer payload = {0, 1, 2, 3, 4, 5, 6};
  V12::CRawRingItem item(V12::PHYSICS_EVENT, 100, 2, payload);

  sink << item;

  std::string record = sink.str();

  Buffer::RangeDeserializer<std::string::iterator> recStream(record.begin(), record.end());
  uint32_t size, type, id;
  uint64_t tstamp;
  recStream >> size >> type >> tstamp >> id;

  CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of bytes written are correct",
                               size_t(item.size()), record.size());
  CPPUNIT_ASSERT_EQUAL_MESSAGE("size", item.size(), size);
  CPPUNIT_ASSERT_EQUAL_MESSAGE("type", V12::PHYSICS_EVENT, type);
  CPPUNIT_ASSERT_EQUAL_MESSAGE("source id", uint32_t(2), id);
  CPPUNIT_ASSERT_EQUAL_MESSAGE("evt tstamp", uint64_t(100), tstamp);

  CPPUNIT_ASSERT_MESSAGE("What was written actually was written",
                          equal(recStream.pos(), recStream.end(), payload.begin()));


}

#ifdef NSCLDAQ_BUILD

void CFormattedIOV12Test::sourceInput_0()
{
  CTestSourceSink ss(128);
  // Load the source/sink with data
  const uint32_t data[] = {28, 30, 1, 0, 0, 2, 3};
  ss.put(data, sizeof(data));


  // extract a complete ring item
  V12::CRawRingItem item;
  ss >> item;

  CPPUNIT_ASSERT_EQUAL_MESSAGE("Size after extraction should be correct",
                               uint32_t(28), item.size());

  CPPUNIT_ASSERT_EQUAL_MESSAGE("Extracted type should be correct",
                               uint32_t(30), item.type());

  CPPUNIT_ASSERT_EQUAL_MESSAGE("Extracted evt tstamp should be correct",
                               uint64_t(1), item.getEventTimestamp());

  CPPUNIT_ASSERT_EQUAL_MESSAGE("Extracted source id should be correct",
                               uint32_t(0), item.getSourceId());

  auto body = item.getBody();

  CPPUNIT_ASSERT_MESSAGE("Body of extracted should be correct",
                          equal(body.begin(), body.end(), reinterpret_cast<const unsigned char*>(data+5)));

}

void CFormattedIOV12Test::sourceInput_1()
{
  CTestSourceSink ss(128);
  // Load the source/sink with data (i.e item with body header)
  const uint32_t data[] = {36, 30, 20, 1, 0, 2, 3, 0, 0};
  ss.put(data, sizeof(data));

  // extract a complete ring item
  V12::CRawRingItem item;
  ss >> item;

  CPPUNIT_ASSERT_EQUAL_MESSAGE("Size after extraction should be correct",
                               uint32_t(36), item.size());

  CPPUNIT_ASSERT_EQUAL_MESSAGE("Extracted type should be correct",
                               uint32_t(30), item.type());

  CPPUNIT_ASSERT_EQUAL_MESSAGE("Extracted evt tstamp should be correct",
                               uint64_t(0x0100000014), item.getEventTimestamp());

  CPPUNIT_ASSERT_EQUAL_MESSAGE("Extracted source id should be correct",
                               uint32_t(0), item.getSourceId());


  auto body = item.getBody();

  CPPUNIT_ASSERT_MESSAGE("Body of extracted should be correct",
                          equal(body.begin(), body.end(), reinterpret_cast<const unsigned char*>(data+5)));

  CPPUNIT_ASSERT_EQUAL_MESSAGE("Body size should be correct",
                               uint32_t(16), item.getBodySize());

}

void CFormattedIOV12Test::sinkOutput_0()
{
  CTestSourceSink sink(128);
  Buffer::ByteBuffer payload = {0, 1, 2, 3, 4, 5, 6};
  V12::CRawRingItem item(V12::PHYSICS_EVENT, 100, 2, payload);

  sink << item;

  auto record = sink.getBuffer();

  auto recStream = Buffer::makeRangeDeserializer(record.begin(), record.end(), false);
  uint32_t size, type, id;
  uint64_t tstamp;
  recStream >> size >> type >> tstamp >> id;

  CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of bytes written are correct",
                               size_t(item.size()), record.size());
  CPPUNIT_ASSERT_EQUAL_MESSAGE("size", item.size(), size);
  CPPUNIT_ASSERT_EQUAL_MESSAGE("type", V12::PHYSICS_EVENT, type);
  CPPUNIT_ASSERT_EQUAL_MESSAGE("source id", uint32_t(2), id);
  CPPUNIT_ASSERT_EQUAL_MESSAGE("evt tstamp", uint64_t(100), tstamp);

  CPPUNIT_ASSERT_MESSAGE("What was written actually was written",
                          equal(recStream.pos(), recStream.end(), payload.begin()));




}
#endif
