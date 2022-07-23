#ifndef SPOILERLOGWIDGET_H
#define SPOILERLOGWIDGET_H

#include <QFrame>
#include <QGridLayout>
#include <QParallelAnimationGroup>
#include <QScrollArea>
#include <QToolButton>
#include <QWidget>
#include <QPropertyAnimation>
#include <QPlainTextEdit>

/**
 * @brief The SpoilerLogWidget class
 * Animated (show/hide) log widget with spoiler
 */
class SpoilerLogWidget : public QWidget {
    Q_OBJECT
public:
    explicit SpoilerLogWidget(QWidget* parent = nullptr);

    void setContentLayout();
    // set spoiler's title
    void setTitle(const QString& title);
    // set maximum content height
    void setContentMaxHeight(int height);

signals:
    // emits at the end of animation (dirty parent widget fix)
    void compressed(bool);

public slots:
    // add log string into QPlainTextEdit
    void log(const QString& log);

private slots:
    // emits collapsed
    void notify(void);

private:
    // main spoiler layout
    QGridLayout m_mainLayout;
    // toggle button for expanding/compression
    QToolButton m_toggleButton;
    // decoration line
    QFrame m_headerLine;
    // animation
    QParallelAnimationGroup m_toggleAnimation;
    // log container
    QPlainTextEdit m_textEdit;

    // animation duration ms
    int m_animationDuration;
    // max content height
    int m_contentMaxHeight;
};

#endif // SPOILERLOGWIDGET_H
