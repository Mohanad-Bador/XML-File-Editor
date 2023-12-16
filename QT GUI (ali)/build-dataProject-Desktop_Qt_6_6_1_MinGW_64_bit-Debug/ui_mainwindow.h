/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QScrollArea *scrollArea_1;
    QWidget *scrollAreaWidgetContents;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QPushButton *upload_xml;
    QPushButton *Enter_XML_File;
    QPushButton *Correct_Errors_Button;
    QPushButton *Format_Button;
    QPushButton *Convert_To_Json;
    QPushButton *Save_Json_Button;
    QPushButton *Minify_Button;
    QPushButton *Compress_Button;
    QPushButton *Decompress_Button;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        scrollArea_1 = new QScrollArea(centralwidget);
        scrollArea_1->setObjectName("scrollArea_1");
        scrollArea_1->setGeometry(QRect(40, 40, 311, 441));
        scrollArea_1->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 309, 439));
        verticalLayoutWidget = new QWidget(scrollAreaWidgetContents);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 19, 281, 401));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea_1->setWidget(scrollAreaWidgetContents);
        scrollArea_2 = new QScrollArea(centralwidget);
        scrollArea_2->setObjectName("scrollArea_2");
        scrollArea_2->setGeometry(QRect(410, 40, 331, 441));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName("scrollAreaWidgetContents_2");
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 329, 439));
        scrollArea_2->setWidget(scrollAreaWidgetContents_2);
        upload_xml = new QPushButton(centralwidget);
        upload_xml->setObjectName("upload_xml");
        upload_xml->setGeometry(QRect(40, 510, 141, 29));
        Enter_XML_File = new QPushButton(centralwidget);
        Enter_XML_File->setObjectName("Enter_XML_File");
        Enter_XML_File->setGeometry(QRect(210, 510, 131, 29));
        Correct_Errors_Button = new QPushButton(centralwidget);
        Correct_Errors_Button->setObjectName("Correct_Errors_Button");
        Correct_Errors_Button->setGeometry(QRect(370, 490, 111, 29));
        Format_Button = new QPushButton(centralwidget);
        Format_Button->setObjectName("Format_Button");
        Format_Button->setGeometry(QRect(370, 530, 111, 21));
        Convert_To_Json = new QPushButton(centralwidget);
        Convert_To_Json->setObjectName("Convert_To_Json");
        Convert_To_Json->setGeometry(QRect(490, 490, 111, 29));
        Save_Json_Button = new QPushButton(centralwidget);
        Save_Json_Button->setObjectName("Save_Json_Button");
        Save_Json_Button->setGeometry(QRect(490, 530, 111, 29));
        Minify_Button = new QPushButton(centralwidget);
        Minify_Button->setObjectName("Minify_Button");
        Minify_Button->setGeometry(QRect(610, 490, 83, 29));
        Compress_Button = new QPushButton(centralwidget);
        Compress_Button->setObjectName("Compress_Button");
        Compress_Button->setGeometry(QRect(610, 530, 83, 29));
        Decompress_Button = new QPushButton(centralwidget);
        Decompress_Button->setObjectName("Decompress_Button");
        Decompress_Button->setGeometry(QRect(700, 490, 91, 29));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        upload_xml->setText(QCoreApplication::translate("MainWindow", "choose xml file", nullptr));
        Enter_XML_File->setText(QCoreApplication::translate("MainWindow", "Enter XML file", nullptr));
        Correct_Errors_Button->setText(QCoreApplication::translate("MainWindow", "Correct errors", nullptr));
        Format_Button->setText(QCoreApplication::translate("MainWindow", "Format", nullptr));
        Convert_To_Json->setText(QCoreApplication::translate("MainWindow", "Convert to JSON", nullptr));
        Save_Json_Button->setText(QCoreApplication::translate("MainWindow", "Save JSON ", nullptr));
        Minify_Button->setText(QCoreApplication::translate("MainWindow", "Minify", nullptr));
        Compress_Button->setText(QCoreApplication::translate("MainWindow", "Compress", nullptr));
        Decompress_Button->setText(QCoreApplication::translate("MainWindow", "Decompress", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
