#ifndef DAQ_V12_RINGIOV12_H
#define DAQ_V12_RINGIOV12_H

#include <CDataSource.h>

#include <iosfwd>
#include <functional>

namespace DAQ {
namespace V12 {
    class CRingItem;
    class CRawRingItem;
} // end V12
} // end DAQ

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

namespace DAQ {
class CDataSource;
class CDataSink;
}

/*!
 * \brief Insert V12 CRingItem into CDataSink
 *
 * \param stream  the sink
 * \param item    a raw ring item
 * \return the sink
 */
extern DAQ::CDataSink& operator<<(DAQ::CDataSink& stream,
                             const DAQ::V12::CRawRingItem& item);


/*!
 * \brief Extract a V12 CRingItem from a CDataSource
 *
 * \param stream  the source
 * \param item    a raw ring item
 *
 * \return the source
 */
extern DAQ::CDataSource& operator>>(DAQ::CDataSource& stream,
                               DAQ::V12::CRawRingItem& item);


namespace DAQ {

void writeItem(CDataSink& source, const V12::CRawRingItem& item);
void writeItem(CDataSink& source, const V12::CRingItem& item);

void readItem(CDataSource& source, V12::CRawRingItem& item);


/*!
 * \brief Selectively read data item
 *
 * \param source    the data source to read from
 * \param item      a raw ring item to fill with data from the source
 * \param pred      a functional that will determine whether we need to
 *                  keep looking (search criteria was not satisfied)
 *
 * The pred parameter should be a functional object that has the signature
 *
 *     bool Predicate(CDataSource& source)
 *
 *  It should return true if the search criteria has not been satisfied. In
 *  other words, it indicates that the caller should keep searching. If the
 *  search can be ended, then the predicate should return false.
 */
template<class UnaryPredicate>
bool readItemIf(CDataSource& source, V12::CRawRingItem& item,
                UnaryPredicate& pred)
{

    bool stopLooking;
    do {
      stopLooking = pred(source);
    }
    while ( !stopLooking && !source.eof());

    if (stopLooking) {
        readItem(source, item);
    }

    return stopLooking;
}

} // end DAQ

#endif // NSCLDAQ_BUILD


#endif // DAQ_V12_RINGIOV12_H
