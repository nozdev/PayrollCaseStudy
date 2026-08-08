#ifndef PAYMENTCLASSIFICATION_H
#define PAYMENTCLASSIFICATION_H

class Paycheck;

class PaymentClassification
{
public:
    virtual ~PaymentClassification();

    virtual double CalculatePay(
        Paycheck& pc) const = 0;
};

#endif
