#include <iostream>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

int main() {
    try {
        // Load the XML file into memory
        rapidxml::file<> xmlFile("../sample.xml");

        // Print the entire XML content
        std::cout << xmlFile.data() << std::endl;
    } catch (const rapidxml::parse_error& e) {
        std::cerr << "Parsing error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
