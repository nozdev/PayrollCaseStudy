#include "PayrollTest.h"

#include "AddSalariedEmployee.h"
#include "AddHourlyEmployee.h"
#include "AddCommissionedEmployee.h"
#include "PayrollDatabase.h"
#include "PayrollDomain/Employee.h"
#include "UnionAffiliation.h"
#include "SalariedClassification.h"
#include "CommissionedClassification.h"
#include "HourlyClassification.h"
#include "DeleteEmployeeTransaction.h"
#include "MonthlySchedule.h"
#include "WeeklySchedule.h"
#include "BiweeklySchedule.h"
#include "ChangeNameTransaction.h"
#include "ChangeEmployeeTransaction.h"
#include "ChangeAddressTransaction.h"
#include "ChangeHourlyTransaction.h"
#include "ChangeClassificationTransaction.h"
#include "ChangeSalariedTransaction.h"
#include "ChangeCommissionedTransaction.h"
#include "ChangeHoldTransaction.h"
#include "HoldMethod.h"
#include "ChangeDirectTransaction.h"
#include "DirectMethod.h"
#include "ChangeMailTransaction.h"
#include "MailMethod.h"
#include "TimeCardTransaction.h"
#include "TimeCard.h"
#include "SalesReceiptTransaction.h"
#include "SalesReceipt.h"
#include "PaydayTransaction.h"
#include "TransactionFactory/TransactionFactory.h"
#include "PayrollDomain/Paycheck.h"
#include "ChangeMemberTransaction.h"
#include "ServiceChargeTransaction.h"
#include <iostream>
#include <cmath>
#include <cassert>
#include <iostream>

void assertEquals(
    double expected,
    double actual,
    double delta)
{
    assert(std::fabs(expected - actual) < delta);
}

extern PayrollDatabase GpayrollDatabase;
using namespace std;


void PayrollTest::TestAddSalariedEmployee()
{
    int empId = 1;

    Transaction* t =
        TransactionFactory::GetFactory()
            .MakeAddSalariedTransaction(
                empId,
                "Bob",
                "Home",
                1000.00);
    t->Execute();

    Employee* e =
        GpayrollDatabase.GetEmployee(empId);

    assert(e);
    assert("Bob" == e->GetName());

    PaymentClassification* pc =
        e->GetClassification();

    SalariedClassification* sc =
        dynamic_cast<SalariedClassification*>(pc);

    assert(sc);

    assertEquals(
        1000.00,
        sc->GetSalary(),
        0.001);

    PaymentSchedule* ps =
        e->GetSchedule();

    MonthlySchedule* ms =
        dynamic_cast<MonthlySchedule*>(ps);

    assert(ms);

    PaymentMethod* pm =
        e->GetMethod();

    HoldMethod* hm =
        dynamic_cast<HoldMethod*>(pm);

    assert(hm);
}

void PayrollTest::TestDeleteEmployee()
{
    std::cerr << "TestDeleteEmployee" << std::endl;

    int empId = 3;

    Transaction* t =
        TransactionFactory::GetFactory()
            .MakeAddCommissionedTransaction(
                empId,
                "Lance",
                "Home",
                2500.00,
                3.2);

    t->Execute();

    {
        Employee* e =
            GpayrollDatabase.GetEmployee(empId);

        assert(e);
    }

    delete t;

    Transaction* dt =
        TransactionFactory::GetFactory()
            .MakeDeleteEmployeeTransaction(empId);

    dt->Execute();

    {
        Employee* e =
            GpayrollDatabase.GetEmployee(empId);

        assert(e == 0);
    }

    delete dt;
}

void PayrollTest::TestPaydayMultipleHourlyEmployees()
{
    std::cerr << "TestPaydayMultipleHourlyEmployees" << std::endl;

    int empId1 = 25;
    int empId2 = 26;

    // ---------------------------------------------------------
    // Add first hourly employee
    // ---------------------------------------------------------

    Transaction* e1 =
        TransactionFactory::GetFactory()
            .MakeAddHourlyTransaction(
                empId1,
                "Bob",
                "Home",
                15.00);

    e1->Execute();

    delete e1;

    // ---------------------------------------------------------
    // Add second hourly employee
    // ---------------------------------------------------------

    Transaction* e2 =
        TransactionFactory::GetFactory()
            .MakeAddHourlyTransaction(
                empId2,
                "Alice",
                "Home",
                20.00);

    e2->Execute();

    delete e2;

    // ---------------------------------------------------------
    // Add time card for first employee
    // ---------------------------------------------------------

    Date payDate(11, 9, 2001);

    Transaction* tc1 =
        TransactionFactory::GetFactory()
            .MakeTimeCardTransaction(
                payDate,
                8.0,
                empId1);

    tc1->Execute();

    delete tc1;

    // ---------------------------------------------------------
    // Add time card for second employee
    // ---------------------------------------------------------

    Transaction* tc2 =
        TransactionFactory::GetFactory()
            .MakeTimeCardTransaction(
                payDate,
                10.0,
                empId2);

    tc2->Execute();

    delete tc2;

    // ---------------------------------------------------------
    // Run payroll
    // ---------------------------------------------------------

    Transaction* pt =
        TransactionFactory::GetFactory()
            .MakePaydayTransaction(payDate);

    pt->Execute();

    // ---------------------------------------------------------
    // Convert Transaction* to PaydayTransaction*
    // ---------------------------------------------------------

    PaydayTransaction* payday =
        dynamic_cast<PaydayTransaction*>(pt);

    assert(payday != nullptr);

    // ---------------------------------------------------------
    // Validate first employee
    // $15/hour * 8 hours = $120
    // ---------------------------------------------------------

    ValidatePaycheck(
        *payday,
        empId1,
        payDate,
        120.00);

    // ---------------------------------------------------------
    // Validate second employee
    // $20/hour * 10 hours = $200
    //
    // If your payroll rules include overtime:
    // 8 regular hours = $160
    // 2 overtime hours = $60
    // Total = $220
    // ---------------------------------------------------------

    ValidatePaycheck(
        *payday,
        empId2,
        payDate,
        220.00);

    delete pt;
}

