#ifndef CHANGECOMMISSIONEDTRANSACTION_H
#define CHANGECOMMISSIONEDTRANSACTION_H

#include "ChangeClassificationTransaction.h"

class ChangeCommissionedTransaction :
    public ChangeClassificationTransaction
{
public:

    virtual ~ChangeCommissionedTransaction();


    ChangeCommissionedTransaction(
        int empid,
        double salary,
        double commissionRate);


protected:

    PaymentClassification*
    GetClassification() const override;


    PaymentSchedule*
    GetSchedule() const override;


private:

    double itsSalary;
    double itsCommissionRate;

};

#endif
