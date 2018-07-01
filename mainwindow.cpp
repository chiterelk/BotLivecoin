#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QDebug>
#include <QDateTime>
#include <cmath>
#include <JLivecoin/jcandle.h>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->groupBoxPair->hide();

	on_comboBoxSymbol_currentTextChanged(ui->comboBoxSymbol->currentText());
	
	connect(WSLivecoin,&JWSLivecoin::gotTicker,this,&MainWindow::gotTicker);
	connect(WSLivecoin,&JWSLivecoin::gotCandles,this,&MainWindow::gotCandles);
	connect(Livecoin,&JLivecoin::gotBalance,this,&MainWindow::gotBalance);
	connect(Livecoin,&JLivecoin::openedBuyLimit,this,&MainWindow::openedBuyLimit);
	connect(Livecoin,&JLivecoin::error,this,&MainWindow::error);
	connect(Livecoin,&JLivecoin::gotOrder,this,&MainWindow::gotOrder);
	connect(Livecoin,&JLivecoin::openedSellLimit,this,&MainWindow::openedSellLimit);
	connect(Livecoin,&JLivecoin::canceledLimit,this,&MainWindow::canceledLimit);

	connect(watchDog,&QTimer::timeout,this,&MainWindow::connectWS);
	//connectWS();

	getPaymentBalances();
	connect(Livecoin,&JLivecoin::gotMaxBidMinAsk,this,&MainWindow::gotTickerBtcUsd);
	Livecoin->getExchengeMaxBidMinAsk(currensyPair);

	ui->console->append("Программа запущена. Готовлюсь к виставлению ордеров.");
	connect(mainTimer,&QTimer::timeout,this,&MainWindow::mainProcess);
	mainTimer->setInterval(period);

	ui->tableViewOrders->setModel(listOpenedOrders);
	ui->tableViewOrders->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	ui->tableViewBalances->setModel(listBalance);
	ui->tableViewBalances->setColumnWidth(0,ui->tableViewBalances->width()/4);
	ui->tableViewBalances->setColumnWidth(1,ui->tableViewBalances->width()/4);
	ui->tableViewBalances->setColumnWidth(2,ui->tableViewBalances->width()/4);
	ui->tableViewBalances->setColumnWidth(3,ui->tableViewBalances->width()/4);
	ui->tableViewBalances->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	ui->statusBar->addWidget(processInf,0);
	ui->statusBar->addWidget(pingInf,0);
	showProcess();


}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::gotTicker(JTicker ticker)
{
	watchDog->stop();
	ui->labelAsk->setText(QString::number(ticker.getBest_ask(),'g',10));
	ui->labelBid->setText(QString::number(ticker.getBest_bid(),'g',10));
	ui->labelSpread->setText(QString::number(ticker.getSpread()*100,'g',3)+"%");
	if(ticker.getBest_ask()!=0)
		ask = ticker.getBest_ask();
	if(ticker.getBest_bid()!=0)
        bid = ticker.getBest_bid();
    watchDog->start(600000);
	 if(firstConnect)
	 {
		 process = 0;
		 ui->groupBoxPair->show();
	 }
}

void MainWindow::gotCandles(QList<JCandle> _candles)
{

}

void MainWindow::gotBalance(QVector<JBalance> wallet)
{
	for(int i = 0; i<wallet.count();i++)
	{
			if(wallet.at(i).getCurrency()=="USD")
			{
				usdTotal = wallet.at(i).getTotal();
				usdAvailable = wallet.at(i).getAvailable();
				usdTrade = wallet.at(i).getTrade();
			}
			if(wallet.at(i).getCurrency()=="ETH")
			{
				ethTotal = wallet.at(i).getTotal();
				ethAvailable = wallet.at(i).getAvailable();
				ethTrade = wallet.at(i).getTrade();

			}
	}
	if(ui->hideZeroBalances->isChecked())
	{
		for(int i = wallet.count()-1; i>=0; i--)
		{
			if(wallet.at(i).getTotal() == 0 && wallet.at(i).getAvailable()==0 && wallet.at(i).getTrade()==0)
			{
				if(!(wallet.at(i).getCurrency()=="ETH" || wallet.at(i).getCurrency()=="USD" || wallet.at(i).getCurrency()=="BTC"))
				{
					wallet.remove(i);
				}
			}
		}
	}
	listBalance->setBalance(wallet);
}

