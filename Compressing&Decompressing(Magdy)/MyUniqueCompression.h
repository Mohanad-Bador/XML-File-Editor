#pragma once

#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>

struct HuffNode {
    char huffCharacter;
    int huffFrequency;
    HuffNode* huffLeft;
    HuffNode* huffRight;

    HuffNode(char Character, int Frequency) : huffCharacter(Character), huffFrequency(Frequency), huffLeft(nullptr), huffRight(nullptr) {}
};

struct CompareHuff {
    bool operator()(HuffNode* L, HuffNode* R) const {
        if (L->huffFrequency == R->huffFrequency)
            return L->huffCharacter > R->huffCharacter;
        return L->huffFrequency > R->huffFrequency;
    }
};

class MyUniqueCompression {
private:
    HuffNode* huffRoot;
    std::string compressedText;

    HuffNode* buildHuffT(std::priority_queue<HuffNode*, std::vector<HuffNode*>, CompareHuff>& X);
    void generateHuffCode(HuffNode* HR, std::string code, std::unordered_map<char, std::string>& huffCodes);
    std::string encoding(std::string inputData, std::unordered_map<char, std::string>& huffCodes);
    char binaryStringToChar(const std::string& binaryString);
    std::string byteToChar(std::string data);

public:
    MyUniqueCompression();
    ~MyUniqueCompression();
    std::string compressData(std::string inputText);
    std::string decompressData(const std::string& encodedText);
    void setCompress(std::string compressedData);
    std::string getCompress();
    HuffNode* getHuffRoot();
    std::string charToBinaryStr(const std::string& text);
    std::string Decoding(const std::string& encodedData, HuffNode* root);
    void deleteHuffTree(HuffNode* huffNode);
};
