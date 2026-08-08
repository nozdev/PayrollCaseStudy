#include "PayrollTest.h"

#include "AddSalariedEmployee.h"
#include "AddHourlyEmployee.h"
#include "AddCommissionedEmployee.h"
#include "PayrollDatabase.h"
#include "Employee.h"
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
#include "Paycheck.h"
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

    AddSalariedEmployee t(
        empId,
        "Bob",
        "Home",
        1000.00);

    t.Execute();

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

    AddCommissionedEmployee t(
        empId,
        "Lance",
        "Home",
        2500.00,
        3.2);

    t.Execute();

    {
        Employee* e =
            GpayrollDatabase.GetEmployee(empId);

        assert(e);
    }

    DeleteEmployeeTransaction dt(empId);

    dt.Execute();

    {
        Employee* e =
            GpayrollDatabase.GetEmployee(empId);

        assert(e == 0);
    }
}

void PayrollTest::TestPaydayMultipleHourlyEmployees()
{
    int empId1 = 25;
    int empId2 = 26;

    AddHourlyEmployee e1(
        empId1,
        "Bob",
        "Home",
        15.00);

    e1.Execute();

    AddHourlyEmployee e2(
        empId2,
        "Alice",
        "Home",
        20.00);

    e2.Execute();

    Date payDate(11, 9, 2001);

    TimeCardTransaction tc1(
        payDate,
        8.0,
        empId1);

    tc1.Execute();

    TimeCardTransaction tc2(
        payDate,
        10.0,
        empId2);

    tc2.Execute();

    PaydayTransaction pt(payDate);

    pt.Execute();

    ValidatePaycheck(
        pt,
        empId1,
        payDate,
        120.00);

    ValidatePaycheck(
        pt,
        empId2,
        payDate,
        220.00);
}

void PayrollTest::TestAddServiceCharge()
{
    cerr << "TestAddServiceCharge"
         << endl;


    int empId = 2;


    AddHourlyEmployee t(
        empId,
        "Bill",
        "Home",
        15.25);

    t.Execute();


    Employee* e =
        GpayrollDatabase.GetEmployee(empId);

    assert(e);


    int memberId = 86;


    UnionAffiliation* af =
        new UnionAffiliation(
            memberId,
            12.5);


    e->SetAffiliation(af);


    GpayrollDatabase.AddUnionMember(
        memberId,
        e);


    Date date(11,1,2001);


    ServiceChargeTransaction sct(
        memberId,
        date,
        12.95);


    sct.Execute();


    ServiceCharge* sc =
        af->GetServiceCharge(date);

    assert(sc);


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
    cerr << "TestChangeNameTransaction"
         << endl;


    int empId = 2;


    AddHourlyEmployee t(
        empId,
        "Bill",
        "Home",
        15.25);

    t.Execute();


    ChangeNameTransaction cnt(
        empId,
        "Bob");

    cnt.Execute();


    Employee* e =
        GpayrollDatabase.GetEmployee(empId);

    assert(e);


    assert(
        "Bob" ==
        e->GetName());


    cout
        << "TestChangeNameTransaction passed"
        << endl;
}

void PayrollTest::TestChangeHourlyTransaction()
{
    cerr << "TestChangeHourlyTransaction"
         << endl;


    int empId = 3;


    AddCommissionedEmployee t(
        empId,
        "Lance",
        "Home",
        2500.00,
        3.2);

    t.Execute();


    ChangeHourlyTransaction cht(
        empId,
        27.52);

    cht.Execute();


    Employee* e =
        GpayrollDatabase.GetEmployee(empId);

    assert(e);


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
    cerr << "TestChangeMemberTransaction"
         << endl;


    int empId = 2;


    int memberId = 7734;


    AddHourlyEmployee t(
        empId,
        "Bill",
        "Home",
        15.25);

    t.Execute();


    ChangeMemberTransaction cmt(
        empId,
        memberId,
        99.42);

    cmt.Execute();


    Employee* e =
        GpayrollDatabase.GetEmployee(empId);

    assert(e);


    Affiliation* af =
        e->GetAffiliation();

    assert(af);


    UnionAffiliation* uf =
        dynamic_cast<UnionAffiliation*>(af);

    assert(uf);


    assertEquals(
        99.42,
        uf->GetDues(),
        0.001);


    Employee* member =
        GpayrollDatabase.GetUnionMember(
            memberId);

    assert(member);


    assert(
        e == member);


    cout
        << "TestChangeMemberTransaction passed"
        << endl;
}

