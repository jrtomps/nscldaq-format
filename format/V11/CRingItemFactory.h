/*
    This software is Copyright by the Board of Trustees of Michigan
    State University (c) Copyright 2009.

    You may use this software under the terms of the GNU public license
    (GPL).  The terms of this license are described at:

     http://www.gnu.org/licenses/gpl.txt

     Author:
             Ron Fox
	     NSCL
	     Michigan State University
	     East Lansing, MI 48824-1321
*/


#ifndef DAQ_V11_CRINGITEMFACTORY_H
#define DAQ_V11_CRINGITEMFACTORY_H

#include <memory>

namespace DAQ {
  namespace V11 {

class CRingItem;

    class CRingItemFactory;
    using CRingItemFactoryUPtr = std::unique_ptr<CRingItemFactory>;
    using CRingItemFactoryPtr  = std::shared_ptr<CRingItemFactory>;

/**
 * This class is a factory for the correct type of ring item.
 * It is used to effectively up-cast CRingItem base class objects
 * to specific CRingItem derived classes.  Currently the only use case
 * is to be able to use the itemType and toString members to get the correct
 * results for the actual underlying ring item.
 */
class CRingItemFactory
{
public:
  static CRingItem* createRingItem(const CRingItem& item);
  static CRingItem* createRingItem(const void*     pItem);
  static bool   isKnownItemType(const void* pItem);
};

} // end of V11 namespace
} // end DAQ
#endif
