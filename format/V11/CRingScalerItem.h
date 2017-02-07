#ifndef NSCLDAQ11_CRINGSCALERITEM_H
#define NSCLDAQ11_CRINGSCALERITEM_H
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



#include "V11/CRingItem.h"

#include <vector>
#include <typeinfo>
#include <string>

namespace DAQ {
  namespace V11 {

/*!
   This class derived from CRingItem and represents a set of scalers that have been 
   formatted as a ring item.  
*/
class CRingScalerItem : public CRingItem
{
public:
  static uint32_t m_ScalerFormatMask;

  // Constructors and canonicals.:

public:
  CRingScalerItem(size_t numScalers);
  CRingScalerItem(uint32_t startTime,
                  uint32_t stopTime,
                  time_t   timestamp,
                  std::vector<uint32_t> scalers,
                  bool                  isIncremental = true,
                  uint32_t              timeOffsetDivisor = 1);
  CRingScalerItem(uint64_t eventTimestamp, uint32_t source, uint32_t barrier,
                  uint32_t startTime,
		  uint32_t stopTime,
		  time_t   timestamp,
		  std::vector<uint32_t> scalers,
                  uint32_t timeDivisor = 1, bool incremental=true);
  CRingScalerItem(const CRingItem& rhs);
  CRingScalerItem(const CRingScalerItem& rhs);
  
  virtual ~CRingScalerItem();

  CRingScalerItem& operator=(const CRingScalerItem& rhs);
  int operator==(const CRingScalerItem& rhs) const;
  int operator!=(const CRingScalerItem& rhs) const;

  // Accessor member functions.

  void     setStartTime(uint32_t startTime);
  uint32_t getStartTime() const;
  float    computeStartTime() const;
  
  void     setEndTime(uint32_t endTime);
  uint32_t getEndTime() const;
  float    computeEndTime() const;

  uint32_t getTimeDivisor() const;

  void     setTimestamp(time_t stamp);
  time_t   getTimestamp() const;
  
  bool isIncremental() const;

  void     setScaler(uint32_t channel, uint32_t value);
  uint32_t getScaler(uint32_t channel) const;
  std::vector<uint32_t> getScalers() const;
  void setScalers(const std::vector<uint32_t>& values);

  uint32_t getScalerCount() const;

  // Virtual methods overriddent:

  virtual std::string typeName() const;
  virtual std::string toString() const;

  // utility.

private:
  size_t bodySize(size_t n);
  void init(size_t n);
  void throwIfInvalidChannel(uint32_t channel, 
                 const char* message) const;
};
   
} // end of V11 namespace
} // end DAQ
#endif
