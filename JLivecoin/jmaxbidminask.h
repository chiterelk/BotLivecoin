#ifndef JMAXBIDMINASK_H
#define JMAXBIDMINASK_H

#include <QString>

class JMaxBidMinAsk
{
public:
    JMaxBidMinAsk();
    JMaxBidMinAsk(QString _symbol, double _maxBid, double _minAsk);

    QString getSymbol(){    return symbol_; };
    double getMaxBid(){ return maxBid_; };
    double getMinAsk(){ return minAsk_; };

private:
    QString symbol_;
    double maxBid_ = 0;
    double minAsk_ = 0;
};

#endif // JMAXBIDMINASK_H