void MainWindow::gotTickerBtcUsd(JMaxBidMinAsk _tickerBtcUsd)
{
	disconnect(Livecoin,&JLivecoin::gotMaxBidMinAsk,this,&MainWindow::gotTickerBtcUsd);
	minValueUsd = 0.0002 * _tickerBtcUsd.getMaxBid();
	//qDebug()<<minValueUsd;
}

void MainWindow::mainProcess()
{
	if(process == 100)
	{
		connectWS();
	}
	if(process == 0) //бот не торгует. Ожидаю момента для входа в сделку.
	{
		Depozit = depozit * usdAvailable;
		if(minValueUsd != 0)
		{
			double summ = 0;
			for(double i = 0; i<numberOrders;i++)
			{
                summ += 1 + martingeil * i;
                //summ += 1 + pow(martingeil,i);
			}
			double stepQuantity = Depozit/summ;
			//qDebug()<<"Первий ордер"<<stepQuantity;
			double maxPrice = (bid - bid * otstup);
            double stepPrice;
            if(numberOrders != 1)
            {
                stepPrice = (maxPrice - (bid - bid * perekritie))/(numberOrders -1);
            }else{
                stepPrice = 0;
            }



			buyOrders.clear();
			if(minValueUsd < stepQuantity)
			{
				for(double i = 0; i<numberOrders;i++)
				{

                    double price = maxPrice - i * stepPrice;
                    //qDebug()<<"Quantity"<<i+1<<": "<<(stepQuantity + martingeil * stepQuantity * i)/price;
                    //buyOrders << new JSellOrder(price,(stepQuantity + pow(martingeil,i) * stepQuantity)/price,currensyPair);
						  buyOrders << JSellOrder(price,(stepQuantity + martingeil * stepQuantity * i)/price,currensyPair);
				}
                //qDebug()<<"buyOrders.count()"<<buyOrders.count();
				process = 1;

				showProcess();
				sendMesageToTelegram("Начинаю выставлять ордера на покупку.");
				ui->console->append("Начинаю выставлять ордера на покупку.");
			}else{
				ui->console->append("Недостаточный баланс для вибраного количества ордеров!");
                sendMesageToTelegram("Недостаточный баланс для вибраного количества ордеров!");
                process = 100;
					 showProcess();
				mainTimer->stop();
                ui->groupBox_5->setHidden(false);
			}
		}
	}
	if(process == 1)//идет виставление ордеров
	{

		if(!buyOrders.isEmpty())
		{
			//qDebug()<<currensyPair<<buyOrders.first()->getPrice()<<buyOrders.first()->getQuantity();
			Livecoin->buyLimit(currensyPair,buyOrders.first().getPrice(),buyOrders.first().getQuantity(),apiKey,secretKey);
			openedBuyOrders.append(JOrder());
			openedBuyOrders.last().setPrice(buyOrders.first().getPrice());
			openedBuyOrders.last().setQuantity(buyOrders.first().getQuantity());
			process = 11;
			showProcess();
			mainTimer->setInterval(1000);
		}
	}
	if(process == 2)//Мониторинг ордеров.
	{
        if(!openedSellOrders.isEmpty())
        {
            if(openedSellOrders.count() == numberOrders)
            {
					 if(bid > (openedBuyOrders.first().getPrice()*(1+otstup)*(1+procent)))
                            {
                                ui->console->append("Цена ушла. Переставляю ордера");
                                sendMesageToTelegram("Цена ушла. Переставляю ордера.");
                                process = 4;
										  showProcess();
                            }
            }

        }
        if(!openedBuyOrders.isEmpty())
        {
				Livecoin->getOrder(openedBuyOrders.first().getId(),apiKey,secretKey);
        }
        if(!openedSellOrders.isEmpty())
        {
				Livecoin->getOrder(openedSellOrders.first().getId(),apiKey,secretKey);
        }

	}
	if(process == 3)//Перестановка ордера на продажу
	{
		if(openedSellOrders.isEmpty())
		{
			process = 13;
			showProcess();
//			if(midPrice > bid*(1-otstup))
//			{

                Livecoin->sellLimit(currensyPair,midPrice*(1+profit),summQuntity-0.00000001,apiKey,secretKey);
//			}

		}else{
			process = 12;
			showProcess();
			Livecoin->cancelLimit(currensyPair,openedSellOrders.first().getId(),apiKey,secretKey);

		}
	}
	if(process == 4)
	{
		if(!openedBuyOrders.isEmpty())
		{
			process = 14;
			showProcess();
			Livecoin->cancelLimit(currensyPair,openedBuyOrders.first().getId(),apiKey,secretKey);
		}else{
            //mainTimer->stop();
            //ui->console->append("End");
            buyOrders.clear();

            openedBuyOrders.clear();
            openedSellOrders.clear();

            midPrice = 0;
            summQuntity = 0;



            process = 0;
				showProcess();
		}
	}
//	if(process == 5)
//	{

//	}
	if(process == 11)//ожидание пока ордер виставиться
	{

	}
	if(process == 12)//ожидание пока убирается ордер
	{

	}
	if(process == 13)//ожидание пока ордер на продажу выставляеться.
	{

	}
	if(process == 14)
	{

	}
}

