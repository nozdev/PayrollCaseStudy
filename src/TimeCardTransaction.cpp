#include "TimeCardTransaction.h"

#include "Employee.h"
#include "PayrollDatabase.h"
#include "HourlyClassification.h"
#include "TimeCard.h"
#include "PaymentClassification.h"

extern PayrollDatabase GpayrollDatabase;

TimeCardTransaction::~TimeCardTransaction()
{
}

TimeCardTransaction::TimeCardTransaction(
    const Date& date,
    double hours,
    int empId)
    : itsEmpId(empId),
      itsDate(date),
      itsHours(hours)
{
}

void TimeCardTransaction::Execute()
{
    Employee* e =
        GpayrollDatabase.GetEmployee(itsEmpId);

    if (e)
    {
        PaymentClassification* pc =
            e->GetClassification();

        HourlyClassification* hc =
            dynamic_cast<HourlyClassification*>(pc);

        if (hc)
        {
            hc->AddTimeCard(
                new TimeCard(
                    itsDate,
                    itsHours));
        }
        else
        {
            throw "Tried to add timecard to non-hourly employee";
        }
    }
    else
    {
        throw "No such employee.";
    }
}
