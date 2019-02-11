#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>

namespace Ui
{
class MainWindow;
}

using byteArray = QVector<bool>;

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
    uchar* dst;
};

#endif // MAINWINDOW_H
