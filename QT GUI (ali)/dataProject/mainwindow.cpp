#include "mainwindow.h"
#include "ui_mainwindow.h"

QString filePath;
QVector<QString> xml_file;
//.
XMLParser parser;
vector<User*> users =parser.parseXML("sample.xml");
Graph userGraph(users.size(),users);
//.
XML_Parser parse_xml;
MyUniqueCompression xali;
string compressed ;
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
                QStringList stringList = xmlContent.split("\n");
                vector <string> Bdetection;
                // Convert each QString to std::string
                for (const QString& str : stringList) {
                    Bdetection.push_back(str.toStdString());
                }
                vector <err_data> errors = detectError(Bdetection);
                Display_Problematic_XML(xmlContent, errors);
            }
        } else {
            qDebug() << "Error opening XML file";
        }
    }


}


void MainWindow::Display_Problematic_XML(const QString& xmlContent, const std::vector<err_data>& errors) {
    // Create a new QTextEdit to display the XML content with mistakes highlighted
    QTextEdit *xmlBrowser = new QTextEdit(this);

    // Set the XML content to the QTextEdit
    xmlBrowser->setPlainText(xmlContent);

    // Process the XML content and highlight mistakes
    QTextCursor cursor(xmlBrowser->document());

    QTextCharFormat errorFormat;
    errorFormat.setForeground(QColor(Qt::red));
    //errorFormat.setFontUnderline(true);

    QList<QTextEdit::ExtraSelection> selections;

    // Split the XML content into lines
    QStringList lines = xmlContent.split('\n');

    for (const err_data& error : errors) {
        // Ensure the error line number is valid
        int errorLineNumber = error.err_loc ; // Adjust for zero-based index
        if (errorLineNumber >= 0 && errorLineNumber < lines.size()) {
            // Set the cursor to the start of the error line
            cursor.setPosition(cursor.document()->findBlockByLineNumber(errorLineNumber).position());

            // Set the selection range for the error line
            QTextEdit::ExtraSelection selection;
            selection.format = errorFormat;
            selection.cursor = cursor;
            selection.cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);

            // Add the extra selection to the list
            selections.append(selection);
        }
    }

    // Set all the extra selections
    xmlBrowser->setExtraSelections(selections);

    // Add the new QTextEdit to the layout
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
            QStringList stringList = xmlContent.split("\n");
            vector <string> Bdetection;
            // Convert each QString to std::string
            for (const QString& str : stringList) {
                Bdetection.push_back(str.toStdString());
            }
            vector <err_data> errors = detectError(Bdetection);
        }
    }

}


void MainWindow::on_Correct_Errors_Button_clicked()
{
    QString xmlcontent = parse_xml.Get_XML_Content();
    QString correctedContent;
    QStringList stringList = xmlcontent.split("\n");
    vector <string> Bcorrection;
    // Convert each QString to std::string
    for (const QString& str : stringList) {
        Bcorrection.push_back(str.toStdString());
    }
    vector <err_data> correction = detectError(Bcorrection);

    vector <string> correctionn= error_corrector(Bcorrection, correction);
    QString result;
    for (const std::string& str : correctionn) {
        result += QString::fromStdString(str);
        result += "\n";
    }
    correctedContent = result;






    QLabel *Correct_Errors = new QLabel(this);
    Correct_Errors->setText(correctedContent);
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
    QString jsonContent = QString::fromStdString(convert_to_json((filePath.toStdString())));







    QLabel *Convert_To_Json = new QLabel(this);
    Convert_To_Json->setText(jsonContent);
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
    QString minfiedContent = minifyS((filePath.toStdString()));







    QLabel *Minify = new QLabel(this);
    Minify->setText(minfiedContent);
    // Set the alignment to allow word wrapping at spaces
    Minify->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    // Set the size policy to make the QLabel adjust its size based on the content
    Minify->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    Minify->setMaximumWidth(ui->scrollArea_2->width());

    Minify->setWordWrap(true);

    ui->scrollArea_2->setWidget(Minify);
    ui->scrollArea_2->setWidgetResizable(true);
}


void MainWindow::on_Compress_Button_clicked()
{
    QString xmlcontent = parse_xml.Get_XML_Content();
    compressed = xali.compressData((xmlcontent.toStdString()));
    //xali.compressData((xmlcontent.toStdString()));
    QString compressedContent = QString::fromStdString(compressed);







    QLabel *Compress = new QLabel(this);
    Compress->setText(compressedContent);
    Compress->setWordWrap(true);

    ui->scrollArea_2->setWidget(Compress);
    ui->scrollArea_2->setWidgetResizable(true);
}


