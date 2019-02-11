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
    /*
    if(ui->comboBoxWaterMark->currentIndex() == 2)
    {
        QRegExp regx("[0-1]+$");
        QValidator *validator = new QRegExpValidator(regx, this );
        ui->lineEditWaterMark->setValidator( validator );
    }
    else
    {
        QRegExp regx(".");
        QValidator *validator = new QRegExpValidator(regx, this );
        ui->lineEditWaterMark->setValidator( validator );
    }
    */
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
    watermark WT;
    if(QFileInfo(ui->lineEdit->displayText()).exists())
    {
        int height, width;
        uchar* buffer = WT.readBmp(ui->lineEdit->displayText().toStdString().data(), width, height);
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
    watermark WT;
    if(ui->comboBoxWaterMark->currentIndex() == 2)
    {
        QRegExp regx("[0-1]+$");
        QValidator *validator = new QRegExpValidator(regx, this );
        ui->lineEditWaterMark->setValidator( validator );
        QString str1 = ui->lineEditWaterMark->text();
        code = WT.byte2Array(str1);
		delete validator;
	}
    else
    {
        QRegExp regx(".+\n");
        QValidator *validator = new QRegExpValidator(regx, this );
        ui->lineEditWaterMark->setValidator( validator );
        QString str2 = ui->lineEditWaterMark->text();
        //code = str2Array(ui->lineEditWaterMark->text());
        code = WT.str2Array(str2);
		delete validator;
	}
    key = WT.generateKey(code.length());
    int width, height;
    uchar* buffer = WT.readBmp(ui->lineEdit->displayText().toStdString().data(), width, height);
    uchar* edge = WT.edgeExtract(buffer, width, height);
    dst = WT.watermarkImg(buffer, edge, width*height, WT.encode(code, key));

    image = QPixmap::fromImage(QImage(dst, width, height, QImage::Format_Grayscale8));
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(image);
    ui->graphicsViewAfter->setScene(scene);
    ui->graphicsViewAfter->show();
    ui->graphicsViewAfter->fitInView(image.rect(), Qt::KeepAspectRatio);

    WT.savebmp("encode.bmp", dst, height, width);
}

void MainWindow::on_pushButtonDecode_clicked()
{
    watermark WT;
    int width, height;
    uchar* buffer = WT.readBmp(ui->lineEdit->displayText().toStdString().data(), width, height);
    byteArray code = WT.encode(WT.decodeImg(buffer, dst, width, height, key.length()), key);
    if(ui->comboBoxWaterMark->currentIndex() == 2)
    {
        QMessageBox::warning(this, "Decode", "The watermark is " + WT.array2byte(code)+"!");
    }
    if(ui->comboBoxWaterMark->currentIndex() == 1)
    {
        QMessageBox::warning(this, "Decode", "The watermark is " + WT.array2str(code)+"!");
    }
}
