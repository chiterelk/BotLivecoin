#include "jticker.h"

JTicker::JTicker()
{
     last_ = 0.0;
     high_ = 0.0;
     low_ = 0.0;
     volume_ = 0.0;
     vwap_ = 0.0;
     max_bid_ = 0.0;
     min_ask_ = 0.0;
     best_bid_ = 0.0;
     best_ask_ = 0.0;
}

void JTicker::setLast(double _last)
{
    last_ = _last;
}

void JTicker::setHigh(double _higt)
{
    high_ = _higt;
}

void JTicker::setLow(double _low)
{
    low_ = _low;
}

void JTicker::setVolume(double _volume)
{
    volume_ = _volume;
}

void JTicker::setVwap(double _vwap)
{
    vwap_ = _vwap;
}

void JTicker::setBidAndAsk(double _best_bid, double _best_ask)
{
    best_bid_ = _best_bid;
    best_ask_ = _best_ask;
    spread_ = (_best_ask-_best_bid)/_best_ask;
}
void JTicker::setMax_bid(double _max_bid)
{
    max_bid_ = _max_bid;
}

void JTicker::setMin_ask(double _min_ask)
{
    min_ask_ = _min_ask;
}

void JTicker::setBest_bid(double _best_bid)
{
    best_bid_ = _best_bid;
}

void JTicker::setBest_ask(double _best_ask)
{
    best_ask_ = _best_ask;
}