void MainWindow::on_Decompress_Button_clicked()
{
    QString xmlcontent = parse_xml.Get_XML_Content();

    QString decompressedContent = QString::fromStdString(xali.decompressData((compressed)));






    QLabel *Decompress = new QLabel(this);
    Decompress->setText(decompressedContent);
    Decompress->setWordWrap(true);

    ui->scrollArea_2->setWidget(Decompress);
    ui->scrollArea_2->setWidgetResizable(true);
}


void MainWindow::on_Detect_Error_clicked()
{
    QString xmlcontent = parse_xml.Get_XML_Content();

    QString detectedContent;
    QStringList stringList = xmlcontent.split("\n");
    vector <string> Bdetection;
    // Convert each QString to std::string
    for (const QString& str : stringList) {
        Bdetection.push_back(str.toStdString());
    }
    vector <err_data> detection = detectError(Bdetection);

    string  detectionn = printError (detection);

    detectedContent = QString::fromStdString(detectionn);


    QLabel *Detect = new QLabel(this);
    Detect->setText(detectedContent);
    Detect->setWordWrap(true);

    ui->scrollArea_2->setWidget(Detect);
    ui->scrollArea_2->setWidgetResizable(true);

}


void MainWindow::on_SocialNetworkAnalysis_clicked()
{
    QString xmlcontent = parse_xml.Get_XML_Content();





    QDialog *newDialog = new QDialog(this);
    newDialog->setFixedSize(500, 400);
    newDialog->setWindowTitle("Social Network Analysis");
    QScrollArea *dataScrollArea = new QScrollArea(newDialog);
    QLabel *label = new QLabel(xmlcontent, newDialog);
    dataScrollArea->setWidget(label);
    dataScrollArea->setWidgetResizable(true);
    newDialog->exec();
}


void MainWindow::on_mutualUsers_clicked()
{
    QDialog *inputDialog = new QDialog(this);
    inputDialog->setFixedSize(300, 150);
    inputDialog->setWindowTitle("Mutual users");
    QVBoxLayout *layout = new QVBoxLayout(inputDialog);
    QLabel *labelFirstID = new QLabel("Enter First ID:", inputDialog);
    QLineEdit *lineEditFirstID = new QLineEdit(inputDialog);
    QLabel *labelSecondID = new QLabel("Enter Second ID:", inputDialog);
    QLineEdit *lineEditSecondID = new QLineEdit(inputDialog);
    layout->addWidget(labelFirstID);
    layout->addWidget(lineEditFirstID);
    layout->addWidget(labelSecondID);
    layout->addWidget(lineEditSecondID);
    QPushButton *submitButton = new QPushButton("Submit", inputDialog);
    layout->addWidget(submitButton);
    connect(submitButton, &QPushButton::clicked, [this, inputDialog, lineEditFirstID, lineEditSecondID]() {
        int firstID = lineEditFirstID->text().toInt();
        int secondID = lineEditSecondID->text().toInt();
        vector<User*> users =parser.parseXML(filePath.QString::toStdString());
        Graph userGraph(users.size(),users);
        userGraph.buildGraph();
        QString resultString = QString ::fromStdString(userGraph.get_mutualFollowers(to_string(firstID ),to_string(secondID)));
        // Perform your logic with the entered IDs HEREEEE AND PUT THE RESULTS IN THIS resultString
        //QString resultString = "THE ID of the first is " + QString::number(firstID) + " and that of the second is: " + QString::number(secondID);



        QDialog *resultDialog = new QDialog(this);
        resultDialog->setFixedSize(300, 150);
        resultDialog->setWindowTitle("Mutual between two users");
        QVBoxLayout *resultLayout = new QVBoxLayout(resultDialog);
        QLabel *resultLabel = new QLabel(resultString, resultDialog);
        resultLayout->addWidget(resultLabel);
        resultDialog->exec();
        inputDialog->close();
    });
    inputDialog->exec();
}



