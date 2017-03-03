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

#ifndef NSCLDAQ11_RINGIO_H
#define NSCLDAQ11_RINGIO_H

#include <iosfwd>

namespace DAQ {
  namespace V11 {
    class CRingItem;
  }
}

/*!
 * \brief Insert V11 CRingItem into a std::ostream
 *
 * \param stream  the stream
 * \param item    any V11 item
 *
 * \return the stream
 */
extern std::ostream& operator<<(std::ostream& stream,
                                const DAQ::V11::CRingItem& item);

/*!
 * \brief Extract a V11 CRingItem from a std::istream
 *
 * \param stream  the stream
 * \param item    any V11 item
 *
 * \return the stream
 */
extern std::istream& operator>>(std::istream& stream,
                                DAQ::V11::CRingItem& item);


#ifdef NSCLDAQ_BUILD

namespace DAQ {
class CDataSource;
class CDataSink;

    void writeItem(CDataSink& sink, const V11::CRingItem& item);
    void readItem(CDataSource& sink, V11::CRingItem& item);


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
    bool readItemIf(CDataSource& source, V11::CRingItem& item,
                    UnaryPredicate& pred)
    {

        bool stopLooking;
        do {
          stopLooking = pred(source);
        }
        while ( !stopLooking );

        if (stopLooking) {
            readItem(source, item);
        }

        return stopLooking;
    }

}

/*!
 * \brief Insert V11 CRingItem into CDataSink
 *
 * \param stream  the sink
 * \param item    any V11 item
 * \return the sink
 */
extern DAQ::CDataSink& operator<<(DAQ::CDataSink& stream,
                             const DAQ::V11::CRingItem& item);


/*!
 * \brief Extract a V11 CRingItem from a CDataSource
 *
 * \param stream  the source
 * \param item    any V11 item
 *
 * \return the source
 */
extern DAQ::CDataSource& operator>>(DAQ::CDataSource& stream,
                               DAQ::V11::CRingItem& item);


#endif // NSCLDAQ_BUILD

#endif // RINGIO_H
