#include "SignalPowerWidget.h"

const static float kSpaceBetween = 0.2;

SignalPowerWidget::SignalPowerWidget(QWidget *parent) : QWidget(parent), m_power(SignalPower::kNoSignal)
{
    setMinimumSize(30, 30);
}

void SignalPowerWidget::setSignalQualityRSSI(float rssi)
{
    if (rssi == 99)
        m_power = SignalPower::kNoSignal;
    else if (rssi == 0)
        m_power = SignalPower::kVeryLow;
    else if (rssi == 1)
        m_power = SignalPower::kLow;
    else if (rssi > 1 && rssi < 31)
        m_power = SignalPower::kMedium;
    else
        m_power = SignalPower::kHigh;

    update();
}

void SignalPowerWidget::paintEvent(QPaintEvent *)
{
    for (int i = 2; i > -1; --i)
        drawRect(i);

    if (m_power == SignalPower::kNoSignal)
        drawCross();
}

void SignalPowerWidget::drawRect(int scale)
{
    QPainter painter(this);

    int factor = qMin(width() - 1, height() - 1);
    int left = width() / 3 + (factor + factor * kSpaceBetween) * scale / 3;
    int top = (2 - scale) * factor / 3;
    int width = (factor - kSpaceBetween * factor) / 3;
    int height = factor - top;

    QRect rect(left, top, width, height);

    int power = static_cast<int>(m_power);
    if (power > scale + 1)
        painter.setBrush(QBrush(QColor(Qt::darkGreen)));

    painter.drawRect(rect);
}

void SignalPowerWidget::drawCross()
{
    QPainter painter(this);

    int factor = qMin(width() - 1, height() - 1);
    factor = (factor - kSpaceBetween * factor) / 3;

    QPen pen(Qt::red);
    pen.setWidth(2);

    painter.setPen(pen);
    painter.drawLine(QLine(width() / 3 + 2, 2, factor + width() / 3, factor));
    painter.drawLine(QLine(factor + width() / 3, 2, width() / 3 + 2, factor));
}
