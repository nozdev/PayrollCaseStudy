#ifndef PAYMENTSCHEDULE_H
#define PAYMENTSCHEDULE_H

#include "Date.h"

class PaymentSchedule
{
public:
    virtual ~PaymentSchedule();

    virtual bool IsPayDate(
        const Date& payDate) const = 0;

    virtual Date GetPayPeriodStartDate(
        const Date& payPeriodEndDate) const = 0;
};

#endif
