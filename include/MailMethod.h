#ifndef MAILMETHOD_H
#define MAILMETHOD_H

#include "PaymentMethod.h"
#include <string>


class MailMethod : public PaymentMethod
{
public:

    MailMethod(std::string address);

    virtual ~MailMethod();


    void Pay(Paycheck& paycheck) override;


    std::string GetAddress() const;


private:

    std::string itsAddress;
};


#endif
