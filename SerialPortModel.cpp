#include "SerialPortModel.h"
#include <QDebug>

SerialPortModel::SerialPortModel(QObject* parent)
    : QAbstractListModel(parent), m_ports(QSerialPortInfo::availablePorts())
{
    // TODO: sort serial ports by numbers
}

QVariant SerialPortModel::data(const QModelIndex &index, int role) const
{
    auto port = m_ports.at(index.row());
    QVariant data;
    switch (role) {
        case Qt::DisplayRole:
            data.setValue(port.portName());
            break;
        case Qt::UserRole:
            data.setValue(port);
            break;
    }

    return data;
}

int SerialPortModel::rowCount(const QModelIndex &parent) const
{
    return m_ports.count();
}
