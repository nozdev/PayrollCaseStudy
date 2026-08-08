#ifndef PAYROLLTEST_H
#define PAYROLLTEST_H
#include "PaydayTransaction.h"

class PayrollTest
{
public:
    void TestPaySingleHourlyEmployeeOnWrongDate();
    void TestPaySingleHourlyEmployeeOvertimeOneTimeCard();
    void TestPaySingleHourlyEmployeeOneTimeCard();
    void TestPaySingleHourlyEmployeeNoTimeCards();
    void TestPaySingleSalariedEmployeeOnWrongDate();
    void TestPaySingleSalariedEmployee();
    void TestChangeMemberTransaction();
    void TestAddServiceCharge();

    void ValidatePaycheck(PaydayTransaction& pt,int empid,const Date& payDate,double pay);

    void TestDeleteEmployee();
    void TestAddSalariedEmployee();
    void TestAddHourlyEmployee();
    void TestAddCommissionedEmployee();
    void TestChangeNameTransaction();
    void TestChangeAddressTransaction();
    void TestChangeHourlyTransaction();
    void TestChangeSalariedTransaction();
    void TestChangeCommissionedTransaction();
    void TestChangeHoldTransaction();
    void TestChangeDirectTransaction();
    void TestChangeMailTransaction();
    void TestTimeCardTransaction();
    void TestTimeCardForNonHourlyEmployee();
    void TestSalesReceiptTransaction();
    void TestSalesReceiptForNonCommissioned();
    void TestSingleSalariedEmployeePayday();
    void TestSingleHourlyEmployeePayday();
    void TestHourlyEmployeeOvertimePayday();
    void TestSingleCommissionedEmployeePayday();
    void TestCommissionedSalesReceiptPayday();
    void TestPaydayMultipleEmployees();
    void TestPaydayMultipleSalariedEmployees();
    void TestPaydayMultipleCommissionedEmployees();
    void TestPaydayMultipleHourlyEmployees();
    void TestHourlyUnionMemberServiceCharge();
    void TestSalariedUnionMemberDues();
    void TestPaySingleHourlyEmployeeWithTimeCardsSpanningTwoPayPeriods();
    void TestPaySingleHourlyEmployeeTwoTimeCards();
};

#endif

