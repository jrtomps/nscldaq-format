/*
    This software is Copyright by the Board of Trustees of Michigan
    State University (c) Copyright 2017

    You may use this software under the terms of the GNU public license
    (GPL).  The terms of this license are described at:

     http://www.gnu.org/licenses/gpl.txt

     Author:
     Jeromy Tompkins
	     NSCL
	     Michigan State University
	     East Lansing, MI 48824-1321
*/
static const char* Copyright = "(C) Copyright Michigan State University 2017, All rights reserved";

#include <ByteOrder.h>

namespace DAQ
{
  namespace BO
  {

    CByteSwapper::CByteSwapper(bool needsSwap) : m_needsSwap(needsSwap) {}

  }  // end of BO
} // end of DAQ
