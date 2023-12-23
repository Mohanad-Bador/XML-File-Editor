#ifndef XMLPARSER_H
#define XMLPARSER_H
#include <fstream>
#include <algorithm>
#include "User.h"

#pragma once

class XMLParser
{
public:
    XMLParser();
    ~XMLParser();
   vector<User *> parseXML(string filepath);
   
private:
       

};

#endif