#include "xmlparser.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

using namespace std;

string parseXMLFile(const char* filename) {
    try {
        // Load the XML file into memory
        rapidxml::file<> xmlFile(filename);

        // Return the entire XML content as a string
        return string(xmlFile.data());
    } catch (const rapidxml::parse_error& e) {
        cerr << "Parsing error: " << e.what() << endl;
        return ""; // Return an empty string in case of error
    }
}
