#ifndef JSELLORDER_H
#define JSELLORDER_H

#include <QString>


class JSellOrder
{
public:
	JSellOrder(double _price, double _quantity, QString _currencyPair);
	double getPrice(){	return price_;	};
	double getQuantity(){	return quantity_;	};
	QString getCurrencyPair(){	return currencyPair_;	};
private:
	double price_ = 0.0;
	double quantity_ = 0.0;
	QString currencyPair_;
};

#endif // JSELLORDER_H
