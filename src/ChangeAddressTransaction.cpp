#include "ChangeAddressTransaction.h"

#include "PayrollDomain/Employee.h"


ChangeAddressTransaction::ChangeAddressTransaction(
    int empid,
    std::string address)
    :
    ChangeEmployeeTransaction(empid),
    itsAddress(address)
{
}


ChangeAddressTransaction::~ChangeAddressTransaction()
{
}


void ChangeAddressTransaction::Change(Employee& e)
{
    e.SetAddress(itsAddress);
}
