#ifndef SALESRECEIPTTRANSACTION_H
#define SALESRECEIPTTRANSACTION_H

#include "PayrollDomain/Transaction.h"
#include "PayrollDomain/Date.h"


class SalesReceiptTransaction : public Transaction
{
public:

    SalesReceiptTransaction(
        int empid,
        Date date,
        double amount);


    virtual ~SalesReceiptTransaction();


    void Execute() override;


private:

    int itsEmpid;
    Date itsDate;
    double itsAmount;
};


#endif
