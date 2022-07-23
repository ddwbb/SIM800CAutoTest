#include "Widget.h"

#include <QApplication>

#include <windows.h>
#include "ftd2xx.h"

static FT_HANDLE ftHandle;
static UCHAR ftMask = 0x33; // CBUS0, CBUS1 as output, CBUS0 & CBUS1 set high

// init function for ft230x device for configure pins (turnint on sim800c modem)
// WARNING: crashed, if there is no physical plugged device
bool init() {
    FT_STATUS status = FT_Open(0, &ftHandle);
    if (status != FT_OK)
        return false;
    status = FT_SetBitMode(ftHandle, ftMask, 0x20);
    return status == FT_OK;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // main application window
    Widget w;

    bool initStatus = init();

    if (initStatus == FT_OK) {
        QMessageBox(QMessageBox::Critical, "Ошибка",
            "Невозможно инициализировать ft230x и выставить питание на пины модема CBUS0, CBUS1").exec();
        return EXIT_SUCCESS;
    } else {
        w.show();
    }

    return a.exec();
}
