#ifndef CHANGECLASSIFICATIONTRANSACTION_H
#define CHANGECLASSIFICATIONTRANSACTION_H

#include "ChangeEmployeeTransaction.h"

class PaymentClassification;
class PaymentSchedule;


class ChangeClassificationTransaction :
    public ChangeEmployeeTransaction
{
public:

    virtual ~ChangeClassificationTransaction();


    ChangeClassificationTransaction(
        int empid);


protected:

    virtual PaymentClassification*
    GetClassification() const = 0;


    virtual PaymentSchedule*
    GetSchedule() const = 0;


    void Change(
        Employee& e) override;

};

#endif
