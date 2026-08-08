#include "MonthlySchedule.h"

MonthlySchedule::~MonthlySchedule()
{
}

bool MonthlySchedule::IsPayDate(
    const Date& payDate) const
{
    Date nextDay = payDate + 1;

    return nextDay.GetMonth() != payDate.GetMonth();
}

Date MonthlySchedule::GetPayPeriodStartDate(
    const Date& payPeriodEndDate) const
{
    return Date(
        payPeriodEndDate.GetMonth(),
        1,
        payPeriodEndDate.GetYear());
}
