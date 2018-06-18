#ifndef JCANDLE_H
#define JCANDLE_H


class JCandle
{
public:
	JCandle();
private:
	double time_;
	double open_;
	double close_;
	double hight_;
	double low_;
	double volume_;
	double quantity_;
public:
    double getTime(){return time_;};
	double getOpen(){return open_;};
	double getClose(){return close_;};
	double getHight(){return hight_;};
	double getLow(){return low_;};
	double getVolume(){return volume_;};
	double getQuantity(){return quantity_;};

	void setTime(double _time){time_=_time;};
	void setOpen(double _open){open_=_open;};
	void setClose(double _close){close_=_close;};
	void setHight(double _hight){hight_=_hight;};
	void setLow(double _low){low_=_low;};
	void setVolume(double _volume){volume_=_volume;};
	void setQuantity(double _quantity){quantity_=_quantity;};
};

#endif // JCANDLE_H
