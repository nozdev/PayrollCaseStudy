#include "PayrollTest.h"
#include <iostream>
#include "PayrollDomain/Date.h"
#include "TransactionFactory/TransactionFactory.h"
#include "TransactionFactory/TransactionFactoryImplementation.h"

using namespace std;
int main()
{

    TransactionFactoryImplementation factory;
    TransactionFactory::SetFactory(&factory);

 
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
