#include "WeeklySchedule.h"

WeeklySchedule::~WeeklySchedule()
{
}

bool WeeklySchedule::IsPayDate(
    const Date& payDate) const
{
    return payDate.GetDayOfWeek() == Date::friday;
}

Date WeeklySchedule::GetPayPeriodStartDate(
    const Date& payPeriodEndDate) const
{
    // Weekly pay period:
    // Saturday through Friday.
    return payPeriodEndDate - 6;
}
