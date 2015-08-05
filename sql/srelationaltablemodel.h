#ifndef SRELATIONALTABLEMODEL_H
#define SRELATIONALTABLEMODEL_H

#include <QSqlRelationalTableModel>

class SRelationalTableModel : public QSqlRelationalTableModel
{
public:
    SRelationalTableModel();

protected:
    virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
};

#endif // SRELATIONALTABLEMODEL_H
