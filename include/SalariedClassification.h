#ifndef SALARIEDCLASSIFICATION_H
#define SALARIEDCLASSIFICATION_H

#include "PayrollDomain/PaymentClassification.h"
#include "PayrollDomain/Date.h"

class Paycheck;

class SalariedClassification : public PaymentClassification
{
public:

    SalariedClassification(double salary);

    virtual ~SalariedClassification();


    double CalculatePay(
        Paycheck& pc) const override;


    double GetSalary() const;


private:

    double itsSalary;
};

#endif
