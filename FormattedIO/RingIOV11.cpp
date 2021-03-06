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

#include "RingIOV11.h"

#include <V11/CRingItem.h>
#include <byte_cast.h>

#include <V11/DataFormat.h>

#include <iostream>
#include <stdexcept>

std::ostream& operator<<(std::ostream& stream,
                         const DAQ::V11::CRingItem& item)
{
  const char* pItem = reinterpret_cast<const char*>(item.getItemPointer());
  stream.write(pItem, item.size());
  return stream;
}



std::istream& operator>>(std::istream& stream,
                         DAQ::V11::CRingItem& item)
{
  size_t headerSize = 2*sizeof(uint32_t);

  char* pItem = reinterpret_cast<char*>(item.getItemPointer());
  stream.read(pItem, headerSize);

  uint32_t totalSize = item.size();
  char* pBody = pItem + headerSize;
  stream.read(pBody, totalSize-headerSize);

  item.setBodyCursor(pItem+totalSize);
  item.updateSize();

  return stream;
}


#ifdef NSCLDAQ_BUILD

#include <CDataSource.h>
#include <CDataSink.h>

namespace DAQ {

    void writeItem(CDataSink& sink, const V11::CRingItem& item)
    {
        sink.put(item.getItemPointer(), item.size());
    }

    void readItem(CDataSource& source, V11::CRingItem& item)
    {
        size_t headerSize = 2*sizeof(uint32_t);

        char* pItem = reinterpret_cast<char*>(item.getItemPointer());
        source.read(pItem, headerSize);
        if (source.eof()) {
            return;
        }

        uint32_t totalSize = byte_cast<uint32_t>(pItem);

        if (totalSize < headerSize) {
            throw std::runtime_error("Encountered incomplete V11 RingItem. "
                                     "Fewer than 8 bytes in size field.");
        }

        char* pBody = pItem + headerSize;
        source.read(pBody, totalSize-headerSize);

        item.setBodyCursor(pItem+totalSize);
        item.updateSize();
    }

} // end DAQ


DAQ::CDataSink& operator<<(DAQ::CDataSink& sink,
                      const DAQ::V11::CRingItem& item)
{
  DAQ::writeItem(sink,item);

  return sink;
}


DAQ::CDataSource& operator>>(DAQ::CDataSource& source,
                        DAQ::V11::CRingItem& item)
{
    DAQ::readItem(source, item);

    return source;
}

#endif // NSCLDAQ_BUILD
