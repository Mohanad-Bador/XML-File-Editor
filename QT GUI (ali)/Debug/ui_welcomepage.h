/********************************************************************************
** Form generated from reading UI file 'welcomepage.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WELCOMEPAGE_H
#define UI_WELCOMEPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_welcomePage
{
public:
    QPushButton *upload_xml_1;
    QPushButton *Enter_XML_File_1;

    void setupUi(QDialog *welcomePage)
    {
        if (welcomePage->objectName().isEmpty())
            welcomePage->setObjectName("welcomePage");
        welcomePage->resize(807, 526);
        upload_xml_1 = new QPushButton(welcomePage);
        upload_xml_1->setObjectName("upload_xml_1");
        upload_xml_1->setGeometry(QRect(280, 440, 83, 29));
        Enter_XML_File_1 = new QPushButton(welcomePage);
        Enter_XML_File_1->setObjectName("Enter_XML_File_1");
        Enter_XML_File_1->setGeometry(QRect(420, 440, 83, 29));

        retranslateUi(welcomePage);

        QMetaObject::connectSlotsByName(welcomePage);
    } // setupUi

    void retranslateUi(QDialog *welcomePage)
    {
        welcomePage->setWindowTitle(QCoreApplication::translate("welcomePage", "Dialog", nullptr));
        upload_xml_1->setText(QCoreApplication::translate("welcomePage", "Upload xml", nullptr));
        Enter_XML_File_1->setText(QCoreApplication::translate("welcomePage", "Enter XML File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class welcomePage: public Ui_welcomePage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WELCOMEPAGE_H
