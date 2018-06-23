#include "jlistbalancemodel.h"

JListBalanceModel::JListBalanceModel(QObject *parent)
{

}

int JListBalanceModel::rowCount(const QModelIndex &parent) const
{
	return balance.count();
}

int JListBalanceModel::columnCount(const QModelIndex &parent) const
{
	//if(balance.count())
	//{
		//return 0;
	//}
	return 4;
}

QVariant JListBalanceModel::data(const QModelIndex &index, int role) const
{

	if(!index.isValid())
	{
		return QVariant();
	}
	int row = index.row();
	int column = index.column();


	switch(column){
	case 0:
		switch(role)
		{
		case Qt::DisplayRole:
			return balance.at(row)->getCurrency();
		case Qt::TextAlignmentRole:
			return Qt::AlignCenter;
		default:
			return QVariant();
		}
	case 1:
		switch(role)
		{
		case Qt::DisplayRole:
			return balance.at(row)->getTotal();
		case Qt::TextAlignmentRole:
			return Qt::AlignCenter;
		default:
			return QVariant();
		}
	case 2:
		switch(role)
		{
		case Qt::DisplayRole:
			return balance.at(row)->getAvailable();
		case Qt::TextAlignmentRole:
			return Qt::AlignCenter;
		default:
			return QVariant();
		}
	case 3:
		switch(role)
		{
		case Qt::DisplayRole:
			return balance.at(row)->getTrade();
		case Qt::TextAlignmentRole:
			return Qt::AlignCenter;
		default:
			return QVariant();
		}
	}
}

Qt::ItemFlags JListBalanceModel::flags(const QModelIndex &index) const
{
	if(!index.isValid())
	{
		return Qt::NoItemFlags;
	}
	return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void JListBalanceModel::setBalance(QVector<JBalance *> _balance)
{
	balance.clear();
	balance = _balance;
	_balance.clear();
	emit layoutChanged();;
}
QVariant JListBalanceModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	switch(role)
	{
	case Qt::DisplayRole:
		switch(section)
		{
		case 0:
			return QString("Name");
		case 1:
			return QString("Total");
		case 2:
			return QString("Available");
		case 3:
			return QString("Trade");
		}
	default:
			return QVariant();
	}

}