void PayrollTest::TestPaySingleSalariedEmployee()
{
    cerr << "TestPaySingleSalariedEmployee"
         << endl;


    int empId = 1;


    AddSalariedEmployee t(
        empId,
        "Bob",
        "Home",
        1000.00);

    t.Execute();


    Date payDate(11,30,2001);


    PaydayTransaction pt(payDate);

    pt.Execute();


    Paycheck* pc =
        pt.GetPaycheck(empId);


    assert(pc);


    assert(
        pc->GetPayPeriodEndDate()
        ==
        payDate);


    assertEquals(
        1000.00,
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
        1000.00,
        pc->GetNetPay(),
        0.001);


    cout
        << "TestPaySingleSalariedEmployee passed"
        << endl;
}

void PayrollTest::TestPaySingleSalariedEmployeeOnWrongDate()
{
    cerr << "TestPaySingleSalariedEmployeeWrongDate"
         << endl;


    int empId = 1;


    AddSalariedEmployee t(
        empId,
        "Bob",
        "Home",
        1000.00);

    t.Execute();


    Date payDate(11,29,2001);   // Thursday, not month end


    PaydayTransaction pt(payDate);

    pt.Execute();


    Paycheck* pc =
        pt.GetPaycheck(empId);


    assert(pc == nullptr);


    cout
        << "TestPaySingleSalariedEmployeeOnWrongDate passed"
        << endl;
}

void PayrollTest::TestPaySingleHourlyEmployeeNoTimeCards()
{
    cerr << "TestPaySingleHourlyEmployeeNoTimeCards"
         << endl;


    int empId = 2;


    AddHourlyEmployee t(
        empId,
        "Bill",
        "Home",
        15.25);

    t.Execute();


    Date payDate(11,9,2001);   // Friday


    PaydayTransaction pt(payDate);

    pt.Execute();


    ValidatePaycheck(
        pt,
        empId,
        payDate,
        0.0);
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
    cerr << "TestPaySingleHourlyEmployeeOneTimeCard"
         << endl;


    int empId = 2;


    AddHourlyEmployee t(
        empId,
        "Bill",
        "Home",
        15.25);

    t.Execute();


    Date payDate(11,9,2001);   // Friday


    TimeCardTransaction tc(
        payDate,
        2.0,empId);

    tc.Execute();


    PaydayTransaction pt(payDate);

    pt.Execute();


    Paycheck* pc =
        pt.GetPaycheck(empId);


    assert(pc);


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


    cout
        << "TestPaySingleHourlyEmployeeOneTimeCard passed"
        << endl;
}

void PayrollTest::TestPaySingleHourlyEmployeeOvertimeOneTimeCard()
{
    cerr << "TestPaySingleHourlyEmployeeOvertimeOneTimeCard"
         << endl;


    int empId = 2;


    AddHourlyEmployee t(
        empId,
        "Bill",
        "Home",
        15.25);

    t.Execute();


    Date payDate(11,9,2001);   // Friday


    TimeCardTransaction tc(
        payDate,
        9.0,empId);

    tc.Execute();


    PaydayTransaction pt(payDate);

    pt.Execute();


    Paycheck* pc =
        pt.GetPaycheck(empId);


    assert(pc);


    assertEquals(
        (8 + (1 * 1.5)) * 15.25,
        pc->GetGrossPay(),
        0.001);


    assertEquals(
        (8 + (1 * 1.5)) * 15.25,
        pc->GetNetPay(),
        0.001);


    assert(
        payDate ==
        pc->GetPayPeriodEndDate());


    assert(
        "Hold" ==
        pc->GetField("Disposition"));


    cout
        << "TestPaySingleHourlyEmployeeOvertimeOneTimeCard passed"
        << endl;
}

void PayrollTest::TestPaySingleHourlyEmployeeOnWrongDate()
{
    cerr << "TestPaySingleHourlyEmployeeOnWrongDate"
         << endl;


    int empId = 2;


    AddHourlyEmployee t(
        empId,
        "Bill",
        "Home",
        15.25);

    t.Execute();


    Date payDate(11,8,2001);   // Thursday


    TimeCardTransaction tc(
        payDate,
        9.0,empId);

    tc.Execute();


    PaydayTransaction pt(payDate);

    pt.Execute();


    Paycheck* pc =
        pt.GetPaycheck(empId);


    assert(pc == nullptr);


    cout
        << "TestPaySingleHourlyEmployeeOnWrongDate passed"
        << endl;
}

