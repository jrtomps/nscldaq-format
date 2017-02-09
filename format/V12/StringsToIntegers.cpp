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

#include "V12/StringsToIntegers.h"
#include <stdio.h>
#include <stdlib.h>
#include <V12/DataFormat.h>

#include <map>

using namespace std;
using namespace DAQ::V12;

static bool initialized = false;
static map<string, int>   textToInt;


static void initialize()
{
  textToInt["BEGIN_RUN"]           = BEGIN_RUN;
  textToInt["END_RUN"]             = END_RUN;
  textToInt["PAUSE_RUN"]           = PAUSE_RUN;
  textToInt["RESUME_RUN"]          = RESUME_RUN;
  textToInt["ABNORMAL_ENDRUN"]     = ABNORMAL_ENDRUN;
  textToInt["PACKET_TYPE"]         = PACKET_TYPES;
  textToInt["MONITORED_VARIABLES"] = MONITORED_VARIABLES;
  textToInt["RING_FORMAT"]         = RING_FORMAT;
  textToInt["PERIODIC_SCALERS"]    = PERIODIC_SCALERS;    // Compatibility.
  textToInt["PHYSICS_EVENT"]       = PHYSICS_EVENT;
  textToInt["PHYSICS_EVENT_COUNT"] = PHYSICS_EVENT_COUNT;
  textToInt["EVB_GLOM_INFO"]       = EVB_GLOM_INFO;

  textToInt["COMP_BEGIN_RUN"]           = COMP_BEGIN_RUN;
  textToInt["COMP_END_RUN"]             = COMP_END_RUN;
  textToInt["COMP_PAUSE_RUN"]           = COMP_PAUSE_RUN;
  textToInt["COMP_RESUME_RUN"]          = COMP_RESUME_RUN;
  textToInt["COMP_ABNORMAL_ENDRUN"]     = COMP_ABNORMAL_ENDRUN;
  textToInt["COMP_PACKET_TYPE"]         = COMP_PACKET_TYPES;
  textToInt["COMP_MONITORED_VARIABLES"] = COMP_MONITORED_VARIABLES;
  textToInt["COMP_RING_FORMAT"]         = COMP_RING_FORMAT;
  textToInt["COMP_PERIODIC_SCALERS"]    = COMP_PERIODIC_SCALERS;    // Compatibility.
  textToInt["COMP_PHYSICS_EVENT"]       = COMP_PHYSICS_EVENT;
  textToInt["COMP_PHYSICS_EVENT_COUNT"] = COMP_PHYSICS_EVENT_COUNT;
  textToInt["COMP_EVB_GLOM_INFO"]       = COMP_EVB_GLOM_INFO;

}

// 
//
static int
convertOne(string aNumber)
{
  char *end;

  int  value = strtol(aNumber.c_str(), &end, 0);
  if (*end != '\0') {
    if (textToInt.find(aNumber) != textToInt.end()) {
      return textToInt[aNumber];
    }
    else {
      string whyBad  = " must be an integer or a symbolic item type but was ";
      whyBad        += aNumber;
      throw CInvalidArgumentException(aNumber, whyBad,
				      string("Converting a list to integers"));
    }
  }
  return value;
}

namespace DAQ {
  namespace V12 {

////////////////////////////////////////////////////////////////////////////////
/*!
 *  This header rovides an unbound function that takes a comma separated
 *  list of integer (in string form) and converts them into a 
 *  vector of ints.
 *  This is most useful in decodin things like:
 *  
 * \verbatim
 *   ... --exclude=1,2,3 ...
 * \endverbatim
 *
 * \param items  - Stringified comma separated list of integers.
 * \return std::vector<int>
 * \retval Ordered vector of the integers decoded from the string.
 * \throw std::invalid_argument
 */
vector<int>
stringListToIntegers(string items) 
{
    size_t      start = 0;
    vector<int> result;
    size_t comma;

    if (!initialized) initialize();

    while ((comma = items.find(string(","), start)) != string::npos) {
        string aNumber;
	aNumber.assign(items, start, comma - start);

	result.push_back(convertOne(aNumber));
	start = comma+1;
    }
    // There's one last string that does not terminate in a comma:

    string aNumber;
    aNumber.assign(items, start, items.size() - start);
    result.push_back(convertOne(aNumber));

    return result;
}


} // end V12 namespace
} // end DAQ namespace
