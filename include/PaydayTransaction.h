#ifndef PAYDAYTRANSACTION_H
#define PAYDAYTRANSACTION_H

#include "PayrollDomain/Transaction.h"
#include "PayrollDomain/Date.h"

#include <map>

class Paycheck;

class PaydayTransaction : public Transaction
{
public:
    PaydayTransaction(const Date& payDate);
    virtual ~PaydayTransaction();

    virtual void Execute();

    Paycheck* GetPaycheck(int empId) const;

private:
    Date itsPayDate;
    std::map<int, Paycheck*> itsPaychecks;
};

#endif
