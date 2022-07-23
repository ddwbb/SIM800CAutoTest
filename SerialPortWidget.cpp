#include "SerialPortWidget.h"

SerialPortWidget::SerialPortWidget(QWidget *parent)
    : QWidget(parent), m_button("Подключиться", this), m_comboBox(this)
{
    QHBoxLayout* layout = new QHBoxLayout(this);

    layout->addWidget(&m_comboBox);
    layout->addWidget(&m_button);

    m_comboBox.setModel(new SerialPortModel);

    connect(&m_button, &QPushButton::clicked, this, &SerialPortWidget::click);
}

void SerialPortWidget::setEnable()
{
    m_comboBox.setEnabled(true);
    m_button.setText("Подключиться");
}

void SerialPortWidget::setDisable()
{
    m_comboBox.setEnabled(false);
    m_button.setText("Отключиться");
}

void SerialPortWidget::click(bool)
{
    if (m_comboBox.isEnabled())
        emit opened(m_comboBox.currentData().value<QSerialPortInfo>());
    else
        emit closed();
}
