#ifndef JLISTBALANCEMODEL_H
#define JLISTBALANCEMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QVector>
#include <JLivecoin/jbalance.h>

class JListBalanceModel : public QAbstractListModel
{
	Q_OBJECT
public:
	explicit JListBalanceModel(QObject * parent = 0);
	int rowCount(const QModelIndex &parent) const;
	int columnCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	void setBalance(QVector<JBalance> &_balance);
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
private:
	QVector<JBalance> balance;
};

#endif // JLISTBALANCEMODEL_H
