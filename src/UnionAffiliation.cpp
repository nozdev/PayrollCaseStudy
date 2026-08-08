#include "UnionAffiliation.h"
#include "Paycheck.h"
#include "ServiceCharge.h"
#include <iostream>
UnionAffiliation::UnionAffiliation(
    int memberId,
    double dues)
    :
    itsMemberId(memberId),
    itsDues(dues)
{
}


ServiceCharge*
UnionAffiliation::GetServiceCharge(
    Date date) const
{
    for(ServiceCharge* sc : itsServiceCharges)
    {
        if(sc->GetDate() == date)
        {
            return sc;
        }
    }

    return nullptr;
}

double UnionAffiliation::GetDues() const
{
    return itsDues;
}

bool UnionAffiliation::IsMember(
    int memberId) const
{
    return itsMemberId == memberId;
}

void UnionAffiliation::AddServiceCharge(
    Date date,
    double amount)
{
    itsServiceCharges.push_back(
        new ServiceCharge(date, amount));
}


double UnionAffiliation::CalculateDeductions(
    Paycheck& pc) const
{
    double deductions = itsDues;

    Date startDate =
        pc.GetPayPeriodStartDate();

    Date endDate =
        pc.GetPayPeriodEndDate();

    std::cout << "Union dues = "
              << itsDues << std::endl;

    std::cout << "Pay period: "
              << startDate.GetMonth() << "/"
              << startDate.GetDay() << "/"
              << startDate.GetYear()
              << " -> "
              << endDate.GetMonth() << "/"
              << endDate.GetDay() << "/"
              << endDate.GetYear()
              << std::endl;

    for(ServiceCharge* charge : itsServiceCharges)
    {
        Date chargeDate = charge->GetDate();

        std::cout << "Service charge: "
                  << chargeDate.GetMonth() << "/"
                  << chargeDate.GetDay() << "/"
                  << chargeDate.GetYear()
                  << " amount="
                  << charge->GetAmount()
                  << std::endl;

        if(chargeDate >= startDate &&
           chargeDate <= endDate)
        {
            deductions += charge->GetAmount();

            std::cout << "  INCLUDED" << std::endl;
        }
        else
        {
            std::cout << "  EXCLUDED" << std::endl;
        }
    }

    std::cout << "TOTAL DEDUCTIONS = "
              << deductions << std::endl;

    return deductions;
}

UnionAffiliation::~UnionAffiliation()
{
    for(auto sc : itsServiceCharges)
    {
        delete sc;
    }
}
