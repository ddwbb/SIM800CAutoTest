#ifndef LEDINDICATOR_H
#define LEDINDICATOR_H

#include <QWidget>
#include <QResizeEvent>
#include <QColor>
#include <QLabel>
#include <QPainter>

enum class LedState {
    kOn,
    kOff,
    kError
};

/**
 * @brief The LedIndicator class
 * Simple led widget
 * There is 3 states: On, Off, Error
 */
class LedIndicator : public QWidget
{
    Q_OBJECT
public:
    LedIndicator(QWidget *parent);

    // sets led state and repaints
    void setState(LedState state);

public slots:
    // turn on led depending on condition or set error state
    void toggle(bool);

protected:
    // base painting function
    virtual void paintEvent (QPaintEvent *event);
    // resize function
    virtual void resizeEvent(QResizeEvent *event);

private:
    // scale ratio
    static const qreal m_scaledSize;
    // current led state
    LedState m_state;

};

#endif // LEDINDICATOR_H
