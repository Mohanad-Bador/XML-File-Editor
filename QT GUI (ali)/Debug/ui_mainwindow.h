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
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
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
    QPushButton *Enter_XML_File;
    QPushButton *Decompress_Button;
    QPushButton *Minify_Button;
    QPushButton *Correct_Errors_Button;
    QPushButton *upload_xml;
    QPushButton *Compress_Button;
    QScrollArea *scrollArea_1;
    QWidget *scrollAreaWidgetContents;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *Convert_To_Json;
    QPushButton *Format_Button;
    QPushButton *Save_Json_Button;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QMenuBar *menubar;
    QMenu *menuds_ali_l_gamed;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1240, 667);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        Enter_XML_File = new QPushButton(centralwidget);
        Enter_XML_File->setObjectName("Enter_XML_File");
        Enter_XML_File->setGeometry(QRect(150, 550, 141, 29));
        Decompress_Button = new QPushButton(centralwidget);
        Decompress_Button->setObjectName("Decompress_Button");
        Decompress_Button->setGeometry(QRect(1072, 550, 101, 29));
        Minify_Button = new QPushButton(centralwidget);
        Minify_Button->setObjectName("Minify_Button");
        Minify_Button->setGeometry(QRect(670, 550, 83, 29));
        Correct_Errors_Button = new QPushButton(centralwidget);
        Correct_Errors_Button->setObjectName("Correct_Errors_Button");
        Correct_Errors_Button->setGeometry(QRect(550, 550, 111, 29));
        upload_xml = new QPushButton(centralwidget);
        upload_xml->setObjectName("upload_xml");
        upload_xml->setGeometry(QRect(30, 550, 91, 29));
        Compress_Button = new QPushButton(centralwidget);
        Compress_Button->setObjectName("Compress_Button");
        Compress_Button->setGeometry(QRect(980, 550, 83, 29));
        scrollArea_1 = new QScrollArea(centralwidget);
        scrollArea_1->setObjectName("scrollArea_1");
        scrollArea_1->setGeometry(QRect(20, 30, 581, 471));
        scrollArea_1->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 579, 469));
        verticalLayoutWidget = new QWidget(scrollAreaWidgetContents);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(9, 9, 561, 451));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea_1->setWidget(scrollAreaWidgetContents);
        Convert_To_Json = new QPushButton(centralwidget);
        Convert_To_Json->setObjectName("Convert_To_Json");
        Convert_To_Json->setGeometry(QRect(760, 550, 121, 29));
        Format_Button = new QPushButton(centralwidget);
        Format_Button->setObjectName("Format_Button");
        Format_Button->setGeometry(QRect(460, 550, 83, 29));
        Save_Json_Button = new QPushButton(centralwidget);
        Save_Json_Button->setObjectName("Save_Json_Button");
        Save_Json_Button->setGeometry(QRect(890, 550, 83, 29));
        scrollArea_2 = new QScrollArea(centralwidget);
        scrollArea_2->setObjectName("scrollArea_2");
        scrollArea_2->setGeometry(QRect(640, 30, 581, 471));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName("scrollAreaWidgetContents_2");
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 579, 469));
        scrollArea_2->setWidget(scrollAreaWidgetContents_2);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1240, 25));
        menuds_ali_l_gamed = new QMenu(menubar);
        menuds_ali_l_gamed->setObjectName("menuds_ali_l_gamed");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuds_ali_l_gamed->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        Enter_XML_File->setText(QCoreApplication::translate("MainWindow", "Enter_XML_File", nullptr));
        Decompress_Button->setText(QCoreApplication::translate("MainWindow", "Decompress", nullptr));
        Minify_Button->setText(QCoreApplication::translate("MainWindow", "Minify", nullptr));
        Correct_Errors_Button->setText(QCoreApplication::translate("MainWindow", "Correct_Errors", nullptr));
        upload_xml->setText(QCoreApplication::translate("MainWindow", "upload_xml", nullptr));
        Compress_Button->setText(QCoreApplication::translate("MainWindow", "Compress", nullptr));
        Convert_To_Json->setText(QCoreApplication::translate("MainWindow", "Convert_To_Json", nullptr));
        Format_Button->setText(QCoreApplication::translate("MainWindow", "Format", nullptr));
        Save_Json_Button->setText(QCoreApplication::translate("MainWindow", "Save_Json", nullptr));
        menuds_ali_l_gamed->setTitle(QCoreApplication::translate("MainWindow", "ds ali l gamed", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