void PayrollTest::TestPaySingleHourlyEmployeeTwoTimeCards()
{
    cerr << "TestPaySingleHourlyEmployeeTwoTimeCards"
         << endl;


    int empId = 2;


    AddHourlyEmployee t(
        empId,
        "Bill",
        "Home",
        15.25);

    t.Execute();


    Date payDate(11,9,2001);   // Friday


    TimeCardTransaction tc(
        payDate,
        2.0,empId);

    tc.Execute();


    TimeCardTransaction tc2(
        Date(11,8,2001),
        5.0,empId);

    tc2.Execute();


    PaydayTransaction pt(payDate);

    pt.Execute();


    Paycheck* pc =
        pt.GetPaycheck(empId);


    assert(pc);


    assertEquals(
        7 * 15.25,
        pc->GetGrossPay(),
        0.001);


    assertEquals(
        7 * 15.25,
        pc->GetNetPay(),
        0.001);


    assert(
        payDate ==
        pc->GetPayPeriodEndDate());


    assert(
        "Hold" ==
        pc->GetField("Disposition"));


    cout
        << "TestPaySingleHourlyEmployeeTwoTimeCards passed"
        << endl;
}

void PayrollTest::TestPaySingleHourlyEmployeeWithTimeCardsSpanningTwoPayPeriods()
{
    cerr << "TestPaySingleHourlyEmployeeWithTimeCardsSpanningTwoPayPeriods"
         << endl;


    int empId = 2;


    AddHourlyEmployee t(
        empId,
        "Bill",
        "Home",
        15.25);

    t.Execute();


    Date payDate(11,9,2001);


    Date dateInPreviousPayPeriod(11,2,2001);


    TimeCardTransaction tc(
        payDate,
        2.0,empId);

    tc.Execute();


    TimeCardTransaction tc2(
        dateInPreviousPayPeriod,
        5.0,empId);

    tc2.Execute();


    PaydayTransaction pt(payDate);

    pt.Execute();


    Paycheck* pc =
        pt.GetPaycheck(empId);


    assert(pc);


    assertEquals(
        2 * 15.25,
        pc->GetGrossPay(),
        0.001);


    assertEquals(
        2 * 15.25,
        pc->GetNetPay(),
        0.001);


    assert(
        payDate ==
        pc->GetPayPeriodEndDate());


    assert(
        "Hold" ==
        pc->GetField("Disposition"));


    cout
        << "TestPaySingleHourlyEmployeeWithTimeCardsSpanningTwoPayPeriods passed"
        << endl;
}

void PayrollTest::TestSalariedUnionMemberDues()
{
    cerr << "TestSalariedUnionMemberDues"
         << endl;


    int empId = 1;


    AddSalariedEmployee t(
        empId,
        "Bob",
        "Home",
        1000.00);

    t.Execute();


    int memberId = 7734;


    ChangeMemberTransaction cmt(
        empId,
        memberId,
        9.42);

    cmt.Execute();


    Date payDate(11,30,2001);


    PaydayTransaction pt(payDate);

    pt.Execute();


    Paycheck* pc =
        pt.GetPaycheck(empId);


    assert(pc);


    assertEquals(
        1000.00,
        pc->GetGrossPay(),
        0.001);


    assertEquals(
        9.42,
        pc->GetDeductions(),
        0.001);


    assertEquals(
        990.58,
        pc->GetNetPay(),
        0.001);


    assert(
        "Hold" ==
        pc->GetField("Disposition"));


    cout
        << "TestSalariedUnionMemberDues passed"
        << endl;
}


void PayrollTest::TestHourlyUnionMemberServiceCharge()
{
    int empId = 1;


    AddHourlyEmployee t(
        empId,
        "Bill",
        "Home",
        15.24);

    t.Execute();


    int memberId = 7734;


    ChangeMemberTransaction cmt(
        empId,
        memberId,
        9.42);

    cmt.Execute();


    Date payDate(11,9,2001);


    ServiceChargeTransaction sct(
        memberId,
        payDate,
        19.42);

    sct.Execute();


    TimeCardTransaction tct(
        payDate,
        8.0,empId);

    tct.Execute();


    PaydayTransaction pt(payDate);

    pt.Execute();


    Paycheck* pc =
        pt.GetPaycheck(empId);


    assert(pc);


    assertEquals(
        8 * 15.24,
        pc->GetGrossPay(),
        0.001);


    assertEquals(
        9.42 + 19.42,
        pc->GetDeductions(),
        0.001);


    assertEquals(
        (8 * 15.24) - (9.42 + 19.42),
        pc->GetNetPay(),
        0.001);


    assert(
        "Hold" ==
        pc->GetField("Disposition")
    );


    cout
        << "TestHourlyUnionMemberServiceCharge passed"
        << endl;
}


