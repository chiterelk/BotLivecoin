#include "jmaxbidminask.h"

JMaxBidMinAsk::JMaxBidMinAsk()
{

}

JMaxBidMinAsk::JMaxBidMinAsk(QString _symbol, double _maxBid, double _minAsk)
{
    symbol_ = _symbol;
    maxBid_ = _maxBid;
    minAsk_ = _minAsk;
}
