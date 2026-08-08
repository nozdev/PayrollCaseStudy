#ifndef HOURLYCLASSIFICATION_H
#define HOURLYCLASSIFICATION_H

#include "PaymentClassification.h"
#include "Date.h"
#include <vector>

class Paycheck;
class TimeCard;

class HourlyClassification : public PaymentClassification
{
public:
    HourlyClassification(double hourlyRate);
    virtual ~HourlyClassification();

    virtual double CalculatePay(Paycheck& pc) const override;

    void AddTimeCard(TimeCard* tc);

    TimeCard* GetTimeCard(const Date& date) const;

    double GetRate() const;

private:
    double itsHourlyRate;
    std::vector<TimeCard*> itsTimeCards;
};

#endif
