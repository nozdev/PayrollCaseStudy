#include "HoldMethod.h"

#include "Paycheck.h"


HoldMethod::~HoldMethod()
{
}


void HoldMethod::Pay(Paycheck& paycheck)
{
    paycheck.SetField(
        "Disposition",
        "Hold");
}
