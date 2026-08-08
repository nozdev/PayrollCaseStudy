#ifndef CHANGEPAYMENTMETHODTRANSACTION_H
#define CHANGEPAYMENTMETHODTRANSACTION_H

#include "ChangeEmployeeTransaction.h"


class PaymentMethod;


class ChangePaymentMethodTransaction 
    : public ChangeEmployeeTransaction
{
public:

    ChangePaymentMethodTransaction(int empid);

    virtual ~ChangePaymentMethodTransaction();


protected:

    void Change(Employee& e) override;

    virtual PaymentMethod* GetMethod() const = 0;
};


#endif
