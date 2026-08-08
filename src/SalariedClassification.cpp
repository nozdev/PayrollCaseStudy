#include "SalariedClassification.h"
#include "Paycheck.h"

SalariedClassification::SalariedClassification(
    double salary)
    :
    itsSalary(salary)
{
}

SalariedClassification::~SalariedClassification()
{
}

double SalariedClassification::GetSalary() const
{
    return itsSalary;
}

double SalariedClassification::CalculatePay(
    Paycheck& pc) const
{
    return itsSalary;
}

