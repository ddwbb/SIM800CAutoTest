#ifndef SERIALPORTMODEL_H
#define SERIALPORTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QSerialPortInfo>

Q_DECLARE_METATYPE(QSerialPortInfo);

/**
 * @brief The SerialPortModel class
 * ComboBox model for available serial ports
 */
class SerialPortModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit SerialPortModel(QObject* parent = nullptr);

    virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;

private:
    // available serial ports info list
    QList<QSerialPortInfo> m_ports;
};



#endif // SERIALPORTMODEL_H