void MainWindow::on_showSuggestions_clicked()
{
    QDialog *inputDialog = new QDialog(this);
    inputDialog->setFixedSize(300, 150);
    inputDialog->setWindowTitle("Suggestions");
    QVBoxLayout *layout = new QVBoxLayout(inputDialog);
    QLabel *labelFirstID = new QLabel("Enter The user's ID:", inputDialog);
    QLineEdit *lineEditFirstID = new QLineEdit(inputDialog);
    layout->addWidget(labelFirstID);
    layout->addWidget(lineEditFirstID);
    QPushButton *submitButton = new QPushButton("Submit", inputDialog);
    layout->addWidget(submitButton);
    connect(submitButton, &QPushButton::clicked, [this, inputDialog, lineEditFirstID]() {
        int ID = lineEditFirstID->text().toInt();

        // Perform your logic with the entered IDs HEREEEE AND PUT THE RESULTS IN THIS resultString

        vector<User*> users =parser.parseXML(filePath.QString::toStdString());
        Graph userGraph(users.size(),users);
        userGraph.buildGraph();
        QString resultString = QString ::fromStdString(userGraph.get_suggestedFollowers(to_string(ID )));


        QDialog *resultDialog = new QDialog(this);
        resultDialog->setFixedSize(300, 150);
        resultDialog->setWindowTitle("Mutual between two users");
        QVBoxLayout *resultLayout = new QVBoxLayout(resultDialog);
        QLabel *resultLabel = new QLabel(resultString, resultDialog);
        resultLayout->addWidget(resultLabel);
        resultDialog->exec();
        inputDialog->close();
    });
    inputDialog->exec();
}


void MainWindow::on_postSearch_clicked()
{
    QDialog *inputDialog = new QDialog(this);
    inputDialog->setFixedSize(300, 150);
    inputDialog->setWindowTitle("Post search");
    QVBoxLayout *layout = new QVBoxLayout(inputDialog);
    QLabel *post = new QLabel("Enter a post:", inputDialog);
    QLineEdit *postText = new QLineEdit(inputDialog);
    layout->addWidget(post);
    layout->addWidget(postText);
    QPushButton *submitButton = new QPushButton("Submit", inputDialog);
    layout->addWidget(submitButton);
    connect(submitButton, &QPushButton::clicked, [this, inputDialog, postText]() {
        string post = postText->text().toStdString();

        // Perform your logic with the entered IDs HEREEEE AND PUT THE RESULTS IN THIS resultString
        QString resultString = QString::fromStdString(post);



        QDialog *resultDialog = new QDialog(this);
        resultDialog->setFixedSize(300, 150);
        resultDialog->setWindowTitle("Mutual between two users");
        QVBoxLayout *resultLayout = new QVBoxLayout(resultDialog);
        QLabel *resultLabel = new QLabel(resultString, resultDialog);
        resultLayout->addWidget(resultLabel);
        resultDialog->exec();
        inputDialog->close();
    });
    inputDialog->exec();
}


void MainWindow::on_mostActive_clicked()
{


    vector<User*> users =parser.parseXML(filePath.QString::toStdString());
    Graph userGraph(users.size(),users);
    userGraph.buildGraph();
    QString mostActive = QString ::fromStdString(userGraph.get_mostActiveUser());

    QDialog *newDialog = new QDialog(this);
    newDialog->setFixedSize(250, 250); // Increased height to accommodate QLabel
    newDialog->setWindowTitle("Social Network Analysis");

    // Create a QVBoxLayout for the dialog
    QVBoxLayout *mainLayout = new QVBoxLayout(newDialog);

    // Create a QLabel and set its alignment to center
    QLabel *label = new QLabel(mostActive, newDialog);
    label->setAlignment(Qt::AlignCenter);

    // Add the QLabel to the layout
    mainLayout->addWidget(label);

    // Set the layout for the QDialog
    newDialog->setLayout(mainLayout);

    newDialog->exec();
}


void MainWindow::on_mostInfluential_clicked()
{
    vector<User*> users =parser.parseXML(filePath.QString::toStdString());
    Graph userGraph(users.size(),users);
    userGraph.buildGraph();
    QString mostActive = QString ::fromStdString(userGraph.get_mostInfluentialUser());
    // Perform your logic with the entered IDs HEREEEE AND PUT THE RESULTS IN THIS resultString




    //QDialog *resultDialog = new QDialog(this);



    QDialog *newDialog = new QDialog(this);
    newDialog->setFixedSize(250, 250); // Increased height to accommodate QLabel
    newDialog->setWindowTitle("Social Network Analysis");

    // Create a QVBoxLayout for the dialog
    QVBoxLayout *mainLayout = new QVBoxLayout(newDialog);

    // Create a QLabel and set its alignment to center
    QLabel *label = new QLabel(mostActive, newDialog);
    label->setAlignment(Qt::AlignCenter);

    // Add the QLabel to the layout
    mainLayout->addWidget(label);

    // Set the layout for the QDialog
    newDialog->setLayout(mainLayout);

    newDialog->exec();
}

