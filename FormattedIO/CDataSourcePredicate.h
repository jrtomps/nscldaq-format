#ifndef DAQ_CDATASOURCEPREDICATE_H
#define DAQ_CDATASOURCEPREDICATE_H


namespace DAQ {

class CDataSource;

class CDataSourcePredicate {
public:
    enum State { FOUND, NOT_FOUND, INSUFFICIENT_DATA };
public:
    virtual State operator()(CDataSource& source) = 0;
};

} // end DAQ

#endif // DAQ_CDATASOURCEPREDICATE_H
