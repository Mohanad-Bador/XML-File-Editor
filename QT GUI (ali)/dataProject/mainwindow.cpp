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

UndoRedoManager undoRedoManager;

QString detectedContent;
QString correctedContent;
QString minfiedContent;
QString formattedContent;
QString jsonContent;
QString compressedContent;
QString decompressedContent;

QString textToSave;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    // Set the main window's palette background color to light green
    // QPalette mainWindowPalette;
    // mainWindowPalette.setColor(QPalette::Window, QColor(144, 238, 144)); // Light green color
    // setPalette(mainWindowPalette);

    // // Customize the stylesheet for buttons
    // QString buttonStylesheet = "QPushButton {"
    //                            "    background-color: red;"
    //                            "    color: white;"
    //                            "}";

    // // Apply the stylesheet to all QPushButton instances in the main window
    // setStyleSheet(buttonStylesheet);
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

    undoRedoManager.addToUndoStack(correctedContent);

    textToSave=correctedContent;


    QLabel *Correct_Errors = new QLabel(this);
    Correct_Errors->setText(correctedContent);
    Correct_Errors->setWordWrap(true);

    ui->scrollArea_2->setWidget(Correct_Errors);
    ui->scrollArea_2->setWidgetResizable(true);
}


void MainWindow::on_Format_Button_clicked()
{
    QString xmlcontent = parse_xml.Get_XML_Content();
    formattedContent = QString::fromStdString(FORMAT((filePath.toStdString())));


    textToSave = formattedContent;
    undoRedoManager.addToUndoStack(formattedContent);
    QLabel *Format = new QLabel(this);
    Format->setText(formattedContent);
    Format->setWordWrap(true);

    ui->scrollArea_2->setWidget(Format);
    ui->scrollArea_2->setWidgetResizable(true);
}


void MainWindow::on_Convert_To_Json_clicked()
{
    QString xmlcontent = parse_xml.Get_XML_Content();
    jsonContent = QString::fromStdString(convert_to_json((filePath.toStdString())));




    textToSave = jsonContent;

    undoRedoManager.addToUndoStack(jsonContent);
    QLabel *Convert_To_Json = new QLabel(this);
    Convert_To_Json->setText(jsonContent);
    Convert_To_Json->setWordWrap(true);

    ui->scrollArea_2->setWidget(Convert_To_Json);
    ui->scrollArea_2->setWidgetResizable(true);
}





void MainWindow::on_Minify_Button_clicked()
{
    QString xmlcontent = parse_xml.Get_XML_Content();
    minfiedContent = minifyS((filePath.toStdString()));

    undoRedoManager.addToUndoStack(minfiedContent);

    textToSave = minfiedContent;



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
    compressedContent = QString::fromStdString(compressed);


    textToSave = compressedContent;

    undoRedoManager.addToUndoStack(compressedContent);


    QLabel *Compress = new QLabel(this);
    Compress->setText(compressedContent);
    Compress->setWordWrap(true);

    ui->scrollArea_2->setWidget(Compress);
    ui->scrollArea_2->setWidgetResizable(true);
}


void MainWindow::on_Decompress_Button_clicked()
{
    QString xmlcontent = parse_xml.Get_XML_Content();

    decompressedContent = QString::fromStdString(xali.decompressData((compressed)));


    textToSave = decompressedContent;


    undoRedoManager.addToUndoStack(decompressedContent);
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

    undoRedoManager.addToUndoStack(detectedContent);

    QLabel *Detect = new QLabel(this);
    Detect->setText(detectedContent);
    Detect->setWordWrap(true);

    ui->scrollArea_2->setWidget(Detect);
    ui->scrollArea_2->setWidgetResizable(true);

}


// void MainWindow::on_SocialNetworkAnalysis_clicked()
// {
//     //QString xmlcontent = parse_xml.Get_XML_Content();
//     QString imagePath = "ali.dot.png";  // Adjust the path to your image
//     vector<User*> userrs =parser.parseXML(filePath.QString::toStdString());
//     Graph users(userrs.size(),userrs);
//     users.buildGraph();
//     // string result = "digraph Graph {\n\n";
//     // result += "\tnode [ shape = \"record\"  color = \"purple\"]\n\n";
//     // for(const auto &user : userrs)
//     // {
//     //     result += "\t" + user->id + " [ label = \"{ " + user->name + +" | id = " + user->id +
//     //               " }\" ]\n";
//     //     result += "\t" + user->id + " -> {";
//     //     //result += "1,2,3";
//     //     for(size_t i = 0; i < user->followers.size(); i++)
//     //     {
//     //         if(i)
//     //             result += " ,";
//     //         result += (user->followers[i]->id);
//     //     }
//     //     result += "}\n";
//     // }
//     // result += "}\n\n";


