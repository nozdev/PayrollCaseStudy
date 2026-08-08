#ifndef ADDHOURLYEMPLOYEE_H
#define ADDHOURLYEMPLOYEE_H

#include "AddEmployeeTransaction.h"


class AddHourlyEmployee : public AddEmployeeTransaction
{
public:

    AddHourlyEmployee(
        int empid,
        std::string name,
        std::string address,
        double hourlyRate);


    virtual ~AddHourlyEmployee();


protected:

    PaymentClassification* GetClassification() const override;

    PaymentSchedule* GetSchedule() const override;


private:

    double itsHourlyRate;
};


#endif
