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
  char header[20];
  uint32_t temp32;
  uint64_t temp64;

  temp32 = item.size();
  std::copy(reinterpret_cast<char*>(&temp32),
            reinterpret_cast<char*>(&temp32)+sizeof(temp32),
            header);

  temp32 = item.type();
  std::copy(reinterpret_cast<char*>(&temp32),
            reinterpret_cast<char*>(&temp32)+sizeof(temp32),
            header+4);

  temp64 = item.getEventTimestamp();
  std::copy(reinterpret_cast<char*>(&temp64),
            reinterpret_cast<char*>(&temp64)+sizeof(temp64),
            header+8);

  temp32 = item.getSourceId();
  std::copy(reinterpret_cast<char*>(&temp32),
            reinterpret_cast<char*>(&temp32)+sizeof(temp32),
            header+16);

  stream.write(reinterpret_cast<char*>(header), sizeof(header));
  stream.write(reinterpret_cast<const char*>(item.getBody().data()), item.getBody().size());

  return stream;
}



std::istream& operator>>(std::istream& stream,
                         DAQ::V12::CRawRingItem& item)
{
    char header[20];
    stream.read(header, sizeof(header));

    uint32_t size, type, sourceId;
    uint64_t tstamp;
    bool swapNeeded;
    DAQ::V12::Parser::parseHeader(header, header+sizeof(header),
                                  size, type, tstamp, sourceId, swapNeeded);

    item.setType(type);
    item.setEventTimestamp(tstamp);
    item.setSourceId(sourceId);

    item.setMustSwap(swapNeeded);

    item.getBody().resize(size-sizeof(header));
    stream.read(reinterpret_cast<char*>(item.getBody().data()), size-sizeof(header));

    return stream;
}


#ifdef NSCLDAQ_BUILD

#include <CDataSource.h>
#include <CDataSink.h>

CDataSink& operator<<(CDataSink& sink,
                      const DAQ::V12::CRawRingItem& item)
{
//  sink.put(item.getItemPointer(), item.size());

  return sink;
}


CDataSource& operator>>(CDataSource& source,
                        DAQ::V12::CRawRingItem& item)
{
//  size_t headerSize = 2*sizeof(uint32_t);

//  char* pItem = reinterpret_cast<char*>(item.getItemPointer());
//  source.read(pItem, headerSize);

//  uint32_t totalSize = byte_cast<uint32_t>(pItem);
//  char* pBody = pItem + headerSize;
//  source.read(pBody, totalSize-headerSize);

//  item.setBodyCursor(pItem+totalSize);
//  item.updateSize();

  return source;
}

#endif // NSCLDAQ_BUILD
