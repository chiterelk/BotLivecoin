#ifndef JLIVECOIN_H
#define JLIVECOIN_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QVector>

#include "jbalance.h"
#include "jmaxbidminask.h"
#include "jorder.h"


class JLivecoin : public QObject
{
    Q_OBJECT
public:
    explicit JLivecoin(QObject *parent = nullptr);
    void getExchengeTicker();//получить все тикеры
    void getExchengeTicker(QString _currencyPair);//Получить тикер по выбраной паре
    void getExchengeMaxBidMinAsk();//получить все биды и аски
    void getExchengeMaxBidMinAsk(QString _currencyPair);//получить бид и аск по выбраной паре


    void getPaymentBalances(QString _apiKey, QString _secretKey, QString _currency);
    void getPaymentBalances(QString _apiKey, QString _secretKey);

    void sellLimit(QString _currencyPair,double _price,double _quantity, QString _apiKey, QString _secretKey);//выставление ордера на продажу
    void buyLimit(QString _currencyPair,double _price,double _quantity, QString _apiKey, QString _secretKey);
    void cancelLimit(QString _currencyPair, double orderId, QString _apiKey, QString _secretKey);
    void getOrder(double _orderId, QString _apiKey, QString _secretKey);
    static QString httpBuildQuery(QString _parametr);
private:
    QNetworkAccessManager *QNAM = new QNetworkAccessManager(this);
    QString baseUrl = "https://api.livecoin.net";

    void gotData(QNetworkReply *reply);

signals:
    void gotMaxBidMinAsk(JMaxBidMinAsk);
	 void gotBalance(QVector<JBalance>);
    void openedSellLimit(double orderId);
    void openedBuyLimit(double orderId);
    void canceledLimit(double quantity, double tradeQuantity);
    void gotOrder(JOrder);
	 void error(QString);



public slots:
};

#endif // JLIVECOIN_H