void PayrollTest::TestAddServiceCharge()
{
    std::cerr << "TestAddServiceCharge" << std::endl;

    int empId = 2;

    // ---------------------------------------------------------
    // Add hourly employee
    // ---------------------------------------------------------

    Transaction* t =
        TransactionFactory::GetFactory()
            .MakeAddHourlyTransaction(
                empId,
                "Bill",
                "Home",
                15.25);

    t->Execute();

    delete t;

    // ---------------------------------------------------------
    // Get employee
    // ---------------------------------------------------------

    Employee* e =
        GpayrollDatabase.GetEmployee(empId);

    assert(e != nullptr);

    // ---------------------------------------------------------
    // Create union affiliation
    // ---------------------------------------------------------

    int memberId = 86;

    UnionAffiliation* af =
        new UnionAffiliation(
            memberId,
            12.5);

    e->SetAffiliation(af);

    // ---------------------------------------------------------
    // Add union member to database
    // ---------------------------------------------------------

    GpayrollDatabase.AddUnionMember(
        memberId,
        e);

    // ---------------------------------------------------------
    // Add service charge
    // ---------------------------------------------------------

    Date date(11, 1, 2001);

    Transaction* sct =
        TransactionFactory::GetFactory()
            .MakeServiceChargeTransaction(
                memberId,
                date,
                12.95);

    sct->Execute();

    delete sct;

    // ---------------------------------------------------------
    // Verify service charge
    // ---------------------------------------------------------

    ServiceCharge* sc =
        af->GetServiceCharge(date);

    assert(sc != nullptr);

    assertEquals(
        12.95,
        sc->GetAmount(),
        0.001);

    cout
        << "TestAddServiceCharge passed"
        << endl;
}


void PayrollTest::TestChangeNameTransaction()
{
    std::cerr << "TestChangeNameTransaction" << std::endl;

    int empId = 2;

    Transaction* t =
        TransactionFactory::GetFactory().MakeAddHourlyTransaction(
            empId,
            "Bill",
            "Home",
            15.25);

    t->Execute();
    delete t;

    Transaction* cnt =
        TransactionFactory::GetFactory().MakeChangeNameTransaction(
            empId,
            "Bob");

    cnt->Execute();
    delete cnt;

    Employee* e =
        GpayrollDatabase.GetEmployee(empId);

    assert(e);

    assert(e->GetName() == "Bob");
}

void PayrollTest::TestChangeHourlyTransaction()
{
    std::cerr << "TestChangeHourlyTransaction" << std::endl;

    int empId = 3;

    // Create commissioned employee through the factory
    Transaction* t =
        TransactionFactory::GetFactory().MakeAddCommissionedTransaction(
            empId,
            "Lance",
            "Home",
            2500.00,
            3.2);

    t->Execute();
    delete t;

    // Change employee to hourly through the factory
    Transaction* cht =
        TransactionFactory::GetFactory().MakeChangeHourlyTransaction(
            empId,
            27.52);

    cht->Execute();
    delete cht;

    // Verify employee
    Employee* e =
        GpayrollDatabase.GetEmployee(empId);

    assert(e);

    // Verify classification
    PaymentClassification* pc =
        e->GetClassification();

    assert(pc);

    HourlyClassification* hc =
        dynamic_cast<HourlyClassification*>(pc);

    assert(hc);

    assertEquals(
        27.52,
        hc->GetRate(),
        0.001);

    // Verify schedule
    PaymentSchedule* ps =
        e->GetSchedule();

    assert(ps);

    WeeklySchedule* ws =
        dynamic_cast<WeeklySchedule*>(ps);

    assert(ws);

    cout
        << "TestChangeHourlyTransaction passed"
        << endl;
}


void PayrollTest::TestChangeMemberTransaction()
{
    std::cerr << "TestChangeMemberTransaction" << std::endl;

    int empId = 2;
    int memberId = 7734;

    Transaction* t =
        TransactionFactory::GetFactory().MakeAddHourlyTransaction(
            empId,
            "Bill",
            "Home",
            15.25);

    t->Execute();
    delete t;

    Transaction* cmt =
        TransactionFactory::GetFactory().MakeChangeMemberTransaction(
            empId,
            memberId,
            99.42);

    cmt->Execute();
    delete cmt;

    // Employee should exist
    Employee* e =
        GpayrollDatabase.GetEmployee(empId);

    assert(e);

    // Employee should now be registered as a union member
    Employee* member =
        GpayrollDatabase.GetUnionMember(memberId);

    assert(member);

    // It should be the same employee
    assert(member == e);

    // Verify affiliation
    Affiliation* affiliation =
        e->GetAffiliation();

    assert(affiliation);

    UnionAffiliation* ua =
        dynamic_cast<UnionAffiliation*>(affiliation);

    assert(ua);

    assertEquals(
        99.42,
        ua->GetDues(),
        0.001);

    cout
        << "TestChangeMemberTransaction passed"
        << endl;
}

void PayrollTest::TestPaySingleSalariedEmployee()
{
    std::cerr << "TestPaySingleSalariedEmployee" << std::endl;

    int empId = 1;

    TransactionFactory& factory =
        TransactionFactory::GetFactory();

    Transaction* t =
        factory.MakeAddSalariedTransaction(
            empId,
            "Bob",
            "Home",
            1000.00);

    assert(t);
    t->Execute();
    delete t;

    Date payDate(11, 30, 2001);

    Transaction* transaction =
        factory.MakePaydayTransaction(payDate);

    assert(transaction);

    transaction->Execute();

    PaydayTransaction* pt =
        dynamic_cast<PaydayTransaction*>(transaction);

    assert(pt);

    Paycheck* pc =
        pt->GetPaycheck(empId);

    assert(pc);

    assert(
        pc->GetPayPeriodEndDate() == payDate);

    assertEquals(
        1000.00,
        pc->GetGrossPay(),
        0.001);

    assert(
        "Hold" == pc->GetField("Disposition"));

    assertEquals(
        0.0,
        pc->GetDeductions(),
        0.001);

    delete transaction;

    cout
        << "TestPaySingleSalariedEmployee passed"
        << endl;
}


void PayrollTest::TestPaySingleSalariedEmployeeOnWrongDate()
{
    std::cerr << "TestPaySingleSalariedEmployeeWrongDate"
              << std::endl;

    int empId = 1;

    TransactionFactory& factory =
        TransactionFactory::GetFactory();

    // Add salaried employee
    Transaction* t =
        factory.MakeAddSalariedTransaction(
            empId,
            "Bob",
            "Home",
            1000.00);

    assert(t);

    t->Execute();

    delete t;

    // November 29, 2001 is not the monthly payday
    Date payDate(11, 29, 2001);

    // Create payday transaction through factory
    Transaction* transaction =
        factory.MakePaydayTransaction(payDate);

    assert(transaction);

    transaction->Execute();

    PaydayTransaction* pt =
        dynamic_cast<PaydayTransaction*>(transaction);

    assert(pt);

    // Employee should NOT receive a paycheck
    Paycheck* pc =
        pt->GetPaycheck(empId);

    assert(pc == nullptr);

    delete transaction;
    cout
        << "TestPaySingleSalariedEmployeeOnWrongDate passed"
        << endl;
}

