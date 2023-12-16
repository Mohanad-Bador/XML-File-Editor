#ifndef XML_PARSER_H
#define XML_PARSER_H

#include <QString>
#include <QXmlStreamReader>
#include "globals.h"
#include <QDebug>
#include <QStack>


class XML_Parser
{
public:
    XML_Parser();
    void Set_XML_Content(const QString& content);
    bool Check_Consistency();
    QString Get_XML_Content();
    bool isOpeningTag(const QString& tag);
    bool isClosingTag(const QString& tag);
private:
    QString XML_File;
    QStack<QString> Tags;

};

#endif // XML_PARSER_H
