#ifndef DAQ_V12_CRINGSELECTIONPREDICATE_H
#define DAQ_V12_CRINGSELECTIONPREDICATE_H


/*
    This software is Copyright by the Board of Trustees of Michigan
    State University (c) Copyright 2017.

    You may use this software under the terms of the GNU public license
    (GPL).  The terms of this license are described at:

     http://www.gnu.org/licenses/gpl.txt

     Author:
             Ron Fox
             Jeromy Tompkins
         NSCL
         Michigan State University
         East Lansing, MI 48824-1321
*/

#include <CDataSourcePredicate.h>
#include <memory>


class CRingSelectionPredicate;

namespace DAQ {

class CDataSource;

class CRingSelectPredWrapper : public CDataSourcePredicate
{

private:
    std::shared_ptr<CRingSelectionPredicate> m_pPredicate;

  // Constructors and canonicals.

public:
  CRingSelectPredWrapper(std::shared_ptr<CRingSelectionPredicate> pPred);
  virtual ~CRingSelectPredWrapper();

  // Predicate virtual interface.

  virtual State operator()(CDataSource& ring);

  CRingSelectionPredicate& getPredicate();

};


} // end DAQ
#endif // CRINGSELECTIONPREDICATE_H
