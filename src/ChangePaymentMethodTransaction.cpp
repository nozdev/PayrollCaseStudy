#include "ChangePaymentMethodTransaction.h"

#include "Employee.h"
#include "PaymentMethod.h"


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
