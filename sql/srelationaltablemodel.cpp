#include "srelationaltablemodel.h"

#include <QDebug>

SRelationalTableModel::SRelationalTableModel()
{

}

QVariant SRelationalTableModel::data(const QModelIndex & index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        QVariant vv = QSqlRelationalTableModel::data(index, role);
        if (vv.isValid() && vv.type() == QVariant::String)
        {
            /// handler bit type in the database table
            QByteArray ba = vv.toString().toLatin1();
            if (ba.size() == 1)
            {
                char c = ba.at(0);
                if (c == 1)
                    return tr("是");
                else if (c == 0)
                    return tr("否");
            }
        }
    }
    return QSqlRelationalTableModel::data(index, role);
}
