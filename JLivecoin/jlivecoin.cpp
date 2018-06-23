#include "jlivecoin.h"
#include <QUrl>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QCryptographicHash>
#include <QMessageAuthenticationCode>
#include <QVector>


#include "jmaxbidminask.h"

JLivecoin::JLivecoin(QObject *parent) : QObject(parent)
{
    connect(QNAM,&QNetworkAccessManager::finished,this,&JLivecoin::gotData);
}

void JLivecoin::getExchengeTicker()//получение асков, бидов обьемов по всех парах
{
    QNetworkRequest requsest;
    requsest.setUrl(QUrl(baseUrl+"/exchange/ticker"));
    QNAM->get(requsest);
}

void JLivecoin::getExchengeTicker(QString _currencyPair)//получение асков, бидов обьемов по указаной паре
{
    QNetworkRequest requsest;
    requsest.setUrl(QUrl(baseUrl+"/exchange/ticker?currencyPair="+_currencyPair));
    QNAM->get(requsest);
}

void JLivecoin::getExchengeMaxBidMinAsk()//получение асков, бидов по всех парах
{
    QNetworkRequest requsest;
    requsest.setUrl(QUrl(baseUrl+"/exchange/maxbid_minask"));
    QNAM->get(requsest);
}

void JLivecoin::getExchengeMaxBidMinAsk(QString _currencyPair)//получение асков, бидов по указаной паре
{
    QNetworkRequest requsest;
    requsest.setUrl(QUrl(baseUrl+"/exchange/maxbid_minask?currencyPair="+_currencyPair));
    QNAM->get(requsest);
}

void JLivecoin::getPaymentBalances(QString _apiKey, QString _secretKey, QString _currency)
{
	 QString parametr = "currency=" + _currency;
	 QString url = QString(baseUrl + "/payment/balances?currency=" + _currency);


    QMessageAuthenticationCode code(QCryptographicHash::Sha256);
    code.setKey(_secretKey.toUtf8());
	 code.addData(parametr.toUtf8());

    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    request.setRawHeader("Api-Key",_apiKey.toUtf8());
    request.setRawHeader("Sign",code.result().toHex().toUpper());

    QNAM->get(request);
}

void JLivecoin::getPaymentBalances(QString _apiKey, QString _secretKey)
{
    QString url = QString(baseUrl + "/payment/balances");
    QMessageAuthenticationCode code(QCryptographicHash::Sha256);
    code.setKey(_secretKey.toUtf8());
    code.addData("");

    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    request.setRawHeader("Api-Key",_apiKey.toUtf8());
    request.setRawHeader("Sign",code.result().toHex().toUpper());

    QNAM->get(request);
}

void JLivecoin::sellLimit(QString _currencyPair, double _price, double _quantity, QString _apiKey, QString _secretKey)
{
    QString parametr = "currencyPair=" + _currencyPair+"&price="+QString::number(_price)+"&quantity="+QString::number(_quantity);
    parametr = JLivecoin::httpBuildQuery(parametr);
    QString url = QString(baseUrl + "/exchange/selllimit");
    QMessageAuthenticationCode code(QCryptographicHash::Sha256);
    code.setKey(_secretKey.toUtf8());
    code.addData(parametr.toUtf8());

    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    request.setRawHeader("Api-Key",_apiKey.toUtf8());
    request.setRawHeader("Sign",code.result().toHex().toUpper());

    QNAM->post(request,parametr.toUtf8());
}

void JLivecoin::buyLimit(QString _currencyPair, double _price, double _quantity, QString _apiKey, QString _secretKey)
{
    QString parametr = "currencyPair=" + _currencyPair+"&price="+QString::number(_price)+"&quantity="+QString::number(_quantity);
    parametr = JLivecoin::httpBuildQuery(parametr);
    QString url = QString(baseUrl + "/exchange/buylimit");
    QMessageAuthenticationCode code(QCryptographicHash::Sha256);
    code.setKey(_secretKey.toUtf8());
    code.addData(parametr.toUtf8());

    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    request.setRawHeader("Api-Key",_apiKey.toUtf8());
    request.setRawHeader("Sign",code.result().toHex().toUpper());

    QNAM->post(request,parametr.toUtf8());
}

void JLivecoin::cancelLimit(QString _currencyPair, double _orderId, QString _apiKey, QString _secretKey)
{
    QString parametr = "currencyPair=" + _currencyPair+"&orderId="+QString::number(_orderId,'g',20);
    parametr = JLivecoin::httpBuildQuery(parametr);
    QString url = QString(baseUrl + "/exchange/cancellimit");
    QMessageAuthenticationCode code(QCryptographicHash::Sha256);
    code.setKey(_secretKey.toUtf8());
    code.addData(parametr.toUtf8());

    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    request.setRawHeader("Api-Key",_apiKey.toUtf8());
    request.setRawHeader("Sign",code.result().toHex().toUpper());

    QNAM->post(request,parametr.toUtf8());
}

