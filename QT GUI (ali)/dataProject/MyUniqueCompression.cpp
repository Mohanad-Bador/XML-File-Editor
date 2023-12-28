#include "MyUniqueCompression.h"
#include <iostream>
#include <fstream>
#include <bitset>

MyUniqueCompression::MyUniqueCompression() : huffRoot(nullptr) {}

MyUniqueCompression::~MyUniqueCompression() {
    deleteHuffTree(huffRoot);
}

void MyUniqueCompression::deleteHuffTree(HuffNode* huffNode) {
    if (huffNode != nullptr) {
        deleteHuffTree(huffNode->huffLeft);
        deleteHuffTree(huffNode->huffRight);
        delete huffNode;
    }
}

HuffNode* MyUniqueCompression::buildHuffT(std::priority_queue<HuffNode*, std::vector<HuffNode*>, CompareHuff>& X) {
    while (X.size() > 1) {
        HuffNode* huffLeft = X.top();
        X.pop();

        HuffNode* huffRight = X.top();
        X.pop();

        HuffNode* Internal = new HuffNode('\0', huffLeft->huffFrequency + huffRight->huffFrequency);
        Internal->huffLeft = huffLeft;
        Internal->huffRight = huffRight;

        X.push(Internal);
    }

    return X.top();
}

void MyUniqueCompression::generateHuffCode(HuffNode* HR, std::string code, std::unordered_map<char, std::string>& huffCodes) {
    if (HR == nullptr) {
        return;
    }

    if (HR->huffCharacter != '\0') {
        huffCodes[HR->huffCharacter] = code;
    }

    generateHuffCode(HR->huffRight, code + "1", huffCodes);
    generateHuffCode(HR->huffLeft, code + "0", huffCodes);
}




std::string MyUniqueCompression::encoding(std::string inputData, std::unordered_map<char, std::string>& huffCodes) {
    std::string encodedResult = "";

    for (char c : inputData) {

        if (huffCodes.find(c) != huffCodes.end()) {
            // Character has a Huffman code, append the code
            encodedResult += huffCodes[c];
        } else {
            // Character is not in Huffman codes (e.g., XML tags), preserve it
            encodedResult += c;
        }
    }

    return byteToChar(encodedResult);
}





char MyUniqueCompression::binaryStringToChar(const std::string& binaryString) {
    int intValue = std::bitset<8>(binaryString).to_ulong();
    return static_cast<char>(intValue);
}

std::string MyUniqueCompression::byteToChar(std::string data) {
    std::string output;
    for (size_t i = 0; i < data.size(); i = i + 8) {
        output += binaryStringToChar(data.substr(i, 8));
    }
    return output;
}

std::string MyUniqueCompression::compressData(std::string inputText) {
    // Count the frequency of each character
    std::unordered_map<char, int> freqMap;
    for (char c : inputText) {
        freqMap[c]++;
    }

    // Create nodes for each character and insert into priority queue
    std::priority_queue<HuffNode*, std::vector<HuffNode*>, CompareHuff> X;
    for (auto entry : freqMap) {
        X.push(new HuffNode(entry.first, entry.second));
    }

    // Build Huffman tree
    huffRoot = buildHuffT(X);

    // Generate Huffman codes
    std::unordered_map<char, std::string> huffCodes;
    generateHuffCode(huffRoot, "", huffCodes);

    // Step 5: Encode the input word
    std::string compressedResult = encoding(inputText, huffCodes);
    setCompress(compressedResult);
    return compressedResult;
}

std::string MyUniqueCompression::charToBinaryStr(const std::string& text) {
    std::string binaryStr = "";
    for (char c : text) {
        int intValue = static_cast<int>(c);
        std::string binaryChar = std::bitset<8>(intValue).to_string();
        binaryStr += binaryChar;
    }

    return binaryStr;
}

std::string MyUniqueCompression::Decoding(const std::string& encodedData, HuffNode* root) {
    std::string decodedText = "";
    HuffNode* current = root;

    for (char bit : encodedData) {
        if (bit == '0') {
            current = current->huffLeft;
        } else if (bit == '1') {
            current = current->huffRight;
        }

        if (current->huffLeft == nullptr && current->huffRight == nullptr) {
            decodedText += current->huffCharacter;
            current = root;
        }
    }

    return decodedText;
}

std::string MyUniqueCompression::decompressData(const std::string& encodedText) {
    std::string binaryText = charToBinaryStr(encodedText);
    std::string decodedText = Decoding(binaryText, huffRoot);
    return decodedText;
}

void MyUniqueCompression::setCompress(std::string compressedData) {
    compressedText = compressedData;
}

std::string MyUniqueCompression::getCompress() {
    return compressedText;
}

HuffNode* MyUniqueCompression::getHuffRoot() {
    return huffRoot;
}
