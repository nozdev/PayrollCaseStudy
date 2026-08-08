#include "TimeCard.h"

TimeCard::TimeCard(
    const Date& date,
    double hours)
    : itsDate(date),
      itsHours(hours)
{
}

TimeCard::~TimeCard()
{
}

Date TimeCard::GetDate() const
{
    return itsDate;
}

double TimeCard::GetHours() const
{
    return itsHours;
}