void PayrollTest::TestPaySingleHourlyEmployeeNoTimeCards()
{
    std::cerr << "TestPaySingleHourlyEmployeeNoTimeCards"
              << std::endl;

    int empId = 2;

    TransactionFactory& factory =
        TransactionFactory::GetFactory();

    // Add hourly employee
    Transaction* t =
        factory.MakeAddHourlyTransaction(
            empId,
            "Bill",
            "Home",
            15.25);

    assert(t);

    t->Execute();

    delete t;

    // Friday, November 9, 2001
    Date payDate(11, 9, 2001);

    // Create payday transaction
    Transaction* transaction =
        factory.MakePaydayTransaction(payDate);

    assert(transaction);

    transaction->Execute();

    PaydayTransaction* pt =
        dynamic_cast<PaydayTransaction*>(transaction);

    assert(pt);

    // No time cards -> gross pay should be 0
    ValidatePaycheck(
        *pt,
        empId,
        payDate,
        0.0);

    delete transaction;
}

void PayrollTest::ValidatePaycheck(
    PaydayTransaction& pt,
    int empid,
    const Date& payDate,
    double pay)
{
    Paycheck* pc = pt.GetPaycheck(empid);

    assert(pc);

    assert(pc->GetPayPeriodEndDate() == payDate);

    assertEquals(
        pay,
        pc->GetGrossPay(),
        0.001);

    assert(
        "Hold" ==
        pc->GetField("Disposition"));

    assertEquals(
        0.0,
        pc->GetDeductions(),
        0.001);

    assertEquals(
        pay,
        pc->GetNetPay(),
        0.001);
}

void PayrollTest::TestPaySingleHourlyEmployeeOneTimeCard()
{
    std::cerr << "TestPaySingleHourlyEmployeeOneTimeCard"
              << std::endl;

    int empId = 2;

    TransactionFactory& factory =
        TransactionFactory::GetFactory();

    // Add hourly employee
    Transaction* t =
        factory.MakeAddHourlyTransaction(
            empId,
            "Bill",
            "Home",
            15.25);

    assert(t);

    t->Execute();

    delete t;

    // Friday, November 9, 2001
    Date payDate(11, 9, 2001);

    // Add one time card
    Transaction* timeCard =
        factory.MakeTimeCardTransaction(
            payDate,
            2.0,
            empId);

    assert(timeCard);

    timeCard->Execute();

    delete timeCard;

    // Run payroll
    Transaction* transaction =
        factory.MakePaydayTransaction(payDate);

    assert(transaction);

    transaction->Execute();

    PaydayTransaction* pt =
        dynamic_cast<PaydayTransaction*>(transaction);

    assert(pt);

    // Get paycheck
    Paycheck* pc =
        pt->GetPaycheck(empId);

    assert(pc);

    // 2 hours * $15.25 = $30.50
    assertEquals(
        30.5,
        pc->GetGrossPay(),
        0.001);

    assertEquals(
        30.5,
        pc->GetNetPay(),
        0.001);

    assert(
        payDate ==
        pc->GetPayPeriodEndDate());

    assert(
        "Hold" ==
        pc->GetField("Disposition"));

    delete transaction;

    cout
        << "TestPaySingleHourlyEmployeeOneTimeCard passed"
        << endl;
}

void PayrollTest::TestPaySingleHourlyEmployeeOvertimeOneTimeCard()
{
    std::cerr << "TestPaySingleHourlyEmployeeOvertimeOneTimeCard"
              << std::endl;

    int empId = 2;

    TransactionFactory& factory =
        TransactionFactory::GetFactory();

    // Add hourly employee
    Transaction* t =
        factory.MakeAddHourlyTransaction(
            empId,
            "Bill",
            "Home",
            15.25);

    assert(t);

    t->Execute();

    delete t;

    // Friday, November 9, 2001
    Date payDate(11, 9, 2001);

    // 9 hours -> 8 regular + 1 overtime
    Transaction* timeCard =
        factory.MakeTimeCardTransaction(
            payDate,
            9.0,
            empId);

    assert(timeCard);

    timeCard->Execute();

    delete timeCard;

    // Run payroll
    Transaction* transaction =
        factory.MakePaydayTransaction(payDate);

    assert(transaction);

    transaction->Execute();

    PaydayTransaction* pt =
        dynamic_cast<PaydayTransaction*>(transaction);

    assert(pt);

    Paycheck* pc =
        pt->GetPaycheck(empId);

    assert(pc);

    // 8 regular hours + 1 overtime hour at 1.5x
    double expectedPay =
        (8 + (1 * 1.5)) * 15.25;

    assertEquals(
        expectedPay,
        pc->GetGrossPay(),
        0.001);

    assertEquals(
        expectedPay,
        pc->GetNetPay(),
        0.001);

    assert(
        payDate ==
        pc->GetPayPeriodEndDate());

    assert(
        "Hold" ==
        pc->GetField("Disposition"));

    delete transaction;
    cout
        << "TestPaySingleHourlyEmployeeOvertimeOneTimeCard passed"
        << endl;
}

void PayrollTest::TestPaySingleHourlyEmployeeOnWrongDate()
{
    std::cerr << "TestPaySingleHourlyEmployeeOnWrongDate"
              << std::endl;

    int empId = 2;

    TransactionFactory& factory =
        TransactionFactory::GetFactory();

    // Add hourly employee
    Transaction* t =
        factory.MakeAddHourlyTransaction(
            empId,
            "Bill",
            "Home",
            15.25);

    assert(t);

    t->Execute();

    delete t;

    // Thursday, November 8, 2001
    // This is NOT the weekly payday.
    Date payDate(11, 8, 2001);

    // Add time card
    Transaction* timeCard =
        factory.MakeTimeCardTransaction(
            payDate,
            9.0,
            empId);

    assert(timeCard);

    timeCard->Execute();

    delete timeCard;

    // Attempt to run payroll on the wrong date
    Transaction* transaction =
        factory.MakePaydayTransaction(payDate);

    assert(transaction);

    transaction->Execute();

    PaydayTransaction* pt =
        dynamic_cast<PaydayTransaction*>(transaction);

    assert(pt);

    // No paycheck should be generated
    Paycheck* pc =
        pt->GetPaycheck(empId);

    assert(pc == nullptr);

    delete transaction;
    cout
        << "TestPaySingleHourlyEmployeeOnWrongDate passed"
        << endl;
}

