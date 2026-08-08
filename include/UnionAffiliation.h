#ifndef UNIONAFFILIATION_H
#define UNIONAFFILIATION_H

#include "PayrollDomain/Affiliation.h"
#include "PayrollDomain/Date.h"
#include "ServiceCharge.h"

#include <vector>

class UnionAffiliation : public Affiliation
{
public:

    double GetDues() const;
    virtual ~UnionAffiliation();

    UnionAffiliation(
        int memberId,
        double dues);

    bool IsMember(
        int memberId) const;

    void AddServiceCharge(
        Date date,
        double amount) override;

    ServiceCharge* GetServiceCharge(
        Date date) const;

    double CalculateDeductions(
        Paycheck& pc) const override;

private:

    int itsMemberId;
    double itsDues;

    std::vector<ServiceCharge*> itsServiceCharges;
};

#endif
