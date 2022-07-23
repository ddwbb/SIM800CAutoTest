#include "SpoilerLogWidget.h"

#include "SpoilerLogWidget.h"

const static int kAnimationDuration = 300;

SpoilerLogWidget::SpoilerLogWidget(QWidget *parent)
    : QWidget(parent), m_animationDuration(kAnimationDuration) {
    m_toggleButton.setStyleSheet("QToolButton { border: none; }");
    m_toggleButton.setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_toggleButton.setArrowType(Qt::ArrowType::RightArrow);
    m_toggleButton.setCheckable(true);
    m_toggleButton.setChecked(false);

    m_headerLine.setFrameShape(QFrame::HLine);
    m_headerLine.setFrameShadow(QFrame::Sunken);
    m_headerLine.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

    m_textEdit.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    // start out collapsed
    m_textEdit.setMaximumHeight(0);
    m_textEdit.setMinimumHeight(0);
    // let the entire widget grow and shrink with its content
    m_toggleAnimation.addAnimation(new QPropertyAnimation(this, "minimumHeight"));
    m_toggleAnimation.addAnimation(new QPropertyAnimation(this, "maximumHeight"));
    m_toggleAnimation.addAnimation(new QPropertyAnimation(&m_textEdit, "maximumHeight"));
    // don't waste space
    m_mainLayout.setVerticalSpacing(0);
    m_mainLayout.setContentsMargins(0, 0, 0, 0);
    int row = 0;
    m_mainLayout.addWidget(&m_toggleButton, row, 0, 1, 1, Qt::AlignLeft);
    m_mainLayout.addWidget(&m_headerLine, row++, 2, 1, 1);
    m_mainLayout.addWidget(&m_textEdit, row, 0, 1, 3);

    setLayout(&m_mainLayout);

    QObject::connect(&m_toggleButton, &QToolButton::clicked, [this](const bool checked) {
        m_toggleButton.setArrowType(checked ? Qt::ArrowType::DownArrow : Qt::ArrowType::RightArrow);
        m_toggleAnimation.setDirection(checked ? QAbstractAnimation::Forward : QAbstractAnimation::Backward);
        m_toggleAnimation.start();
    });

    connect(&m_toggleAnimation, &QParallelAnimationGroup::finished, this, &SpoilerLogWidget::notify);

    setContentLayout();
}

void SpoilerLogWidget::setContentLayout() {
    const auto collapsedHeight = sizeHint().height() - m_textEdit.maximumHeight();
    auto m_contentMaxHeight = 200;
    for (int i = 0; i < m_toggleAnimation.animationCount() - 1; ++i) {
        QPropertyAnimation * spoilerAnimation = static_cast<QPropertyAnimation *>(m_toggleAnimation.animationAt(i));
        spoilerAnimation->setDuration(m_animationDuration);
        spoilerAnimation->setStartValue(collapsedHeight);
        spoilerAnimation->setEndValue(collapsedHeight + m_contentMaxHeight);
    }
    QPropertyAnimation * contentAnimation = static_cast<QPropertyAnimation *>(m_toggleAnimation.animationAt(m_toggleAnimation.animationCount() - 1));
    contentAnimation->setDuration(m_animationDuration);
    contentAnimation->setStartValue(0);
    contentAnimation->setEndValue(m_contentMaxHeight);
}

void SpoilerLogWidget::setTitle(const QString& title)
{
    m_toggleButton.setText(title);
}

void SpoilerLogWidget::setContentMaxHeight(int height)
{
    m_contentMaxHeight = height;
}

void SpoilerLogWidget::log(const QString &log)
{
    m_textEdit.moveCursor(QTextCursor::End);
    m_textEdit.insertPlainText(log + "\r\n");
    m_textEdit.moveCursor(QTextCursor::End);
}

void SpoilerLogWidget::notify()
{
    emit collapsed(m_textEdit.height() == m_contentMaxHeight);
}
