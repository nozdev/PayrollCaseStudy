#include "ChangeAffiliationTransaction.h"
#include "Employee.h"


ChangeAffiliationTransaction::
~ChangeAffiliationTransaction()
{
}


ChangeAffiliationTransaction::
ChangeAffiliationTransaction(
    int empId)
:
ChangeEmployeeTransaction(empId)
{
}


void ChangeAffiliationTransaction::Change(
    Employee& e)
{
    RecordMembership(&e);

    e.SetAffiliation(
        GetAffiliation());
}