void PayrollTest::TestPaySingleHourlyEmployeeTwoTimeCards()
{
    std::cerr << "TestPaySingleHourlyEmployeeTwoTimeCards"
              << std::endl;

    int empId = 2;

    TransactionFactory& factory =
        TransactionFactory::GetFactory();

    // Add hourly employee
    Transaction* t =
        factory.MakeAddHourlyTransaction(
            empId,
            "Bill",
            "Home",
            15.25);

    assert(t);

    t->Execute();

    delete t;

    // Friday, November 9, 2001
    Date payDate(11, 9, 2001);

    // Time card: 2 hours on payday
    Transaction* tc1 =
        factory.MakeTimeCardTransaction(
            payDate,
            2.0,
            empId);

    assert(tc1);

    tc1->Execute();

    delete tc1;

    // Time card: 5 hours on Thursday
    Date previousDate(11, 8, 2001);

    Transaction* tc2 =
        factory.MakeTimeCardTransaction(
            previousDate,
            5.0,
            empId);

    assert(tc2);

    tc2->Execute();

    delete tc2;

    // Run payroll
    Transaction* transaction =
        factory.MakePaydayTransaction(payDate);

    assert(transaction);

    transaction->Execute();

    PaydayTransaction* pt =
        dynamic_cast<PaydayTransaction*>(transaction);

    assert(pt);

    // Get paycheck
    Paycheck* pc =
        pt->GetPaycheck(empId);

    assert(pc);

    // 2 + 5 = 7 hours
    double expectedPay =
        7 * 15.25;

    assertEquals(
        expectedPay,
        pc->GetGrossPay(),
        0.001);

    assertEquals(
        expectedPay,
        pc->GetNetPay(),
        0.001);

    assert(
        payDate ==
        pc->GetPayPeriodEndDate());

    assert(
        "Hold" ==
        pc->GetField("Disposition"));

    delete transaction;
    cout
        << "TestPaySingleHourlyEmployeeTwoTimeCards passed"
        << endl;
}

void PayrollTest::TestPaySingleHourlyEmployeeWithTimeCardsSpanningTwoPayPeriods()
{
    std::cerr << "TestPaySingleHourlyEmployeeWithTimeCardsSpanningTwoPayPeriods"
              << std::endl;

    int empId = 2;

    TransactionFactory& factory =
        TransactionFactory::GetFactory();

    // Add hourly employee
    Transaction* t =
        factory.MakeAddHourlyTransaction(
            empId,
            "Bill",
            "Home",
            15.25);

    assert(t);

    t->Execute();

    delete t;

    // Current payday: Friday, November 9, 2001
    Date payDate(11, 9, 2001);

    // Previous pay period
    Date dateInPreviousPayPeriod(11, 2, 2001);

    // 2 hours in the current pay period
    Transaction* tc1 =
        factory.MakeTimeCardTransaction(
            payDate,
            2.0,
            empId);

    assert(tc1);

    tc1->Execute();

    delete tc1;

    // 5 hours in the previous pay period
    Transaction* tc2 =
        factory.MakeTimeCardTransaction(
            dateInPreviousPayPeriod,
            5.0,
            empId);

    assert(tc2);

    tc2->Execute();

    delete tc2;

    // Run payroll
    Transaction* transaction =
        factory.MakePaydayTransaction(payDate);

    assert(transaction);

    transaction->Execute();

    PaydayTransaction* pt =
        dynamic_cast<PaydayTransaction*>(transaction);

    assert(pt);

    // Get paycheck
    Paycheck* pc =
        pt->GetPaycheck(empId);

    assert(pc);

    // Only the 2 hours from the current pay period count
    double expectedPay =
        2 * 15.25;

    assertEquals(
        expectedPay,
        pc->GetGrossPay(),
        0.001);

    assertEquals(
        expectedPay,
        pc->GetNetPay(),
        0.001);

    assert(
        payDate ==
        pc->GetPayPeriodEndDate());

    assert(
        "Hold" ==
        pc->GetField("Disposition"));

    delete transaction;
    cout
        << "TestPaySingleHourlyEmployeeWithTimeCardsSpanningTwoPayPeriods passed"
        << endl;
}

void PayrollTest::TestSalariedUnionMemberDues()
{
    std::cerr << "TestSalariedUnionMemberDues"
              << std::endl;

    int empId = 1;

    TransactionFactory& factory =
        TransactionFactory::GetFactory();

    // Add salaried employee
    Transaction* t =
        factory.MakeAddSalariedTransaction(
            empId,
            "Bob",
            "Home",
            1000.00);

    assert(t);

    t->Execute();

    delete t;

    // Make employee a union member
    int memberId = 7734;

    Transaction* cmt =
        factory.MakeChangeMemberTransaction(
            empId,
            memberId,
            9.42);

    assert(cmt);

    cmt->Execute();

    delete cmt;

    // Payday: Friday, November 30, 2001
    Date payDate(11, 30, 2001);

    Transaction* transaction =
        factory.MakePaydayTransaction(payDate);

    assert(transaction);

    transaction->Execute();

    PaydayTransaction* pt =
        dynamic_cast<PaydayTransaction*>(transaction);

    assert(pt);

    // Get paycheck
    Paycheck* pc =
        pt->GetPaycheck(empId);

    assert(pc);

    // Gross salary
    assertEquals(
        1000.00,
        pc->GetGrossPay(),
        0.001);

    // Union dues
    assertEquals(
        9.42,
        pc->GetDeductions(),
        0.001);

    // Net = gross - deductions
    assertEquals(
        990.58,
        pc->GetNetPay(),
        0.001);

    assert(
        "Hold" ==
        pc->GetField("Disposition"));

    delete transaction;
    cout
        << "TestSalariedUnionMemberDues passed"
        << endl;
}


void PayrollTest::TestHourlyUnionMemberServiceCharge()
{
    std::cerr << "TestHourlyUnionMemberServiceCharge" << std::endl;

    int empId = 1;

    // Add hourly employee
    Transaction* t =
        TransactionFactory::GetFactory().MakeAddHourlyTransaction(
            empId,
            "Bill",
            "Home",
            15.24);

    t->Execute();
    delete t;


    int memberId = 7734;

    // Make employee a union member
    t =
        TransactionFactory::GetFactory().MakeChangeMemberTransaction(
            empId,
            memberId,
            9.42);

    t->Execute();
    delete t;


    Date payDate(11, 9, 2001);

    // Add service charge
    t =
        TransactionFactory::GetFactory().MakeServiceChargeTransaction(
            memberId,
            payDate,
            19.42);

    t->Execute();
    delete t;


    // Add 8 hours
    t =
        TransactionFactory::GetFactory().MakeTimeCardTransaction(
            payDate,
            8.0,
            empId);

    t->Execute();
    delete t;


    // Run payroll
    PaydayTransaction* pt =
        dynamic_cast<PaydayTransaction*>(
            TransactionFactory::GetFactory().MakePaydayTransaction(
                payDate));

    assert(pt);

    pt->Execute();


    Paycheck* pc =
        pt->GetPaycheck(empId);

    assert(pc);


    // Gross pay
    assertEquals(
        8 * 15.24,
        pc->GetGrossPay(),
        0.001);


    // Union dues + service charge
    assertEquals(
        9.42 + 19.42,
        pc->GetDeductions(),
        0.001);


    // Net pay
    assertEquals(
        (8 * 15.24) - (9.42 + 19.42),
        pc->GetNetPay(),
        0.001);


    // Payment method
    assert(
        "Hold" ==
        pc->GetField("Disposition")
    );

    delete pt;

    cout
        << "TestHourlyUnionMemberServiceCharge passed"
        << endl;
}


