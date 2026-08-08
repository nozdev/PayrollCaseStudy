#ifndef HOLDMETHOD_H
#define HOLDMETHOD_H

#include "PaymentMethod.h"

class HoldMethod : public PaymentMethod
{
public:

    virtual ~HoldMethod();

    void Pay(Paycheck& paycheck) override;
};

#endif
