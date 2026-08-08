#include "ChangeMailTransaction.h"

#include "MailMethod.h"


ChangeMailTransaction::ChangeMailTransaction(
    int empid,
    std::string address)
    :
    ChangePaymentMethodTransaction(empid),
    itsAddress(address)
{
}


ChangeMailTransaction::~ChangeMailTransaction()
{
}


PaymentMethod*
ChangeMailTransaction::GetMethod() const
{
    return new MailMethod(itsAddress);
}