void PayrollTest::TestPaydayMultipleEmployees()
{
    std::cerr << "TestPaydayMultipleEmployees" << std::endl;

    int salariedId = 18;

    // Add salaried employee
    Transaction* t =
        TransactionFactory::GetFactory().MakeAddSalariedTransaction(
            salariedId,
            "Alice",
            "Home",
            1000.00);

    t->Execute();
    delete t;


    int hourlyId = 19;

    // Add hourly employee
    t =
        TransactionFactory::GetFactory().MakeAddHourlyTransaction(
            hourlyId,
            "Bob",
            "Home",
            15.00);

    t->Execute();
    delete t;


    int commissionedId = 20;

    // Add commissioned employee
    t =
        TransactionFactory::GetFactory().MakeAddCommissionedTransaction(
            commissionedId,
            "Charlie",
            "Home",
            2000.00,
            10.0);

    t->Execute();
    delete t;


    // --------------------------------------------------------
    // Friday payroll
    // --------------------------------------------------------

    Date payDate(11, 9, 2001);

    // Add 8 hours to hourly employee
    t =
        TransactionFactory::GetFactory().MakeTimeCardTransaction(
            payDate,
            8.0,
            hourlyId);

    t->Execute();
    delete t;


    // Run Friday payroll
    PaydayTransaction* fridayPayday =
        dynamic_cast<PaydayTransaction*>(
            TransactionFactory::GetFactory().MakePaydayTransaction(
                payDate));

    assert(fridayPayday);

    fridayPayday->Execute();


    // Hourly employee should be paid
    ValidatePaycheck(
        *fridayPayday,
        hourlyId,
        payDate,
        120.00);


    // Commissioned employee should also be paid
    ValidatePaycheck(
        *fridayPayday,
        commissionedId,
        payDate,
        2000.00);


    // --------------------------------------------------------
    // Monthly payroll
    // --------------------------------------------------------

    Date monthlyPayDate(11, 30, 2001);

    PaydayTransaction* monthlyPayday =
        dynamic_cast<PaydayTransaction*>(
            TransactionFactory::GetFactory().MakePaydayTransaction(
                monthlyPayDate));

    assert(monthlyPayday);

    monthlyPayday->Execute();


    // Salaried employee should be paid
    ValidatePaycheck(
        *monthlyPayday,
        salariedId,
        monthlyPayDate,
        1000.00);


    delete fridayPayday;
    delete monthlyPayday;

    std::cout
        << "TestPaydayMultipleEmployees passed"
        << std::endl;
}


void PayrollTest::TestPaydayMultipleCommissionedEmployees()
{
    std::cerr << "TestPaydayMultipleCommissionedEmployees"
              << std::endl;

    int empId1 = 21;
    int empId2 = 22;


    // --------------------------------------------------------
    // Add first commissioned employee
    // --------------------------------------------------------

    Transaction* t =
        TransactionFactory::GetFactory()
            .MakeAddCommissionedTransaction(
                empId1,
                "Bob",
                "Home",
                1000.00,
                10.0);

    t->Execute();
    delete t;


    // --------------------------------------------------------
    // Add second commissioned employee
    // --------------------------------------------------------

    t =
        TransactionFactory::GetFactory()
            .MakeAddCommissionedTransaction(
                empId2,
                "Alice",
                "Home",
                2000.00,
                10.0);

    t->Execute();
    delete t;


    // --------------------------------------------------------
    // Add sales receipt for first employee
    // --------------------------------------------------------

    Date payDate(11, 9, 2001);

    t =
        TransactionFactory::GetFactory()
            .MakeSalesReceiptTransaction(
                empId1,
                payDate,
                500.00);

    t->Execute();
    delete t;


    // --------------------------------------------------------
    // Add sales receipt for second employee
    // --------------------------------------------------------

    t =
        TransactionFactory::GetFactory()
            .MakeSalesReceiptTransaction(
                empId2,
                payDate,
                1000.00);

    t->Execute();
    delete t;


    // --------------------------------------------------------
    // Run payroll
    // --------------------------------------------------------

    PaydayTransaction* pt =
        dynamic_cast<PaydayTransaction*>(
            TransactionFactory::GetFactory()
                .MakePaydayTransaction(payDate));

    assert(pt);

    pt->Execute();


    // --------------------------------------------------------
    // Validate first employee
    // Base = 1000
    // Commission = 10% of 500 = 50
    // Gross = 1050
    // --------------------------------------------------------

    ValidatePaycheck(
        *pt,
        empId1,
        payDate,
        1050.00);


    // --------------------------------------------------------
    // Validate second employee
    // Base = 2000
    // Commission = 10% of 1000 = 100
    // Gross = 2100
    // --------------------------------------------------------

    ValidatePaycheck(
        *pt,
        empId2,
        payDate,
        2100.00);


    delete pt;
    std::cout
        << "TestPaydayMultipleCommissionedEmployees passed"
        << std::endl;
}

void PayrollTest::TestPaydayMultipleSalariedEmployees()
{
    std::cerr << "TestPaydayMultipleSalariedEmployees"
              << std::endl;

    int empId1 = 23;
    int empId2 = 24;


    // --------------------------------------------------------
    // Add first salaried employee
    // --------------------------------------------------------

    Transaction* t =
        TransactionFactory::GetFactory()
            .MakeAddSalariedTransaction(
                empId1,
                "Bob",
                "Home",
                1000.00);

    t->Execute();
    delete t;


    // --------------------------------------------------------
    // Add second salaried employee
    // --------------------------------------------------------

    t =
        TransactionFactory::GetFactory()
            .MakeAddSalariedTransaction(
                empId2,
                "Alice",
                "Home",
                2000.00);

    t->Execute();
    delete t;


    // --------------------------------------------------------
    // Run monthly payroll
    // --------------------------------------------------------

    Date payDate(11, 30, 2001);

    PaydayTransaction* pt =
        dynamic_cast<PaydayTransaction*>(
            TransactionFactory::GetFactory()
                .MakePaydayTransaction(payDate));

    assert(pt);

    pt->Execute();


    // --------------------------------------------------------
    // Validate second salaried employee
    // --------------------------------------------------------

    ValidatePaycheck(
        *pt,
        empId2,
        payDate,
        2000.00);


    delete pt;
    std::cout
        << "TestPaydayMultipleSalariedEmployees passed"
        << std::endl;
}


