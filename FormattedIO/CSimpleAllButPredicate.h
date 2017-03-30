#ifndef CSIMPLEALLBUTPREDICATE_H
#define CSIMPLEALLBUTPREDICATE_H

#include <CDataSourcePredicate.h>

#include <set>
#include <cstdint>

namespace DAQ {

class CDataSource;


class CSimpleAllButPredicate : public CDataSourcePredicate
{
    std::set<uint32_t> m_blacklist;

public:
    CSimpleAllButPredicate();

    void addExceptionType(uint32_t type);

    State operator()(CDataSource& source);
};


} // end DAQ namespace

#endif // CSIMPLEALLBUTPREDICATE_H
