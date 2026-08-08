cmake_minimum_required(VERSION 3.10)

project(PayrollCaseStudy)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ============================================================
# Common include directory
# ============================================================

set(PROJECT_INCLUDE_DIR
    ${PROJECT_SOURCE_DIR}/include
)


# ============================================================
# PayrollDomain
#
# Core abstractions/domain objects.
# ============================================================

add_library(PayrollDomain

    src/PayrollDomain/Employee.cpp
    src/PayrollDomain/PaymentClassification.cpp
    src/PayrollDomain/PaymentMethod.cpp
    src/PayrollDomain/PaymentSchedule.cpp
    src/PayrollDomain/Paycheck.cpp
    src/PayrollDomain/Date.cpp
)

target_include_directories(PayrollDomain
    PUBLIC
        ${PROJECT_INCLUDE_DIR}
)


# ============================================================
# PayrollDatabase
# ============================================================

add_library(PayrollDatabase

    src/PayrollDatabase.cpp
)

target_include_directories(PayrollDatabase
    PUBLIC
        ${PROJECT_INCLUDE_DIR}
)

target_link_libraries(PayrollDatabase
    PUBLIC
        PayrollDomain
)


# ============================================================
# PayrollImplementation
#
# Concrete implementations of:
#   - PaymentClassification
#   - PaymentMethod
#   - PaymentSchedule
#   - Affiliation
#   - TimeCard
#   - SalesReceipt
# ============================================================

add_library(PayrollImplementation

    # Classifications
    src/HourlyClassification.cpp
    src/SalariedClassification.cpp
    src/CommissionedClassification.cpp

    # Schedules
    src/WeeklySchedule.cpp
    src/MonthlySchedule.cpp
    src/BiweeklySchedule.cpp

    # Payment Methods
    src/DirectMethod.cpp
    src/HoldMethod.cpp
    src/MailMethod.cpp

    # Affiliations
    src/NoAffiliation.cpp
    src/UnionAffiliation.cpp

    # Supporting domain objects
    src/TimeCard.cpp
    src/SalesReceipt.cpp
)

target_include_directories(PayrollImplementation
    PUBLIC
        ${PROJECT_INCLUDE_DIR}
)

target_link_libraries(PayrollImplementation
    PUBLIC
        PayrollDomain
)


# ============================================================
# TransactionImplementation
#
# Concrete Transaction classes.
# ============================================================

add_library(TransactionImplementation

    # Add employee transactions
    src/AddEmployeeTransaction.cpp
    src/AddHourlyEmployee.cpp
    src/AddSalariedEmployee.cpp
    src/AddCommissionedEmployee.cpp

    # Delete employee
    src/DeleteEmployeeTransaction.cpp

    # Base employee changes
    src/ChangeEmployeeTransaction.cpp
    src/ChangeNameTransaction.cpp
    src/ChangeAddressTransaction.cpp

    # Classification changes
    src/ChangeClassificationTransaction.cpp
    src/ChangeHourlyTransaction.cpp
    src/ChangeSalariedTransaction.cpp
    src/ChangeCommissionedTransaction.cpp

    # Payment method changes
    src/ChangePaymentMethodTransaction.cpp
    src/ChangeDirectTransaction.cpp
    src/ChangeHoldTransaction.cpp
    src/ChangeMailTransaction.cpp

    # Affiliation changes
    src/ChangeAffiliationTransaction.cpp
    src/ChangeMemberTransaction.cpp

    # Time cards
    src/TimeCardTransaction.cpp

    # Sales receipts
    src/SalesReceiptTransaction.cpp

    # Service charges
    src/ServiceChargeTransaction.cpp

    # Payroll
    src/PaydayTransaction.cpp
)


add_library(TransactionFactory
    src/TransactionFactory/TransactionFactoryImplementation.cpp
    src/TransactionFactory/TransactionFactory.cpp
)

target_include_directories(TransactionFactory
    PUBLIC
        ${PROJECT_INCLUDE_DIR}
)

target_link_libraries(TransactionFactory
    PUBLIC
        TransactionImplementation
        PayrollDomain
)

target_include_directories(TransactionImplementation
    PUBLIC
        ${PROJECT_INCLUDE_DIR}
)

target_link_libraries(TransactionImplementation
    PUBLIC
        PayrollDomain
        PayrollDatabase
        PayrollImplementation
)


# ============================================================
# PayrollTest
# ============================================================

add_executable(PayrollTest

    main.cpp

    tests/PayrollTest.cpp
)

target_include_directories(PayrollTest
    PRIVATE
        ${PROJECT_INCLUDE_DIR}
)

target_link_libraries(PayrollTest
    PRIVATE
        PayrollDomain
        PayrollDatabase
        PayrollImplementation
        TransactionImplementation
        TransactionFactory
)


# ============================================================
# Optional: warnings
# ============================================================

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(PayrollDomain PRIVATE -Wall -Wextra)
    target_compile_options(PayrollDatabase PRIVATE -Wall -Wextra)
    target_compile_options(PayrollImplementation PRIVATE -Wall -Wextra)
    target_compile_options(TransactionImplementation PRIVATE -Wall -Wextra)
    target_compile_options(PayrollTest PRIVATE -Wall -Wextra)
endif()
