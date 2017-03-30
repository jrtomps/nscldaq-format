#include "CSimpleAllButPredicate.h"

#include <V12/CRingItemParser.h>
#include <CDataSource.h>
#include <array>
#include <thread>
#include <chrono>

namespace DAQ {

CSimpleAllButPredicate::CSimpleAllButPredicate()
 : m_blacklist()
{
}


void CSimpleAllButPredicate::addExceptionType(uint32_t type)
{
    m_blacklist.insert(type);
}


CDataSourcePredicate::State CSimpleAllButPredicate::operator()(CDataSource& source)
{

    std::array<char,8> shortHeader;

    size_t nRead = 0;
    nRead = source.peek(shortHeader.data() + nRead, shortHeader.size() - nRead);
    if (nRead < shortHeader.size()) {
        return INSUFFICIENT_DATA;
    }

    uint32_t size, type;
    bool needsSwap;

    V12::Parser::parseSizeAndType(shortHeader.begin(), shortHeader.end(),
                                  size, type, needsSwap);

    if (m_blacklist.find(type) == m_blacklist.end()) {
        return FOUND;
    } else {
        // skip ahead to the next event
        source.ignore(size);
        return NOT_FOUND;
    }

}

} // end DAQ
