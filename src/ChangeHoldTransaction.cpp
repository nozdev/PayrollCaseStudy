#include "ChangeHoldTransaction.h"

#include "HoldMethod.h"


ChangeHoldTransaction::ChangeHoldTransaction(int empid)
    :
    ChangePaymentMethodTransaction(empid)
{
}


ChangeHoldTransaction::~ChangeHoldTransaction()
{
}


PaymentMethod*
ChangeHoldTransaction::GetMethod() const
{
    return new HoldMethod();
}
