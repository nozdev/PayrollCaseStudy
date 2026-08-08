#include "DirectMethod.h"
#include "PayrollDomain/Paycheck.h"


DirectMethod::DirectMethod(
    std::string bank,
    int account)
    :
    itsBank(bank),
    itsAccount(account)
{
}


DirectMethod::~DirectMethod()
{
}


void DirectMethod::Pay(Paycheck& paycheck)
{
}


std::string DirectMethod::GetBank() const
{
    return itsBank;
}


int DirectMethod::GetAccount() const
{
    return itsAccount;
}
