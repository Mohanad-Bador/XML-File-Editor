#include "./rapidjson/document.h"
#include "./rapidjson/prettywriter.h"
#include "./rapidjson/stringbuffer.h"
#include "./tinyxml2.cpp"
#include <string>

using namespace std;


/*
    This function is meant to be called inside xmlToJson only
    NOT FOR USE
*/
void processXmlElement(const tinyxml2::XMLElement* element, rapidjson::Value& jsonElement, rapidjson::Document::AllocatorType& allocator) {
    // iterate over tag attributes
    for (const tinyxml2::XMLAttribute* attribute = element->FirstAttribute(); attribute != nullptr; attribute = attribute->Next()) {
        jsonElement.AddMember(rapidjson::Value().SetString(attribute->Name(), allocator), rapidjson::Value().SetString(attribute->Value(), allocator), allocator);
    }

    // handle text content
    const char* text = element->GetText();
    if (text) {
        jsonElement.AddMember(rapidjson::Value().SetString("text", allocator), rapidjson::Value().SetString(text, allocator), allocator);
    }

    // recursion
    for (const tinyxml2::XMLNode* node = element->FirstChild(); node != nullptr; node = node->NextSibling()) {
        if (node->ToElement()) {
            rapidjson::Value childElement(rapidjson::kObjectType);
            processXmlElement(node->ToElement(), childElement, allocator);
            jsonElement.AddMember(rapidjson::Value().SetString(node->ToElement()->Name(), allocator), childElement, allocator);
        }
    }
}



/*
    Convert XML String to JSON String
    @param xmlString minified XML content as a string
    @return prettified JSON content as a string
*/
string xmlToJson(string xmlString) {
    // convert string to xml document
    tinyxml2::XMLDocument doc;
    if (doc.Parse(xmlString.c_str()) != tinyxml2::XML_SUCCESS) {
        return "Invalid XML Text";
    }


    rapidjson::Document jsonDoc;
    jsonDoc.SetObject();

     // get root element
    const tinyxml2::XMLElement* root = doc.RootElement();
    if (root) {
        // recursively process the root element and its children
        processXmlElement(root, jsonDoc, jsonDoc.GetAllocator());
    }

    // json to pretty string
    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    jsonDoc.Accept(writer);
    return buffer.GetString();
}