void PayrollTest::TestPaydayMultipleEmployees()
{
    int salariedId = 18;

    AddSalariedEmployee salaried(
        salariedId,
        "Alice",
        "Home",
        1000.00);

    salaried.Execute();
    int hourlyId = 19;

    AddHourlyEmployee hourly(
        hourlyId,
        "Bob",
        "Home",
        15.00);

    hourly.Execute();

    int commissionedId = 20;

    AddCommissionedEmployee commissioned(
        commissionedId,
        "Charlie",
        "Home",
        2000.00,
        10.0);

    commissioned.Execute();
     Date payDate(11, 9, 2001);
     TimeCardTransaction tc(
        payDate,
        8.0,
        hourlyId);

    tc.Execute();

    PaydayTransaction fridayPayday(payDate);

    fridayPayday.Execute();

    ValidatePaycheck(
        fridayPayday,
        hourlyId,
        payDate,
        120.00);

    ValidatePaycheck(
        fridayPayday,
        commissionedId,
        payDate,
        2000.00);
     Date monthlyPayDate(11, 30, 2001);

    PaydayTransaction monthlyPayday(
        monthlyPayDate);

    monthlyPayday.Execute();

     ValidatePaycheck(
        monthlyPayday,
        salariedId,
        monthlyPayDate,
        1000.00);


    std::cout
        << "TestPaydayMultipleEmployees passed"
        << std::endl;
}

void PayrollTest::TestPaydayMultipleCommissionedEmployees()
{
    int empId1 = 21;
    int empId2 = 22;

    AddCommissionedEmployee e1(
        empId1,
        "Bob",
        "Home",
        1000.00,
        10.0);

    e1.Execute();

    AddCommissionedEmployee e2(
        empId2,
        "Alice",
        "Home",
        2000.00,
        10.0);

    e2.Execute();

    Date payDate(11, 9, 2001);

    SalesReceiptTransaction sr1(
        empId1,
        payDate,
        500.00);

    sr1.Execute();

    SalesReceiptTransaction sr2(
        empId2,
        payDate,
        1000.00);

    sr2.Execute();

    PaydayTransaction pt(payDate);

    pt.Execute();

    ValidatePaycheck(
        pt,
        empId1,
        payDate,
        1050.00);

    ValidatePaycheck(
        pt,
        empId2,
        payDate,
        2100.00);

    std::cout
        << "TestPaydayMultipleCommissionedEmployees passed"
        << std::endl;
}

void PayrollTest::TestPaydayMultipleSalariedEmployees()
{
    int empId1 = 23;
    int empId2 = 24;


    AddSalariedEmployee e1(
        empId1,
        "Bob",
        "Home",
        1000.00);

    e1.Execute();


    AddSalariedEmployee e2(
        empId2,
        "Alice",
        "Home",
        2000.00);

    e2.Execute();


    Date payDate(11,30,2001);


    PaydayTransaction pt(payDate);

    pt.Execute();


    ValidatePaycheck(
        pt,
        empId1,
        payDate,
        1000.00);

    ValidatePaycheck(
        pt,
        empId2,
        payDate,
        2000.00);

    std::cout
        << "TestPaydayMultipleSalariedEmployees passed"
        << std::endl;
}


void PayrollTest::TestCommissionedSalesReceiptPayday()
{
    int empId = 17;

    AddCommissionedEmployee t(
        empId,
        "Bob",
        "Home",
        1000.00,
        10.0);

    t.Execute();

    Date payDate(11, 9, 2001);

    SalesReceiptTransaction srt(
        empId,
        payDate,
        500.00);

    srt.Execute();

    PaydayTransaction pt(payDate);

    pt.Execute();


    ValidatePaycheck(
    pt,
    empId,
    payDate,
    1050.00);

    std::cout
        << "TestCommissionedSalesReceiptPayday passed"
        << std::endl;
}

