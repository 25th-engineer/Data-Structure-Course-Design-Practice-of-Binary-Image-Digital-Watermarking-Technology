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
    ui->comboBoxWaterMark->setModel(new QStringListModel(bands));
    ui->comboBoxWaterMark->setCurrentIndex(1);
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
    watermark WT;
    byteArray code;
    if(ui->comboBoxWaterMark->currentIndex() == 1)
    {
//        if(ui->lineEditWaterMark->text().length()!=32)
//        {
//            QMessageBox::warning(this, "Error", "Only Support for 32-size byteArray!");
//        }
        QRegExp regx("[0-1]+$");
        QValidator *validator = new QRegExpValidator(regx, this );
        ui->lineEditWaterMark->setValidator( validator );
        QString str = ui->lineEditWaterMark->text();
        code = WT.byte2Array(str);
        delete validator;
    }
    else
    {
//        if(ui->lineEditWaterMark->text().length()!=4)
//        {
//            QMessageBox::warning(this, "Error", "Only Support for 4-size string!");
//        }
        QRegExp regx(".+\n");
        QValidator *validator = new QRegExpValidator(regx, this );
        ui->lineEditWaterMark->setValidator( validator );
        QString str = ui->lineEditWaterMark->text();
        code = WT.str2Array(str);
        delete validator;
    }
    key = WT.generateKey(code.length());
    Mat src = imread(ui->lineEdit->displayText().toStdString().data(), IMREAD_ANYDEPTH)/255;
    //Mat src = imread(ui->lineEdit->displayText().toStdString().data(), IMREAD_ANYDEPTH);
    Mat edge = WT.edgeExtract(src);
    Mat dst = WT.watermarkImg(src, edge, WT.encode(code, key));
    //imwrite("encode.bmp", dst);
    imwrite("encode.bmp", dst*255);

    auto buffer = WT.mat2Array(dst);
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
    watermark WT;
    Mat src = imread(ui->lineEdit->displayText().toStdString().data(), IMREAD_ANYDEPTH)/255;
    //Mat src = imread(ui->lineEdit->displayText().toStdString().data(), IMREAD_ANYDEPTH);
    Mat dst = imread("encode.bmp", IMREAD_ANYDEPTH)/255;
    //Mat dst = imread("encode.bmp", IMREAD_ANYDEPTH);
    byteArray code = WT.encode(WT.decodeImg(src, dst, key.length()), key);
    if(ui->comboBoxWaterMark->currentIndex() == 1)
    {
        QMessageBox::warning(this, "Decode", "The watermark is " + WT.array2byte(code)+"!");
    }
    if(ui->comboBoxWaterMark->currentIndex() == 0)
    {
        QMessageBox::warning(this, "Decode", "The watermark is " + WT.array2str(code)+"!");
    }
}
