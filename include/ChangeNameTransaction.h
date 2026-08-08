#ifndef CHANGENAMETRANSACTION_H
#define CHANGENAMETRANSACTION_H

#include "ChangeEmployeeTransaction.h"

#include <string>


class ChangeNameTransaction : public ChangeEmployeeTransaction
{
public:

    ChangeNameTransaction(
        int empid,
        std::string name);


    virtual ~ChangeNameTransaction();


protected:

    void Change(Employee& e) override;


private:

    std::string itsName;
};


#endif
