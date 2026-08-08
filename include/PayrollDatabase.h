#ifndef PAYROLLDATABASE_H
#define PAYROLLDATABASE_H

#include <map>

class Employee;


class PayrollDatabase
{
public:
    
    void AddUnionMember(
    int memberId,
    Employee* e);

    Employee* GetUnionMember(
    int memberId) const;
    void RemoveUnionMember(
    int memberId);

    std::map<int, Employee*> GetEmployees() const;

    PayrollDatabase();


    void Clear()
    {
        itsEmployees.clear();
    }

    virtual ~PayrollDatabase();

    void DeleteEmployee(int empid);
    Employee* GetEmployee(int empid);


    void AddEmployee(
        int empid,
        Employee* e);


private:

    std::map<int, Employee*> itsUnionMembers;

    std::map<int, Employee*> itsEmployees;

};


#endif