void PayrollTest::TestCommissionedSalesReceiptPayday()
{
    std::cerr << "TestCommissionedSalesReceiptPayday"
              << std::endl;

    int empId = 17;


    // --------------------------------------------------------
    // Add commissioned employee
    // --------------------------------------------------------

    Transaction* t =
        TransactionFactory::GetFactory()
            .MakeAddCommissionedTransaction(
                empId,
                "Bob",
                "Home",
                1000.00,
                10.0);

    t->Execute();
    delete t;


    // --------------------------------------------------------
    // Add sales receipt
    // --------------------------------------------------------

    Date payDate(11, 9, 2001);

    t =
        TransactionFactory::GetFactory()
            .MakeSalesReceiptTransaction(
                empId,
                payDate,
                500.00);

    t->Execute();
    delete t;


    // --------------------------------------------------------
    // Run payroll
    // --------------------------------------------------------

    PaydayTransaction* pt =
        dynamic_cast<PaydayTransaction*>(
            TransactionFactory::GetFactory()
                .MakePaydayTransaction(payDate));

    assert(pt);

    pt->Execute();


    // --------------------------------------------------------
    // Validate paycheck
    //
    // Base salary = 1000
    // Sales = 500
    // Commission = 10% = 50
    // Gross = 1050
    // --------------------------------------------------------

    ValidatePaycheck(
        *pt,
        empId,
        payDate,
        1050.00);


    delete pt;
    std::cout
        << "TestCommissionedSalesReceiptPayday passed"
        << std::endl;
}

void PayrollTest::TestSingleCommissionedEmployeePayday()
{
    std::cerr << "TestSingleCommissionedEmployeePayday"
              << std::endl;

    int empId = 16;


    // --------------------------------------------------------
    // Add commissioned employee
    // --------------------------------------------------------

    Transaction* t =
        TransactionFactory::GetFactory()
            .MakeAddCommissionedTransaction(
                empId,
                "Bob",
                "Home",
                1000.00,
                10.0);

    t->Execute();
    delete t;


    // --------------------------------------------------------
    // Run payroll
    // --------------------------------------------------------

    Date payDate(11, 9, 2001);

    PaydayTransaction* pt =
        dynamic_cast<PaydayTransaction*>(
            TransactionFactory::GetFactory()
                .MakePaydayTransaction(payDate));

    assert(pt);

    pt->Execute();


    // --------------------------------------------------------
    // Validate paycheck
    //
    // No sales receipts:
    // Gross pay = 1000.00
    // --------------------------------------------------------

    ValidatePaycheck(
        *pt,
        empId,
        payDate,
        1000.00);


    delete pt;

    std::cout
        << "TestSingleCommissionedEmployeePayday passed"
        << std::endl;
}

void PayrollTest::TestHourlyEmployeeOvertimePayday()
{
    std::cerr << "TestHourlyEmployeeOvertimePayday"
              << std::endl;

    int empId = 15;


    // --------------------------------------------------------
    // Add hourly employee
    // --------------------------------------------------------

    Transaction* t =
        TransactionFactory::GetFactory()
            .MakeAddHourlyTransaction(
                empId,
                "Bob",
                "Home",
                15.25);

    t->Execute();
    delete t;


    // --------------------------------------------------------
    // Add 9-hour time card
    //
    // 8 regular hours  = 8 * 15.25
    // 1 overtime hour  = 1 * 15.25 * 1.5
    //
    // Total = 144.875
    // --------------------------------------------------------

    Date date(11, 9, 2001);

    t =
        TransactionFactory::GetFactory()
            .MakeTimeCardTransaction(
                date,
                9.0,
                empId);

    t->Execute();
    delete t;


    // --------------------------------------------------------
    // Run payroll
    // --------------------------------------------------------

    PaydayTransaction* pt =
        dynamic_cast<PaydayTransaction*>(
            TransactionFactory::GetFactory()
                .MakePaydayTransaction(date));

    assert(pt);

    pt->Execute();


    // --------------------------------------------------------
    // Validate paycheck
    // --------------------------------------------------------

    ValidatePaycheck(
        *pt,
        empId,
        date,
        144.875);


    delete pt;
    std::cout
        << "TestHourlyEmployeeOvertimePayday passed"
        << std::endl;
}

void PayrollTest::TestSingleHourlyEmployeePayday()
{
    std::cerr << "TestSingleHourlyEmployeePayday"
              << std::endl;

    int empId = 14;


    // --------------------------------------------------------
    // Add hourly employee
    // --------------------------------------------------------

    Transaction* t =
        TransactionFactory::GetFactory()
            .MakeAddHourlyTransaction(
                empId,
                "Bob",
                "Home",
                15.25);

    t->Execute();
    delete t;


    // --------------------------------------------------------
    // Add 8-hour time card
    // --------------------------------------------------------

    Date date(11, 9, 2001);

    t =
        TransactionFactory::GetFactory()
            .MakeTimeCardTransaction(
                date,
                8.0,
                empId);

    t->Execute();
    delete t;


    // --------------------------------------------------------
    // Run payroll
    // --------------------------------------------------------

    PaydayTransaction* pt =
        dynamic_cast<PaydayTransaction*>(
            TransactionFactory::GetFactory()
                .MakePaydayTransaction(date));

    assert(pt);

    pt->Execute();


    // --------------------------------------------------------
    // Validate paycheck
    // --------------------------------------------------------

    ValidatePaycheck(
        *pt,
        empId,
        date,
        8 * 15.25);


    delete pt;
}

void PayrollTest::TestSingleSalariedEmployeePayday()
{
    std::cerr << "TestSingleSalariedEmployeePayday"
              << std::endl;

    int empId = 13;


    // --------------------------------------------------------
    // Add salaried employee
    // --------------------------------------------------------

    Transaction* t =
        TransactionFactory::GetFactory()
            .MakeAddSalariedTransaction(
                empId,
                "Bob",
                "Home",
                1000.00);

    t->Execute();
    delete t;


    // --------------------------------------------------------
    // Run monthly payroll
    // --------------------------------------------------------

    Date payDate(8, 31, 2001);

    PaydayTransaction* pt =
        dynamic_cast<PaydayTransaction*>(
            TransactionFactory::GetFactory()
                .MakePaydayTransaction(payDate));

    assert(pt);

    pt->Execute();


    // --------------------------------------------------------
    // Validate paycheck
    // --------------------------------------------------------

    ValidatePaycheck(
        *pt,
        empId,
        payDate,
        1000.00);


    delete pt;

    std::cout
        << "TestSingleSalariedEmployeePayday passed"
        << std::endl;
}

void PayrollTest::TestSalesReceiptForNonCommissioned()
{
    std::cout
        << "TestSalesReceiptForNonCommissioned"
        << std::endl;

    int empId = 12;


    // --------------------------------------------------------
    // Add salaried employee
    // --------------------------------------------------------

    Transaction* t =
        TransactionFactory::GetFactory()
            .MakeAddSalariedTransaction(
                empId,
                "Bob",
                "Home",
                1000.00);

    t->Execute();
    delete t;


    // --------------------------------------------------------
    // Attempt to add sales receipt
    // --------------------------------------------------------

    Date date(8, 7, 2001);

    t =
        TransactionFactory::GetFactory()
            .MakeSalesReceiptTransaction(
                empId,
                date,
                500.00);

    try
    {
        t->Execute();

        // Should never reach here.
        assert(false);
    }
    catch (const char* message)
    {
        assert(
            std::string(message) ==
            "Tried to add sales receipt to non-commissioned employee");
    }

    delete t;


    // --------------------------------------------------------
    // Verify employee still exists
    // --------------------------------------------------------

    Employee* e =
        GpayrollDatabase.GetEmployee(empId);

    assert(e);


    std::cout
        << "TestSalesReceiptForNonCommissioned passed"
        << std::endl;
}

