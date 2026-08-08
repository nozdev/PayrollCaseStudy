#ifndef TIMECARDTRANSACTION_H
#define TIMECARDTRANSACTION_H

#include "PayrollDomain/Transaction.h"
#include "PayrollDomain/Date.h"

class TimeCardTransaction : public Transaction
{
public:
    virtual ~TimeCardTransaction();

    TimeCardTransaction(
        const Date& date,
        double hours,
        int empId);

    virtual void Execute();

private:
    int itsEmpId;
    Date itsDate;
    double itsHours;
};

#endif
