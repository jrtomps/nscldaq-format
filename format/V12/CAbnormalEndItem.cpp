/**

#    This software is Copyright by the Board of Trustees of Michigan
#    State University (c) Copyright 2017.
#
#    You may use this software under the terms of the GNU public license
#    (GPL).  The terms of this license are described at:
#
#     http://www.gnu.org/licenses/gpl.txt
#
#    Author:
#            Jeromy Tompkins
#            NSCL
#            Michigan State University
#            East Lansing, MI 48824-1321

##
# @file   CAbnormalEndItem.cpp
# @brief  Implements the abnormal end run ring item class.
*/

#include "V12/CAbnormalEndItem.h"
#include "V12/CRawRingItem.h"
#include "V12/DataFormat.h"

#include <make_unique.h>

#include <typeinfo>
#include <string>

namespace DAQ {
  namespace V12 {

  /*!
 * \brief Construct from a raw ring item
 *
 * \param rhs   the raw ring item to construct from
 *
 * \throws std::runtime_error if the raw ring item has a type other than ABNORMAL_ENDRUN
 */
  CAbnormalEndItem::CAbnormalEndItem(const CRawRingItem& rhs)
  {
      if(rhs.type() != ABNORMAL_ENDRUN) {
          throw std::bad_cast();
      }

      m_evtTimestamp = rhs.getEventTimestamp();
      m_sourceId     = rhs.getSourceId();
  }

  /**
 * \brief Equality comparison operator
 *
 * \retval true if tstamp, source id, and type are the same
 * \retval false otherwise
 */
  bool
  CAbnormalEndItem::operator==(const CRingItem& rhs) const
  {
      if (ABNORMAL_ENDRUN != rhs.type()) return false;
      if (m_evtTimestamp != rhs.getEventTimestamp()) return false;
      if (m_sourceId != rhs.getSourceId()) return false;

      return true;
  }

  /**
 * \brief Inequality comparison operator
 *
 * \retval true if not equal
 * \retval false otherwise
 */
  bool
  CAbnormalEndItem::operator!=(const CRingItem& rhs) const
  {
      return !operator==(rhs);
  }


  /*!
   * \return 20 (always will be the same size)
   */
  uint32_t CAbnormalEndItem::size() const
  {
      return 20;
  }

  /*!
   * \return V12::ABNORMAL_ENDRUN
   */
  uint32_t CAbnormalEndItem::type() const
  {
      return ABNORMAL_ENDRUN;
  }

  /*!
   * \brief CAbnormalEndItem::setType
   * \param type    the type
   *
   * \throws std::invalid_argument if user passes type other than V12::ABNORMAL_ENDRUN
   */
  void CAbnormalEndItem::setType(uint32_t type)
  {
      if (type != ABNORMAL_ENDRUN) {
          std::string msg("CAbnormalEndRun::setType() only accepts the V12::ABNORMAL_ENDRUN type.");
          throw std::invalid_argument(msg);
      }
  }

  uint64_t CAbnormalEndItem::getEventTimestamp() const
  {
      return m_evtTimestamp;
  }

  void CAbnormalEndItem::setEventTimestamp(uint64_t tstamp)
  {
      m_evtTimestamp = tstamp;
  }

  void CAbnormalEndItem::setSourceId(uint32_t id) {
      m_sourceId = id;
  }

  uint32_t CAbnormalEndItem::getSourceId() const {
      return m_sourceId;
  }

  /*!
   * \brief CAbnormalEndItem::isComposite
   *
   * Abnormal endrun items are always leaf types.
   *
   * \return false
   */
  bool CAbnormalEndItem::isComposite() const
  {
      return false;
  }

  /*!
   * \brief CAbnormalEndItem::mustSwap
   *
   * Abnormal end run items are always stored in native byte order.
   *
   * \return false
   */
  bool CAbnormalEndItem::mustSwap() const
  {
      return false;
  }

  /*!
   * \brief Serialize the data to a raw ring item
   *
   * Prior to filling the raw item's body with data, the body is cleared.
   *
   * \param item    the ring item to fill with data
   */
  void CAbnormalEndItem::toRawRingItem(CRawRingItem& item) const
  {
      // clear out prior contents of raw ring item body
      item.getBody().clear();

      item.setType(type());
      item.setEventTimestamp(getEventTimestamp());
      item.setSourceId(getSourceId());
  }


  /* Formatting interface */

  /**
 * typeName
 *    Returns a textual name of the item type
 * @return std::string
 */
  std::string
  CAbnormalEndItem::typeName() const
  {
      return "Abnormal End";
  }
  /**
 * toString
 *
 *  Return a nicely formatted rendition of the ring item.
 * @return std::string
 */
  std::string
  CAbnormalEndItem::toString() const
  {
      return headerToString(*this);
  }

  CRingItemUPtr CAbnormalEndItem::clone() const {
      return make_unique<CAbnormalEndItem>(*this);
  }

  } // end of V12 namespace
} // end DAQ
