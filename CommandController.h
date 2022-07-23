#ifndef COMMANDCONTROLLER_H
#define COMMANDCONTROLLER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QFunctionPointer>
#include <QMap>

/**
 * @brief The CommandController class
 * Command controller writes and reads data to/form serial port,
 * parse it and emits relevant signals
 * WARNING: supposed that data arrived entirely in one packet.
 * Otherwise command parsing will have undefined behaviour
 */

class CommandController : public QObject
{
    Q_OBJECT
public:
    explicit CommandController(QObject *parent = nullptr);
    // reset m_cmd
    void reset();

signals:
    // port opened or not
    void opened(bool);
    // port closed
    void closed();
    // emits, when (according to sim800c spec) first data arrived
    void connected();
    // sim inserted state checked
    void simInserted(bool);
    // checked pin requirements
    void pinRequired(bool);
    // signal quality arrived
    void signalQualityCalculated(float);
    // checked network registration
    void registered(bool);
    // unexpected bad response
    void badResponseOccured(void);
    // transfer log-string
    void log(const QString& cmd);

public slots:
    // open port via serial port info
    void open(QSerialPortInfo);
    // close serial port
    void close();
    // send pin-code
    void enterPin(const QString& pin);

private slots:
    // read available data
    void read();
    // send sim availability request
    void checkSim(void);
    // send pin requirements request
    void checkPinRequirement(void);
    // send signal quality request
    void getSignalQuality(void);
    // send network registration request
    void getRegistrationStatus(void);

private:
    // serial port
    QSerialPort* m_port;
    // last sended command (uses for response parsing)
    QString m_cmd;

    // parsing response
    void parseResponse(QByteArray response);
    // emits signal according current request
    void triggerSignal(bool);
    // emits error signal
    void triggerError();
    // emits signals according command and it params
    void triggerSignalAccordingResponsedValues(const QString& cmd, const QList<QString>& values);
    // send command to port
    void write(const QString& cmd);
};

#endif // COMMANDCONTROLLER_H