void MainWindow::openedBuyLimit(double orderId)
{
	getPaymentBalances();
	//openedBuyOrders << new JOrder(orderId);
	openedBuyOrders.last().setId(orderId);
	openedBuyOrders.last().setType("Buy");
	buyOrders.removeFirst();
	if(!buyOrders.isEmpty())
	{
		process = 1;
		showProcess();
	}else{
		mainTimer->setInterval(period);
		process = 2;
		showProcess();
		showOrders();
		sendMesageToTelegram("Ордера на покупку виставлены.");
		ui->console->append("Ордера на покупку виставлены.");
		sendMesageToTelegram("Мониторю.");
		ui->console->append("Мониторю.");
	}
}
void MainWindow::openedSellLimit(double orderId)
{
	getPaymentBalances();
    if(process == 13)
    {
		  openedSellOrders <<JOrder(orderId);
		  openedSellOrders.last().setType("Sell");
		  openedSellOrders.last().setPrice(midPrice*(1+profit));
		  openedSellOrders.last().setQuantity(summQuntity-0.00000001);
        process = 2;
		  showProcess();
        showOrders();

        sendMesageToTelegram("Ордер на продажу виставлен/переставлен.");//
        ui->console->append("Ордер на продажу виставлен/переставлен.");
        sendMesageToTelegram("Мониторю.");
        ui->console->append("Мониторю.");
    }

}

void MainWindow::canceledLimit(double quantity, double tradeQuantity)
{
	getPaymentBalances();
	if(process == 12)
	{

		if(!openedSellOrders.isEmpty())
			openedSellOrders.clear();
		process = 3;
		showProcess();
		showOrders();
	}
	if(process == 14)
	{

		openedBuyOrders.removeFirst();
		process = 4;
		showProcess();
		showOrders();
	}

}
void MainWindow::sendMesageToTelegram(QString _mesage)
{
    QUrl url;
    url.setUrl("https://api.telegram.org/bot610400445:AAFp4SRTmbM8jlUI38JmGl8FxBzAFYHeV3k/sendMessage?chat_id=324087454&text="+QDateTime::currentDateTime().toString("dd.MM.yy hh:mm:ss")+": "+_mesage);
    NAMTelegram->get(QNetworkRequest(url));
}

void MainWindow::showOrders()
{
	 listOpenedOrders->clear();
	 if(!openedSellOrders.isEmpty())
	 {
		  for(int i = 0;i<openedSellOrders.count();i++)
		  {
			  listOpenedOrders->addRow(openedSellOrders.at(i).getId(),openedSellOrders.at(i).getPrice(),openedSellOrders.at(i).getQuantity(),
											  openedSellOrders.at(i).getType());
		  }

	 }
	 if(!openedBuyOrders.isEmpty())
	 {
		  for(int i = 0;i<openedBuyOrders.count();i++)
		  {
			  listOpenedOrders->addRow(openedBuyOrders.at(i).getId(),openedBuyOrders.at(i).getPrice(),openedBuyOrders.at(i).getQuantity(),
											  openedBuyOrders.at(i).getType());
		  }

	 }






}