void PayrollTest::TestSalesReceiptTransaction()
{
    std::cerr << "TestSalesReceiptTransaction"
              << std::endl;

    int empId = 11;


    // --------------------------------------------------------
    // Add commissioned employee
    // --------------------------------------------------------

    Transaction* t =
        TransactionFactory::GetFactory()
            .MakeAddCommissionedTransaction(
                empId,
                "Bob",
                "Home",
                2500.00,
                10.0);

    t->Execute();
    delete t;


    // --------------------------------------------------------
    // Add sales receipt
    // --------------------------------------------------------

    Date date(8, 7, 2001);

    t =
        TransactionFactory::GetFactory()
            .MakeSalesReceiptTransaction(
                empId,
                date,
                500.00);

    t->Execute();
    delete t;


    // --------------------------------------------------------
    // Verify sales receipt
    // --------------------------------------------------------

    Employee* e =
        GpayrollDatabase.GetEmployee(empId);

    assert(e);


    PaymentClassification* pc =
        e->GetClassification();

    assert(pc);


    CommissionedClassification* cc =
        dynamic_cast<CommissionedClassification*>(pc);

    assert(cc);


    SalesReceipt* sr =
        cc->GetSalesReceipt(date);

    assert(sr);


    assertEquals(
        500.00,
        sr->GetAmount(),
        0.001);


    std::cout
        << "TestSalesReceiptTransaction passed"
        << std::endl;
}

void PayrollTest::TestTimeCardForNonHourlyEmployee()
{
    std::cout
        << "TestTimeCardForNonHourlyEmployee"
        << std::endl;

    int empId = 10;


    // --------------------------------------------------------
    // Add salaried employee
    // --------------------------------------------------------

    Transaction* t =
        TransactionFactory::GetFactory()
            .MakeAddSalariedTransaction(
                empId,
                "Bob",
                "Home",
                1000.00);

    t->Execute();
    delete t;


    // --------------------------------------------------------
    // Attempt to add time card
    // --------------------------------------------------------

    Date date(8, 7, 2001);

    t =
        TransactionFactory::GetFactory()
            .MakeTimeCardTransaction(
                date,
                8.0,
                empId);

    try
    {
        t->Execute();

        // We should never get here.
        assert(false);
    }
    catch (const char* message)
    {
        assert(
            std::string(message) ==
            "Tried to add timecard to non-hourly employee");
    }

    delete t;


    // --------------------------------------------------------
    // Verify employee still exists and is salaried
    // --------------------------------------------------------

    Employee* e =
        GpayrollDatabase.GetEmployee(empId);

    assert(e);


    SalariedClassification* sc =
        dynamic_cast<SalariedClassification*>(
            e->GetClassification());

    assert(sc);


    std::cout
        << "TestTimeCardForNonHourlyEmployee passed"
        << std::endl;
}

void PayrollTest::TestTimeCardTransaction()
{
    std::cerr << "TestTimeCardTransaction"
              << std::endl;

    int empId = 9;


    // --------------------------------------------------------
    // Add hourly employee
    // --------------------------------------------------------

    Transaction* t =
        TransactionFactory::GetFactory()
            .MakeAddHourlyTransaction(
                empId,
                "Bob",
                "Home",
                15.25);

    t->Execute();
    delete t;


    // --------------------------------------------------------
    // Add time card
    // --------------------------------------------------------

    Date date(8, 7, 2001);

    t =
        TransactionFactory::GetFactory()
            .MakeTimeCardTransaction(
                date,
                8.0,
                empId);

    t->Execute();
    delete t;


    // --------------------------------------------------------
    // Verify time card
    // --------------------------------------------------------

    Employee* e =
        GpayrollDatabase.GetEmployee(empId);

    assert(e);


    HourlyClassification* hc =
        dynamic_cast<HourlyClassification*>(
            e->GetClassification());

    assert(hc);


    TimeCard* card =
        hc->GetTimeCard(date);

    assert(card);


    assertEquals(
        8.0,
        card->GetHours(),
        0.001);


    std::cout
        << "TestTimeCardTransaction passed"
        << std::endl;
}

void PayrollTest::TestChangeMailTransaction()
{
    std::cerr << "TestChangeMailTransaction"
              << std::endl;

    int empId = 8;


    // --------------------------------------------------------
    // Add salaried employee
    // --------------------------------------------------------

    Transaction* t =
        TransactionFactory::GetFactory()
            .MakeAddSalariedTransaction(
                empId,
                "Bob",
                "Home",
                1000.00);

    t->Execute();
    delete t;


    // --------------------------------------------------------
    // Change payment method to MailMethod
    // --------------------------------------------------------

    t =
        TransactionFactory::GetFactory()
            .MakeChangeMailTransaction(
                empId,
                "123 Main Street");

    t->Execute();
    delete t;


    // --------------------------------------------------------
    // Verify payment method
    // --------------------------------------------------------

    Employee* e =
        GpayrollDatabase.GetEmployee(empId);

    assert(e);


    MailMethod* mm =
        dynamic_cast<MailMethod*>(
            e->GetMethod());

    assert(mm);


    assert(
        mm->GetAddress() ==
        "123 Main Street");


    std::cout
        << "TestChangeMailTransaction passed"
        << std::endl;
}

void PayrollTest::TestChangeDirectTransaction()
{
    std::cerr << "TestChangeDirectTransaction"
              << std::endl;

    int empId = 7;


    // --------------------------------------------------------
    // Add salaried employee
    // --------------------------------------------------------

    Transaction* t =
        TransactionFactory::GetFactory()
            .MakeAddSalariedTransaction(
                empId,
                "Bob",
                "Home",
                1000.00);

    t->Execute();
    delete t;


    // --------------------------------------------------------
    // Change payment method to DirectMethod
    // --------------------------------------------------------

    t =
        TransactionFactory::GetFactory()
            .MakeChangeDirectTransaction(
                empId,
                "NatWest",
                12345);

    t->Execute();
    delete t;


    // --------------------------------------------------------
    // Verify payment method
    // --------------------------------------------------------

    Employee* e =
        GpayrollDatabase.GetEmployee(empId);

    assert(e);


    DirectMethod* dm =
        dynamic_cast<DirectMethod*>(
            e->GetMethod());

    assert(dm);


    assert(
        dm->GetBank() ==
        "NatWest");

    assert(
        dm->GetAccount() ==
        12345);


    std::cout
        << "TestChangeDirectTransaction passed"
        << std::endl;
}

