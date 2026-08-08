#include "SalesReceiptTransaction.h"
#include "SalesReceipt.h"
#include "PayrollDatabase.h"
#include "Employee.h"
#include "CommissionedClassification.h"


extern PayrollDatabase GpayrollDatabase;


SalesReceiptTransaction::SalesReceiptTransaction(
    int empid,
    Date date,
    double amount)
    :
    itsEmpid(empid),
    itsDate(date),
    itsAmount(amount)
{
}


SalesReceiptTransaction::~SalesReceiptTransaction()
{
}


void SalesReceiptTransaction::Execute()
{
    Employee* e =
        GpayrollDatabase.GetEmployee(itsEmpid);

    if (e)
    {
        PaymentClassification* pc =
            e->GetClassification();

        CommissionedClassification* cc =
            dynamic_cast<CommissionedClassification*>(pc);

        if (cc)
        {
            cc->AddSalesReceipt(
                new SalesReceipt(
                    itsDate,
                    itsAmount));
        }
        else
        {
            throw "Tried to add sales receipt to non-commissioned employee";
        }
    }
    else
    {
        throw "No such employee.";
    }
}
