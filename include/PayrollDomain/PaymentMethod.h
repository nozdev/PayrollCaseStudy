#ifndef PAYMENTMETHOD_H
#define PAYMENTMETHOD_H

class Paycheck;

class PaymentMethod
{
public:

    virtual ~PaymentMethod();

    virtual void Pay(Paycheck& paycheck) = 0;
};

#endif
