#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;
#pragma once


static inline void ltrim(string& s);
static inline void rtrim(string& s);
static inline void trim(string& s);
string replace_str(string str, const string& toReplace, const string& replaceWith);
string getOpenTag(string t);
string getClosedTag(string t);
string getTagValue(string t); 

vector <string> file_to_vector(string file_loc);


#endif