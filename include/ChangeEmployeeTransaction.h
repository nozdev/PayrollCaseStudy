#ifndef CHANGEEMPLOYEETRANSACTION_H
#define CHANGEEMPLOYEETRANSACTION_H

#include "Transaction.h"

class Employee;

class ChangeEmployeeTransaction :
    public Transaction
{
public:

    ChangeEmployeeTransaction(
        int empid);


    virtual ~ChangeEmployeeTransaction();


    void Execute() override;


protected:

    virtual void Change(
        Employee& e) = 0;


private:

    int itsEmpId;
};

#endif
