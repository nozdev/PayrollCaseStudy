#ifndef CHANGEDIRECTTRANSACTION_H
#define CHANGEDIRECTTRANSACTION_H

#include "ChangePaymentMethodTransaction.h"
#include <string>


class PaymentMethod;


class ChangeDirectTransaction
    : public ChangePaymentMethodTransaction
{
public:

    ChangeDirectTransaction(
        int empid,
        std::string bank,
        int account);


    virtual ~ChangeDirectTransaction();


protected:

    PaymentMethod* GetMethod() const override;


private:

    std::string itsBank;
    int itsAccount;
};


#endif
