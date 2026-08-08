#ifndef WEEKLYSCHEDULE_H
#define WEEKLYSCHEDULE_H

#include "PaymentSchedule.h"
#include "Date.h"

class WeeklySchedule : public PaymentSchedule
{
public:
    virtual ~WeeklySchedule();

    virtual bool IsPayDate(
        const Date& payDate) const override;

    virtual Date GetPayPeriodStartDate(
        const Date& payPeriodEndDate) const override;
};

#endif
