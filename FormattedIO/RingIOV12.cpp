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

void readItem(CDataSource& source, V12::CRawRingItem& item,
              const CTimeout& timeout)
{
    std::array<char,20> header;

    source.timedRead(header.data(), header.size(), timeout);
    if (source.eof() || timeout.expired()) {
        return;
    }

    uint32_t size, type, sourceId;
    uint64_t tstamp;
    bool swapNeeded;
    DAQ::V12::Parser::parseHeader(header.begin(), header.end(),
                                  size, type, tstamp, sourceId, swapNeeded);

    item.setType(type);
    item.setEventTimestamp(tstamp);
    item.setSourceId(sourceId);

    item.setMustSwap(swapNeeded);

    if (size < header.size()) {
      throw std::runtime_error("Encountered incomplete V12 RingItem type. Fewer than 20 bytes in size field.");
    }
    item.getBody().resize(size-header.size());
    source.timedRead(reinterpret_cast<char*>(item.getBody().data()),
                     size-header.size(), timeout);
}

}

#endif // NSCLDAQ_BUILD
