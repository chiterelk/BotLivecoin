#include "jtablmodel.h"

JTablModel::JTablModel(QObject *parent) :
	QAbstractListModel(parent)
{

}

int JTablModel::rowCount(const QModelIndex &parent) const
{
	return listId.count();
}

int JTablModel::columnCount(const QModelIndex &parent) const
{
	return 3;
}

QVariant JTablModel::data(const QModelIndex &index, int role) const
{
	if(index.isValid())
		return QVariant();
	int row = index.row();
	int column = index.column();
	switch(column){
	case 0:
		switch(role)
		{
		case Qt::DisplayRole:
			return QString::number(listId.at(row),'g',20);
		case Qt::TextAlignmentRole:
			return Qt::AlignCenter;
		case Qt::BackgroundColorRole:
			if(listType.at(row)=="sell")
			{
				return QBrush(Qt::red);
			}else{
				return QBrush(Qt::blue);
			}
		default:
			return QVariant();
		}
	case 1:
		switch(role)
		{
		case Qt::DisplayRole:
			return QString::number(listPrice.at(row),'g',20);
		case Qt::TextAlignmentRole:
			return Qt::AlignCenter;
		case Qt::BackgroundColorRole:
			if(listType.at(row)=="sell")
			{
				return QBrush(Qt::red);
			}else{
				return QBrush(Qt::blue);
			}
		default:
			return QVariant();
		}
	case 2:
		switch(role)
		{
		case Qt::DisplayRole:
			return QString::number(listQuantity.at(row),'g',20);
		case Qt::TextAlignmentRole:
			return Qt::AlignCenter;
		case Qt::BackgroundColorRole:
			if(listType.at(row)=="Sell")
			{
				return QBrush(Qt::red);
			}else{
				return QBrush(Qt::blue);
			}
		default:
			return QVariant();
		}
	}
}
Qt::ItemFlags JTablModel::flags(const QModelIndex &index) const
{
	if(!index.isValid())
	{
		return Qt::NoItemFlags;
	}
	return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void JTablModel::addRow(double _id, double _price, double _quantity, QString _type)
{
	listId << _id;
	listPrice << _price;
	listQuantity << _quantity;
	listType <<_type;
	emit layoutChanged();
}

void JTablModel::clear()
{
	listId.clear();
	listPrice.clear();
	listQuantity.clear();
	listType.clear();
	emit layoutChanged();
}
