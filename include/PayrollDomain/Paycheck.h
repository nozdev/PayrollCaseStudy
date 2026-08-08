#ifndef PAYCHECK_H
#define PAYCHECK_H

#include <map>
#include <string>
#include "Date.h"

class Paycheck
{
public:
    Paycheck(
        const Date& payPeriodStartDate,
        const Date& payPeriodEndDate);

    virtual ~Paycheck();

    Date GetPayPeriodStartDate() const;
    Date GetPayPeriodEndDate() const;

    void SetGrossPay(double grossPay);
    double GetGrossPay() const;

    void SetDeductions(double deductions);
    double GetDeductions() const;

    double GetNetPay() const;

    void SetField(
        const std::string& field,
        const std::string& value);

    std::string GetField(
        const std::string& field) const;

private:
    Date itsPayPeriodStartDate;
    Date itsPayPeriodEndDate;

    double itsGrossPay;
    double itsDeductions;

    std::map<std::string, std::string> itsFields;
};

#endif
