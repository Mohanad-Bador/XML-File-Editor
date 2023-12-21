#ifndef XML_CHECKER_H
#define XML_CHECKER_H
#include <stack>
#include <vector>
#include <utility>
#include <string>
// #include "XmlChecker.cpp"

using namespace std;

class XmlChecker
{
private:
    stack<string> tagStack;
    vector<pair<int, int>> errorIndices; 
public:
     vector<pair<int, int>> checkXmlErrors(const string& xmlContent);


};



#endif // XML_CHECKER_H