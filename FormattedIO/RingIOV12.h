#ifndef DAQ_V12_RINGIOV12_H
#define DAQ_V12_RINGIOV12_H


#include <iosfwd>

namespace DAQ {
  namespace V12 {
    class CRawRingItem;
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
