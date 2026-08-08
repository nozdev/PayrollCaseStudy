#ifndef CHANGEMAILTRANSACTION_H
#define CHANGEMAILTRANSACTION_H

#include "ChangePaymentMethodTransaction.h"
#include <string>


class PaymentMethod;


class ChangeMailTransaction
    : public ChangePaymentMethodTransaction
{
public:

    ChangeMailTransaction(
        int empid,
        std::string address);


    virtual ~ChangeMailTransaction();


protected:

    PaymentMethod* GetMethod() const override;


private:

    std::string itsAddress;
};


#endif
