#include "ChangeMemberTransaction.h"
#include "UnionAffiliation.h"
#include "PayrollDatabase.h"


extern PayrollDatabase GpayrollDatabase;


ChangeMemberTransaction::
~ChangeMemberTransaction()
{
}


ChangeMemberTransaction::
ChangeMemberTransaction(
    int empId,
    int memberId,
    double dues)
:
ChangeAffiliationTransaction(empId),
itsMemberId(memberId),
itsDues(dues)
{
}


Affiliation*
ChangeMemberTransaction::GetAffiliation() const
{
    return new UnionAffiliation(
        itsMemberId,
        itsDues);
}


void ChangeMemberTransaction::RecordMembership(
    Employee* e)
{
    GpayrollDatabase.AddUnionMember(
        itsMemberId,
        e);
}
