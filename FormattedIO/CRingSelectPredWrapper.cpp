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

#include "CRingSelectPredWrapper.h"
#include <CRingSelectionPredicate.h>
#include <CDataSource.h>
#include <CRingDataSource.h>
#include <CRingBuffer.h>

using namespace std;


namespace DAQ {

//////////////////////////////////////////////////////////////////////
// Constructors and other canonicals.
//

/*!
  Default constructor.  The object is created with an empty selection list.
  Actual predicates will usually define a mechanism for manipulating the
  selection that has an appropriate name for how the selection is used.
*/
CRingSelectPredWrapper::CRingSelectPredWrapper(shared_ptr<CRingSelectionPredicate> pPred)
    : m_pPredicate(pPred)
{}

CRingSelectPredWrapper::~CRingSelectPredWrapper() {}

/*!
*/
bool
CRingSelectPredWrapper::operator()(CDataSource& ring)
{
  // We need to have at least a header:
  auto& ringSource = dynamic_cast<CRingDataSource&>(ring);
  CRingBuffer& aRing = ringSource.getRing();

  return ! m_pPredicate->operator()(aRing);

}

} // end DAQ