void JLivecoin::getOrder(double _orderId, QString _apiKey, QString _secretKey)
{
    QString parametr = "orderId="+QString::number(_orderId,'g',20);
    QString url = QString(baseUrl + "/exchange/order?"+parametr);
    QMessageAuthenticationCode code(QCryptographicHash::Sha256);
    code.setKey(_secretKey.toUtf8());
    code.addData(parametr.toUtf8());

    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    request.setRawHeader("Api-Key",_apiKey.toUtf8());
    request.setRawHeader("Sign",code.result().toHex().toUpper());

    QNAM->get(request);
}

QString JLivecoin::httpBuildQuery(QString _parametr)
{
    _parametr.replace("/","%2F");
    _parametr.replace("@","%40");
    _parametr.replace(";","%3B");
    return _parametr;
}

void JLivecoin::gotData(QNetworkReply *reply)
{
    if(!reply->error())
    {
        //qDebug()<<reply->url().toString();
        QString data = reply->readAll();
        if(data.indexOf("0E-8"))
        {
            data.replace("0E-8","0");
        }
        QString url = reply->url().toString();


        if(url.indexOf("/exchange/ticker") >= 0)// если это пришли аски, биды и обьемы....
        {
            if(url.indexOf("currencyPair=") >= 0)
            {
                //если указанна пара
                QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
                QJsonObject root = doc.object();
                qDebug()<<root;

            }else{
                //если не указанна пара
                QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
                QJsonArray root = doc.array();
                qDebug()<<root.at(0).toObject();
            }

        }
        if(url.indexOf("/exchange/maxbid_minask")>=1)// если это пришли только аски и биды.....
        {
            if(url.indexOf("currencyPair=") >= 0)
            {
                //если указанна пара
                QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
                QJsonObject root = doc.object();
                QJsonObject currencyPair = root.value("currencyPairs").toArray().at(0).toObject();
                qDebug()<<currencyPair.value("symbol").toString();
                JMaxBidMinAsk maxBidMinAsk(currencyPair.value("symbol").toString(),currencyPair.value("maxBid").toString().toDouble(),currencyPair.value("minAsk").toString().toDouble());
                emit gotMaxBidMinAsk(maxBidMinAsk);
            }else{
                //если не указанна пара
                QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());


                //дописать









            }
        }
        if(url.indexOf("/payment/balances")>=1)
        {
            if(/*url.indexOf("currency=") >= 0*/1)
            {
                QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
                QJsonArray root = doc.array();
                QVector<JBalance*> wallet;
                if(root.count() > 0)
                {

                    QString currency ="";
                    for(int i = 0;i<(root.count());i++)
                    {
                        if(currency != root.at(i).toObject().value("currency").toString())
                        {
                            wallet << new JBalance(this);
                            wallet.last()->setCurrency(root.at(i).toObject().value("currency").toString());
                            currency = root.at(i).toObject().value("currency").toString();
                        }
                        if(root.at(i).toObject().value("type").toString() == "total")
                        {
                            wallet.last()->setTotal(root.at(i).toObject().value("value").toDouble());
                        }
                        if(root.at(i).toObject().value("type").toString() == "available")
                        {
                            wallet.last()->setAvailable(root.at(i).toObject().value("value").toDouble());
                        }
                        if(root.at(i).toObject().value("type").toString() == "trade")
                        {
                            wallet.last()->setTrade(root.at(i).toObject().value("value").toDouble());
                        }
                        if(root.at(i).toObject().value("type").toString() == "available_withdrawal")
                        {
                            wallet.last()->setAvailableWithdrawal(root.at(i).toObject().value("value").toDouble());
                        }





                    }
                }
                qDebug()<<wallet.count();
                emit gotBalance(wallet);
                wallet.clear();

            }else{

                //дописать





            }
        }

        if(url.indexOf("/exchange/selllimit")>=1)
        {
            QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
            QJsonObject root = doc.object();
				qDebug()<<root.value("orderId").toDouble();
            emit openedSellLimit(root.value("orderId").toDouble());
        }//end selllimit
        if(url.indexOf("/exchange/buylimit")>=1)
        {
            QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
            QJsonObject root = doc.object();
            emit openedBuyLimit(root.value("orderId").toDouble());
        }//end buylimit

        if(url.indexOf("/exchange/cancellimit")>=1)
        {
            QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
            QJsonObject root = doc.object();
            emit canceledLimit(root.value("quantity").toDouble(),root.value("tradeQuantity").toDouble());
        }//end cancellimit
        if(url.indexOf("/exchange/order")>=1)
        {
            QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
            QJsonObject root = doc.object();
            JOrder order;
            order.setId(root.value("id").toDouble());
            order.setClientId(root.value("client_id").toDouble());
            order.setStatus(root.value("status").toString());
            order.setSymbol(root.value("symbol").toString());
            order.setPrice(root.value("price").toDouble());
            order.setQuantity(root.value("quantity").toDouble());
            order.setRemainingQuantity(root.value("remining_quantity").toDouble());
            order.setBlocked(root.value("blocked").toDouble());
            order.setBlockedRemain(root.value("blocked_remain").toDouble());
            order.setCommissionRate(root.value("commission_rate").toDouble());
            emit gotOrder(order);
        }
    }else{
        qDebug()<<"Error: "<<reply->errorString()<<'.';
		  emit error(reply->errorString());
	 }
}


