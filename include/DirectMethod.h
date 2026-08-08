#ifndef DIRECTMETHOD_H
#define DIRECTMETHOD_H

#include "PaymentMethod.h"
#include <string>


class DirectMethod : public PaymentMethod
{
public:

    DirectMethod(
        std::string bank,
        int account);


    virtual ~DirectMethod();


    void Pay(Paycheck& paycheck) override;


    std::string GetBank() const;

    int GetAccount() const;


private:

    std::string itsBank;
    int itsAccount;
};


#endif
