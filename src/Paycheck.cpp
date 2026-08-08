#include "Paycheck.h"

Paycheck::Paycheck(
    const Date& payPeriodStartDate,
    const Date& payPeriodEndDate)
    : itsPayPeriodStartDate(payPeriodStartDate),
      itsPayPeriodEndDate(payPeriodEndDate),
      itsGrossPay(0.0),
      itsDeductions(0.0)
{
}

Paycheck::~Paycheck()
{
}

Date Paycheck::GetPayPeriodStartDate() const
{
    return itsPayPeriodStartDate;
}

Date Paycheck::GetPayPeriodEndDate() const
{
    return itsPayPeriodEndDate;
}

void Paycheck::SetGrossPay(double grossPay)
{
    itsGrossPay = grossPay;
}

double Paycheck::GetGrossPay() const
{
    return itsGrossPay;
}

void Paycheck::SetDeductions(double deductions)
{
    itsDeductions = deductions;
}

double Paycheck::GetDeductions() const
{
    return itsDeductions;
}

double Paycheck::GetNetPay() const
{
    return itsGrossPay - itsDeductions;
}

void Paycheck::SetField(
    const std::string& field,
    const std::string& value)
{
    itsFields[field] = value;
}

std::string Paycheck::GetField(
    const std::string& field) const
{
    auto it = itsFields.find(field);

    if (it != itsFields.end())
        return it->second;

    return "";
}
