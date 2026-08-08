#ifndef MONTHLYSCHEDULE_H
#define MONTHLYSCHEDULE_H

#include "PayrollDomain/PaymentSchedule.h"
#include "PayrollDomain/Date.h"

class MonthlySchedule : public PaymentSchedule
{
public:
    virtual ~MonthlySchedule();

    virtual bool IsPayDate(
        const Date& payDate) const override;

    virtual Date GetPayPeriodStartDate(
        const Date& payPeriodEndDate) const override;
};

#endif
