#include "CSimpleDesiredTypesPredicate.h"

#include <V12/CRingItemParser.h>

#include <CDataSource.h>
#include <array>
#include <thread>
#include <chrono>

namespace DAQ {


void CSimpleDesiredTypesPredicate::addDesiredType(uint32_t type, bool sample)
{
    m_whiteList.insert(type);
}

CDataSourcePredicate::State
CSimpleDesiredTypesPredicate::operator()(CDataSource& source) {
    std::array<char,8> shortHeader;

    // Wait first for enough data to arrive to process. This will return
    // after waiting a very short amount of time so that we do not block
    // indefinitely. We are assuming we have a 1 second granularity in the
    // timeout.
    size_t nRead = 0;

    nRead = source.peek(shortHeader.data() + nRead,
                         shortHeader.size() - nRead);
    if (nRead < shortHeader.size()) {
        return INSUFFICIENT_DATA;
    }

    uint32_t size, type;
    bool needsSwap;

    V12::Parser::parseSizeAndType(shortHeader.begin(), shortHeader.end(),
                                  size, type, needsSwap);

    if (m_whiteList.find(type) != m_whiteList.end()) {
        return FOUND;
    } else {
        // skip ahead to the next event
        source.ignore(size);
        return NOT_FOUND;
    }
}



} // end DAQ
