#include "HourlyClassification.h"
#include "Paycheck.h"
#include "TimeCard.h"

HourlyClassification::HourlyClassification(
    double hourlyRate)
    : itsHourlyRate(hourlyRate)
{
}

HourlyClassification::~HourlyClassification()
{
    for (TimeCard* tc : itsTimeCards)
    {
        delete tc;
    }
}

double HourlyClassification::CalculatePay(
    Paycheck& pc) const
{
    double totalPay = 0.0;

    Date startDate =
        pc.GetPayPeriodStartDate();

    Date endDate =
        pc.GetPayPeriodEndDate();

    for (TimeCard* tc : itsTimeCards)
    {
        Date date = tc->GetDate();

        if (date < startDate ||
            date > endDate)
        {
            continue;
        }

        double hours = tc->GetHours();

        if (hours <= 8.0)
        {
            totalPay += hours * itsHourlyRate;
        }
        else
        {
            totalPay +=
                8.0 * itsHourlyRate;

            totalPay +=
                (hours - 8.0) *
                itsHourlyRate *
                1.5;
        }
    }

    return totalPay;
}

void HourlyClassification::AddTimeCard(
    TimeCard* tc)
{
    itsTimeCards.push_back(tc);
}

TimeCard* HourlyClassification::GetTimeCard(
    const Date& date) const
{
    for (TimeCard* tc : itsTimeCards)
    {
        if (tc->GetDate() == date)
        {
            return tc;
        }
    }

    return nullptr;
}

double HourlyClassification::GetRate() const
{
    return itsHourlyRate;
}
