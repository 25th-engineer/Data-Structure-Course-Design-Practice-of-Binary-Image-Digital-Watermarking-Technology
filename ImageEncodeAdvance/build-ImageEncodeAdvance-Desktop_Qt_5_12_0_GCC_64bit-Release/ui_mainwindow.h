/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QPushButton *pushButtonBrowse;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEditWaterMark;
    QComboBox *comboBoxWaterMark;
    QGridLayout *gridLayout;
    QGraphicsView *graphicsViewPrevious;
    QGraphicsView *graphicsViewAfter;
    QPushButton *pushButtonEncode;
    QPushButton *pushButtonDecode;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(843, 533);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);

        pushButtonBrowse = new QPushButton(centralWidget);
        pushButtonBrowse->setObjectName(QString::fromUtf8("pushButtonBrowse"));

        horizontalLayout_2->addWidget(pushButtonBrowse);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEditWaterMark = new QLineEdit(centralWidget);
        lineEditWaterMark->setObjectName(QString::fromUtf8("lineEditWaterMark"));

        horizontalLayout->addWidget(lineEditWaterMark);

        comboBoxWaterMark = new QComboBox(centralWidget);
        comboBoxWaterMark->setObjectName(QString::fromUtf8("comboBoxWaterMark"));

        horizontalLayout->addWidget(comboBoxWaterMark);


        verticalLayout->addLayout(horizontalLayout);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        graphicsViewPrevious = new QGraphicsView(centralWidget);
        graphicsViewPrevious->setObjectName(QString::fromUtf8("graphicsViewPrevious"));

        gridLayout->addWidget(graphicsViewPrevious, 0, 0, 1, 1);

        graphicsViewAfter = new QGraphicsView(centralWidget);
        graphicsViewAfter->setObjectName(QString::fromUtf8("graphicsViewAfter"));

        gridLayout->addWidget(graphicsViewAfter, 0, 1, 1, 1);

        pushButtonEncode = new QPushButton(centralWidget);
        pushButtonEncode->setObjectName(QString::fromUtf8("pushButtonEncode"));

        gridLayout->addWidget(pushButtonEncode, 1, 0, 1, 1);

        pushButtonDecode = new QPushButton(centralWidget);
        pushButtonDecode->setObjectName(QString::fromUtf8("pushButtonDecode"));

        gridLayout->addWidget(pushButtonDecode, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\345\233\276\347\211\207 ", nullptr));
        pushButtonBrowse->setText(QApplication::translate("MainWindow", "\346\265\217\350\247\210", nullptr));
        label->setText(QApplication::translate("MainWindow", "\346\260\264\345\215\260 ", nullptr));
        pushButtonEncode->setText(QApplication::translate("MainWindow", "\347\274\226\347\240\201", nullptr));
        pushButtonDecode->setText(QApplication::translate("MainWindow", "\350\247\243\347\240\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
