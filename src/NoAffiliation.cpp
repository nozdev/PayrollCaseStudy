#include "NoAffiliation.h"


NoAffiliation::NoAffiliation()
{
}


double NoAffiliation::CalculateDeductions(
    Paycheck& pc) const
{
    return 0.0;
}


void NoAffiliation::AddServiceCharge(
    Date date,
    double amount)
{
    // No union membership.
    // Ignore service charges.
}
