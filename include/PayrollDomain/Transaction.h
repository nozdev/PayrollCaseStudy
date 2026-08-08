#ifndef TRANSACTION_H
#define TRANSACTION_H

class Transaction
{
public:
    virtual ~Transaction() = default;

    virtual void Execute() = 0;
};

#endif

