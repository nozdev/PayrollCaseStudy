#ifndef SERVICECHARGE_H
#define SERVICECHARGE_H

#include "Date.h"

class ServiceCharge
{
public:

    ServiceCharge(
        Date date,
        double amount)
        :
        itsDate(date),
        itsAmount(amount)
    {
    }


    Date GetDate() const
    {
        return itsDate;
    }


    double GetAmount() const
    {
        return itsAmount;
    }


private:

    Date itsDate;
    double itsAmount;
};

#endif