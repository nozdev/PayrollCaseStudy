#include "ServiceChargeTransaction.h"

#include "Employee.h"
#include "ServiceCharge.h"
#include "PayrollDatabase.h"
#include "UnionAffiliation.h"


extern PayrollDatabase GpayrollDatabase;


ServiceChargeTransaction::
~ServiceChargeTransaction()
{
}


ServiceChargeTransaction::
ServiceChargeTransaction(
    int memberId,
    Date date,
    double charge)
:
itsMemberId(memberId),
itsDate(date),
itsCharge(charge)
{
}


void ServiceChargeTransaction::Execute()
{
    Employee* e =
        GpayrollDatabase.GetUnionMember(
            itsMemberId);


    if(e != nullptr)
    {
        Affiliation* af =
            e->GetAffiliation();


        UnionAffiliation* uaf =
            dynamic_cast<UnionAffiliation*>(af);


        if(uaf != nullptr)
        {
            uaf->AddServiceCharge(
                itsDate,
                itsCharge);
        }
    }
}
