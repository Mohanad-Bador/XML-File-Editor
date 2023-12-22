#include "./rapidjson/document.h"
#include "./rapidjson/writer.h"
#include "./rapidjson/stringbuffer.h"
#include "./tinyxml2.h"
#include <string>

using namespace std;

/*
    Convert XML String to JSON String
    @param xmlString XML content as a string
    @return JSON content as a string
*/
string xmlToJson(string xmlString) {
    // convert string to xml document
    tinyxml2::XMLDocument doc;
    if (doc.Parse(xmlString.c_str()) != tinyxml2::XML_SUCCESS) {
        return "Invalid XML Text";
    }


    rapidjson::Document jsonDoc;
    jsonDoc.SetObject();

    // Iterate over XML tags
    for (const tinyxml2::XMLNode* node = doc.FirstChild(); node != nullptr; node = node->NextSibling()) {
        if (node->ToElement()) {
            rapidjson::Value jsonElement(rapidjson::kObjectType);
            // Iterate over tag attributes
            for (const tinyxml2::XMLAttribute* attribute = node->ToElement()->FirstAttribute(); attribute != nullptr; attribute == attribute->Next()) {
                jsonElement.AddMember(rapidjson::Value().SetString(attribute->Name()), jsonElement, jsonDoc.GetAllocator()); // TODO: fix IntelliSense warning here
            }
            {
                /* code */
            }
            
        }
    }
    // TODO
    return "WIP";
}