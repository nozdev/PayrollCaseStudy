#include "ChangeSalariedTransaction.h"

#include "SalariedClassification.h"
#include "MonthlySchedule.h"


ChangeSalariedTransaction::~ChangeSalariedTransaction()
{
}


ChangeSalariedTransaction::
ChangeSalariedTransaction(
    int empid,
    double salary)
:
ChangeClassificationTransaction(empid),
itsSalary(salary)
{
}


PaymentClassification*
ChangeSalariedTransaction::GetClassification() const
{
    return new SalariedClassification(
        itsSalary);
}


PaymentSchedule*
ChangeSalariedTransaction::GetSchedule() const
{
    return new MonthlySchedule();
}
