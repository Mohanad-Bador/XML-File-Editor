#include "XmlChecker.h"
#include <string>
using namespace std;

vector<pair<int, int>> XmlChecker::checkXmlErrors(const string& xmlContent) {
    vector<pair<int, int>> errorIndices;
    size_t tagStart = 0;
    size_t tagEnd = 0;

    for (size_t i = 0; i < xmlContent.size(); ++i) {
        if (xmlContent[i] == '<') {
            tagStart = i;
        } else if (xmlContent[i] == '>') {
            tagEnd = i;
            string tagContent = xmlContent.substr(tagStart + 1, tagEnd - tagStart - 1);  // extracts tag content

            if (tagContent.empty() || tagContent.back() == '/' || tagContent[0] == '?') {
                // Skips for Self-closing tag or processing instruction
                continue;
            }

            if (tagContent[0] != '/') {  // checks for opening tags
                tagStack.push(tagContent);
            } else {  // checks for closing tags
                if (tagStack.empty() || tagContent.substr(1) != tagStack.top()) {
                    errorIndices.emplace_back(tagStart, tagEnd);
                } else {
                    tagStack.pop();  // pops top element if the tags match
                }
            }
        }
    }

    return errorIndices;
}

