#ifndef DAQ_V12_RINGIOV12_H
#define DAQ_V12_RINGIOV12_H

#include <V12/CRingItem.h>

#include <array>
#include <iosfwd>

namespace DAQ {
  namespace V12 {
    class CRawRingItem;

    /*!
     * \brief Serialize the ring item header into some memory
     *
     * \param item      the ring item to serialize
     * \param buffer    the buffer to fill with the serial representation
     *
     */
    template<class ByteIterator>
    ByteIterator serializeHeader(const DAQ::V12::CRingItem &item, ByteIterator out)
    {
        uint32_t temp32;
        uint64_t temp64;

        temp32 = item.size();
        out = std::copy(reinterpret_cast<char*>(&temp32),
                        reinterpret_cast<char*>(&temp32)+sizeof(temp32),
                        out);

        temp32 = item.type();
        out = std::copy(reinterpret_cast<char*>(&temp32),
                        reinterpret_cast<char*>(&temp32)+sizeof(temp32),
                        out);

        temp64 = item.getEventTimestamp();
        out = std::copy(reinterpret_cast<char*>(&temp64),
                        reinterpret_cast<char*>(&temp64)+sizeof(temp64),
                        out);

        temp32 = item.getSourceId();
        out = std::copy(reinterpret_cast<char*>(&temp32),
                        reinterpret_cast<char*>(&temp32)+sizeof(temp32),
                        out);

        return out;

    }
  }
}

/*!
 * \brief Insert V12 CRingItem into a std::ostream
 *
 * \param stream  the stream
 * \param item    a raw ring item
 *
 * \return the stream
 */
extern std::ostream& operator<<(std::ostream& stream,
                                const DAQ::V12::CRawRingItem& item);

/*!
 * \brief Extract a V12 CRingItem from a std::istream
 *
 * \param stream  the stream
 * \param item    a raw ring item
 *
 * \return the stream
 */
extern std::istream& operator>>(std::istream& stream,
                                DAQ::V12::CRawRingItem& item);



#ifdef NSCLDAQ_BUILD

class CDataSource;
class CDataSink;

/*!
 * \brief Insert V12 CRingItem into CDataSink
 *
 * \param stream  the sink
 * \param item    a raw ring item
 * \return the sink
 */
extern CDataSink& operator<<(CDataSink& stream,
                             const DAQ::V12::CRawRingItem& item);


/*!
 * \brief Extract a V12 CRingItem from a CDataSource
 *
 * \param stream  the source
 * \param item    a raw ring item
 *
 * \return the source
 */
extern CDataSource& operator>>(CDataSource& stream,
                               DAQ::V12::CRawRingItem& item);


#endif // NSCLDAQ_BUILD


#endif // DAQ_V12_RINGIOV12_H
