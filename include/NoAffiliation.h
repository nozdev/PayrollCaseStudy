#ifndef NOAFFILIATION_H
#define NOAFFILIATION_H

#include "Affiliation.h"


class NoAffiliation : public Affiliation
{
public:

    NoAffiliation();

    double CalculateDeductions(
        Paycheck& pc) const override;


    void AddServiceCharge(
        Date date,
        double amount) override;

};

#endif