//     // QFile file("ali.dot");
//     // if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
//     //     return;
//     // }
//     // else{
//     // QTextStream out(&file);
//     // QString text = QString::fromStdString(result);
//     // out << text;
//     // file.flush();
//     // file.close();
//     // }
//     // //system("E:");
//     // system("dot -Tpng -O ali.dot");

//     // //QPixmap mypix("E:/ali/DS-Project/QT GUI (ali)/dataProject/ali.dot.png");

//     // //ui->img->setPixmap(mypix);
//     // QPixmap image(imagePath);


//     if (image.isNull()) {
//         QMessageBox::warning(this, "Error", "Failed to open the image.");
//     } else {
//         //QMessageBox::information(this, "Image Viewer", "", QMessageBox::NoButton, QMessageBox::NoButton);
//         QMessageBox msgBox;
//         msgBox.setIconPixmap(image.scaled(400, 400, Qt::KeepAspectRatio, Qt::SmoothTransformation));
//         msgBox.setWindowTitle("Graph Visualization");
//         msgBox.exec();
//     }




//     // QDialog *newDialog = new QDialog(this);
//     // newDialog->setFixedSize(500, 400);
//     // newDialog->setWindowTitle("Social Network Analysis");
//     // QScrollArea *dataScrollArea = new QScrollArea(newDialog);
//     // QLabel *label = new QLabel(xmlcontent, newDialog);
//     // dataScrollArea->setWidget(label);
//     // dataScrollArea->setWidgetResizable(true);
//     // newDialog->exec();
// }


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
        resultDialog->setWindowTitle("Suggested Followers");
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

        vector<User*> users =parser.parseXML(filePath.QString::toStdString());
        Graph userGraph(users.size(),users);
        userGraph.buildGraph();
        QString postSearch;
        for(int i=0;i<users.size();i++)
        {
            postSearch+= QString ::fromStdString(users[i]->postSearchByWord(post));
            postSearch+="\n";
        }

        QDialog *resultDialog = new QDialog(this);
        resultDialog->setFixedSize(400, 300);
        resultDialog->setWindowTitle("Post Search");
        QVBoxLayout *resultDialogLayout = new QVBoxLayout(resultDialog);
        QScrollArea *scrollArea = new QScrollArea(resultDialog);
        scrollArea->setWidgetResizable(true);
        QLabel *resultLabel = new QLabel(postSearch, resultDialog);
        resultLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop); // Adjust alignment as needed
        resultLabel->setWordWrap(true);
        scrollArea->setWidget(resultLabel);
        scrollArea->setWidgetResizable(true);
        resultDialogLayout->addWidget(scrollArea);
        resultDialog->setLayout(resultDialogLayout);
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
    newDialog->setWindowTitle("Most Active");

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
    newDialog->setWindowTitle("Most Influential");

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


void MainWindow::on_undo_clicked()
{
    QString undo = undoRedoManager.undo();
    QLabel *Undo = new QLabel(this);
    Undo->setText(undo);
    Undo->setWordWrap(true);

    ui->scrollArea_2->setWidget(Undo);
    ui->scrollArea_2->setWidgetResizable(true);
}


void MainWindow::on_redo_clicked()
{
    QString redo = undoRedoManager.redo();
    QLabel *Redo = new QLabel(this);
    Redo->setText(redo);
    Redo->setWordWrap(true);

    ui->scrollArea_2->setWidget(Redo);
    ui->scrollArea_2->setWidgetResizable(true);
}


void MainWindow::on_Save_xml_clicked() {
    // Assuming you have a QTextEdit named xmlTextEdit in your MainWindow


    // Open a file dialog for choosing the save location
    QString selectedFilePath = QFileDialog::getSaveFileName(this, "Save XML File", QDir::homePath(), "XML Files (*.xml)");

    if (!selectedFilePath.isEmpty()) {
        // Save the text to the selected file
        saveTextToXml(textToSave, selectedFilePath);
    } else {
        // User canceled the operation
        QMessageBox::information(this, "Information", "Save operation canceled.");
    }
}

