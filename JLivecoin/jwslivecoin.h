#ifndef JWSLIVECOIN_H
#define JWSLIVECOIN_H

#include <QtWebSockets/QtWebSockets>
#include <QObject>
#include "jticker.h"
#include "jcandle.h"
#include <QList>
#include <QTimer>


class JWSLivecoin : public QObject
{
    Q_OBJECT
public:
    explicit JWSLivecoin(QObject *parent = nullptr);
    ~JWSLivecoin();
	 void connect(QString _currensyPair);
    //void disconnect();

private:
    QWebSocket *WSocket = new QWebSocket();
    void disconnected();
	 void connected();
    void textMessageReceived(QString message);
	 QString currensyPair_;
	 QJsonDocument makeParamCandle(QString _currencyPair,QString _interval);
     QTimer *timer = new QTimer(this);
signals:
    void gotTicker(JTicker);
	 void gotCandle(JCandle);
	 void gotCandles(QList<JCandle>);

public slots:
};

#endif // JWSLIVECOIN_H