void MainWindow::connectWS()
{
	WSLivecoin->connect(currensyPair);
}

void MainWindow::getPaymentBalances()
{

    //Livecoin->getPaymentBalances(apiKey,secretKey,"USD");
    //Livecoin->getPaymentBalances(apiKey,secretKey,"ETH");
    Livecoin->getPaymentBalances(apiKey,secretKey);
}

void MainWindow::error(QString)
{
	if(process == 11)
	{
		process = 1;
		showProcess();
	}
	if(process == 12)
	{
		process = 3;
		showProcess();
	}
	if(process == 13)
	{
		process = 3;
		showProcess();
	}
	if(process == 14)
	{
		process = 4;
		showProcess();
	}
}

void MainWindow::gotOrder(JOrder order)
{
	if(!openedBuyOrders.isEmpty())
	{
		if(order.getId() == openedBuyOrders.first().getId())
		{
			if(order.getStatus() == "EXECUTED")
			{
				midPrice = (midPrice*summQuntity+ openedBuyOrders.first().getPrice()*openedBuyOrders.first().getQuantity())/(summQuntity+openedBuyOrders.first().getQuantity());
				summQuntity += openedBuyOrders.first().getQuantity();

				//qDebug()<<"midPrice: "<<midPrice;
				//qDebug()<<"summQuntity: "<<summQuntity;
				openedBuyOrders.removeFirst();
                sendMesageToTelegram("Ордер на покупку исполнен.");
                ui->console->append("Ордер на покупку исполнен.");

				process = 3;
				showProcess();
			}
		}
		if(order.getStatus() == "CANCELLED")
		{
			//Пока отладка
			openedBuyOrders.removeFirst();
			process = 4;
			showProcess();
			//
		}
	}
	if(!openedSellOrders.isEmpty())
	{
		  if(order.getId() == openedSellOrders.first().getId())
        {
            if(order.getStatus() == "EXECUTED")
            {
                process = 4;
					 showProcess();
                openedSellOrders.clear();
                sendMesageToTelegram("Ордер на продажу исполнен.");
                ui->console->append("Ордер на продажу исполнен.");

            }
        }

	}
}




void MainWindow::on_pushButton_clicked()
{
	 mainTimer->setInterval(10000);
    mainTimer->start();
	 watchDog->start(600000);
	 process = 100;
	 showProcess();

    numberOrders = ui->lineEditNumberOrders->text().toDouble();
    martingeil = ui->lineEditMartingaile->text().toDouble();
    procent = ui->lineEditProcent->text().toDouble();
    otstup = ui->lineEditOtstup->text().toDouble();
    perekritie = ui->lineEditPerekritie->text().toDouble();
    profit = ui->lineEditProfit->text().toDouble();
    depozit = ui->lineEdit_deposit->text().toDouble();
    ui->groupBox_5->setHidden(true);
    ui->console->append("Бот запущен");
    sendMesageToTelegram("Бот запущен.");
	 mainProcess();
}

void MainWindow::resizeEvent(QResizeEvent*)
{

}


void MainWindow::on_hideZeroBalances_clicked()
{
	getPaymentBalances();
}

void MainWindow::showPing()
{

}

void MainWindow::showProcess()
{
	processInf->setText("Process: " + QString::number((int) process));
}

void MainWindow::on_comboBoxSymbol_currentTextChanged(const QString &arg1)
{
	mainCurrensy.clear();
	secondaryCurrensy.clear();
	currensyPair.clear();

	currensyPair = arg1;
	secondaryCurrensy = arg1.mid(0,arg1.indexOf("/"));
	mainCurrensy = arg1.mid(arg1.indexOf("/")+1, arg1.count()-1);
}
