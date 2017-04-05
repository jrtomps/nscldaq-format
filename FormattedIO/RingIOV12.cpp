#include "RingIOV12.h"
/*
    This software is Copyright by the Board of Trustees of Michigan
    State University (c) Copyright 2015

    You may use this software under the terms of the GNU public license
    (GPL).  The terms of this license are described at:

     http://www.gnu.org/licenses/gpl.txt

     Author:
             Jeromy Tompkins
             NSCL
             Michigan State University
             East Lansing, MI 48824-1321
*/

#include <V12/CRawRingItem.h>
#include <V12/CRingItemParser.h>
#include <byte_cast.h>
#include <ByteBuffer.h>

#include <V12/DataFormat.h>

#include <iostream>
#include <algorithm>
#include <stdexcept>

std::ostream& operator<<(std::ostream& stream,
                         const DAQ::V12::CRawRingItem& item)
{
  std::array<char,20> header;

  DAQ::V12::serializeHeader(item, header.begin());

  stream.write(header.data(), header.size());
  stream.write(reinterpret_cast<const char*>(item.getBody().data()), item.getBody().size());

  return stream;
}



std::istream& operator>>(std::istream& stream,
                         DAQ::V12::CRawRingItem& item)
{
    std::array<char,20> header;
    stream.read(header.data(), header.size());

    uint32_t size, type, sourceId;
    uint64_t tstamp;
    bool swapNeeded;
    DAQ::V12::Parser::parseHeader(header.begin(), header.end(),
                                  size, type, tstamp, sourceId, swapNeeded);

    item.setType(type);
    item.setEventTimestamp(tstamp);
    item.setSourceId(sourceId);

    item.setMustSwap(swapNeeded);

    item.getBody().resize(size-header.size());
    stream.read(reinterpret_cast<char*>(item.getBody().data()), size-header.size());

    return stream;
}



#ifdef NSCLDAQ_BUILD

#include <CDataSource.h>
#include <CDataSink.h>
#include <thread>
#include <chrono>

DAQ::CDataSink& operator<<(DAQ::CDataSink& sink,
                      const DAQ::V12::CRawRingItem& item)
{
    DAQ::writeItem(sink, item);
    return sink;
}


DAQ::CDataSource& operator>>(DAQ::CDataSource& source,
                        DAQ::V12::CRawRingItem& item)
{
    DAQ::readItem(source, item);

    return source;
}

namespace DAQ {

void writeItem(CDataSink& sink, const V12::CRawRingItem& item)
{
    std::array<char,20> header;
    DAQ::V12::serializeHeader(item, header.begin());

    auto& body = item.getBody();

    // the write is atomic
    sink.putv({ {header.data(), header.size()},
                {body.data(), body.size()} });
}


void writeItem(CDataSink& sink, const V12::CRingItem& item)
{
    auto pRawItem = dynamic_cast<const DAQ::V12::CRawRingItem*>(&item);

    // if this is a raw ring item, we can just ship it out
    if (pRawItem) {
        writeItem(sink, *pRawItem);
    } else {
        // the item needs to be serialized first as a raw ring item
        // and then written to the sink
        writeItem(sink, DAQ::V12::CRawRingItem(item));
    }
}


CDataSourcePredicate::State readItem(CDataSource& source, V12::CRawRingItem& item,
              const CTimeout& timeout)
{

    // To maintain sanity in the data stream, this function will only read data from
    // the data stream if and only if a complete ring itme is found. It will peek
    // at the source to learn whether there is indeed enough data to extract a complete
    // a complete item.

    std::array<char,20> header;
    uint32_t size, type, sourceId;
    uint64_t tstamp;
    bool swapNeeded;

    if ( ! timeout.isPoll() ) {
        // wait until there is enough data for the header or the timeout expired
        while (source.availableData() < header.size() && !timeout.expired() && !source.eof()) {
          std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }

        if (timeout.expired() || source.eof()) {
          return CDataSourcePredicate::INSUFFICIENT_DATA;
        }
    }

        // don't read... just peek
    size_t nRead = source.peek(header.data(), header.size());
    if (nRead != header.size()) {
       return CDataSourcePredicate::INSUFFICIENT_DATA;
    }

    if (source.eof()) {
        return CDataSourcePredicate::INSUFFICIENT_DATA;
    }

    DAQ::V12::Parser::parseHeader(header.begin(), header.end(),
                                  size, type, tstamp, sourceId, swapNeeded);

    if (size < header.size()) {
        throw std::runtime_error("Encountered incomplete V12 RingItem type. Fewer than 20 bytes in size field.");
    }

    // Read the body
    if (timeout.isPoll()) {
        // polling means that only one attempt is made to read the item.
        // the entire item is there or it is not.
        if (source.availableData() < size) {
            return CDataSourcePredicate::INSUFFICIENT_DATA;
        }
    } else {
      // timeout ... keep trying until the data is present or it is time to
      // give up
      while (source.availableData() < size && !timeout.expired() && !source.eof()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
      }
      if (timeout.expired() || source.eof()) {
        return CDataSourcePredicate::INSUFFICIENT_DATA;
      }

    }

    // the data for the header has already been acquired through the peek()
    // operation, so it does not need to be read again. Skip it.
    source.ignore(header.size());

    // use the data that was already parsed from the header
    item.setType(type);
    item.setEventTimestamp(tstamp);
    item.setSourceId(sourceId);
    item.setMustSwap(swapNeeded);

    item.getBody().resize(size-header.size());
    source.read(reinterpret_cast<char*>(item.getBody().data()),
                         size-header.size());

    return CDataSourcePredicate::FOUND;

}




CDataSourcePredicate::State
readItemIf(CDataSource& source, V12::CRawRingItem& item, CDataSourcePredicate& pred,
           const CTimeout& timeout)
{
    CDataSourcePredicate::State result;
    do {
        result = pred(source);

        if (result == CDataSourcePredicate::INSUFFICIENT_DATA) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    while ( (result != CDataSourcePredicate::FOUND) 
              && !source.eof() 
              && !timeout.expired()                  );

    if (result == CDataSourcePredicate::FOUND) {
        readItem(source, item, timeout);
    }

    return result;
}


}

#endif // NSCLDAQ_BUILD
