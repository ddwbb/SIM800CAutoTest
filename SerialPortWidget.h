#ifndef SERIALPORTWIDGET_H
#define SERIALPORTWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>

#include "SerialPortModel.h"

/**
 * @brief The SerialPortWidget class
 * SerialPortWidget contains QComboBox with serial ports info and button to connect
 */
class SerialPortWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SerialPortWidget(QWidget *parent = nullptr);

public slots:
    // unlock widget
    void setEnable();
    // lock widget
    void setDisable();

private slots:
    // emits signals depending on current lock state
    void click(bool);

signals:
    // emits signal for open serial port
    void opened(QSerialPortInfo);
    // emits signal for close serial port
    void closed();

private:
    // opem/close button
    QPushButton m_button;
    // combo box with serial ports
    QComboBox m_comboBox;
};

#endif // SERIALPORTWIDGET_H
