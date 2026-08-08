#ifndef ADDCOMMISSIONEDEMPLOYEE_H
#define ADDCOMMISSIONEDEMPLOYEE_H

#include "AddEmployeeTransaction.h"


class AddCommissionedEmployee : public AddEmployeeTransaction
{
public:

    AddCommissionedEmployee(
        int empid,
        std::string name,
        std::string address,
        double salary,
        double commissionRate);


    virtual ~AddCommissionedEmployee();


protected:

    PaymentClassification* GetClassification() const override;

    PaymentSchedule* GetSchedule() const override;


private:

    double itsSalary;
    double itsCommissionRate;
};


#endif
