#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QXmlStreamReader>
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QXmlStreamReader>
#include <QTextStream>
#include <QString>
#include <QLabel>
#include <QInputDialog>
#include <xml_parser.h>
#include <QTextEdit>
#include <QTextDocument>
#include <QTextCursor>
#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QVector>
#include <QPair>
#include <QMessageBox>
#include <QTextBrowser>
#include <QDomDocument>
#include "formatting.h"
#include "xmltojson.h"
#include "MyUniqueCompression.h"
#include "consistency.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_upload_xml_clicked();

    void on_Enter_XML_File_clicked();

    void on_Correct_Errors_Button_clicked();

    void on_Format_Button_clicked();

    void on_Convert_To_Json_clicked();

    void on_Save_Json_Button_clicked();

    void on_Minify_Button_clicked();

    void on_Compress_Button_clicked();

    void on_Decompress_Button_clicked();

    void on_Detect_Error_clicked();

    void on_SocialNetworkAnalysis_clicked();

    void on_mutualUsers_clicked();

    void on_showSuggestions_clicked();

    void on_postSearch_clicked();

private:
    Ui::MainWindow *ui;
    void Display_Problematic_XML(const QString& xmlContent, const std::vector<err_data>& errors);
};
#endif // MAINWINDOW_H
