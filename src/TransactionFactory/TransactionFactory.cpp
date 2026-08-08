#include "TransactionFactory/TransactionFactory.h"
#include <stdexcept>

TransactionFactory* TransactionFactory::transactionFactory = nullptr;

void TransactionFactory::SetFactory(TransactionFactory* factory)
{
    transactionFactory = factory;
}

TransactionFactory& TransactionFactory::GetFactory()
{
    if (transactionFactory == nullptr)
        throw std::runtime_error("TransactionFactory has not been initialized");

    return *transactionFactory;
}
