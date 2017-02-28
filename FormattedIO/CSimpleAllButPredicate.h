#ifndef CSIMPLEALLBUTPREDICATE_H
#define CSIMPLEALLBUTPREDICATE_H

#include <set>
#include <cstdint>

namespace DAQ {

class CDataSource;


class CSimpleAllButPredicate
{
    std::set<uint32_t> m_blacklist;

public:
    CSimpleAllButPredicate();

    void addExceptionType(uint32_t type);

    bool operator()(CDataSource& source);
};


} // end DAQ namespace

#endif // CSIMPLEALLBUTPREDICATE_H