#ifndef JTABLMODEL_H
#define JTABLMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QBrush>
#include <QList>
#include <QString>


class JTablModel : public QAbstractListModel
{
	Q_OBJECT
public:
	explicit JTablModel(QObject *parent = 0);

	int rowCount(const QModelIndex &parent) const;
	int columnCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;

	void addRow(double _id, double _price, double _quantity, QString _type);
	void clear();
private:
	QList <double> listId;
	QList <double> listPrice;
	QList <double> listQuantity;
	QList <QString> listType;

};

#endif // JTABLMODEL_H
