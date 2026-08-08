#ifndef CHANGEADDRESSTRANSACTION_H
#define CHANGEADDRESSTRANSACTION_H

#include "ChangeEmployeeTransaction.h"

#include <string>


class ChangeAddressTransaction : public ChangeEmployeeTransaction
{
public:

    ChangeAddressTransaction(
        int empid,
        std::string address);


    virtual ~ChangeAddressTransaction();


protected:

    void Change(Employee& e) override;


private:

    std::string itsAddress;
};


#endif
