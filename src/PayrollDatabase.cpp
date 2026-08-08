#include "PayrollDatabase.h"
#include "PayrollDomain/Employee.h"


PayrollDatabase GpayrollDatabase;


PayrollDatabase::PayrollDatabase()
{
}


Employee* PayrollDatabase::GetUnionMember(
    int memberId) const
{
    auto it =
        itsUnionMembers.find(memberId);


    if(it == itsUnionMembers.end())
        return nullptr;


    return it->second;
}

void PayrollDatabase::AddUnionMember(
    int memberId,
    Employee* e)
{
    itsUnionMembers[memberId] = e;
}


void PayrollDatabase::RemoveUnionMember(
    int memberId)
{
    itsUnionMembers.erase(memberId);
}

std::map<int, Employee*> 
PayrollDatabase::GetEmployees() const
{
    return itsEmployees;
}

void PayrollDatabase::DeleteEmployee(int empid)
{
    auto it = itsEmployees.find(empid);

    if (it != itsEmployees.end())
    {
        delete it->second;
        itsEmployees.erase(it);
    }
}
PayrollDatabase::~PayrollDatabase()
{
    for(auto employee : itsEmployees)
    {
        delete employee.second;
    }
}


Employee* PayrollDatabase::GetEmployee(int empid)
{
    auto it = itsEmployees.find(empid);

    if(it == itsEmployees.end())
    {
        return nullptr;
    }

    return it->second;
}


void PayrollDatabase::AddEmployee(
    int empid,
    Employee* e)
{
    itsEmployees[empid] = e;
}
