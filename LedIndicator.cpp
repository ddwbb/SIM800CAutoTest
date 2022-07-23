#include "LedIndicator.h"

const qreal LedIndicator::scaledSize = 1000;

const static QColor onColorStart(0, 255, 0);
const static QColor onColorEnd(0, 192, 0);
const static QColor offColorStart(0, 28, 0);
const static QColor offColorEnd(0, 128, 0);
const static QColor errColorStart(255, 0, 0);
const static QColor errColorEnd(192, 0, 0);

const static QPointF gradientPoint(-500, -500);

LedIndicator::LedIndicator(QWidget *parent)
    : QWidget(parent), state(LedState::Off)
{
}

void LedIndicator::toggle(bool state)
{
    LedState newState = state ? LedState::On : LedState::Error;
    setState(newState);
}

void LedIndicator::setState(LedState state)
{
    this->state = state;
    update();
}

void LedIndicator::resizeEvent(QResizeEvent *event) {
    update();
}

void LedIndicator::paintEvent(QPaintEvent *event) {
    qreal realSize = qMin(width(), height());

    QRadialGradient gradient;
    QPainter painter(this);
    QPen pen(Qt::black);
    pen.setWidth(1);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width()/2, height()/2);
    painter.scale(realSize/scaledSize, realSize/scaledSize);

    gradient = QRadialGradient(gradientPoint, 1500, gradientPoint);
    gradient.setColorAt(0, QColor(224,224,224));
    gradient.setColorAt(1, QColor(28,28,28));
    painter.setPen(pen);
    painter.setBrush(QBrush(gradient));
    painter.drawEllipse(QPointF(0,0), 300, 300);

    gradient = QRadialGradient (gradientPoint, 1500, gradientPoint);
    gradient.setColorAt(0, QColor(224,224,224));
    gradient.setColorAt(1, QColor(28,28,28));
    painter.setPen(pen);
    painter.setBrush(QBrush(gradient));
    painter.drawEllipse(QPointF(0,0), 300, 300);

    painter.setPen(pen);
    switch (state) {
        case LedState::On:
            gradient = QRadialGradient (QPointF(-200,-200), 1500, QPointF(-200,-200));
            gradient.setColorAt(0, onColorStart);
            gradient.setColorAt(1, onColorEnd);
        break;
        case LedState::Off:
            gradient = QRadialGradient (QPointF(200,200), 1500, QPointF(200,200));
            gradient.setColorAt(0, offColorStart);
            gradient.setColorAt(1, offColorEnd);
        break;
        case LedState::Error:
            gradient = QRadialGradient (QPointF(200,200), 1500, QPointF(200,200));
            gradient.setColorAt(0, errColorStart);
            gradient.setColorAt(1, errColorEnd);
        break;
    }
    painter.setBrush(gradient);
    painter.drawEllipse(QPointF(0,0), 260, 260);
}

