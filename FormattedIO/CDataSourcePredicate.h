#ifndef DAQ_CDATASOURCEPREDICATE_H
#define DAQ_CDATASOURCEPREDICATE_H


namespace DAQ {

class CDataSource;

class CDataSourcePredicate {
public:
    virtual bool operator()(CDataSource& source) = 0;
};

} // end DAQ

#endif // DAQ_CDATASOURCEPREDICATE_H