void MainWindow::saveTextToXml(const QString &text, const QString &filename) {
    QFile file(filename);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // Handle error, e.g., show an error message
        QMessageBox::critical(this, "Error", "Failed to open file for writing.");
        return;
    }
    QTextStream out(&file);
    out << "<root>" << text << "</root>";  // You may want to modify this based on your XML structure
    file.close();

    QMessageBox::information(this, "Information", "Text saved to XML file successfully.");

}
void MainWindow::on_SocialNetworkAnalysis_clicked()
{
    QString imagePath = "ali.dot.png";  // Adjust the path to your image
    vector<User*> userrs = parser.parseXML(filePath.QString::toStdString());

    Graph users(userrs.size(), userrs);
    users.buildGraph();
    QVector<User*> qtUsers(userrs.begin(), userrs.end());

    // Create a new QGraphicsView and QGraphicsScene
    QGraphicsScene* graphScene = new QGraphicsScene(this);
    graphScene->setSceneRect(0, 0, 800, 600);  // Set the size of the scene

    QGraphicsView* graphView = new QGraphicsView(graphScene);
    graphView->setRenderHint(QPainter::Antialiasing);

    // Draw the graph on the QGraphicsView
    drawGraph(graphScene, qtUsers);

    // Create a new QDialog to display the QGraphicsView
    QDialog* graphDialog = new QDialog(this);
    graphDialog->setWindowTitle("Social Network Analysis");

    QVBoxLayout* layout = new QVBoxLayout(graphDialog);
    layout->addWidget(graphView);
    qDebug() << "Before opening graphDialog";
    graphDialog->show();
    qDebug() << "After opening graphDialog";
}


void MainWindow::drawGraph(QGraphicsScene* scene, const QVector<User*>& users)
{
    if (scene == nullptr) {
        qDebug() << "Error: QGraphicsScene is null in drawGraph.";
        return;
    }

    const qreal nodeWidth = 110;
    const qreal nodeHeight = 50;
    QVector<QGraphicsRectItem*> nodeItems;

    QVector<QPointF> nodePositions;

    // Determine node positions based on the number of users
    int numUsers = users.size();
    if (numUsers > 0) {
        qreal angleIncrement = 360.0 / numUsers;
        qreal currentAngle = 0;

        for (int i = 0; i < numUsers; ++i) {
            qreal x = 400 + 200 * qCos(qDegreesToRadians(currentAngle));
            qreal y = 300 + 200 * qSin(qDegreesToRadians(currentAngle));
            nodePositions.append(QPointF(x, y));
            currentAngle += angleIncrement;
        }
    }

    for (int i = 0; i < numUsers; ++i) {
        QGraphicsRectItem* nodeItem = scene->addRect(0, 0, nodeWidth, nodeHeight);
        if (nodeItem == nullptr) {
            qDebug() << "Error: Failed to create QGraphicsRectItem.";
            return;
        }

        nodeItem->setPos(nodePositions[i]);

        QGraphicsTextItem* textItem = scene->addText(QString("%1\n%2").arg(QString::fromStdString(users[i]->name)).arg(QString::fromStdString(users[i]->id)));
        if (textItem == nullptr) {
            qDebug() << "Error: Failed to create QGraphicsTextItem.";
            return;
        }

        textItem->setPos(nodeItem->pos() + QPointF(5, 5));

        nodeItems.append(nodeItem);
    }

    // Create edges (arrows)
    for (int i = 0; i < users.size(); ++i) {
        for (const auto& follower : users[i]->followers) {
            int followerIndex = -1; // Initialize to -1 to indicate not found

            // Find the follower in the users vector based on id
            for (int j = 0; j < users.size(); ++j) {
                if (follower->id == users[j]->id) {
                    followerIndex = j;
                    break;  // Follower found, exit the loop
                }
            }

            if (followerIndex != -1 && followerIndex < nodeItems.size()) {
                // Calculate the closest points on the rectangles for entering and leaving
                QPointF startCenter = nodeItems[i]->mapToScene(nodeWidth / 2, nodeHeight );
                QPointF endCenter = nodeItems[followerIndex]->mapToScene(nodeWidth / 2, nodeHeight );

                // Create arrow
                QGraphicsLineItem* edgeItem = new QGraphicsLineItem(QLineF(startCenter, endCenter));
                edgeItem->setPen(QPen(Qt::gray));
                scene->addItem(edgeItem);

                // Create arrowhead
                QGraphicsPolygonItem* arrowHead = new QGraphicsPolygonItem(QPolygonF() << QPointF(-5, 0) << QPointF(5, 0) << QPointF(0, 10));
                arrowHead->setPos(endCenter);
                arrowHead->setRotation(QLineF(endCenter, startCenter).angle());
                arrowHead->setBrush(QBrush(Qt::blue));

                scene->addItem(arrowHead);
            } else {
                qDebug() << "Warning: Follower not found in users vector.";
            }
        }
    }
}








