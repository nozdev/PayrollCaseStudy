#include "ChangeCommissionedTransaction.h"

#include "CommissionedClassification.h"
#include "BiweeklySchedule.h"


ChangeCommissionedTransaction::
~ChangeCommissionedTransaction()
{
}


ChangeCommissionedTransaction::
ChangeCommissionedTransaction(
    int empid,
    double salary,
    double commissionRate)
:
ChangeClassificationTransaction(empid),
itsSalary(salary),
itsCommissionRate(commissionRate)
{
}


PaymentClassification*
ChangeCommissionedTransaction::
GetClassification() const
{
    return new CommissionedClassification(
        itsSalary,
        itsCommissionRate);
}


PaymentSchedule*
ChangeCommissionedTransaction::
GetSchedule() const
{
    return new BiweeklySchedule();
}