void PayrollTest::TestSingleCommissionedEmployeePayday()
{
    int empId = 16;

    AddCommissionedEmployee t(
        empId,
        "Bob",
        "Home",
        1000.00,
        10.0);

    t.Execute();

    Date payDate(11, 9, 2001);

    PaydayTransaction pt(payDate);

    pt.Execute();

    ValidatePaycheck(
    pt,
    empId,
    payDate,
    1000.00);

    std::cout
        << "TestSingleCommissionedEmployeePayday passed"
        << std::endl;
}
void PayrollTest::TestHourlyEmployeeOvertimePayday()
{
    int empId = 15;


    AddHourlyEmployee t(
        empId,
        "Bob",
        "Home",
        15.25);


    t.Execute();


    Date date(11,9,2001);


    TimeCardTransaction tc(
        date,
        9.0,empId);


    tc.Execute();


    PaydayTransaction pt(date);

    pt.Execute();


    ValidatePaycheck(
    pt,
    empId,
    date,
    144.875);


    std::cout
        << "TestHourlyEmployeeOvertimePayday passed"
        << std::endl;
}

void PayrollTest::TestSingleHourlyEmployeePayday()
{
    int empId = 14;

    AddHourlyEmployee t(
        empId,
        "Bob",
        "Home",
        15.25);

    t.Execute();


    Date date(11,9,2001);   // Friday payday


    TimeCardTransaction tc(
        date,
        8.0,empId);

    tc.Execute();


    PaydayTransaction pt(date);

    pt.Execute();

    ValidatePaycheck(
    pt,
    empId,
    date,
    8 * 15.25);
}

void PayrollTest::TestSingleSalariedEmployeePayday()
{
    int empId = 13;


    AddSalariedEmployee t(
        empId,
        "Bob",
        "Home",
        1000.00);


    t.Execute();


    Date payDate(8,31,2001);


    PaydayTransaction pt(payDate);

    pt.Execute();


    ValidatePaycheck(
    pt,
    empId,
    payDate,
    1000.00);


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

    AddSalariedEmployee t(
        empId,
        "Bob",
        "Home",
        1000.00);

    t.Execute();

    Date date(8, 7, 2001);

    SalesReceiptTransaction srt(
        empId,
        date,
        500.00);

    try
    {
        srt.Execute();

        // Should never reach here.
        assert(false);
    }
    catch (const char* message)
    {
        assert(
            std::string(message)
            ==
            "Tried to add sales receipt to non-commissioned employee");
    }

    Employee* e =
        GpayrollDatabase.GetEmployee(empId);

    assert(e);

    std::cout
        << "TestSalesReceiptForNonCommissioned passed"
        << std::endl;
}

void PayrollTest::TestSalesReceiptTransaction()
{
    int empId = 11;


    AddCommissionedEmployee t(
        empId,
        "Bob",
        "Home",
        2500.00,
        10.0);


    t.Execute();


    Date date(8,7,2001);


    SalesReceiptTransaction srt(
        empId,
        date,
        500.00);


    srt.Execute();


    Employee* e =
        GpayrollDatabase.GetEmployee(empId);


    CommissionedClassification* cc =
        dynamic_cast<CommissionedClassification*>(
            e->GetClassification());


    assert(cc);


    SalesReceipt* sr =
        cc->GetSalesReceipt(date);


    assert(sr);

    assert(sr->GetAmount() == 500.00);


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

    AddSalariedEmployee t(
        empId,
        "Bob",
        "Home",
        1000.00);

    t.Execute();

    Date date(8, 7, 2001);

    TimeCardTransaction tc(
        date,
        8.0,
        empId);

    try
    {
        tc.Execute();

        // We should never get here.
        assert(false);
    }
    catch (const char* message)
    {
        assert(
            std::string(message) ==
            "Tried to add timecard to non-hourly employee");
    }

    Employee* e =
        GpayrollDatabase.GetEmployee(empId);

    assert(e);

    SalariedClassification* sc =
        dynamic_cast<SalariedClassification*>(
            e->GetClassification());

    assert(sc);
}

void PayrollTest::TestTimeCardTransaction()
{
    int empId = 9;


    AddHourlyEmployee t(
        empId,
        "Bob",
        "Home",
        15.25);

    t.Execute();


    Date date(8,7,2001);


    TimeCardTransaction tc(
        date,
        8.0, empId);


    tc.Execute();


    Employee* e =
        GpayrollDatabase.GetEmployee(empId);


    HourlyClassification* hc =
        dynamic_cast<HourlyClassification*>(
            e->GetClassification());


    assert(hc);


    TimeCard* card =
        hc->GetTimeCard(date);


    assert(card);

    assert(card->GetHours() == 8.0);


    std::cout
        << "TestTimeCardTransaction passed"
        << std::endl;
}

