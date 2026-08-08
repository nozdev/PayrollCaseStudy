#include "BiweeklySchedule.h"

BiweeklySchedule::~BiweeklySchedule()
{
}

bool BiweeklySchedule::IsPayDate(
    const Date& payDate) const
{
    // Biweekly employees are paid on Friday.
    //
    // The alternating-Friday calculation needs a
    // reference Friday. For now, this checks Friday.
    return payDate.GetDayOfWeek() == Date::friday;
}

Date BiweeklySchedule::GetPayPeriodStartDate(
    const Date& payPeriodEndDate) const
{
    // Biweekly = 14 days.
    // The end date counts as one of those 14 days,
    // so go back 13 days.
    return payPeriodEndDate - 13;
}
