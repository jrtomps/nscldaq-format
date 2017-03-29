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


bool CSimpleAllButPredicate::operator()(CDataSource& source)
{

    std::array<char,8> shortHeader;

    // Block for a short period of time while waiting for enough data.
    // This will try 100 times before timing out. There is an implicit
    // assumption that there is a 1 second granularity in the timeout
    // and that it is not important we go over the timeout by 1 second.
    size_t nRead = 0;
    int maxAttempts = 10;
    int attemptsMade = 0;

    nRead += source.peek(shortHeader.data() + nRead, shortHeader.size() - nRead);
    attemptsMade++;

    while (nRead < shortHeader.size() && attemptsMade < maxAttempts) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        nRead += source.peek(shortHeader.data() + nRead, shortHeader.size() - nRead);
        attemptsMade++;
    }

    if (attemptsMade == maxAttempts) {
        return false; // timed out
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
