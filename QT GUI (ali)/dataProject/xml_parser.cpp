#include "xml_parser.h"

XML_Parser::XML_Parser() {

}


void XML_Parser::Set_XML_Content(const QString& content) {
    XML_File = content;
}

bool XML_Parser::Check_Consistency() {
    ProblematicTagsQueue.clear();  // Clear the queue before processing
    bool consistent=true;
    int index = 0;
    int length = XML_File.length();

    while (index < length) {
        if (XML_File[index] == '<') {
            // Check if it's a start or end tag
            bool isStartTag = true;
            if (index + 1 < length && XML_File[index + 1] == '/') {
                isStartTag = false;
            }

            // Extract the tag name
            int startTagName = index + (isStartTag ? 1 : 2);  // Adjust index for start/end tags
            int endTagName = XML_File.indexOf('>', startTagName);
            QString tagName = XML_File.mid(startTagName, endTagName - startTagName).trimmed();

            if (isStartTag) {
                Tags.push(tagName);
            } else {
                if (Tags.isEmpty() || Tags.top() != tagName) {
                    consistent=false;
                    ProblematicTagsQueue.enqueue(Tags.top());
                    Tags.pop();
                } else {
                    Tags.pop();
                }
            }

            index = endTagName + 1;  // Move index to the character after '>'
        } else {
            index++;
        }
    }

    // Check for any remaining tags in the stack
    while (!Tags.empty()) {
        ProblematicTagsQueue.enqueue(Tags.top());
        Tags.pop();
    }

    // Return true if the check queue is empty and there are no errors
    return ProblematicTagsQueue.isEmpty()&&consistent;
}
QString XML_Parser::Get_XML_Content(){
    return XML_File;
}
