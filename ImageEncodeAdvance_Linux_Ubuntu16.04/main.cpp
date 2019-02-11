#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
	w.setWindowTitle("8 bits Binary BMP picture watermarking program");
    w.show();

    return a.exec();
}
