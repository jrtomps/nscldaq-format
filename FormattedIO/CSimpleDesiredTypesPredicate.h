#ifndef CSIMPLEDESIREDTYPESPREDICATE_H
#define CSIMPLEDESIREDTYPESPREDICATE_H

/*
    This software is Copyright by the Board of Trustees of Michigan
    State University (c) Copyright 2017.

    You may use this software under the terms of the GNU public license
    (GPL).  The terms of this license are described at:

     http://www.gnu.org/licenses/gpl.txt

     Author:
             Ron Fox
         NSCL
         Michigan State University
         East Lansing, MI 48824-1321
*/

#include <CDataSourcePredicate.h>

#include <set>
#include <cstdint>

namespace DAQ {

class CDataSource;

/*!

   CDesiredTypesPredicate is a CRingSelectionPredicate that only selects items on the
   selection list.
*/
class CSimpleDesiredTypesPredicate : public CDataSourcePredicate
{
private:
    std::set<uint32_t> m_whiteList;

    // Constructors and canonicals.

public:
  CSimpleDesiredTypesPredicate() = default;
  CSimpleDesiredTypesPredicate(const CSimpleDesiredTypesPredicate& rhs) = default;

  CSimpleDesiredTypesPredicate& operator=(const CSimpleDesiredTypesPredicate& rhs) = default;

  // Add a type to the selection set.

  void addDesiredType(uint32_t type, bool sample = false);

  State operator()(CDataSource& source);
};

} // end DAQ

#endif // CSIMPLEDESIREDTYPESPREDICATE_H
