#include "MailMethod.h"
#include "PayrollDomain/Paycheck.h"


MailMethod::MailMethod(std::string address)
    :
    itsAddress(address)
{
}


MailMethod::~MailMethod()
{
}


void MailMethod::Pay(Paycheck& paycheck)
{
}


std::string MailMethod::GetAddress() const
{
    return itsAddress;
}
