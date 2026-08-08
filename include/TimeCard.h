#ifndef TIMECARD_H
#define TIMECARD_H

#include "Date.h"

class TimeCard
{
public:
    TimeCard(const Date& date, double hours);
    virtual ~TimeCard();

    Date GetDate() const;
    double GetHours() const;

private:
    Date itsDate;
    double itsHours;
};

#endif
