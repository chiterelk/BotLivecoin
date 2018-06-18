#include "jbalance.h"

JBalance::JBalance(QObject *parent) : QObject(parent)
{

}

void JBalance::setCurrency(QString _currency)
{
    currency_ = _currency;
}

void JBalance::setTotal(double _total)
{
    total_ = _total;
}

void JBalance::setAvailable(double _available)
{
    available_ = _available;
}

void JBalance::setTrade(double _trade)
{
    trade_ = _trade;
}

void JBalance::setAvailableWithdrawal(double _availableWithdrawal)
{
    availableWithdrawal_ = _availableWithdrawal;
}
