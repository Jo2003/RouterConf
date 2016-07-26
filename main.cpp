#include "qrconfdlg.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QRConfDlg w;
    w.show();

    return a.exec();
}
