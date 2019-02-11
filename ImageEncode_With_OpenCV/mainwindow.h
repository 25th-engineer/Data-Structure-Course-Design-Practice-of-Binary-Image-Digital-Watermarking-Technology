#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "watermarkutil.h"
#include <QPixmap>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonBrowse_clicked();
    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButtonEncode_clicked();

    void on_pushButtonDecode_clicked();

private:
    Ui::MainWindow *ui;

    QPixmap image;
    byteArray key;
};

#endif // MAINWINDOW_H
