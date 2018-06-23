#include "jwslivecoin.h"

#include <QUrl>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include "jticker.h"
#include "mainwindow.h"


JWSLivecoin::JWSLivecoin(QObject *parent) : QObject(parent)
{
    QObject::connect(WSocket,&QWebSocket::connected,this,&JWSLivecoin::connected);
    QObject::connect(WSocket,&QWebSocket::textMessageReceived,this,&JWSLivecoin::textMessageReceived);
    QObject::connect(WSocket,&QWebSocket::disconnected,this,&JWSLivecoin::disconnected);
    //QObject::connect(timer,&QTimer::timeout,this,&JWSLivecoin::connect);

    timer->setInterval(5000);
}

JWSLivecoin::~JWSLivecoin()
{
    disconnect();
    delete WSocket;


}

void JWSLivecoin::connect(QString _currensyPair)
{
    if(timer->isActive())
	 {
        timer->stop();
	 }
	 WSocket->open(QUrl(QStringLiteral("wss://ws.api.livecoin.net/ws/beta")));
    currensyPair_ = _currensyPair;
}

void JWSLivecoin::disconnected()
{
    qDebug()<<"Disconnected!";
    timer->start();
}
void JWSLivecoin::connected()
{
    if(timer->isActive())
    {
        timer->stop();
    }
    qDebug()<<"Connected!";
    QJsonDocument doc;
    QJsonObject root;
    root.insert("channelType","ticker");
	 root.insert("symbol",currensyPair_);
    root.insert("frequency",QJsonValue());
    root.insert("depth",QJsonValue());

    QJsonObject sub;
    sub.insert("Subscribe",QJsonValue(root));
    doc.setObject(sub);
    WSocket->sendTextMessage(doc.toJson());
	 WSocket->sendTextMessage(makeParamCandle(currensyPair_,"1m").toJson());
}

void JWSLivecoin::textMessageReceived(QString message)
{
     //qDebug()<<message;
	 if(!(message == QString("")))
	 {
		 QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
		 QJsonObject root = doc.object();
		 if(!root.value("operation").isObject())
		 {
			 if(root.value("channelId").toString() == "ETH/USD_ticker")
			 {
				 JTicker ticker;
				 ticker.setBidAndAsk(root.value("bestBid").toDouble(),root.value("bestAsk").toDouble());
				 emit gotTicker(ticker);
			 }
			 if(root.value("channelId").toString() == "ETH/USD_candle")
			 {
				 JCandle candle;
				 candle.setTime(root.value("t").toDouble());
				 candle.setOpen(root.value("o").toDouble());
				 candle.setClose(root.value("c").toDouble());
				 candle.setHight(root.value("h").toDouble());
				 candle.setLow(root.value("l").toDouble());
				 candle.setVolume(root.value("v").toDouble());
				 candle.setQuantity(root.value("q").toDouble());
				 emit gotCandle(candle);
			 }

		 }else{
			QJsonObject operation = root.value("operation").toObject();

			if(operation.value("Subscribe").isObject())
			{
				if(root.value("data").isArray())
				{
					QJsonArray data = root.value("data").toArray();
					QList <JCandle> candles;
					for(int i = 0; i<data.count();i++)
					{

						JCandle candle;
						candle.setTime(data.at(i).toObject().value("t").toDouble());
						candle.setOpen(data.at(i).toObject().value("o").toDouble());
						candle.setClose(data.at(i).toObject().value("c").toDouble());
						candle.setHight(data.at(i).toObject().value("h").toDouble());
						candle.setLow(data.at(i).toObject().value("l").toDouble());
						candle.setVolume(data.at(i).toObject().value("v").toDouble());
						candle.setQuantity(data.at(i).toObject().value("q").toDouble());
						candles.append(candle);

					}
					emit gotCandles(candles);
                    qDebug()<<"count: "<<candles.count();

				}
			}

		 }


	 }

//    if(!(message==QString("")))
//    {

//		 JTicker ticker;
//		 QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
//		 QJsonObject root = doc.object();



//		 if(!root.value("operation").isObject())//Игнорирую первое сообщение
//		 {
//			  ticker.setBidAndAsk(root.value("bestBid").toDouble(),root.value("bestAsk").toDouble());
//			  emit gotTicker(ticker);
//		 }

//    }else{

//    }

}

QJsonDocument JWSLivecoin::makeParamCandle(QString _currencyPair, QString _interval)
{
	QJsonDocument doc;
	QJsonObject root;
	root.insert("channelType","candle");
	root.insert("symbol",_currencyPair);
	root.insert("interval",_interval);


	QJsonObject sub;
	sub.insert("Subscribe",QJsonValue(root));
	doc.setObject(sub);
	return doc;
}

