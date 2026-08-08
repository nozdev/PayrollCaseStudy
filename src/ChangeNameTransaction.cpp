#include "ChangeNameTransaction.h"
#include "Employee.h"


ChangeNameTransaction::ChangeNameTransaction(
    int empid,
    std::string name)
    :
    ChangeEmployeeTransaction(empid),
    itsName(name)
{
}


ChangeNameTransaction::~ChangeNameTransaction()
{
}


void ChangeNameTransaction::Change(Employee& e)
{
    e.SetName(itsName);
}
