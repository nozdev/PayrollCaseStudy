#ifndef SERVICECHARGETRANSACTION_H
#define SERVICECHARGETRANSACTION_H

#include "PayrollDomain/Transaction.h"
#include "PayrollDomain/Date.h"


class ServiceChargeTransaction :
    public Transaction
{
public:

    virtual ~ServiceChargeTransaction();


    ServiceChargeTransaction(
        int memberId,
        Date date,
        double charge);


    void Execute() override;


private:

    int itsMemberId;
    Date itsDate;
    double itsCharge;

};

#endif
