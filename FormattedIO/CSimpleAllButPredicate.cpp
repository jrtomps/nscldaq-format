#include "CSimpleAllButPredicate.h"

#include <V12/CRingItemParser.h>
#include <CDataSource.h>
#include <array>
#include <iostream>

namespace DAQ {

CSimpleAllButPredicate::CSimpleAllButPredicate()
{
}


void CSimpleAllButPredicate::addExceptionType(uint32_t type)
{
    m_blacklist.insert(type);
}


bool CSimpleAllButPredicate::operator()(CDataSource& source)
{
    std::array<char,8> shortHeader;

    size_t nRead = 0;
    while (nRead < shortHeader.size()) {
        nRead += source.peek(shortHeader.data() + nRead, shortHeader.size() - nRead);
    }

    uint32_t size, type;
    bool needsSwap;

    V12::Parser::parseSizeAndType(shortHeader.begin(), shortHeader.end(),
                                  size, type, needsSwap);

    if (m_blacklist.find(type) == m_blacklist.end()) {
        return true;
    } else {
        // skip ahead to the next event
        source.ignore(size);
        return false;
    }

}

} // end DAQ
