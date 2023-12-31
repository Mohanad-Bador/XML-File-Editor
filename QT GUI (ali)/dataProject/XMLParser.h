#ifndef XMLPARSER_H
#define XMLPARSER_H
#include <fstream>
#include <algorithm>
#include "Functions.h"
#include "User.h"


#pragma once

//extern Graph graph;

class XMLParser
{
public:
    XMLParser();
    ~XMLParser();
   vector<User *> parseXML(string filepath);
};

#endif
