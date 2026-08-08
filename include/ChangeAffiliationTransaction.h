#ifndef CHANGEAFFILIATIONTRANSACTION_H
#define CHANGEAFFILIATIONTRANSACTION_H

#include "ChangeEmployeeTransaction.h"

class Affiliation;
class Employee;

class ChangeAffiliationTransaction :
    public ChangeEmployeeTransaction
{
public:

    virtual ~ChangeAffiliationTransaction();

    ChangeAffiliationTransaction(
        int empId);


protected:

    virtual Affiliation* GetAffiliation() const = 0;

    virtual void RecordMembership(
        Employee* e) = 0;


    void Change(
        Employee& e) override;

};

#endif
