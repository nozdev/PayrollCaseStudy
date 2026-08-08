#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

class PaymentClassification;
class PaymentSchedule;
class PaymentMethod;
class Affiliation;
class Paycheck;
class Date;


class Employee
{
public:

    Employee(
        int empid,
        std::string name,
        std::string address);


    virtual ~Employee();


    int GetEmpId() const;

    std::string GetName() const;

    std::string GetAddress() const;


    void SetName(std::string name);

    void SetAddress(std::string address);


    void SetClassification(
        PaymentClassification* pc);


    void SetSchedule(
        PaymentSchedule* ps);


    void SetMethod(
        PaymentMethod* pm);


    void SetAffiliation(
        Affiliation* af);


    PaymentClassification* GetClassification() const;


    PaymentSchedule* GetSchedule() const;


    PaymentMethod* GetMethod() const;


    Affiliation* GetAffiliation() const;


    bool IsPayDate(const Date& payDate) const;

    Date GetPayPeriodStartDate(const Date& payDate) const;

    void PayDay(
        Paycheck& pc);


private:

    int itsEmpid;

    std::string itsName;

    std::string itsAddress;


    PaymentClassification* itsClassification;

    PaymentSchedule* itsSchedule;

    PaymentMethod* itsPaymentMethod;

    Affiliation* itsAffiliation;
};


#endif
