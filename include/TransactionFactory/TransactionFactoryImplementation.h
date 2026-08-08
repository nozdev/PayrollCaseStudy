#ifndef TRANSACTION_FACTORY_IMPLEMENTATION_H
#define TRANSACTION_FACTORY_IMPLEMENTATION_H

#include "TransactionFactory/TransactionFactory.h"

class TransactionFactoryImplementation : public TransactionFactory
{
public:
    TransactionFactoryImplementation() = default;
    ~TransactionFactoryImplementation() override = default;

    Transaction* MakeChangeMailTransaction(
        int empid,
        const std::string& address) override;

    Transaction* MakeChangeDirectTransaction(
        int empid,
        const std::string& bank,
        int account) override;

    Transaction* MakeChangeHoldTransaction(
        int empid) override;

    Transaction* MakeChangeCommissionedTransaction(
        int empid,
        double salary,
        double rate) override;

    Transaction* MakeChangeSalariedTransaction(
        int empid,
        double salary) override;

    Transaction* MakeChangeAddressTransaction(
        int empid,
        const std::string& address) override;

    Transaction* MakeChangeMemberTransaction(
        int empid,
        int memberId,
        double dues) override;

    Transaction* MakeChangeHourlyTransaction(
        int empid,
        double hourlyRate) override;

    Transaction* MakeAddSalariedTransaction(
        int empid,
        const std::string& name,
        const std::string& address,
        double salary) override;

    Transaction* MakeAddHourlyTransaction(
        int empid,
        const std::string& name,
        const std::string& address,
        double hourlyRate) override;

    Transaction* MakeAddCommissionedTransaction(
        int empid,
        const std::string& name,
        const std::string& address,
        double salary,
        double commissionRate) override;

    Transaction* MakeDeleteEmployeeTransaction(
        int empid) override;

    Transaction* MakeTimeCardTransaction(
        const Date& date,
        double hours,
        int empid) override;

    Transaction* MakeSalesReceiptTransaction(
        int empid,
        const Date& date,
        double amount) override;

    Transaction* MakeServiceChargeTransaction(
        int memberId,
        const Date& date,
        double amount) override;

    Transaction* MakePaydayTransaction(
        const Date& date) override;

    Transaction* MakeChangeNameTransaction(
        int empid,
        const std::string& name) override;
};

#endif
