#include "jlistbalancemodel.h"
#include <QColor>
#include <QBrush>

JListBalanceModel::JListBalanceModel(QObject *parent)
{

}

int JListBalanceModel::rowCount(const QModelIndex &parent) const
{
	return balance.count();
}

int JListBalanceModel::columnCount(const QModelIndex &parent) const
{
	if(!balance.count())
	{
		return 0;
	}
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
		case Qt::EditRole:
			return balance.at(row)->getCurrency();
		case Qt::TextAlignmentRole:
			return Qt::AlignCenter;
		case Qt::BackgroundColorRole:
			if(balance.at(row)->getCurrency()=="ETH" || balance.at(row)->getCurrency()=="BTC" || balance.at(row)->getCurrency()=="USD")
			{
				return QBrush(QColor("#F2F2F2"));
			}
		default:
			return QVariant();
		}
	case 1:
		switch(role)
		{
		case Qt::DisplayRole:
			return balance.at(row)->getTotal();
		case Qt::EditRole:
			return balance.at(row)->getTotal();
		case Qt::TextAlignmentRole:
			return Qt::AlignCenter;
		case Qt::BackgroundColorRole:
			if(balance.at(row)->getCurrency()=="ETH" || balance.at(row)->getCurrency()=="BTC" || balance.at(row)->getCurrency()=="USD")
			{
				return QBrush(QColor("#F2F2F2"));
			}
		default:
			return QVariant();
		}
	case 2:
		switch(role)
		{
		case Qt::DisplayRole:
			return balance.at(row)->getAvailable();
		case Qt::EditRole:
			return balance.at(row)->getAvailable();
		case Qt::TextAlignmentRole:
			return Qt::AlignCenter;
		case Qt::BackgroundColorRole:
			if(balance.at(row)->getCurrency()=="ETH" || balance.at(row)->getCurrency()=="BTC" || balance.at(row)->getCurrency()=="USD")
			{
				return QBrush(QColor("#F2F2F2"));
			}
		default:
			return QVariant();
		}
	case 3:
		switch(role)
		{
		case Qt::DisplayRole:
			return balance.at(row)->getTrade();
		case Qt::EditRole:
			return balance.at(row)->getTotal();
		case Qt::TextAlignmentRole:
			return Qt::AlignCenter;
		case Qt::BackgroundColorRole:
			if(balance.at(row)->getCurrency()=="ETH" || balance.at(row)->getCurrency()=="BTC" || balance.at(row)->getCurrency()=="USD")
			{
				return QBrush(QColor("#F2F2F2"));
			}
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
	return Qt::ItemIsEnabled | Qt::ItemIsEditable;
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
