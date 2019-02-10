#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

#include "bmputil.h"

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
        int height, width;
        uchar* buffer = readBmp(ui->lineEdit->displayText().toStdString().data(), width, height);
        if(buffer)
        {
            QPixmap img = QPixmap::fromImage(QImage(buffer, width, height, QImage::Format_Grayscale8));
            QGraphicsScene *scene = new QGraphicsScene;
            scene->addPixmap(img);
            ui->graphicsViewPrevious->setScene(scene);
            ui->graphicsViewPrevious->show();
            ui->graphicsViewPrevious->fitInView(img.rect(), Qt::KeepAspectRatio);
        }
    }
}

void MainWindow::on_pushButtonEncode_clicked()
{
    byteArray code;
    if(ui->comboBoxWaterMark->currentIndex() == 2)
    {
        code = byte2Array(ui->lineEditWaterMark->text());
    }
    else
    {
        code = str2Array(ui->lineEditWaterMark->text());
    }
    key = generateKey(code.length());
    int width, height;
    uchar* buffer = readBmp(ui->lineEdit->displayText().toStdString().data(), width, height);
    uchar* edge = edgeExtract(buffer, width, height);
    dst = watermarkImg(buffer, edge, width*height, encode(code, key));

    image = QPixmap::fromImage(QImage(dst, width, height, QImage::Format_Grayscale8));
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(image);
    ui->graphicsViewAfter->setScene(scene);
    ui->graphicsViewAfter->show();
    ui->graphicsViewAfter->fitInView(image.rect(), Qt::KeepAspectRatio);

    savebmp("encode.bmp", dst, height, width);
}

void MainWindow::on_pushButtonDecode_clicked()
{
    int width, height;
    uchar* buffer = readBmp(ui->lineEdit->displayText().toStdString().data(), width, height);
    byteArray code = encode(decodeImg(buffer, dst, width, height, key.length()), key);
    if(ui->comboBoxWaterMark->currentIndex() == 2)
    {
        QMessageBox::warning(this, "Decode", "The watermark is " + array2byte(code)+"!");
    }
    if(ui->comboBoxWaterMark->currentIndex() == 1)
    {
        QMessageBox::warning(this, "Decode", "The watermark is " + array2str(code)+"!");
    }
}
