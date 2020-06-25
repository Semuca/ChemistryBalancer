#include <fstream>
#include <string>
#include "AtomDataSelector.hpp"

std::string FindDataInLine(std::string line, int ID) {
    std::size_t beginPos, endPos = -1;
    for (int i = 0; i < ID; i++) {
        beginPos = endPos + 1;
        endPos = line.find(":", beginPos);
    }
    return line.substr(beginPos, endPos - beginPos);
}

std::string GetAtomData(int keyID, std::string key, int parameterID){
    std::ifstream atomData("AtomData.txt");
    if (!atomData.fail()) {
        std::string line;
        while (atomData >> line) {
            std::string testKey = FindDataInLine(line, keyID);
            if (testKey == key) {
                return FindDataInLine(line, parameterID);
            }
        }
        return "No atom found";
    } else {
        return "Error with reading AtomData file";
    }
}
