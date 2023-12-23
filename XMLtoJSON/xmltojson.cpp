#include "./rapidjson/document.h"
#include "./rapidjson/prettywriter.h"
#include "./rapidjson/stringbuffer.h"
#include "./tinyxml2.cpp"
#include <string>
#include <fstream>

using namespace std;


/*
    This function is meant to be called inside xmlToJson only
    NOT FOR USE
*/
void processXmlElement(const tinyxml2::XMLElement* element, rapidjson::Value& jsonElement, rapidjson::Document::AllocatorType& allocator) {
    // handle text content
    const char* text = element->GetText();
    if (text) {
        // Try to convert text values to various types
        try {
            // Try converting to integer
            int intValue = std::stoi(text);
            jsonElement.AddMember(rapidjson::Value().SetString(element->Name(), allocator), rapidjson::Value().SetInt(intValue), allocator);
        } catch (std::invalid_argument&) {
            try {
                // Try converting to float
                float floatValue = std::stof(text);
                jsonElement.AddMember(rapidjson::Value().SetString(element->Name(), allocator), rapidjson::Value().SetFloat(floatValue), allocator);
            } catch (std::invalid_argument&) {
                // Try converting to boolean
                if (strcasecmp(text, "true") == 0 || strcasecmp(text, "false") == 0) {
                    bool boolValue = (strcasecmp(text, "true") == 0);
                    jsonElement.AddMember(rapidjson::Value().SetString(element->Name(), allocator), rapidjson::Value().SetBool(boolValue), allocator);
                } else if (strcasecmp(text, "null") == 0) {
                    // Treat "null" as a null value
                    jsonElement.AddMember(rapidjson::Value().SetString(element->Name(), allocator), rapidjson::Value().SetNull(), allocator);
                } else {
                    // If all conversions fail, treat it as a string
                    jsonElement.AddMember(rapidjson::Value().SetString(element->Name(), allocator), rapidjson::Value().SetString(text, allocator), allocator);
                }
            }
        }
    }

    // recursion
    for (const tinyxml2::XMLNode* node = element->FirstChild(); node != nullptr; node = node->NextSibling()) {
        if (node->ToElement()) {
            rapidjson::Value childElement(rapidjson::kObjectType);
            processXmlElement(node->ToElement(), childElement, allocator);

            // Convert it to an array if the key already exists
            if (jsonElement.HasMember(element->Name())) {
                if (!jsonElement[element->Name()].IsArray()) {
                    rapidjson::Value existingElement(jsonElement[element->Name()], allocator);
                    jsonElement[element->Name()].SetArray().PushBack(existingElement, allocator);
                }
                jsonElement[element->Name()].PushBack(childElement, allocator);
            } else {
                // Add childElement directly if it's not an array
                jsonElement.AddMember(rapidjson::Value().SetString(element->Name(), allocator), childElement, allocator);
            }
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

/*
    Saves string into a file
    @param fileContent the file's text content
    @param filePath saving path
*/
void save_file(string fileContent, string filePath) {
    std::ofstream outfile(filePath);
    if (outfile.is_open()) {
        outfile << fileContent;
        outfile.close();
    }
}