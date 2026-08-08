#ifndef COMMISSIONEDCLASSIFICATION_H
#define COMMISSIONEDCLASSIFICATION_H

#include "PayrollDomain/PaymentClassification.h"
#include "PayrollDomain/Date.h"
#include <vector>

class Paycheck;
class SalesReceipt;

class CommissionedClassification : public PaymentClassification
{
public:
    CommissionedClassification(
        double salary,
        double commissionRate);

    virtual ~CommissionedClassification();

    virtual double CalculatePay(
        Paycheck& pc) const override;

    void AddSalesReceipt(SalesReceipt* sr);

    SalesReceipt* GetSalesReceipt(
        const Date& date) const;

    double GetSalary() const;
    double GetRate() const;

private:
    double itsSalary;
    double itsRate;

    std::vector<SalesReceipt*> itsSalesReceipts;
};

#endif
