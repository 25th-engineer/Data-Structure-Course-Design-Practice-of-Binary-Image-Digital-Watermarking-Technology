#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

#include "watermarkutil.h"
#include "mainwindow.h"

using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    image = QPixmap();

    QStringList bands = QStringList() << "QString" << "byteArray";
    ui->lineEditWaterMark->setText("encode.bmp");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonBrowse_clicked()
{
    auto file = QFileDialog::getOpenFileName(this, tr("Append selected images"));
    ui->lineEdit->setText(file);
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    if(QFileInfo(ui->lineEdit->displayText()).exists())
    {
        QGraphicsScene *scene = new QGraphicsScene;
        QPixmap img = QPixmap(ui->lineEdit->displayText());
        scene->addPixmap(img);
        ui->graphicsViewPrevious->setScene(scene);
        ui->graphicsViewPrevious->show();
        ui->graphicsViewPrevious->fitInView(img.rect(), Qt::KeepAspectRatio);
    }
}

void MainWindow::on_pushButtonEncode_clicked()
{
    watermark WT;
    byteArray code;
    QString newName = ui->lineEditWaterMark->text();
    Mat src = imread(ui->lineEdit->displayText().toStdString().data(), IMREAD_ANYDEPTH)/255;
    std::string fileName = newName.toStdString();
    newFileName = new char[fileName.length()];
    newFileName = fileName.c_str();
    imwrite(newFileName, src*255);
    auto buffer = WT.mat2Array(src);
    image = QPixmap::fromImage(QImage(&buffer[0], src.cols, src.rows, QImage::Format_Grayscale8));
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(image);
    ui->graphicsViewAfter->setScene(scene);
    ui->graphicsViewAfter->show();
    ui->graphicsViewAfter->fitInView(image.rect(), Qt::KeepAspectRatio);
}

void MainWindow::on_pushButtonDecode_clicked()
{

}
