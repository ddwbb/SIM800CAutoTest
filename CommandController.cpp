#include "CommandController.h"

#include <QDebug>

CommandController::CommandController(QObject *parent)
    : QObject(parent), m_port(new QSerialPort(this))
{
    connect(this, &CommandController::connected, this, &CommandController::checkSim);

    connect(this, &CommandController::simInserted, this, [=](bool inserted) {
        if (inserted)
            checkPinRequirement();
    });

    connect(this, &CommandController::pinRequired, this, [=](bool required) {
        if (!required)
            getSignalQuality();
    });

    connect(this, &CommandController::signalQualityCalculated, this, &CommandController::getRegistrationStatus);

    connect(m_port, &QSerialPort::readyRead, this, &CommandController::read);
}

void CommandController::reset()
{
    m_cmd = "";
}

void CommandController::open(QSerialPortInfo port)
{
    if (!m_port) {
        emit opened(false);
        return;
    }

    m_port->setPort(port);

    if (m_port->open(QSerialPort::ReadWrite)) {
        m_port->setDataTerminalReady(true);
        emit opened(true);
    } else
        emit opened(false);
}

void CommandController::close() {
    m_port->close();
    emit closed();
}

void CommandController::enterPin(const QString &pin)
{
    m_cmd = "AT+CPIN=";
    write(QString(m_cmd + pin + "\r\n"));
}

void CommandController::read()
{
    QByteArray response = m_port->readAll();
    emit log(response);
    parseResponse(response);
}

void CommandController::checkPinRequirement()
{
    m_cmd = "AT+CPIN?\r\n";
    write(m_cmd);
}

void CommandController::getSignalQuality()
{
    m_cmd = "AT+CSQ?\r\n";
    write(m_cmd);
}

void CommandController::getRegistrationStatus()
{
    m_cmd = "AT+CREG?\r\n";
    write(m_cmd);
}

void CommandController::checkSim()
{
    m_cmd = "AT+CSMINS?\r\n";
    write(m_cmd);
}

void CommandController::parseResponse(QByteArray response)
{
    // first turn on
    if (m_cmd.isEmpty()) {
        emit connected();
        return;
    }

    QString responseStr(response.trimmed());
    responseStr = responseStr.split("\r\n")[0];

    int cmdBeginIndex = responseStr.indexOf('+');

    if (cmdBeginIndex == -1) {
        triggerSignal(response == "OK");
        return;
    }

    QString cmd = responseStr.mid(cmdBeginIndex + 1, responseStr.indexOf(':') - cmdBeginIndex - 1);
    responseStr.remove(0, cmd.length() + 2);
    responseStr = responseStr.trimmed();

    auto params = responseStr.split(',');

    triggerSignalAccordingResponsedValues(cmd, params);
}

void CommandController::triggerSignal(bool state)
{
    if (m_cmd == "AT+CPIN=")
        emit pinRequired(!state);
}

void CommandController::triggerError()
{
    emit badResponseOccured();
}

void CommandController::triggerSignalAccordingResponsedValues(const QString &cmd, const QList<QString> &values)
{
    if (values.empty()) {
        triggerError();
        return;
    }

    if (cmd == "CMEERROR") {
        triggerSignal(false);
        return;
    }

    if (cmd == "CPIN")
        emit pinRequired(values.front() != "READY");
    else if (cmd == "CSMINS")
        emit simInserted(values.back() == "1");
    else if (cmd == "CSQ")
        emit signalQualityCalculated(values.front().toFloat());
    else if (cmd == "CREG") {
        if (values.size() < 2)
            triggerError();
        else
            emit registered(values[1] == "1" || values[1] == "5");
    }
}

void CommandController::write(const QString &cmd)
{
    m_port->write(cmd.toLocal8Bit());
    emit log(cmd);
}









