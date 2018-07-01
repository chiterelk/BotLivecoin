#ifndef JBALANCE_H
#define JBALANCE_H

#include <QObject>

class JBalance
{
public:
    JBalance();
	 QString getCurrency() const {return currency_;};
	 double getTotal() const {return total_;};
	 double getAvailable() const {return available_;};
	 double getTrade() const {return trade_;};
	 double getAvailableWithdrawal() const {return availableWithdrawal_;};

    void setCurrency(QString _currency);
    void setTotal(double _total);
    void setAvailable(double _available);
    void setTrade(double _trade);
    void setAvailableWithdrawal(double _availableWithdrawal);

private:
    QString currency_;
    double total_;
    double available_;
    double trade_;
    double availableWithdrawal_;
};

#endif // JBALANCE_H
