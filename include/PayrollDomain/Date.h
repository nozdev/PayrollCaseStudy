#ifndef DATE_H
#define DATE_H

class Date
{
public:

    enum DayOfWeek
    {
        sunday,
        monday,
        tuesday,
        wednesday,
        thursday,
        friday,
        saturday
    };
    
    long ToLong() const;

    Date(long date);

    Date(
        int month,
        int day,
        int year);


    int GetMonth() const;

    int GetDay() const;

    int GetYear() const;


    DayOfWeek GetDayOfWeek() const;


    Date operator+(int days) const;

    Date operator-(int days) const;


    int DaysBetween(
        const Date& rhs) const;


    bool operator==(
        const Date& rhs) const;


    bool operator!=(
        const Date& rhs) const;


    bool operator<(
        const Date& rhs) const;


    bool operator<=(
        const Date& rhs) const;


    bool operator>(
        const Date& rhs) const;


    bool operator>=(
        const Date& rhs) const;


private:

    int itsMonth;
    int itsDay;
    int itsYear;

};

#endif
