#ifndef SIGNALPOWERWIDGET_H
#define SIGNALPOWERWIDGET_H

#include <QWidget>
#include <QPainter>

enum class SignalPower {
    kNoSignal,
    kVeryLow,
    kLow,
    kMedium,
    kHigh
};

/**
 * @brief The SignalPowerWidget class
 * Simple widget for signal power display according rssi parameter of sim800c spec
 */

class SignalPowerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SignalPowerWidget(QWidget *parent = nullptr);

signals:

public slots:
    // sets power according rssi spec of sim800c and repaints widget
    void setSignalQualityRSSI(float rssi);
    // paintng widget
    void paintEvent(QPaintEvent*);

private:
    // current signal power
    SignalPower m_power;

    // draw scaled rect
    void drawRect(int scale);
    // draw cross (when there is no signal)
    void drawCross();
};

#endif // SIGNALPOWERWIDGET_H
