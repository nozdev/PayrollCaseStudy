#include "CommissionedClassification.h"
#include "PayrollDomain/Paycheck.h"
#include "SalesReceipt.h"

CommissionedClassification::CommissionedClassification(
    double salary,
    double commissionRate)
    : itsSalary(salary),
      itsRate(commissionRate)
{
}

CommissionedClassification::~CommissionedClassification()
{
    for (SalesReceipt* sr : itsSalesReceipts)
    {
        delete sr;
    }
}

double CommissionedClassification::CalculatePay(
    Paycheck& pc) const
{
    double totalPay = itsSalary;

    Date startDate =
        pc.GetPayPeriodStartDate();

    Date endDate =
        pc.GetPayPeriodEndDate();

    for (SalesReceipt* sr : itsSalesReceipts)
    {
        Date date = sr->GetDate();

        if (date < startDate ||
            date > endDate)
        {
            continue;
        }

        totalPay +=
            sr->GetAmount() * itsRate /100.00;
    }

    return totalPay;
}

void CommissionedClassification::AddSalesReceipt(
    SalesReceipt* sr)
{
    itsSalesReceipts.push_back(sr);
}

SalesReceipt* CommissionedClassification::GetSalesReceipt(
    const Date& date) const
{
    for (SalesReceipt* sr : itsSalesReceipts)
    {
        if (sr->GetDate() == date)
        {
            return sr;
        }
    }

    return nullptr;
}

double CommissionedClassification::GetSalary() const
{
    return itsSalary;
}

double CommissionedClassification::GetRate() const
{
    return itsRate;
}