void PayrollTest::TestChangeMailTransaction()
{
    int empId = 8;


    AddSalariedEmployee t(
        empId,
        "Bob",
        "Home",
        1000.00);

    t.Execute();


    ChangeMailTransaction cmt(
        empId,
        "123 Main Street");


    cmt.Execute();


    Employee* e =
        GpayrollDatabase.GetEmployee(empId);

    assert(e);


    MailMethod* mm =
        dynamic_cast<MailMethod*>(
            e->GetMethod());

    assert(mm);


    assert(mm->GetAddress() ==
           "123 Main Street");


    std::cout
        << "TestChangeMailTransaction passed"
        << std::endl;
}

void PayrollTest::TestChangeDirectTransaction()
{
    int empId = 7;


    AddSalariedEmployee t(
        empId,
        "Bob",
        "Home",
        1000.00);

    t.Execute();


    ChangeDirectTransaction cdt(
        empId,
        "NatWest",
        12345);

    cdt.Execute();


    Employee* e =
        GpayrollDatabase.GetEmployee(empId);

    assert(e);


    DirectMethod* dm =
        dynamic_cast<DirectMethod*>(
            e->GetMethod());

    assert(dm);

    assert(dm->GetBank() == "NatWest");

    assert(dm->GetAccount() == 12345);


    std::cout
        << "TestChangeDirectTransaction passed"
        << std::endl;
}

void PayrollTest::TestChangeHoldTransaction()
{
    int empId = 6;


    AddSalariedEmployee t(
        empId,
        "Bob",
        "Home",
        1000.00);

    t.Execute();


    ChangeHoldTransaction cht(empId);

    cht.Execute();


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
    int empId = 5;

    AddHourlyEmployee t(
        empId,
        "Bob",
        "Home",
        15.25);

    t.Execute();


    ChangeCommissionedTransaction cct(
        empId,
        2500.00,
        10.0);

    cct.Execute();


    Employee* e =
        GpayrollDatabase.GetEmployee(empId);

    assert(e);


    CommissionedClassification* cc =
        dynamic_cast<CommissionedClassification*>(
            e->GetClassification());

    assert(cc);


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

    int empId = 4;

    AddHourlyEmployee t(
        empId,
        "Bob",
        "Home",
        15.25);

    t.Execute();


    ChangeSalariedTransaction cst(
        empId,
        1000.00);

    cst.Execute();


    Employee* e =
        GpayrollDatabase.GetEmployee(empId);

    assert(e);


    SalariedClassification* sc =
        dynamic_cast<SalariedClassification*>(
            e->GetClassification());

    assert(sc);


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
    int empId = 2;

    AddSalariedEmployee t(
        empId,
        "Bob",
        "Old Address",
        1000.00);

    t.Execute();


    ChangeAddressTransaction cat(
        empId,
        "New Address");

    cat.Execute();


    Employee* e =
        GpayrollDatabase.GetEmployee(empId);

    assert(e);

    assert(e->GetAddress() == "New Address");


    std::cout
        << "TestChangeAddressTransaction passed"
        << std::endl;
}


void PayrollTest::TestAddHourlyEmployee()
{

    int empId = 2;

    AddHourlyEmployee t(
        empId,
        "Bill",
        "Home",
        15.25);


    t.Execute();


    Employee* e =
        GpayrollDatabase.GetEmployee(empId);

    assert(e);

    assert(e->GetName() == "Bill");


    HourlyClassification* hc =
        dynamic_cast<HourlyClassification*>(
            e->GetClassification());

    assert(hc);


    WeeklySchedule* ws =
        dynamic_cast<WeeklySchedule*>(
            e->GetSchedule());

    assert(ws);

    std::cout << "TestAddHourlyEmployee passed"
              << std::endl;

}


void PayrollTest::TestAddCommissionedEmployee()
{
        

    int empId = 3;

    AddCommissionedEmployee t(
        empId,
        "Lance",
        "Home",
        2500.00,
        3.2);

    t.Execute();

    Employee* e =
        GpayrollDatabase.GetEmployee(empId);

    assert(e);

    CommissionedClassification* cc =
        dynamic_cast<CommissionedClassification*>(
            e->GetClassification());

    assert(cc);


    BiweeklySchedule* bs =
        dynamic_cast<BiweeklySchedule*>(
            e->GetSchedule());

    assert(bs);
    std::cout << "TestAddCommissionedEmployee passed"
              << std::endl;



}

