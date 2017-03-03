#ifndef DAQ_V11_STRINGSTOINTEGERS_H
#define DAQ_V11_STRINGSTOINTEGERS_H

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

#include <string>
#include <vector>

namespace DAQ {
namespace V11 {

/*! Convert list of strings to integers.
 */
std::vector<int> stringListToIntegers(const std::string& items);

} // end V11 namespace
} // end DAQ namespace

#endif

