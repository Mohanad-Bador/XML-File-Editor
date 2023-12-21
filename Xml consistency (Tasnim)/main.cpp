#include <iostream>
#include "xmlparser.h"
#include "XmlChecker.cpp"
using namespace std;


int main() {
    // Example of how to use the parseXMLFile function
    string xmlContent = parseXMLFile("../sample.xml");

    // Print the entire XML content
    cout << xmlContent << endl;


    XmlChecker xmlChecker;

    vector<pair<int, int>> errors = xmlChecker.checkXmlErrors(xmlContent);

    if (!errors.empty()) {
        cout << "XML errors found:" << endl;
        for (const auto& error : errors) {
            cout << "Error at indices " << error.first << " - " << error.second << endl;
        }
    } else {
        cout << "No XML errors found." << endl;
    }


    return 0;
}