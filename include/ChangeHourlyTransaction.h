#ifndef CHANGEHOURLYTRANSACTION_H
#define CHANGEHOURLYTRANSACTION_H

#include "ChangeClassificationTransaction.h"


class ChangeHourlyTransaction :
    public ChangeClassificationTransaction
{
public:

    virtual ~ChangeHourlyTransaction();


    ChangeHourlyTransaction(
        int empid,
        double hourlyRate);


protected:

    PaymentClassification*
    GetClassification() const override;


    PaymentSchedule*
    GetSchedule() const override;


private:

    double itsHourlyRate;

};

#endif
