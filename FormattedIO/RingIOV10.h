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

#ifndef DAQ_V10_RINGIO_H
#define DAQ_V10_RINGIO_H

#include <iosfwd>


namespace DAQ
{
  namespace V10 {
    class CRingItem;
  }
}

/*!
 * \brief Insert V10 CRingItem into a std::ostream
 *
 * This simply sends the entire item managed by the CRingItem to the
 * stream.
 *
 * \param stream  to send data to
 * \param item    any V10 ring item
 * \return the stream
 */
extern std::ostream& operator<<(std::ostream& stream,
                                const DAQ::V10::CRingItem& item);

/*!
 * \brief Extract a V10 CRingItem from the std::istream
 *
 * \param stream  the stream
 * \param item    a V10 item
 * \return the stream
 */
extern std::istream& operator>>(std::istream& stream,
                                DAQ::V10::CRingItem& item);


#ifdef NSCLDAQ_BUILD

#include <CDataSource.h>

namespace DAQ {
class CDataSink;

    void writeItem(CDataSink& sink, const V10::CRingItem& item);
    void readItem(CDataSource& source, V10::CRingItem& item);



    /*!
     * \brief Selectively read data item
     *
     * \param source    the data source to read from
     * \param item      a ring item to fill with data from the source
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
    bool readItemIf(CDataSource& source, V10::CRingItem& item,
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


}



/*!
 * \brief Insert V10 CRingItem into a CDataSink
 *
 * \param stream  the stream to send data to
 * \param item    any V10 ring item
 *
 * \return  the stream
 */
extern DAQ::CDataSink& operator<<(DAQ::CDataSink& stream,
                             const DAQ::V10::CRingItem& item);


/*!
 * \brief Extract a V10 CRingItem from a CDataSource
 *
 * \param stream  the stream
 * \param item    a V10 item
 * \return the stream
 */
extern DAQ::CDataSource& operator>>(DAQ::CDataSource& stream,
                               DAQ::V10::CRingItem& item);

#endif // NSCLDAQ_BUILD

#endif // DAQ_V10_RINGIO_H
