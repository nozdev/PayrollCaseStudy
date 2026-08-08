#ifndef CHANGEHOLDTRANSACTION_H
#define CHANGEHOLDTRANSACTION_H

#include "ChangePaymentMethodTransaction.h"


class PaymentMethod;


class ChangeHoldTransaction 
    : public ChangePaymentMethodTransaction
{
public:

    ChangeHoldTransaction(int empid);

    virtual ~ChangeHoldTransaction();


protected:

    PaymentMethod* GetMethod() const override;
};


#endif
