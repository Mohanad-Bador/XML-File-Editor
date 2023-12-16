#include "mainwindow.h"
#include "ui_mainwindow.h"
QString filePath;
QVector<QString> xml_file;

XML_Parser parse_xml;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_upload_xml_clicked()
{
      filePath = QFileDialog::getOpenFileName(this, "Choose an XML file", QString(), "XML Files (*.xml)");


    if (!filePath.isEmpty()) {
        QFile file(filePath);



        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();

                // Remove spaces from the line
                line.remove(' ');

                xml_file.push_back(line);
            }
            file.close();
        }
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QString xmlContent = QTextStream(&file).readAll();
            file.close();

            // Set the XML content in the parser
            parse_xml.Set_XML_Content(xmlContent);

            // Check consistency and handle the result
            if (parse_xml.Check_Consistency()) {
                // XML is consistent, show in a new scroll area
                QLabel *XML_File = new QLabel(this);
                XML_File->setText(xmlContent);
                XML_File->setWordWrap(true);

                ui->scrollArea_1->setWidget(XML_File);
                ui->scrollArea_1->setWidgetResizable(true);
            } else {
                Display_Problematic_XML(xmlContent);
            }
        } else {
            qDebug() << "Error opening XML file";
        }
    }


}
void MainWindow::Display_Problematic_XML(const QString& xmlContent) {
    // Create a new QTextBrowser to display the XML content with mistakes highlighted
    QTextBrowser *xmlBrowser = new QTextBrowser(this);

    // Set the XML content to the QTextBrowser
    xmlBrowser->setPlainText(xmlContent);

    // Process the XML content and highlight mistakes
    QTextCursor cursor(xmlBrowser->document());

    // Identify the missing closing tag
    int errorStart = xmlContent.indexOf('<');
    int errorEnd = xmlContent.indexOf('>', errorStart + 1);

    while (errorStart != -1 && errorEnd != -1) {
        if (xmlContent[errorStart + 1] != '/') {
            // Check if the tag is an opening tag
            QString tagName = xmlContent.mid(errorStart + 1, errorEnd - errorStart - 1).trimmed();

            if (!ProblematicTagsQueue.isEmpty() && tagName == ProblematicTagsQueue.front()) {
                // Change the color of the matching tag to red
                QTextCharFormat format;
                format.setForeground(QColor(Qt::red));

                // Calculate the start and end positions of the current tag
                int tagStart = errorStart;
                int tagEnd = errorEnd;

                // Apply formatting only to the current tag
                cursor.setPosition(tagStart);
                cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, tagEnd - tagStart + 1);
                cursor.mergeCharFormat(format);
                // Dequeue the front of the queue
                ProblematicTagsQueue.dequeue();
            }
        }

        // Move to the next potential error
        errorStart = xmlContent.indexOf('<', errorEnd);
        errorEnd = xmlContent.indexOf('>', errorStart + 1);
    }

    // Add the new QTextBrowser to the layout
    ui->verticalLayout->addWidget(xmlBrowser);
}

void MainWindow::on_Enter_XML_File_clicked()
{
    bool ok;
    QString xmlContent = QInputDialog::getText(this, "Enter XML Content", "XML Content:", QLineEdit::Normal, "", &ok);

    if (ok && !xmlContent.isEmpty()) {
        // Set the XML content in the parser
        parse_xml.Set_XML_Content(xmlContent);

        // Check consistency and handle the result
        if (parse_xml.Check_Consistency()) {
            // XML is consistent, show in a new scroll area
            QLabel *Enter_XML_File = new QLabel(this);
            Enter_XML_File->setText(xmlContent);
            Enter_XML_File->setWordWrap(true);

            ui->scrollArea_1->setWidget(Enter_XML_File);
            ui->scrollArea_1->setWidgetResizable(true);
        } else {
            Display_Problematic_XML(xmlContent);
        }
    }

}


void MainWindow::on_Correct_Errors_Button_clicked()
{
    QString xmlcontent = parse_xml.Get_XML_Content();








    QLabel *Correct_Errors = new QLabel(this);
    Correct_Errors->setText(xmlcontent);
    Correct_Errors->setWordWrap(true);

    ui->scrollArea_2->setWidget(Correct_Errors);
    ui->scrollArea_2->setWidgetResizable(true);
}


void MainWindow::on_Format_Button_clicked()
{
    QString xmlcontent = parse_xml.Get_XML_Content();
    QString formattedContent = QString::fromStdString(FORMAT((filePath.toStdString())));




    QLabel *Format = new QLabel(this);
    Format->setText(formattedContent);
    Format->setWordWrap(true);

    ui->scrollArea_2->setWidget(Format);
    ui->scrollArea_2->setWidgetResizable(true);
}


void MainWindow::on_Convert_To_Json_clicked()
{
    QString xmlcontent = parse_xml.Get_XML_Content();








    QLabel *Convert_To_Json = new QLabel(this);
    Convert_To_Json->setText(xmlcontent);
    Convert_To_Json->setWordWrap(true);

    ui->scrollArea_2->setWidget(Convert_To_Json);
    ui->scrollArea_2->setWidgetResizable(true);
}


void MainWindow::on_Save_Json_Button_clicked()
{

}


void MainWindow::on_Minify_Button_clicked()
{
    QString xmlcontent = parse_xml.Get_XML_Content();
    QString minfiedContent = QString::fromStdString(MINIFY((filePath.toStdString())));







    QLabel *Minify = new QLabel(this);
    Minify->setText(minfiedContent);
    Minify->setWordWrap(true);

    ui->scrollArea_2->setWidget(Minify);
    ui->scrollArea_2->setWidgetResizable(true);
}


void MainWindow::on_Compress_Button_clicked()
{
    QString xmlcontent = parse_xml.Get_XML_Content();








    QLabel *Compress = new QLabel(this);
    Compress->setText(xmlcontent);
    Compress->setWordWrap(true);

    ui->scrollArea_2->setWidget(Compress);
    ui->scrollArea_2->setWidgetResizable(true);
}


void MainWindow::on_Decompress_Button_clicked()
{
    QString xmlcontent = parse_xml.Get_XML_Content();








    QLabel *Decompress = new QLabel(this);
    Decompress->setText(xmlcontent);
    Decompress->setWordWrap(true);

    ui->scrollArea_2->setWidget(Decompress);
    ui->scrollArea_2->setWidgetResizable(true);
}

