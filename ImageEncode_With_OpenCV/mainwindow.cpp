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

    QStringList bands = QStringList() << "Image" << "QString" << "byteArray";
    ui->comboBoxWaterMark->setModel(new QStringListModel(bands));
    ui->comboBoxWaterMark->setCurrentIndex(2);
    ui->lineEditWaterMark->setText("01010101010101010101010101010101");
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
    byteArray code;
    if(ui->comboBoxWaterMark->currentIndex() == 2)
    {
//        if(ui->lineEditWaterMark->text().length()!=32)
//        {
//            QMessageBox::warning(this, "Error", "Only Support for 32-size byteArray!");
//        }
        QString str = ui->lineEditWaterMark->text();
        code = byte2Array(str);
    }
    else
    {
//        if(ui->lineEditWaterMark->text().length()!=4)
//        {
//            QMessageBox::warning(this, "Error", "Only Support for 4-size string!");
//        }
        QString str = ui->lineEditWaterMark->text();
        code = str2Array(str);
    }
    key = generateKey(code.length());
    Mat src = imread(ui->lineEdit->displayText().toStdString().data(), IMREAD_ANYDEPTH)/255;
    //Mat src = imread(ui->lineEdit->displayText().toStdString().data(), IMREAD_ANYDEPTH);
    Mat edge = edgeExtract(src);
    Mat dst = watermarkImg(src, edge, encode(code, key));
    //imwrite("encode.bmp", dst);
    imwrite("encode.bmp", dst*255);

    auto buffer = mat2Array(dst);
    image = QPixmap::fromImage(QImage(&buffer[0], src.cols, src.rows, QImage::Format_Grayscale8));
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(image);
    ui->graphicsViewAfter->setScene(scene);
    ui->graphicsViewAfter->show();
    ui->graphicsViewAfter->fitInView(image.rect(), Qt::KeepAspectRatio);
}

//void MainWindow::on_pushButtonDecode_clicked()
//{
//    Mat src = imread(ui->lineEdit->displayText().toStdString().data(), IMREAD_ANYDEPTH)/255;
//    Mat dst = imread("encode.bmp", IMREAD_ANYDEPTH)/255;
//    byteArray code = encode(decodeImg(src, dst, 32), key);
//    QMessageBox::warning(this, "Decode", "The watermark is "+array2byte(code)+"!");
//}

void MainWindow::on_pushButtonDecode_clicked()
{
    Mat src = imread(ui->lineEdit->displayText().toStdString().data(), IMREAD_ANYDEPTH)/255;
    //Mat src = imread(ui->lineEdit->displayText().toStdString().data(), IMREAD_ANYDEPTH);
    Mat dst = imread("encode.bmp", IMREAD_ANYDEPTH)/255;
    //Mat dst = imread("encode.bmp", IMREAD_ANYDEPTH);
    byteArray code = encode(decodeImg(src, dst, key.length()), key);
    if(ui->comboBoxWaterMark->currentIndex() == 2)
    {
        QMessageBox::warning(this, "Decode", "The watermark is " + array2byte(code)+"!");
    }
    if(ui->comboBoxWaterMark->currentIndex() == 1)
    {
        QMessageBox::warning(this, "Decode", "The watermark is " + array2str(code)+"!");
    }
}
