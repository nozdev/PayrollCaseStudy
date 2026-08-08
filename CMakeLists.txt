cmake_minimum_required(VERSION 3.10)

project(PayrollCaseStudy)

set(CMAKE_CXX_STANDARD 17)


include_directories(include)


add_executable(
    PayrollTest

    main.cpp
    src/UnionAffiliation.cpp
    src/ChangeMemberTransaction.cpp
    src/ChangeAffiliationTransaction.cpp
    src/ChangeMemberTransaction.cpp
    src/ServiceChargeTransaction.cpp
    src/UnionAffiliation.cpp
    src/NoAffiliation.cpp
    src/PaydayTransaction.cpp
    src/SalesReceipt.cpp
    src/SalesReceiptTransaction.cpp
    src/TimeCard.cpp
    src/TimeCardTransaction.cpp
    src/MailMethod.cpp
    src/ChangeMailTransaction.cpp
    src/DirectMethod.cpp
    src/ChangeDirectTransaction.cpp
    src/ChangePaymentMethodTransaction.cpp
    src/ChangeHoldTransaction.cpp
    src/Date.cpp
    src/Paycheck.cpp
    src/Employee.cpp
    src/PaymentSchedule.cpp
    src/PaymentClassification.cpp
    src/HourlyClassification.cpp
    src/WeeklySchedule.cpp
    src/MonthlySchedule.cpp
    src/SalariedClassification.cpp
    src/PaymentMethod.cpp
    src/HoldMethod.cpp
    src/Paycheck.cpp
    src/AddEmployeeTransaction.cpp
    src/PayrollDatabase.cpp
    src/AddHourlyEmployee.cpp
    src/AddSalariedEmployee.cpp
    src/BiweeklySchedule.cpp
    src/AddCommissionedEmployee.cpp
    src/CommissionedClassification.cpp
    src/DeleteEmployeeTransaction.cpp
    src/ChangeEmployeeTransaction.cpp
    src/ChangeNameTransaction.cpp
    src/ChangeAddressTransaction.cpp
    src/ChangeHourlyTransaction.cpp
    src/ChangeClassificationTransaction.cpp
    src/ChangeSalariedTransaction.cpp
    src/ChangeCommissionedTransaction.cpp
    tests/PayrollTest.cpp
)
