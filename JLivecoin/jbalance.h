#ifndef JBALANCE_H
#define JBALANCE_H

#include <QObject>

class JBalance : public QObject
{
    Q_OBJECT
public:
    explicit JBalance(QObject *parent = nullptr);
    JBalance();
    QString getCurrency(){return currency_;};
    double getTotal(){return total_;};
    double getAvailable(){return available_;};
    double getTrade(){return trade_;};
    double getAvailableWithdrawal(){return availableWithdrawal_;};

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
signals:

public slots:
};

#endif // JBALANCE_H