void PayrollTest::TestChangeHoldTransaction()
{
    std::cerr << "TestChangeHoldTransaction"
              << std::endl;

    int empId = 6;


    // --------------------------------------------------------
    // Add salaried employee
    // --------------------------------------------------------

    Transaction* t =
        TransactionFactory::GetFactory()
            .MakeAddSalariedTransaction(
                empId,
                "Bob",
                "Home",
                1000.00);

    t->Execute();
    delete t;


    // --------------------------------------------------------
    // Change payment method to HoldMethod
    // --------------------------------------------------------

    t =
        TransactionFactory::GetFactory()
            .MakeChangeHoldTransaction(empId);

    t->Execute();
    delete t;


    // --------------------------------------------------------
    // Verify payment method
    // --------------------------------------------------------

    Employee* e =
        GpayrollDatabase.GetEmployee(empId);

    assert(e);


    HoldMethod* hm =
        dynamic_cast<HoldMethod*>(
            e->GetMethod());

    assert(hm);


    std::cout
        << "TestChangeHoldTransaction passed"
        << std::endl;
}

void PayrollTest::TestChangeCommissionedTransaction()
{
    std::cerr << "TestChangeCommissionedTransaction"
              << std::endl;

    int empId = 5;


    // --------------------------------------------------------
    // Add hourly employee
    // --------------------------------------------------------

    Transaction* t =
        TransactionFactory::GetFactory()
            .MakeAddHourlyTransaction(
                empId,
                "Bob",
                "Home",
                15.25);

    t->Execute();
    delete t;


    // --------------------------------------------------------
    // Change classification to commissioned
    // --------------------------------------------------------

    t =
        TransactionFactory::GetFactory()
            .MakeChangeCommissionedTransaction(
                empId,
                2500.00,
                10.0);

    t->Execute();
    delete t;


    // --------------------------------------------------------
    // Verify classification
    // --------------------------------------------------------

    Employee* e =
        GpayrollDatabase.GetEmployee(empId);

    assert(e);


    CommissionedClassification* cc =
        dynamic_cast<CommissionedClassification*>(
            e->GetClassification());

    assert(cc);


    // --------------------------------------------------------
    // Verify schedule
    // --------------------------------------------------------

    BiweeklySchedule* bs =
        dynamic_cast<BiweeklySchedule*>(
            e->GetSchedule());

    assert(bs);


    std::cout
        << "TestChangeCommissionedTransaction passed"
        << std::endl;
}

void PayrollTest::TestChangeSalariedTransaction()
{
    std::cerr << "TestChangeSalariedTransaction"
              << std::endl;

    int empId = 4;


    // --------------------------------------------------------
    // Add hourly employee
    // --------------------------------------------------------

    Transaction* t =
        TransactionFactory::GetFactory()
            .MakeAddHourlyTransaction(
                empId,
                "Bob",
                "Home",
                15.25);

    t->Execute();
    delete t;


    // --------------------------------------------------------
    // Change classification to salaried
    // --------------------------------------------------------

    t =
        TransactionFactory::GetFactory()
            .MakeChangeSalariedTransaction(
                empId,
                1000.00);

    t->Execute();
    delete t;


    // --------------------------------------------------------
    // Verify classification
    // --------------------------------------------------------

    Employee* e =
        GpayrollDatabase.GetEmployee(empId);

    assert(e);


    SalariedClassification* sc =
        dynamic_cast<SalariedClassification*>(
            e->GetClassification());

    assert(sc);


    // --------------------------------------------------------
    // Verify schedule
    // --------------------------------------------------------

    MonthlySchedule* ms =
        dynamic_cast<MonthlySchedule*>(
            e->GetSchedule());

    assert(ms);


    std::cout
        << "TestChangeSalariedTransaction passed"
        << std::endl;
}

void PayrollTest::TestChangeAddressTransaction()
{
    std::cerr << "TestChangeAddressTransaction"
              << std::endl;

    int empId = 2;


    // --------------------------------------------------------
    // Add salaried employee
    // --------------------------------------------------------

    Transaction* t =
        TransactionFactory::GetFactory()
            .MakeAddSalariedTransaction(
                empId,
                "Bob",
                "Old Address",
                1000.00);

    t->Execute();
    delete t;


    // --------------------------------------------------------
    // Change address
    // --------------------------------------------------------

    t =
        TransactionFactory::GetFactory()
            .MakeChangeAddressTransaction(
                empId,
                "New Address");

    t->Execute();
    delete t;


    // --------------------------------------------------------
    // Verify address
    // --------------------------------------------------------

    Employee* e =
        GpayrollDatabase.GetEmployee(empId);

    assert(e);


    assert(
        e->GetAddress() ==
        "New Address");


    std::cout
        << "TestChangeAddressTransaction passed"
        << std::endl;
}

void PayrollTest::TestAddHourlyEmployee()
{
    std::cerr << "TestAddHourlyEmployee"
              << std::endl;

    int empId = 2;


    // --------------------------------------------------------
    // Add hourly employee
    // --------------------------------------------------------

    Transaction* t =
        TransactionFactory::GetFactory()
            .MakeAddHourlyTransaction(
                empId,
                "Bill",
                "Home",
                15.25);

    t->Execute();
    delete t;


    // --------------------------------------------------------
    // Verify employee
    // --------------------------------------------------------

    Employee* e =
        GpayrollDatabase.GetEmployee(empId);

    assert(e);


    assert(
        e->GetName() ==
        "Bill");


    // --------------------------------------------------------
    // Verify classification
    // --------------------------------------------------------

    HourlyClassification* hc =
        dynamic_cast<HourlyClassification*>(
            e->GetClassification());

    assert(hc);


    // --------------------------------------------------------
    // Verify schedule
    // --------------------------------------------------------

    WeeklySchedule* ws =
        dynamic_cast<WeeklySchedule*>(
            e->GetSchedule());

    assert(ws);


    std::cout
        << "TestAddHourlyEmployee passed"
        << std::endl;
}

void PayrollTest::TestAddCommissionedEmployee()
{
    std::cerr << "TestAddCommissionedEmployee"
              << std::endl;

    int empId = 3;


    // --------------------------------------------------------
    // Add commissioned employee
    // --------------------------------------------------------

    Transaction* t =
        TransactionFactory::GetFactory()
            .MakeAddCommissionedTransaction(
                empId,
                "Lance",
                "Home",
                2500.00,
                3.2);

    t->Execute();
    delete t;


    // --------------------------------------------------------
    // Verify employee
    // --------------------------------------------------------

    Employee* e =
        GpayrollDatabase.GetEmployee(empId);

    assert(e);


    // --------------------------------------------------------
    // Verify classification
    // --------------------------------------------------------

    CommissionedClassification* cc =
        dynamic_cast<CommissionedClassification*>(
            e->GetClassification());

    assert(cc);


    // --------------------------------------------------------
    // Verify schedule
    // --------------------------------------------------------

    BiweeklySchedule* bs =
        dynamic_cast<BiweeklySchedule*>(
            e->GetSchedule());

    assert(bs);


    std::cout
        << "TestAddCommissionedEmployee passed"
        << std::endl;
}
