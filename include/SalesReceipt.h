#ifndef SALESRECEIPT_H
#define SALESRECEIPT_H

#include "PayrollDomain/Date.h"


class SalesReceipt
{
public:

    SalesReceipt(
        Date date,
        double amount);


    Date GetDate() const;

    double GetAmount() const;


private:

    Date itsDate;
    double itsAmount;
};


#endif
