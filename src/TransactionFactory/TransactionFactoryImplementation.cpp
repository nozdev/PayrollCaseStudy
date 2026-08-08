#include "TransactionFactory/TransactionFactoryImplementation.h"
#include "ChangeMailTransaction.h"
#include "ChangeDirectTransaction.h"
#include "ChangeHoldTransaction.h"
#include "ChangeCommissionedTransaction.h"
#include "ChangeSalariedTransaction.h"
#include "ChangeAddressTransaction.h"
#include "ChangeMemberTransaction.h"
#include "ChangeNameTransaction.h"
#include "ChangeHourlyTransaction.h"
#include "AddSalariedEmployee.h"
#include "AddHourlyEmployee.h"
#include "AddCommissionedEmployee.h"
#include "DeleteEmployeeTransaction.h"
#include "TimeCardTransaction.h"
#include "SalesReceiptTransaction.h"
#include "ServiceChargeTransaction.h"
#include "PaydayTransaction.h"

Transaction*
TransactionFactoryImplementation::MakeChangeMailTransaction(
    int empid,
    const std::string& address)
{
    return new ChangeMailTransaction(
        empid,
        address);
}


Transaction*
TransactionFactoryImplementation::MakeChangeDirectTransaction(
    int empid,
    const std::string& bank,
    int account)
{
    return new ChangeDirectTransaction(
        empid,
        bank,
        account);
}


Transaction*
TransactionFactoryImplementation::MakeChangeHoldTransaction(
    int empid)
{
    return new ChangeHoldTransaction(
        empid);
}


Transaction*
TransactionFactoryImplementation::MakeChangeCommissionedTransaction(
    int empid,
    double salary,
    double rate)
{
    return new ChangeCommissionedTransaction(
        empid,
        salary,
        rate);
}


Transaction*
TransactionFactoryImplementation::MakeChangeSalariedTransaction(
    int empid,
    double salary)
{
    return new ChangeSalariedTransaction(
        empid,
        salary);
}


Transaction*
TransactionFactoryImplementation::MakeChangeAddressTransaction(
    int empid,
    const std::string& address)
{
    return new ChangeAddressTransaction(
        empid,
        address);
}

Transaction* TransactionFactoryImplementation::MakeChangeMemberTransaction(
    int empid,
    int memberId,
    double dues)
{
    return new ChangeMemberTransaction(
        empid,
        memberId,
        dues);
}

Transaction* TransactionFactoryImplementation::MakeChangeHourlyTransaction(
    int empid,
    double hourlyRate)
{
    return new ChangeHourlyTransaction(empid, hourlyRate);
}

Transaction* TransactionFactoryImplementation::MakeChangeNameTransaction(
    int empid,
    const std::string& name)
{
    return new ChangeNameTransaction(empid, name);
}

Transaction* TransactionFactoryImplementation::MakeAddSalariedTransaction(
    int empid,
    const std::string& name,
    const std::string& address,
    double salary)
{
    return new AddSalariedEmployee(empid, name, address, salary);
}

Transaction* TransactionFactoryImplementation::MakeAddHourlyTransaction(
    int empid,
    const std::string& name,
    const std::string& address,
    double hourlyRate)
{
    return new AddHourlyEmployee(empid, name, address, hourlyRate);
}

Transaction* TransactionFactoryImplementation::MakeAddCommissionedTransaction(
    int empid,
    const std::string& name,
    const std::string& address,
    double salary,
    double commissionRate)
{
    return new AddCommissionedEmployee(
        empid, name, address, salary, commissionRate);
}

Transaction* TransactionFactoryImplementation::MakeDeleteEmployeeTransaction(
    int empid)
{
    return new DeleteEmployeeTransaction(empid);
}

Transaction* TransactionFactoryImplementation::MakeTimeCardTransaction(
    const Date& date,
    double hours,
    int empid)
{
    return new TimeCardTransaction(date, hours,empid);
}

Transaction* TransactionFactoryImplementation::MakeSalesReceiptTransaction(
    int empid,
    const Date& date,
    double amount)
{
    return new SalesReceiptTransaction(empid, date, amount);
}

Transaction* TransactionFactoryImplementation::MakeServiceChargeTransaction(
    int memberId,
    const Date& date,
    double amount)
{
    return new ServiceChargeTransaction(memberId, date, amount);
}

Transaction* TransactionFactoryImplementation::MakePaydayTransaction(
    const Date& date)
{
    return new PaydayTransaction(date);
}
