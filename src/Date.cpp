#include "Date.h"

#include <ctime>

Date::Date(long date)
{
    itsYear = date / 10000;
    itsMonth = (date / 100) % 100;
    itsDay = date % 100;
}


long Date::ToLong() const
{
    return itsYear * 10000L
         + itsMonth * 100L
         + itsDay;
}

Date::Date(
    int month,
    int day,
    int year)
    :
    itsMonth(month),
    itsDay(day),
    itsYear(year)
{
}


int Date::GetMonth() const
{
    return itsMonth;
}


int Date::GetDay() const
{
    return itsDay;
}


int Date::GetYear() const
{
    return itsYear;
}


Date::DayOfWeek Date::GetDayOfWeek() const
{
    tm time = {};

    time.tm_year = itsYear - 1900;
    time.tm_mon  = itsMonth - 1;
    time.tm_mday = itsDay;

    mktime(&time);

    return static_cast<DayOfWeek>(time.tm_wday);
}


Date Date::operator+(int days) const
{
    tm time = {};

    time.tm_year = itsYear - 1900;
    time.tm_mon  = itsMonth - 1;
    time.tm_mday = itsDay + days;

    mktime(&time);

    return Date(
        time.tm_mon + 1,
        time.tm_mday,
        time.tm_year + 1900);
}


Date Date::operator-(int days) const
{
    return *this + (-days);
}


bool Date::operator==(const Date& rhs) const
{
    return itsYear == rhs.itsYear &&
           itsMonth == rhs.itsMonth &&
           itsDay == rhs.itsDay;
}


bool Date::operator!=(const Date& rhs) const
{
    return !(*this == rhs);
}


bool Date::operator<(const Date& rhs) const
{
    if (itsYear != rhs.itsYear)
        return itsYear < rhs.itsYear;

    if (itsMonth != rhs.itsMonth)
        return itsMonth < rhs.itsMonth;

    return itsDay < rhs.itsDay;
}


bool Date::operator<=(const Date& rhs) const
{
    return *this < rhs || *this == rhs;
}


bool Date::operator>(const Date& rhs) const
{
    return rhs < *this;
}


bool Date::operator>=(const Date& rhs) const
{
    return rhs <= *this;
}

int Date::DaysBetween(const Date& rhs) const
{
    auto DaysSinceEpoch = [](int month, int day, int year)
    {
        int days = day;

        static int daysInMonth[] =
        {
            0, 31, 28, 31, 30, 31, 30,
            31, 31, 30, 31, 30, 31
        };

        for(int m = 1; m < month; m++)
            days += daysInMonth[m];

        days += year * 365;

        // leap years
        days += year / 4;
        days -= year / 100;
        days += year / 400;

        return days;
    };


    int thisDays =
        DaysSinceEpoch(
            itsMonth,
            itsDay,
            itsYear);

    int rhsDays =
        DaysSinceEpoch(
            rhs.GetMonth(),
            rhs.GetDay(),
            rhs.GetYear());

    return thisDays - rhsDays;
}
