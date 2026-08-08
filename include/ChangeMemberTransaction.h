#ifndef CHANGEMEMBERTRANSACTION_H
#define CHANGEMEMBERTRANSACTION_H

#include "ChangeAffiliationTransaction.h"


class ChangeMemberTransaction :
    public ChangeAffiliationTransaction
{
public:

    virtual ~ChangeMemberTransaction();


    ChangeMemberTransaction(
        int empId,
        int memberId,
        double dues);


protected:

    Affiliation* GetAffiliation() const override;


    void RecordMembership(
        Employee* e) override;


private:

    int itsMemberId;

    double itsDues;

};

#endif
