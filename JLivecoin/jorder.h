#ifndef JORDER_H
#define JORDER_H
#include <QString>


class JOrder
{
public:
    JOrder();
	 JOrder(double _id){ id_=_id;    };
    void setId(double _id){ id_=_id;    };
    void setClientId(double _clientId){ clientId_=_clientId;    };
    void setStatus(QString _status){    status_=_status;    };
    void setSymbol(QString _symbol){    symbol_=_symbol;    };
    void setPrice(double _price){   price_=_price;  };
    void setQuantity(double _quantity){ quantity_=_quantity;    };
    void setRemainingQuantity(double _remainingQuantity){   remainingQuantity_=_remainingQuantity;  };
    void setBlocked(double _blocked){   blocked_=_blocked;  };
    void setBlockedRemain(double _blockedRemain){   blockedRemain_=_blockedRemain; };
    void setCommissionRate(double _commission_rate){    commission_rate_=_commission_rate;  };
	 void setType(QString _type){ type_ = _type;	};

	 double getId() const {    return id_; };
	 double getClientId() const {  return clientId_;   };
	 QString getStatus() const {   return status_; };
	 QString getSymbol() const {   return symbol_; };
	 double getPrice() const { return price_;  };
	 double getQuantity() const {  return quantity_;   };
	 double getRemainingQuantity() const { return remainingQuantity_;  };
	 double getBlocked() const {   return blocked_;    };
	 double getBlockedRemain() const { return blockedRemain_;  };
	 double getCommissionRate() const {   return commission_rate_;    };
	 QString getType() const { return type_;	};

private:
    double id_;
    double clientId_;
    QString status_;
    QString symbol_;
    double price_;
    double quantity_;
    double remainingQuantity_;
    double blocked_;
    double blockedRemain_;
    double commission_rate_;
	 QString type_;
};

#endif // JORDER_H
