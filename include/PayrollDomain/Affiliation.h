#ifndef AFFILIATION_H
#define AFFILIATION_H

#include "Date.h"

class Paycheck;

class Affiliation
{
public:

    virtual ~Affiliation(){}

    virtual double CalculateDeductions(
        Paycheck& pc) const = 0;

    virtual void AddServiceCharge(
        Date date,
        double amount) = 0;
};

#endif
