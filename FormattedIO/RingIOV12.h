#ifndef DAQ_V12_RINGIOV12_H
#define DAQ_V12_RINGIOV12_H

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

#include <CDataSource.h>
#include <CTimeout.h>
#include <CDataSourcePredicate.h>
#include <chrono>

namespace DAQ {
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

CDataSourcePredicate::State readItem(CDataSource& source,
              V12::CRawRingItem& item,
              const CTimeout& timeout = CTimeout(std::chrono::hours(24)));


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
 *     CDataSourcePredicate::State Predicate(CDataSource& source)
 *
 *  It should return true if the search criteria has not been satisfied. In
 *  other words, it indicates that the caller should keep searching. If the
 *  search can be ended, then the predicate should return false.
 *
 * The little bit of template metaprogramming magic here just ensures that
 * the UnaryPredicate does not derive from the CDataSourcePredicate base class.
 * By doing so, we make sure that the overload for the CDataSourcePredicate
 * gets called.
 */
template<class UnaryPredicate,
         typename = typename std::enable_if<
                                             ! std::is_base_of<
                                                                CDataSourcePredicate,
                                                                UnaryPredicate
                                                              >::value
                                           >::type >
bool
readItemIf(CDataSource& source, V12::CRawRingItem& item, UnaryPredicate& pred)
{
    bool stopLooking = false;
    do {
      stopLooking = pred(source);
    }
    while ( !stopLooking && !source.eof() );

    if (stopLooking) {
        readItem(source, item);
    }

    return stopLooking;
}

/*!
 * \brief Timed Condition Read
 *
 * \param source    the source to read from
 * \param item      the raw ring item to fill with data from the source
 * \param pred      a data source predicate
 * \param timeout   a timeout object specifying the time till timeout
 *
 * \retval INSUFFICIENT_DATA - if timeout occurred or there was not enough data
 * \retval FOUND             - read a data item that satisfied the predicate
 * \retval NOT_FOUND         - did not read a data item because predicate was not satisfied
 *                             and either the source reached an eof condition or the
 *                             timeout expired.
 */
CDataSourcePredicate::State
readItemIf(CDataSource& source,
                V12::CRawRingItem& item,
                CDataSourcePredicate& pred,
                const CTimeout& timeout = CTimeout(std::chrono::hours(24)));

} // end DAQ

#endif // NSCLDAQ_BUILD


#endif // DAQ_V12_RINGIOV12_H
