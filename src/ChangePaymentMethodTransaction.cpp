#include "ChangePaymentMethodTransaction.h"

#include "PayrollDomain/Employee.h"
#include "PayrollDomain/PaymentMethod.h"


ChangePaymentMethodTransaction::
ChangePaymentMethodTransaction(int empid)
    :
    ChangeEmployeeTransaction(empid)
{
}


ChangePaymentMethodTransaction::
~ChangePaymentMethodTransaction()
{
}


void ChangePaymentMethodTransaction::Change(Employee& e)
{
    e.SetMethod(GetMethod());
}
