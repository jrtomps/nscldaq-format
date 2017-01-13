#ifndef NSCLDAQ11_CRINGSTATECHANGEITEM_H
#define NSCLDAQ11_CRINGSTATECHANGEITEM_H
/*
    This software is Copyright by the Board of Trustees of Michigan
    State University (c) Copyright 2005.

    You may use this software under the terms of the GNU public license
    (GPL).  The terms of this license are described at:

     http://www.gnu.org/licenses/gpl.txt

     Author:
             Ron Fox
	     NSCL
	     Michigan State University
	     East Lansing, MI 48824-1321
*/


#include <V11/CRingItem.h>

#include <string>
#include <typeinfo>
#include <RangeError.h>

namespace DAQ {
  namespace V12 {

/*!
  This class represents a state change item.
  State change items are items in the buffer that indicate a change in the state of
  data taking.  The set of state changes recognized by this class are:

  - BEGIN_RUN  - the run has become active after being stopped.
  - END_RUN    - The run has become inactive after being ended.
  - PAUSE_RUN  - The run has become inactive after being temporarily paused.
  - RESUME_RUN - The run has become active after being resumed while paused.

  This object is suitable for use by both producers (who must create state change
  items), and consumers (who must inspect the contents of such items after getting
  them from a ring).


*/
class CRingStateChangeItem : public CRingItem
{

  // construction and other canonicals
public:
  CRingStateChangeItem(uint16_t reason = 1);

  virtual uint32_t type() const;
  virtual void setType(uint32_t type);

  virtual uint32_t size() const;

  virtual uint64_t getEventTimestamp() const;
  virtual void setEventTimestamp(uint64_t tstamp);

  virtual uint32_t getSourceId() const;
  virtual void setSourceId(uint32_t id);

  virtual bool     isComposite() const;

  virtual bool     mustSwap() const;

  virtual std::string typeName() const;
  virtual std::string toString() const;

  virtual void toRawRingItem(CRawRingItem& item) const;

  //  CRingStateChangeItem(uint16_t reason,
//		       uint32_t runNumber,
//		       uint32_t timeOffset,
//		       time_t   timestamp,
//		       std::string title) throw(CRangeError);
//  CRingStateChangeItem(uint64_t eventTimestamp, uint32_t sourceId, uint32_t barrierType,
//                       uint16_t reason,
//		       uint32_t runNumber,
//		       uint32_t timeOffset,
//		       time_t   timestamp,
//		       std::string title,
//                       uint32_t offsetDivisor = 1);
  
//  CRingStateChangeItem(const CRingItem& item) throw(std::bad_cast);
//  CRingStateChangeItem(const CRingStateChangeItem& rhs);
//  virtual ~CRingStateChangeItem();

//  CRingStateChangeItem& operator=(const CRingStateChangeItem& rhs);
//  int operator==(const CRingStateChangeItem& rhs) const;
//  int operator!=(const CRingStateChangeItem& rhs) const;

//  // Accessors for elements of the item (selectors and mutators both).

//  void setRunNumber(uint32_t run);
//  uint32_t getRunNumber() const;

//  void     setElapsedTime(uint32_t offset);
//  uint32_t getElapsedTime() const;
//  float    computeElapsedTime() const;

//  void setTitle(std::string title) throw(CRangeError);
//  std::string getTitle() const;

//  void setTimestamp(time_t stamp);
//  time_t getTimestamp() const;

//  void setOffsetDivisor(uint32_t divisor);
//  uint32_t getOffsetDivisor() const;
//  // Virtual method overrides.

//  virtual std::string typeName() const;
//  virtual std::string toString() const;

//  // Utitlity functions..

//private:
//  void init();
//  bool isStateChange();
//  _StateChangeItemBody* getStateChangeBody();
};

  } // end of V11 namespace
} // end DAQ
#endif

