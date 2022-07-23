#include "Widget.h"
#include "ui_Widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // dirty fix for collapse widget
    m_defaultState = size();

    connect(ui->serialPortWidget, &SerialPortWidget::opened, &m_controller, &CommandController::open);
    connect(ui->serialPortWidget, &SerialPortWidget::closed, &m_controller, &CommandController::close);

    connect(&m_controller, &CommandController::opened, this, &Widget::checkPortState);
    connect(&m_controller, &CommandController::closed, ui->serialPortWidget, &SerialPortWidget::setEnable);

    connect(&m_controller, &CommandController::closed, this, &Widget::reset);

    connect(&m_controller, &CommandController::simInserted, ui->simAvailableLed, &LedIndicator::toggle);

    connect(&m_controller, &CommandController::pinRequired, this, &Widget::requestPin);

    connect(this, &Widget::pinEntered, &m_controller, &CommandController::enterPin);

    connect(&m_controller, &CommandController::registered, ui->networkAvalableLed, &LedIndicator::toggle);

    connect(&m_controller, &CommandController::signalQualityCalculated, ui->SiganlPowerIndicator, &SignalPowerWidget::setSignalQualityRSSI);

    connect(ui->logWidget, &SpoilerLogWidget::compressed, this, &Widget::compress);

    connect(&m_controller, &CommandController::log, ui->logWidget, &SpoilerLogWidget::log);

    ui->logWidget->setTitle("Логи:");
    ui->logWidget->setContentMaxHeight(200);

    setWindowTitle("Проверка SIM800C");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::reset()
{
    ui->simAvailableLed->setState(LedState::kOff);
    ui->networkAvalableLed->setState(LedState::kOff);
    ui->SiganlPowerIndicator->setSignalQualityRSSI(0);
    m_controller.reset();
}

void Widget::checkPortState(bool opened)
{
    if (!opened)
        QMessageBox(QMessageBox::Critical, "Ошибка", "Не удалось открыть COM-порт!").exec();
    else
        ui->serialPortWidget->setDisable();
}

void Widget::requestPin(bool requested)
{
    if (requested) {
        QString pin = QInputDialog::getText(this, "PIN", "Введите PIN-код: ");
        if (!pin.isEmpty())
            emit pinEntered(pin);
    }
}

void Widget::compress(bool compressed)
{
    if (!compressed)
        resize(m_defaultState);
}


