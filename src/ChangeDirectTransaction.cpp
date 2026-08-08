#include "ChangeDirectTransaction.h"

#include "DirectMethod.h"


ChangeDirectTransaction::ChangeDirectTransaction(
    int empid,
    std::string bank,
    int account)
    :
    ChangePaymentMethodTransaction(empid),
    itsBank(bank),
    itsAccount(account)
{
}


ChangeDirectTransaction::~ChangeDirectTransaction()
{
}


PaymentMethod*
ChangeDirectTransaction::GetMethod() const
{
    return new DirectMethod(
        itsBank,
        itsAccount);
}
