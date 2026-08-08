#include "PayrollTest.h"
#include <iostream>
#include "Date.h"
using namespace std;
int main()
{

Date d(11,30,2001);
Date tomorrow = d + 1;

cout << tomorrow.GetMonth()
     << "/"
     << tomorrow.GetDay()
     << "/"
     << tomorrow.GetYear();

    PayrollTest test;

    test.TestPaySingleHourlyEmployeeOnWrongDate();
    test.TestPaySingleHourlyEmployeeOvertimeOneTimeCard();
    test.TestPaySingleHourlyEmployeeOneTimeCard();
    test.TestPaySingleHourlyEmployeeNoTimeCards();
    test.TestPaySingleSalariedEmployeeOnWrongDate();
    test.TestChangeMemberTransaction();
    test.TestChangeHourlyTransaction();
    test.TestAddServiceCharge();

    test.TestAddSalariedEmployee();
    test.TestAddHourlyEmployee();
    test.TestAddCommissionedEmployee();
    test.TestDeleteEmployee();
    test.TestChangeNameTransaction();
    test.TestChangeAddressTransaction();
    test.TestChangeHourlyTransaction();
    test.TestChangeSalariedTransaction();
    test.TestChangeCommissionedTransaction();
    test.TestChangeHoldTransaction();
    test.TestChangeMailTransaction();
    test.TestTimeCardTransaction();
    test.TestTimeCardForNonHourlyEmployee();
    test.TestSalesReceiptTransaction();
    test.TestSalesReceiptForNonCommissioned();
    test.TestSingleSalariedEmployeePayday();
    test.TestSingleHourlyEmployeePayday();
    test.TestHourlyEmployeeOvertimePayday();
    test.TestSingleCommissionedEmployeePayday();
    test.TestCommissionedSalesReceiptPayday();
    test.TestPaydayMultipleEmployees();

    test.TestPaydayMultipleHourlyEmployees();
    test.TestPaydayMultipleCommissionedEmployees();
    test.TestPaydayMultipleSalariedEmployees();
    test.TestHourlyUnionMemberServiceCharge();
    test.TestSalariedUnionMemberDues();
    test.TestPaySingleHourlyEmployeeWithTimeCardsSpanningTwoPayPeriods();
    test.TestPaySingleHourlyEmployeeTwoTimeCards();
    std::cout << "All tests passed\n";

    return 0;
}
