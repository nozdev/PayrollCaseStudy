#include "SalesReceipt.h"


SalesReceipt::SalesReceipt(
    Date date,
    double amount)
    :
    itsDate(date),
    itsAmount(amount)
{
}


Date SalesReceipt::GetDate() const
{
    return itsDate;
}


double SalesReceipt::GetAmount() const
{
    return itsAmount;
}
