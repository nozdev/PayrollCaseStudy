#ifndef BIWEEKLYSCHEDULE_H
#define BIWEEKLYSCHEDULE_H

#include "PaymentSchedule.h"
#include "Date.h"

class BiweeklySchedule : public PaymentSchedule
{
public:
    virtual ~BiweeklySchedule();

    virtual bool IsPayDate(
        const Date& payDate) const override;

    virtual Date GetPayPeriodStartDate(
        const Date& payPeriodEndDate) const override;
};

#endif
