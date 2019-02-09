#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Binary image watermarking program");
    //w.setWindowIcon(QIcon("$$PWD/miao.jpg"));
    w.show();

    return a.exec();
}
