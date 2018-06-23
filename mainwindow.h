#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QList>
#include <QGridLayout>
#include <QNetworkAccessManager>
#include <QTime>
#include "JLivecoin/jwslivecoin.h"
#include "JLivecoin/jlivecoin.h"
#include "JLivecoin/jorder.h"

#include "jsellorder.h"
#include "JLivecoin/jcandle.h"
#include "jtablmodel.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();



private:

	Ui::MainWindow *ui;
	QTimer *mainTimer = new QTimer(this);
	JWSLivecoin *WSLivecoin = new JWSLivecoin(this);
	JLivecoin *Livecoin = new JLivecoin(this);
    QTimer *watchDog = new QTimer(this);

    QNetworkAccessManager * NAMTelegram = new QNetworkAccessManager(this);


	QString apiKey = "KH91fPFZ2c4fVeQVr4FtnadbaeYAg9YR";
	QString secretKey = "";

	double ask = 0.0;
	double bid = 0.0;

	double usdTotal = 0.00;
	double usdAvailable = 0.00;
    double usdTrade = 0.00;
    double ethTotal = 0.00;
    double ethAvailable = 0.00;
    double ethTrade = 0.00;
    double xemTotal = 0.00;
    double xemAvailable = 0.00;
    double xemTrade = 0.00;


	double minValueUsd = 0.0;

    unsigned int process = 100;

	int period = 5000;

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //

    double perekritie = 0.010;//перекрытие в относительних единицах.
    double numberOrders = 2; //количество страховочних ордеров.
    double otstup = 0.01;//отступ в относительних единицах.
    double martingeil = 0.01;//на сколько процентов увеличивается обьем следующего ордера.
    double profit = 0.20;//Прибыль в относительных единицах, без учета комисии.
    double procent = 0.04;//Если цена выросла на это кол. процентов, то переставляем ордера.
    double depozit = 0.98;//процент от депозита.
    double Depozit = 100.00;//...


// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //

	QString currensyPair = "ETH/USD";
	QList <JSellOrder*> buyOrders;

	QList <JOrder*> openedBuyOrders;
	QList <JOrder*> openedSellOrders;

	double midPrice = 0;
	double summQuntity = 0;

	JTablModel *listOpenedOrders = new JTablModel(this);

private slots:
	void gotTicker(JTicker ticker);
    void gotCandles(QList<JCandle>);
	void gotBalance(QVector<JBalance*>);
	void gotTickerBtcUsd(JMaxBidMinAsk);
	void mainProcess();
	void openedBuyLimit(double orderId);
	void error(QString);
	void gotOrder(JOrder);
	void openedSellLimit(double orderId);
	void canceledLimit(double quantity, double tradeQuantity);

    void sendMesageToTelegram(QString _mesage);
    void showOrders();

    void connectWS();
	void getPaymentBalances();


    void on_pushButton_clicked();
	 void resizeEvent(QResizeEvent*);



};

#endif // MAINWINDOW_H
