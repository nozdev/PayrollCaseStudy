#include "Employee.h"

#include "NoAffiliation.h"
#include "PaymentClassification.h"
#include "PaymentSchedule.h"
#include "PaymentMethod.h"
#include "Paycheck.h"


Employee::~Employee()
{
    delete itsClassification;
    delete itsSchedule;
    delete itsPaymentMethod;
    delete itsAffiliation;
}


Employee::Employee(
    int empid,
    std::string name,
    std::string address)
    :
    itsEmpid(empid),
    itsName(name),
    itsAddress(address),
    itsAffiliation(new NoAffiliation()),
    itsClassification(nullptr),
    itsSchedule(nullptr),
    itsPaymentMethod(nullptr)
{
}


void Employee::SetName(std::string name)
{
    itsName = name;
}


void Employee::SetAddress(std::string address)
{
    itsAddress = address;
}


void Employee::SetClassification(
    PaymentClassification* pc)
{
    delete itsClassification;
    itsClassification = pc;
}


void Employee::SetSchedule(
    PaymentSchedule* ps)
{
    delete itsSchedule;
    itsSchedule = ps;
}


void Employee::SetMethod(
    PaymentMethod* pm)
{
    delete itsPaymentMethod;
    itsPaymentMethod = pm;
}


void Employee::SetAffiliation(
    Affiliation* af)
{
    delete itsAffiliation;
    itsAffiliation = af;
}


bool Employee::IsPayDate(
    const Date& payDate) const
{
    return itsSchedule->IsPayDate(payDate);
}

Date Employee::GetPayPeriodStartDate(
    const Date& payDate) const
{
    return itsSchedule->GetPayPeriodStartDate(payDate);
}

void Employee::PayDay(
    Paycheck& pc)
{
    double grossPay =
        itsClassification->CalculatePay(pc);


    double deductions =
        itsAffiliation->CalculateDeductions(pc);


    double netPay =
        grossPay - deductions;


    pc.SetGrossPay(grossPay);

    pc.SetDeductions(deductions);

    itsPaymentMethod->Pay(pc);
}
int Employee::GetEmpId() const
{
    return itsEmpid;
}


std::string Employee::GetName() const
{
    return itsName;
}


std::string Employee::GetAddress() const
{
    return itsAddress;
}


PaymentClassification* Employee::GetClassification() const
{
    return itsClassification;
}


PaymentSchedule* Employee::GetSchedule() const
{
    return itsSchedule;
}


PaymentMethod* Employee::GetMethod() const
{
    return itsPaymentMethod;
}


Affiliation* Employee::GetAffiliation() const
{
    return itsAffiliation;
}
