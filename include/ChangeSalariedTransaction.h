#ifndef CHANGESALARIEDTRANSACTION_H
#define CHANGESALARIEDTRANSACTION_H

#include "ChangeClassificationTransaction.h"

class ChangeSalariedTransaction :
    public ChangeClassificationTransaction
{
public:

    virtual ~ChangeSalariedTransaction();


    ChangeSalariedTransaction(
        int empid,
        double salary);


protected:

    PaymentClassification*
    GetClassification() const override;


    PaymentSchedule*
    GetSchedule() const override;


private:

    double itsSalary;

};

#endif
