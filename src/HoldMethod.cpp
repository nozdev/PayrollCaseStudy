#include "HoldMethod.h"

#include "PayrollDomain/Paycheck.h"


HoldMethod::~HoldMethod()
{
}


void HoldMethod::Pay(Paycheck& paycheck)
{
    paycheck.SetField(
        "Disposition",
        "Hold");
}
