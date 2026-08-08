#ifndef TRANSACTION_FACTORY_H
#define TRANSACTION_FACTORY_H

#include <string>

#include "PayrollDomain/Transaction.h"
#include "PayrollDomain/Date.h"

class TransactionFactory
{
private:
    static TransactionFactory* transactionFactory;

public:
    virtual ~TransactionFactory() = default;

    static void SetFactory(TransactionFactory* factory);

    static TransactionFactory& GetFactory();

    virtual Transaction* MakeChangeMailTransaction(
        int empid,
        const std::string& address) = 0;

    virtual Transaction* MakeChangeDirectTransaction(
        int empid,
        const std::string& bank,
        int account) = 0;

    virtual Transaction* MakeChangeHoldTransaction(
        int empid) = 0;

    virtual Transaction* MakeChangeCommissionedTransaction(
        int empid,
        double salary,
        double rate) = 0;

    virtual Transaction* MakeChangeSalariedTransaction(
        int empid,
        double salary) = 0;

    virtual Transaction* MakeChangeAddressTransaction(
        int empid,
        const std::string& address) = 0;

    virtual Transaction* MakeChangeMemberTransaction(
        int empid,
        int memberId,
        double dues) = 0;

    virtual Transaction* MakeChangeHourlyTransaction(
        int empid,
        double hourlyRate) = 0;

    virtual Transaction* MakeAddSalariedTransaction(
        int empid,
        const std::string& name,
        const std::string& address,
        double salary) = 0;

    virtual Transaction* MakeAddHourlyTransaction(
        int empid,
        const std::string& name,
        const std::string& address,
        double hourlyRate) = 0;

    virtual Transaction* MakeAddCommissionedTransaction(
        int empid,
        const std::string& name,
        const std::string& address,
        double salary,
        double commissionRate) = 0;

    virtual Transaction* MakeDeleteEmployeeTransaction(
        int empid) = 0;

    virtual Transaction* MakeTimeCardTransaction(
        const Date& date,
        double hours,
        int empid) = 0;

    virtual Transaction* MakeSalesReceiptTransaction(
        int empid,
        const Date& date,
        double amount) = 0;

    virtual Transaction* MakeServiceChargeTransaction(
        int memberId,
        const Date& date,
        double amount) = 0;

    virtual Transaction* MakePaydayTransaction(
        const Date& date) = 0;

    virtual Transaction* MakeChangeNameTransaction(
        int empid,
        const std::string& name) = 0;

};

#endif
