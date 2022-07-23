#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QInputDialog>
#include <QMessageBox>

#include <QSerialPort>
#include <QSerialPortInfo>

#include "CommandController.h"
#include "SignalPowerWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

/**
 * @brief The Widget class
 * Main application form.
 */

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    // reset all to default state
    void reset();

private slots:
    // process port opening state
    void checkPortState(bool opened);
    // ask user for pin
    void requestPin(bool requested);
    // resize widget, if logWidget was compressed (dirty fix)
    void compress(bool collapsed);

signals:
    // pin was entered by user
    void pinEntered(QString);

private:
    Ui::Widget *ui;

    // command controller with serial port
    CommandController m_controller;
    // dirty fix for resize widget
    QSize m_defaultState;
};
#endif // WIDGET_H
