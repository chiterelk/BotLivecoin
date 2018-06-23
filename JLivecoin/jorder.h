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


    double getId(){    return id_; };
    double getClientId(){  return clientId_;   };
    QString getStatus(){   return status_; };
    QString getSymbol(){   return symbol_; };
    double getPrice(){ return price_;  };
    double getQuantity(){  return quantity_;   };
    double getRemainingQuantity(){ return remainingQuantity_;  };
    double getBlocked(){   return blocked_;    };
    double getBlockedRemain(){ return blockedRemain_;  };
    double getCommissionRate(){   return commission_rate_;    };
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
};

#endif // JORDER_H
