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

CDataSink& operator<<(CDataSink& sink,
                      const DAQ::V12::CRawRingItem& item)
{
    std::array<char,20> header;
    DAQ::V12::serializeHeader(item, header.begin());

    sink.put(header.data(), header.size());
    sink.put(reinterpret_cast<const char*>(item.getBody().data()), item.getBody().size());

  return sink;
}


CDataSource& operator>>(CDataSource& source,
                        DAQ::V12::CRawRingItem& item)
{
    std::array<char,20> header;
    source.read(header.data(), header.size());

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
    source.read(reinterpret_cast<char*>(item.getBody().data()), size-header.size());

    return source;
}



#endif // NSCLDAQ_BUILD
