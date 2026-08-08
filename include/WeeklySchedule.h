#ifndef WEEKLYSCHEDULE_H
#define WEEKLYSCHEDULE_H

#include "PayrollDomain/PaymentSchedule.h"
#include "PayrollDomain/Date.h"

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
