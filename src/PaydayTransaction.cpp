#include "PaydayTransaction.h"

#include "Employee.h"
#include "PayrollDatabase.h"
#include "Paycheck.h"

extern PayrollDatabase GpayrollDatabase;

PaydayTransaction::PaydayTransaction(
    const Date& payDate)
    : itsPayDate(payDate)
{
}

PaydayTransaction::~PaydayTransaction()
{
    for (auto& entry : itsPaychecks)
    {
        delete entry.second;
    }
}

void PaydayTransaction::Execute()
{
    auto employees =
        GpayrollDatabase.GetEmployees();

    for (auto& entry : employees)
    {
        int empId = entry.first;

        Employee* e = entry.second;

        if (e && e->IsPayDate(itsPayDate))
        {
            Date payPeriodStart =
                e->GetPayPeriodStartDate(itsPayDate);

            Paycheck* pc =
                new Paycheck(
                    payPeriodStart,
                    itsPayDate);

            itsPaychecks[empId] = pc;

            e->PayDay(*pc);
        }
    }
}

Paycheck* PaydayTransaction::GetPaycheck(
    int empId) const
{
    auto it = itsPaychecks.find(empId);

    if (it != itsPaychecks.end())
    {
        return it->second;
    }

    return nullptr;
}
